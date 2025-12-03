#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::corelib::containers {
#pragma pack(push, 1)
struct StaticArray {
    void* m_data; // 0x0
    uint32_t m_size; // 0x8
    private: char pad_c[0x4]; public:
}; // Size: 0x10
#pragma pack(pop)
}
