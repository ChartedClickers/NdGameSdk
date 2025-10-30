#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::corelib::memory {
struct HeapAllocatorWithOverflow;
}
namespace regenny::shared::corelib::memory {
#pragma pack(push, 1)
struct ScopedTempAllocator {
    regenny::shared::corelib::memory::HeapAllocatorWithOverflow* m_block; // 0x0
    uint64_t m_savedState; // 0x8
    bool m_nodeInserted; // 0x10
    bool m_pushedAllocator; // 0x11
    bool m_stateActive; // 0x12
    private: char pad_13[0x5]; public:
}; // Size: 0x18
#pragma pack(pop)
}
