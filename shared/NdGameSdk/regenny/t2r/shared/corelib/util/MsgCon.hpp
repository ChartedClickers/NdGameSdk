#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::corelib::util {
#pragma pack(push, 1)
struct MsgCon {
    void* vftable; // 0x0
    private: char pad_8[0x8]; public:
    float m_MsgConScale; // 0x10
    uint32_t m_MsgConLeftPad; // 0x14
    uint32_t m_MsgConHorizontalSize; // 0x18
    uint32_t m_MsgConVerticalSize; // 0x1c
    uint32_t m_MsgConTopPad; // 0x20
    private: char pad_24[0xe]; public:
    bool m_DrawRedisTTYTimes; // 0x32
    bool m_DrawRedisTTYStatus; // 0x33
    private: char pad_34[0x2]; public:
    bool m_ApplyMsgConScaletoDebugText; // 0x36
    bool m_EnableMsgConLineWrap; // 0x37
    bool m_EnableMsgConAutoResize; // 0x38
    bool m_ShowCacheMissesDebugText; // 0x39
    private: char pad_3a[0xde]; public:
}; // Size: 0x118
#pragma pack(pop)
}
