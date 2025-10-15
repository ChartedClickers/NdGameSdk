#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::corelib::containers {
#pragma pack(push, 1)
struct FixedSizeHeap {
    void* m_pData; // 0x0
    void* m_pUsageAlloc; // 0x8
    uint64_t* m_pUsage; // 0x10
    uint64_t m_capacity; // 0x18
    uint64_t m_capacityAligned; // 0x20
    uint32_t m_usageWordCount; // 0x28
    private: char pad_2c[0x4]; public:
    uint64_t m_numElements; // 0x30
    uint64_t m_elementSize; // 0x38
    uint64_t m_activeCount; // 0x40
    uint64_t m_alignment; // 0x48
    uint64_t m_lastIndex; // 0x50
}; // Size: 0x58
#pragma pack(pop)
}
