#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::gamelib::level {
#pragma pack(push, 1)
struct DataLoading {
    struct Config {
        uint32_t m_memsize; // 0x0
        uint32_t m_freepackageslots; // 0x4
        uint32_t m_field8; // 0x8
        uint32_t m_fieldc; // 0xc
        uint32_t m_field10; // 0x10
        uint32_t m_field14; // 0x14
        uint32_t m_field18; // 0x18
        uint32_t m_field1c; // 0x1c
    }; // Size: 0x20

}; // Size: 0x0
#pragma pack(pop)
}
