#pragma once
#include <NdGameSdk/sdkstringid.hpp>
#include <cstdint>
namespace regenny::shared::gamelib::statescript {
#pragma pack(push, 1)
struct StateScriptConsoleInfo {
    uint32_t pos_x; // 0x0
    uint32_t size_x; // 0x4
    uint32_t pos_y; // 0x8
    uint32_t size_y; // 0xc
    float font_size_x; // 0x10
    float font_size_y; // 0x14
    bool line_warp; // 0x18
}; // Size: 0x19
#pragma pack(pop)
}
