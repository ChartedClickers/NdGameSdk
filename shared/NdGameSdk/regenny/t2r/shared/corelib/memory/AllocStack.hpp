#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::corelib::memory {
#pragma pack(push, 1)
struct AllocStack {
    void* m_StackPool; // 0x0
    private: char pad_8[0x28]; public:
    bool m_field30; // 0x30
    private: char pad_31[0x1f]; public:
}; // Size: 0x50
#pragma pack(pop)
}
