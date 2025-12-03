#pragma once

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/ndlib/io/PSARC/HeaderBE.hpp>
#include <NdGameSdk/regenny/t2r/shared/ndlib/io/PSARC/EntryBE.hpp>
#endif

#include <cstdint>
#include <cstddef>
#include <cstring>

namespace NdGameSdk::ndlib::io { 
    
#if defined(T2R)

    namespace PSARC {

		using PSARCHeaderBE = regenny::shared::ndlib::io::PSARC::HeaderBE;
		using PSARCEntryBE = regenny::shared::ndlib::io::PSARC::EntryBE;

        // Normalized PSARC header
        struct Header {
            char CompressionType[5]; // "zlib"/"oodl" + NUL
            uint32_t StartOFDatas; // TOC data start
            uint32_t SizeOfEntry; // Size of TOC entry
            uint32_t FilesCount; // Number of TOC entries
            uint32_t BlockSize; // TOC block size
        };

        // Normalized TOC entry (post-conversion)
        struct TEntry {
            uint8_t HashNames[16];
            uint32_t ZSizeIndex;
            uint64_t UncompressedSize;
            uint64_t Offset;
        };

        // Helpers to convert regenny big-endian on-disk headers into normalized host-endian view
        static inline uint32_t bswap32(uint32_t v) {
            return (v >> 24) | ((v >> 8) & 0x0000FF00u) | ((v << 8) & 0x00FF0000u) | (v << 24);
        }

        static inline uint64_t bswap64(uint64_t v) {
            return ((v & 0x00000000000000FFull) << 56) |
                ((v & 0x000000000000FF00ull) << 40) |
                ((v & 0x0000000000FF0000ull) << 24) |
                ((v & 0x00000000FF000000ull) << 8) |
                ((v & 0x000000FF00000000ull) >> 8) |
                ((v & 0x0000FF0000000000ull) >> 24) |
                ((v & 0x00FF000000000000ull) >> 40) |
                ((v & 0xFF00000000000000ull) >> 56);
        }

        static inline uint64_t be40_to_u64(const uint8_t be5[0x5]) {
            return (uint64_t(be5[0]) << 32) | (uint64_t(be5[1]) << 24) | (uint64_t(be5[2]) << 16) | (uint64_t(be5[3]) << 8) | uint64_t(be5[4]);
        }

        constexpr inline uint32_t tag4(const char(&s)[5]) {
            return (uint32_t(s[0]) << 24) | (uint32_t(s[1]) << 16) | (uint32_t(s[2]) << 8) | uint32_t(s[3]);
        }
        
        constexpr inline uint32_t MagicPSAR = tag4("PSAR");
        constexpr inline uint32_t MagicDSAR = tag4("DSAR");

        static inline Header ToHeaderNormalized(const PSARCHeaderBE& be) {
            Header h{};
            const bool hostOrder = (be.m_magic == MagicPSAR);
            if (hostOrder) {
                // Fields already host-endian in ArchiveSystem; compression is a 32-bit tag in host order
                uint32_t compBE = bswap32(be.m_compression);
                std::memcpy(h.CompressionType, &compBE, 4);
                h.CompressionType[4] = 0;
                const uint32_t tocLen = be.m_tocLength;
                const uint32_t tocOff = static_cast<uint32_t>(be.m_tocOffset & 0xFFFFFFFFull);
                h.StartOFDatas = tocLen + tocOff; // Archive stores offset separately
                h.SizeOfEntry = be.m_tocEntrySize;
                h.FilesCount = be.m_fileCount;
                h.BlockSize = be.m_blockSize;
            } else {
                // Raw stream bytes (big-endian values in memory)
                std::memcpy(h.CompressionType, &be.m_compression, 4);
                h.CompressionType[4] = 0;
                h.StartOFDatas = bswap32(be.m_tocLength);
                // Include tocOffset if present (rare; usually 0 for raw stream)
                if (be.m_tocOffset != 0) {
                    const uint64_t off64 = bswap64(be.m_tocOffset);
                    h.StartOFDatas += static_cast<uint32_t>(off64);
                }
                h.SizeOfEntry = bswap32(be.m_tocEntrySize);
                h.FilesCount = bswap32(be.m_fileCount);
                h.BlockSize = bswap32(be.m_blockSize);
            }
            return h;
        }

        static inline TEntry ToEntryNormalized(const PSARCEntryBE& be) {
            TEntry e{};
            std::memcpy(e.HashNames, be.m_hashNames, sizeof(e.HashNames));
            e.ZSizeIndex = bswap32(be.m_zsizeIndexBE);
            e.UncompressedSize = be40_to_u64(be.m_uncompressedSizeBE);
            e.Offset = be40_to_u64(be.m_offsetBE);
            return e;
        }

    } 

#endif
}
