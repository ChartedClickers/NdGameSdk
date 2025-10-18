#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::corelib::containers {
#pragma pack(push, 1)
struct StaticArray {
    void* m_data; // 0x0
    uint64_t m_count; // 0x8
}; // Size: 0x10
#pragma pack(pop)
}
