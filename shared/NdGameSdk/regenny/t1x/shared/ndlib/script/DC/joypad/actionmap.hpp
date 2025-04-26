#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "..\map.hpp"
namespace regenny::shared::ndlib::script::DC::joypad {
#pragma pack(push, 1)
struct actionmap {
    struct ActionDefinition {
        uint64_t field_0; // 0x0
        uint64_t field_8; // 0x8
        uint64_t field_10; // 0x10
    }; // Size: 0x18

    struct kActionDefinition {
        uint64_t m_size; // 0x0
        regenny::shared::ndlib::script::DC::joypad::actionmap::ActionDefinition* field_8; // 0x8
    }; // Size: 0x10

    struct InputDefinition {
        uint64_t field_0; // 0x0
        uint64_t field_8; // 0x8
        uint64_t field_10; // 0x10
        uint64_t field_18; // 0x18
        StringId64 field_20; // 0x20
        StringId64 field_28; // 0x28
        uint64_t field_30; // 0x30
        StringId64 field_38; // 0x38
    }; // Size: 0x40

    struct ActionSet {
        struct InputDefScheme : public regenny::shared::ndlib::script::DC::map {
            StringId64* m_key; // 0x8
            regenny::shared::ndlib::script::DC::joypad::actionmap::InputDefinition* m_value; // 0x10
        }; // Size: 0x18

        InputDefScheme* m_InputDef; // 0x0
        StringId64* field_8; // 0x8
        regenny::shared::ndlib::script::DC::joypad::actionmap::kActionDefinition* field_10; // 0x10
    }; // Size: 0x18

}; // Size: 0x0
#pragma pack(pop)
}
