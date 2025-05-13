#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::ndlib {
#pragma pack(push, 1)
struct NdFrameState {
    struct NdKeyboardLayer {
        bool m_enabled; // 0x0
        bool m_DebugKeyboard; // 0x1
        private: char pad_2[0x6]; public:
        uint64_t m_keysPressed[4]; // 0x8
        uint64_t m_keyState[4]; // 0x28
        uint64_t m_keyState2[4]; // 0x48
        uint64_t m_keys[4]; // 0x68
        uint64_t m_keyState3[4]; // 0x88
        uint64_t m_keyCodes[4]; // 0xa8
        uint8_t scratch[128]; // 0xc8
        uint64_t m_invalid[4]; // 0x148
        float m_repeatDelay; // 0x168
        float m_repeatRate; // 0x16c
        uint32_t m_maxKeyCode; // 0x170
        private: char pad_174[0x4]; public:
        uint64_t m_firstRepeatT; // 0x178
        uint64_t m_nextRepeatT; // 0x180
        uint64_t m_keyTime[256]; // 0x188
        private: char pad_988[0x40]; public:
        regenny::shared::ndlib::NdFrameState::NdKeyboardLayer* ring[8]; // 0x9c8
        private: char pad_a08[0x320]; public:
        uint32_t layerIndex; // 0xd28
        private: char pad_d2c[0xd34]; public:
    }; // Size: 0x1a60

    void* vftable; // 0x0
    private: char pad_8[0x38]; public:
    uint64_t m_gameFrameNumber; // 0x40
    private: char pad_48[0x4d2]; public:
    bool m_KeyboardDevMode; // 0x51a
    private: char pad_51b[0xfd75]; public:
    NdKeyboardLayer m_IMEKeyboard; // 0x10290
    NdKeyboardLayer m_kbdLayer1; // 0x11cf0
    NdKeyboardLayer m_kbdLayer2; // 0x13750
    NdKeyboardLayer m_GameKeyboard; // 0x151b0
    NdKeyboardLayer m_kbdLayer4; // 0x16c10
    NdKeyboardLayer m_kbdLayer5; // 0x18670
    private: char pad_1a0d0[0xe7d0]; public:
}; // Size: 0x288a0
#pragma pack(pop)
}
