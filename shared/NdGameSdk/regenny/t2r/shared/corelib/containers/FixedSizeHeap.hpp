#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::corelib::containers {
#pragma pack(push, 1)
struct FixedSizeHeap {
    void* m_data; // 0x0
    void* m_block; // 0x8
    uint64_t* m_usage; // 0x10
    uint64_t m_usageSize; // 0x18
    uint64_t m_granularity; // 0x20
    uint32_t m_bitmapCount; // 0x28
    private: char pad_2c[0x4]; public:
    uint64_t m_capacity; // 0x30
    uint64_t m_elementSize; // 0x38
    uint64_t m_count; // 0x40
    uint64_t m_allocCount; // 0x48
    uint64_t m_lastIndex; // 0x50
}; // Size: 0x58
#pragma pack(pop)
}
