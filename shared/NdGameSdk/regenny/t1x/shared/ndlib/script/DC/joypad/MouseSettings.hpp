#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::ndlib::script::DC::joypad {
#pragma pack(push, 1)
struct MouseSettings {
    uint32_t global_sensitivity; // 0x0
    uint32_t aim_sensitivity_x; // 0x4
    uint32_t aim_sensitivity_y; // 0x8
    uint32_t look_sensitivity_x; // 0xc
    uint32_t look_sensitivity_y; // 0x10
    uint32_t snipe_sensitivity_x; // 0x14
    uint32_t snipe_sensitivity_y; // 0x18
    uint32_t acceleration_x; // 0x1c
    uint32_t acceleration_y; // 0x20
    bool invert_x; // 0x24
    bool invert_y; // 0x25
    bool field_26; // 0x26
    bool use_raw_input; // 0x27
    private: char pad_28[0x18]; public:
}; // Size: 0x40
#pragma pack(pop)
}
