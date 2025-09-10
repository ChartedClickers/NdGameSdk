#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::ndlib::io::PSARC {
#pragma pack(push, 1)
struct EntryBE {
    uint8_t m_hashNames[16]; // 0x0
    uint32_t m_zsizeIndexBE; // 0x10
    uint8_t m_uncompressedSizeBE[5]; // 0x14
    uint8_t m_offsetBE[5]; // 0x19
}; // Size: 0x1e
#pragma pack(pop)
}
