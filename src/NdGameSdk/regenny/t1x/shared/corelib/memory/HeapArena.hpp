#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::corelib::memory {
#pragma pack(push, 1)
struct HeapArena {
    uint8_t* m_pMemory; // 0x0
    uint8_t* m_current; // 0x8
    uint64_t m_sizeFlags; // 0x10
    uint64_t m_peakUsage; // 0x18
    uint64_t m_lock; // 0x20
    uint64_t m_waiterCount; // 0x28
    void* m_waitListHead; // 0x30
    void* m_waitListTail; // 0x38
    bool m_lockEnabled; // 0x40
    private: char pad_41[0x7]; public:
    uint64_t m_userTag; // 0x48
}; // Size: 0x50
#pragma pack(pop)
}
