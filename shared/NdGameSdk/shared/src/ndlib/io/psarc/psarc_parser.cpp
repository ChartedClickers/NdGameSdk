#include "psarc_parser.hpp"

#include <algorithm>
#include <cstring>
#include <spdlog/spdlog.h>
#include <zlib.h>

namespace NdGameSdk::ndlib::io { 
    
#if defined(T2R)

    namespace PSARC {

        static bool read_header(iReader& r, Header& out) {
            PSARCHeaderBE full{};

            // Only the canonical 0x20 front matter is guaranteed;
            if (!r.Read(0, &full, 0x20)) return false;
            // Validate magic
            if (PSARC::bswap32(full.m_magic) != PSARC::MagicPSAR) 
                return false;

            out = ToHeaderNormalized(full);
            return true;
        }

        static bool zlib_inflate(const unsigned char* src, size_t srcSize, unsigned char* dst, size_t dstSize) {
            uLongf dlen = static_cast<uLongf>(dstSize);
            const int rc = ::uncompress(reinterpret_cast<Bytef*>(dst), &dlen, reinterpret_cast<const Bytef*>(src), static_cast<uLong>(srcSize));
            return rc == Z_OK && dlen == dstSize;
        }

        static inline void split_manifest(const char* s, size_t n, std::vector<std::string>& out) {
            const char* p = s; 
            const char* e = s + n;
            while (p < e) {
                const char* end = p; while (end < e && *end != '\n' && *end != '\r' && *end != '\0') ++end;
                if (end > p) {
                    const char* q = p; while (q < end && *q != ',' && *q != '\t') ++q;
                    if (q > p) out.emplace_back(p, size_t(q - p));
                }
                while (end < e && (*end == '\n' || *end == '\r' || *end == '\0')) ++end;
                p = end;
            }
        }

        static bool parse_entry0_struct(const unsigned char* e, uint32_t entrySize, TEntry& out) {
            if (entrySize != sizeof(PSARCEntryBE)) return false;
            PSARCEntryBE be{};
            std::memcpy(&be, e, entrySize);
            std::memcpy(out.HashNames, be.m_hashNames, sizeof out.HashNames);
            out.ZSizeIndex = bswap32(be.m_zsizeIndexBE);
            out.UncompressedSize = be40_to_u64(be.m_uncompressedSizeBE);
            out.Offset = be40_to_u64(be.m_offsetBE);
            return true;
        }

        static bool list_with_header(iReader& rdr, const Header& ph, std::vector<std::string>& names) {

            // Sanity checks to avoid pathological allocations if header is incompatible
            if (ph.SizeOfEntry != sizeof(PSARCEntryBE)) return false;
            if (ph.FilesCount == 0 || ph.FilesCount > 5'000'000) return false;
            if (ph.BlockSize == 0 || ph.BlockSize > (1u << 24)) return false; // 16MB max block
            if (ph.StartOFDatas < 32) return false;

            const uint64_t entriesOfs = 0x20ull;
            const uint64_t entriesSize = uint64_t(ph.SizeOfEntry) * uint64_t(ph.FilesCount);
            if (entriesSize > (1ull << 30)) return false; // >1GB TOC is suspicious

            std::vector<unsigned char> entries(entriesSize);
            if (!rdr.Read(entriesOfs, entries.data(), entries.size())) { 
                spdlog::error("PsarcParser: entries read failed"); return false;
            }

            const uint64_t zsizeCount = (ph.StartOFDatas - (ph.SizeOfEntry * ph.FilesCount) + 32) / 2;
            const uint64_t zsizeOfs = entriesOfs + entriesSize;

            if (zsizeCount > (1ull << 29)) return false; // >500M zsize entries is invalid
            
            std::vector<unsigned char> zsizes(zsizeCount * 2ull);
            if (!rdr.Read(zsizeOfs, zsizes.data(), zsizes.size())) {
                spdlog::error("PsarcParser: zsizes read failed");
                return false;
            }

            // Entry 0 (filenames blob) — copy into PSARCEntryBE and normalize
            TEntry e0{};
            if (!parse_entry0_struct(entries.data(), ph.SizeOfEntry, e0)) return false;
            uint32_t zindex = e0.ZSizeIndex;
            uint64_t usize = e0.UncompressedSize;
            uint64_t ofs = e0.Offset;

            std::vector<unsigned char> buf;
            buf.reserve(static_cast<size_t>(usize));

            uint64_t remaining = usize;
            uint64_t curOfs = ofs;

            while (remaining > 0) {
                if ((zindex * 2ull + 1ull) >= zsizes.size()) break;

                const uint16_t z = (uint16_t(zsizes[zindex * 2 + 0]) << 8) | uint16_t(zsizes[zindex * 2 + 1]);
                const uint64_t compSize = (z == 0) ? uint64_t(ph.BlockSize) : uint64_t(z);
                const uint64_t outBytes = std::min<uint64_t>(remaining, ph.BlockSize);

                std::vector<unsigned char> block(compSize);
                if (!rdr.Read(curOfs, block.data(), block.size())) { spdlog::warn("PsarcParser: block read failed"); return false; }

                if (z == 0 || compSize == outBytes) {
                    buf.insert(buf.end(), block.data(), block.data() + outBytes);
                } else {
                    if (std::string_view(ph.CompressionType, 4) == "zlib") {
                        std::vector<unsigned char> outBlock(static_cast<size_t>(outBytes));
                        if (!zlib_inflate(block.data(), block.size(), outBlock.data(), outBlock.size())) {
                            spdlog::error("PsarcParser: zlib inflate failed");
                            return false;
                        }
                        buf.insert(buf.end(), outBlock.begin(), outBlock.end());
                    } else if (std::string_view(ph.CompressionType, 4) == "oodl") {
                        spdlog::error("PsarcParser: oodle-compressed TOC not supported");
                        return false;
                    } else {
                        spdlog::error("PsarcParser: unknown compression '{}" "'", ph.CompressionType);
                        return false;
                    }
                }
                curOfs += compSize;
                remaining -= outBytes;
                ++zindex;
            }

            if (buf.empty()) return false;
            split_manifest(reinterpret_cast<const char*>(buf.data()), buf.size(), names);
            return !names.empty();
        }

        bool ListFilenames(iReader& rdr, std::vector<std::string>& names) {
            Header ph{};
            if (!read_header(rdr, ph)) { 
                spdlog::warn("PsarcParser: bad header"); 
                return false; 
            }
            return list_with_header(rdr, ph, names);
        }

        bool ListFilenames(iReader& rdr, const Header& header, std::vector<std::string>& names) {
            return list_with_header(rdr, header, names);
        }
    }

#endif

}
