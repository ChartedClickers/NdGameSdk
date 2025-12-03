#pragma once

#include <cstdint>
#include <vector>

#include "psarc_reader.hpp"


namespace NdGameSdk::ndlib::io { 

#if defined(T2R)

    namespace PSARC {

        #pragma pack(push, 1)
        struct DSARHeader32 {
            uint8_t  unk0[8];
            uint32_t chunkCountLE;
            uint8_t  reserved[20];
        };

        struct DSARChunkRaw32 {
            uint64_t decOfsLE;
            uint64_t compOfsLE;   
            uint32_t sizeDecLE;
            uint32_t sizeComLE;
            uint8_t  compType; // 0 = uncompressed, otherwise LZ4
            uint8_t  pad[7];
        };
        #pragma pack(pop)

        class DSARReader final : public iReader {
        public:
            explicit DSARReader(iReader& base) : m_Reader(base) {}
            bool Read(uint64_t ofs, void* dst, size_t sz) override;
        private:
            struct Chunk { 
                uint64_t decOfs; 
                uint64_t compOfs; 
                uint32_t sizeDec; 
                uint32_t sizeCom; 
                uint8_t compType; 
            };

            bool ensure_table();
            bool read_bytes(uint64_t ofs, void* dst, size_t sz);
            iReader& m_Reader;
            bool m_initialized{ false };
            std::vector<Chunk> m_chunks;
        };
    } 

#endif

}
