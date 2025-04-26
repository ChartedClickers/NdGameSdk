#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::ndlib::script::DC::joypad {
#pragma pack(push, 1)
struct presets {
    struct Preset {
        StringId64 field_0; // 0x0
        uint64_t field_8; // 0x8
        uint32_t field_10; // 0x10
        uint32_t field_14; // 0x14
        uint16_t field_18; // 0x18
        uint32_t field_1a; // 0x1a
        private: char pad_1e[0x2]; public:
    }; // Size: 0x20

    struct AdditionalPresets {
        uint64_t field_0; // 0x0
        StringId64 field_8; // 0x8
        StringId64 field_10; // 0x10
        uint64_t field_18; // 0x18
        regenny::shared::ndlib::script::DC::joypad::presets::Preset* m_presets; // 0x20
        uint32_t m_count; // 0x28
        uint64_t field_30; // 0x2c
        private: char pad_34[0x4]; public:
    }; // Size: 0x38

}; // Size: 0x0
#pragma pack(pop)
}
