#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "FixedSizeHashTable.hpp"
#include "FixedSizeHeap.hpp"
namespace regenny::shared::corelib::containers {
struct Node_StringId64_StringId64;
}
namespace regenny::shared::corelib::containers {
#pragma pack(push, 1)
struct FixedSizeHashTable_regenny_shared_corelib_containers_Node_StringId64_StringId64 {
    regenny::shared::corelib::containers::Node_StringId64_StringId64** m_Buckets; // 0x0
    regenny::shared::corelib::containers::FixedSizeHeap m_Pool; // 0x8
    regenny::shared::corelib::containers::Node_StringId64_StringId64* m_Head; // 0x60
    uint64_t m_NodeSize; // 0x68
    uint64_t m_RequestedBuckets; // 0x70
    regenny::shared::corelib::containers::Node_StringId64_StringId64** m_Begin; // 0x78
    regenny::shared::corelib::containers::Node_StringId64_StringId64** m_End; // 0x80
    uint64_t m_Count; // 0x88
    uint32_t m_BucketCountAligned; // 0x90
    regenny::shared::corelib::containers::FixedSizeHashTable::Flags m_PeakAndFlags; // 0x94
}; // Size: 0x98
#pragma pack(pop)
}
