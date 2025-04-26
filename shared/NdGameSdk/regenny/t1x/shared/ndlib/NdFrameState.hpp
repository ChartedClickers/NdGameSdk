#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::ndlib {
#pragma pack(push, 1)
struct NdFrameState {
    void* vftable; // 0x0
    private: char pad_8[0x38]; public:
    uint64_t m_gameFrameNumber; // 0x40
    private: char pad_48[0x4d2]; public:
    bool m_KeyboardDevMode; // 0x51a
    private: char pad_51b[0x28385]; public:
}; // Size: 0x288a0
#pragma pack(pop)
}
