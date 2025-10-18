#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::corelib::containers {
#pragma pack(push, 1)
struct ListArray {
    uint32_t m_size; // 0x0
    uint32_t m_capacity; // 0x4
    void* m_data; // 0x8
}; // Size: 0x10
#pragma pack(pop)
}
