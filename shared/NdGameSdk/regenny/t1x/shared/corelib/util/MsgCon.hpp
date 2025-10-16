#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::corelib::util {
#pragma pack(push, 1)
struct MsgCon {
    enum MsgOutput : uint32_t {
        kDefault = 0,
        kStdOut = 1,
        kStdconAuto = 2,
        kStdconPersistent = 3,
        kStdconPauseable = 4,
        kStdconNonPauseable = 5,
        kStdconNotRecorded = 6,
        kStdconHost = 7,
        kError = 8,
        kAudio = 9,
        kProcess = 10,
        kCamera = 11,
        kAnimation = 12,
        kAI = 13,
        kParticles = 14,
        kIO = 15,
        kHud = 21,
        kNet = 22,
        kNet2 = 23,
        kHavok = 24,
        kDialogue = 25,
        kMelee = 26,
        kCinematic = 27,
        kSave = 28,
        kGraphics = 29,
        kMusic = 30,
        kFoliage = 31,
        kLogStream = 32,
        kUnknown21 = 33,
        kJafAnim = 34,
    };

    void* vftable; // 0x0
    private: char pad_8[0x8]; public:
    float m_MsgConScale; // 0x10
    uint32_t m_MsgConLeftPad; // 0x14
    uint32_t m_MsgConHorizontalSize; // 0x18
    uint32_t m_MsgConVerticalSize; // 0x1c
    uint32_t m_MsgConTopPad; // 0x20
    uint32_t m_scrollDelta; // 0x24
    uint32_t m_scrollPos; // 0x28
    bool m_scrollActive; // 0x2c
    private: char pad_2d[0x1]; public:
    bool m_PrintTimeInTTY; // 0x2e
    private: char pad_2f[0x1]; public:
    bool m_PrintTTY; // 0x30
    bool m_RedisTTY; // 0x31
    bool m_DrawRedisTTYTimes; // 0x32
    bool m_DrawRedisTTYStatus; // 0x33
    bool m_field34; // 0x34
    private: char pad_35[0x1]; public:
    bool m_ApplyMsgConScaletoDebugText; // 0x36
    bool m_EnableMsgConLineWrap; // 0x37
    bool m_EnableMsgConAutoResize; // 0x38
    bool m_ShowCacheMissesDebugText; // 0x39
    private: char pad_3a[0x6]; public:
}; // Size: 0x40
#pragma pack(pop)
}
