#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::ndlib {
#pragma pack(push, 1)
struct NdFrameState {
    void* vftable; // 0x0
    private: char pad_8[0x38]; public:
    uint64_t m_gameFrameNumber; // 0x40
    private: char pad_48[0xe578]; public:
    bool m_KeyboardDevMode; // 0xe5c0
    private: char pad_e5c1[0x1af57]; public:
}; // Size: 0x29518
#pragma pack(pop)
}
