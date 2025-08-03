#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::ndlib::util {
#pragma pack(push, 1)
struct BitReader {
    uint64_t m_FixUpTable; // 0x0
    uint32_t m_bitIndex; // 0x8
    uint32_t m_byteIndex; // 0xc
    uint32_t m_size; // 0x10
    uint32_t field_14; // 0x14
}; // Size: 0x18
#pragma pack(pop)
}
