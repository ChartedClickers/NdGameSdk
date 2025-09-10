#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::ndlib::io::PSARC {
#pragma pack(push, 1)
struct HeaderBE {
    uint32_t m_magic; // 0x0
    uint32_t m_version; // 0x4
    uint32_t m_compression; // 0x8
    uint32_t m_tocLength; // 0xc
    uint32_t m_tocEntrySize; // 0x10
    uint32_t m_fileCount; // 0x14
    uint32_t m_blockSize; // 0x18
    uint32_t m_flags; // 0x1c
    uint64_t m_tocOffset; // 0x20
    uint64_t m_tocUncompressedLen; // 0x28
    uint8_t m_indexWidth; // 0x30
    uint8_t m_tocIsCompressed; // 0x31
}; // Size: 0x32
#pragma pack(pop)
}
