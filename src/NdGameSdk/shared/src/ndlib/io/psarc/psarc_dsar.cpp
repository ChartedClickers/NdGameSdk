#include "psarc_dsar.hpp"

#include <algorithm>
#include <cstring>
#include <lz4.h>

namespace NdGameSdk::ndlib::io { 

#if defined(T2R)

    namespace PSARC {

        static inline uint32_t le32(const unsigned char* p);
        static inline uint64_t le64(const unsigned char* p);

        bool DSARReader::ensure_table() {
            if (m_initialized) return true;

            // Read DSAR header
            DSARHeader32 hdr{};
            if (!m_Reader.Read(0, &hdr, sizeof(hdr))) return false;
            const uint32_t count = le32(reinterpret_cast<const unsigned char*>(&hdr.chunkCountLE));

            // Read chunk table
            std::vector<DSARChunkRaw32> raw(count);
            const uint64_t tableOfs = sizeof(DSARHeader32);
            if (!m_Reader.Read(tableOfs, raw.data(), raw.size() * sizeof(DSARChunkRaw32))) return false;

            m_chunks.reserve(count);
            for (uint32_t i = 0; i < count; ++i) {
                const auto& rr = raw[i];
                Chunk c{};
                c.decOfs = le64(reinterpret_cast<const unsigned char*>(&rr.decOfsLE));
                c.compOfs = le64(reinterpret_cast<const unsigned char*>(&rr.compOfsLE));
                c.sizeDec = le32(reinterpret_cast<const unsigned char*>(&rr.sizeDecLE));
                c.sizeCom = le32(reinterpret_cast<const unsigned char*>(&rr.sizeComLE));
                c.compType = rr.compType;
                m_chunks.push_back(c);
            }

            m_initialized = true;
            return true;
        }

        bool DSARReader::read_bytes(uint64_t ofs, void* dst, size_t sz) {
            if (!ensure_table()) return false;
            uint8_t* outp = static_cast<uint8_t*>(dst);
            uint64_t remaining = sz;
            uint64_t pos = ofs;

            while (remaining > 0) {
                const Chunk* ch = nullptr;
                for (auto& c : m_chunks) {
                    if (pos >= c.decOfs && pos < (c.decOfs + c.sizeDec)) { ch = &c; break; }
                }

                if (!ch) return false;
                uint64_t within = pos - ch->decOfs;
                uint64_t take = std::min<uint64_t>(remaining, ch->sizeDec - within);
                std::vector<uint8_t> dec(ch->sizeDec);

                if (ch->sizeCom == 0) {
                    std::memset(dec.data(), 0, dec.size());
                } else {
                    std::vector<uint8_t> com(ch->sizeCom);
                    if (!m_Reader.Read(ch->compOfs, com.data(), com.size())) return false;

                    if (ch->compType == 0) {
                        if (ch->sizeCom != ch->sizeDec) return false;
                        std::memcpy(dec.data(), com.data(), ch->sizeDec);
                    } else {
                        const int wrote = ::LZ4_decompress_safe(reinterpret_cast<const char*>(com.data()),                                   
                            reinterpret_cast<char*>(dec.data()),
                            static_cast<int>(com.size()),
                            static_cast<int>(dec.size()));
                        if (wrote < 0 || static_cast<uint32_t>(wrote) != ch->sizeDec) return false;
                    }
                }
                std::memcpy(outp, dec.data() + within, static_cast<size_t>(take));
                outp += take; pos += take; remaining -= take;
            }
            return true;
        }

        bool DSARReader::Read(uint64_t ofs, void* dst, size_t sz) {
            return read_bytes(ofs, dst, sz);
        }

        static inline uint32_t le32(const unsigned char* p) { return uint32_t(p[0]) | (uint32_t(p[1]) << 8) | (uint32_t(p[2]) << 16) | (uint32_t(p[3]) << 24); }
        static inline uint64_t le64(const unsigned char* p) { return uint64_t(le32(p)) | (uint64_t(le32(p + 4)) << 32); }

    }

#endif
}
