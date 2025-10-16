#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "FixedSizeHeap.hpp"
namespace regenny::shared::corelib::containers {
#pragma pack(push, 1)
struct FixedSizeHashTable {
    enum Flags : uint32_t {
        PeakMask = 2147483647,
        Initialized = 2147483648,
    };

    struct ListHead {
        void* m_next; // 0x0
        void* m_prev; // 0x8
    }; // Size: 0x10

    void** m_Buckets; // 0x0
    regenny::shared::corelib::containers::FixedSizeHeap m_Pool; // 0x8
    void* m_Head; // 0x60
    uint64_t m_NodeSize; // 0x68
    uint64_t m_RequestedBuckets; // 0x70
    void** m_Begin; // 0x78
    void** m_End; // 0x80
    uint64_t m_Count; // 0x88
    uint32_t m_BucketCountAligned; // 0x90
    Flags m_PeakAndFlags; // 0x94
}; // Size: 0x98
#pragma pack(pop)
}
