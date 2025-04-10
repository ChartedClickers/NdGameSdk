#pragma once
#include <NdGameSdk/sdkstringid.hpp>
#include <cstdint>
#include "..\map.hpp"
namespace regenny::shared::ndlib::script::DC::joypad {
#pragma pack(push, 1)
struct actionscheme {
    struct inputKeyboard {
        uint64_t m_flag; // 0x0
        uint64_t m_keycode; // 0x8
    }; // Size: 0x10

    struct inputJoypad {
        uint64_t m_flag; // 0x0
        uint64_t m_iBtn; // 0x8
    }; // Size: 0x10

    struct inputMouse {
        uint64_t m_flag; // 0x0
        uint64_t m_keycode; // 0x8
        uint64_t m_keycode2; // 0x10
    }; // Size: 0x18

    struct Input {
        uint64_t m_flag; // 0x0
        StringId64 m_hash; // 0x8
    }; // Size: 0x10

    struct InputCollection {
        uint64_t m_numInputs; // 0x0
        StringId64* m_pArray; // 0x8
    }; // Size: 0x10

    struct inputKeyboardScheme {
        uint64_t m_count; // 0x0
        regenny::shared::ndlib::script::DC::joypad::actionscheme::inputKeyboard* m_scheme; // 0x8
    }; // Size: 0x10

    struct inputJoypadScheme {
        uint64_t m_count; // 0x0
        regenny::shared::ndlib::script::DC::joypad::actionscheme::inputJoypad* m_scheme; // 0x8
    }; // Size: 0x10

    struct inputMouseScheme {
        uint64_t m_count; // 0x0
        regenny::shared::ndlib::script::DC::joypad::actionscheme::inputMouse* m_scheme; // 0x8
    }; // Size: 0x10

    struct inputScheme {
        uint64_t m_count; // 0x0
        regenny::shared::ndlib::script::DC::joypad::actionscheme::Input* m_scheme; // 0x8
    }; // Size: 0x10

    struct inputCommand {
        regenny::shared::ndlib::script::DC::joypad::actionscheme::inputJoypadScheme* m_Joypadinputs; // 0x0
        regenny::shared::ndlib::script::DC::joypad::actionscheme::inputKeyboardScheme* m_Keyboardinputs; // 0x8
        regenny::shared::ndlib::script::DC::joypad::actionscheme::inputKeyboardScheme* inputKeyboardButtons; // 0x10
        regenny::shared::ndlib::script::DC::joypad::actionscheme::inputMouseScheme* m_Mouseinputs; // 0x18
        regenny::shared::ndlib::script::DC::joypad::actionscheme::inputMouseScheme* inputMouseButtons; // 0x20
        bool field_28; // 0x28
        private: char pad_29[0x7]; public:
        regenny::shared::ndlib::script::DC::joypad::actionscheme::inputScheme* m_inputs; // 0x30
        regenny::shared::ndlib::script::DC::joypad::actionscheme::inputJoypadScheme* m_inputButtons; // 0x38
        uint32_t field_40; // 0x40
        uint32_t field_44; // 0x44
        uint64_t field_48; // 0x48
        StringId64 m_InputHash; // 0x50
        uint64_t field_58; // 0x58
        regenny::shared::ndlib::script::DC::joypad::actionscheme::InputCollection* m_InputCollection; // 0x60
        uint64_t field_68; // 0x68
        bool field_70; // 0x70
        private: char pad_71[0xf]; public:
        bool field_80; // 0x80
        bool field_81; // 0x81
        private: char pad_82[0x6]; public:
        // Metadata: utf8*
        char* field_88; // 0x88
    }; // Size: 0x90

    struct ActionScheme {
        struct Scheme : public regenny::shared::ndlib::script::DC::map {
            StringId64* m_key; // 0x8
            regenny::shared::ndlib::script::DC::joypad::actionscheme::inputCommand* m_value; // 0x10
        }; // Size: 0x18

        private: char pad_0[0x8]; public:
        Scheme* m_scheme; // 0x8
    }; // Size: 0x10

}; // Size: 0x0
#pragma pack(pop)
}
