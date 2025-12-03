#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "..\containers\FixedSizeHashTable.hpp"
#include "..\containers\FixedSizeHeap.hpp"
#include "HeapAllocatorWithOverflow.hpp"
#include "..\system\platform\ndsys.hpp"
namespace regenny::shared::corelib::memory {
#pragma pack(push, 1)
struct ScopedTempData {
    struct BlockOwner {
        // Metadata: utf8*
        char* m_source_file; // 0x0
        // Metadata: utf8*
        char* m_source_func; // 0x8
        uint32_t m_source_line; // 0x10
        private: char pad_14[0x4]; public:
    }; // Size: 0x18

    struct HashNode : public regenny::shared::corelib::containers::FixedSizeHashTable::ListHead {
        uint64_t m_jobId; // 0x10
        regenny::shared::corelib::memory::HeapAllocatorWithOverflow* m_block; // 0x18
    }; // Size: 0x20

    struct BitArray_containers__128 {
        uint64_t m_bits[2]; // 0x0
    }; // Size: 0x10

    struct FixedSizeHashTable_containers_HashNode {
        regenny::shared::corelib::memory::ScopedTempData::HashNode** m_Buckets; // 0x0
        regenny::shared::corelib::containers::FixedSizeHeap m_Pool; // 0x8
        regenny::shared::corelib::memory::ScopedTempData::HashNode* m_Head; // 0x60
        uint64_t m_NodeSize; // 0x68
        uint64_t m_RequestedBuckets; // 0x70
        regenny::shared::corelib::memory::ScopedTempData::HashNode** m_Begin; // 0x78
        regenny::shared::corelib::memory::ScopedTempData::HashNode** m_End; // 0x80
        uint64_t m_Count; // 0x88
        uint32_t m_BucketCountAligned; // 0x90
        regenny::shared::corelib::containers::FixedSizeHashTable::Flags m_PeakAndFlags; // 0x94
    }; // Size: 0x98

    private: char pad_0[0x10]; public:
    void* m_poolBase; // 0x10
    private: char pad_18[0x10]; public:
    uint64_t m_poolCurrent; // 0x28
    uint64_t m_poolLimit; // 0x30
    uint64_t m_numBlocks; // 0x38
    BitArray_containers__128 m_usageMask; // 0x40
    FixedSizeHashTable_containers_HashNode m_table; // 0x50
    uint32_t m_activeBlocks; // 0xe8
    uint32_t m_peakBlocks; // 0xec
    private: char pad_f0[0x10]; public:
    regenny::shared::corelib::memory::HeapAllocatorWithOverflow m_blocks[64]; // 0x100
    BlockOwner m_blockOwners[64]; // 0x4100
    private: char pad_4700[0x50]; public:
}; // Size: 0x4750
#pragma pack(pop)
}
