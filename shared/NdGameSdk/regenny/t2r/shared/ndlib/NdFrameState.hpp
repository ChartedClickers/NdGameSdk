#pragma once
#include <NdGameSdk/sdkregenny.hpp>
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
    private: char pad_8[0x18]; public:
    uint32_t m_TargetFramerate; // 0x20
    private: char pad_24[0x4]; public:
    uint32_t m_MinimumFramerate; // 0x28
    uint32_t m_speed; // 0x2c
    private: char pad_30[0x10]; public:
    uint64_t m_gameFrameNumber; // 0x40
    private: char pad_48[0xe578]; public:
    bool m_KeyboardDevMode; // 0xe5c0
    private: char pad_e5c1[0x244f]; public:
    NdKeyboardLayer m_IMEKeyboard; // 0x10a10
    NdKeyboardLayer m_kbdLayer1; // 0x12470
    NdKeyboardLayer m_kbdLayer2; // 0x13ed0
    NdKeyboardLayer m_GameKeyboard; // 0x15930
    NdKeyboardLayer m_kbdLayer4; // 0x17390
    NdKeyboardLayer m_kbdLayer5; // 0x18df0
    private: char pad_1a850[0xecc8]; public:
}; // Size: 0x29518
#pragma pack(pop)
}
