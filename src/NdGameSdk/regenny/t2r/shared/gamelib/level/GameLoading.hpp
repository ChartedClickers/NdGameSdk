#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "..\..\corelib\containers\FixedSizeHashTable.hpp"
#include "..\..\corelib\containers\FixedSizeHeap.hpp"
namespace regenny::shared::gamelib::level {
#pragma pack(push, 1)
struct GameLoading {
    enum TransitionStatus : uint32_t {
        kSteady = 0,
        kMountWorld = 1,
        kMountLanguage = 2,
        kMountSPMP = 3,
        kCopyToHDD = 4,
        kPlayGoWait = 5,
        kPlayGoWait_Alias = 6,
        kMountedInitial = 7,
        kMountingOthers = 8,
        kMountingFirstWorld = 9,
        kMountingSPCommon = 10,
        kMountingMPCommon = 11,
        kMountingCommon = 12,
        kMountingCore = 13,
        kMountingBin = 14,
    };

    enum SpMpMode : uint32_t {
        kModeNone = 0,
        kModeSP = 1,
        kModeMP = 2,
    };

    struct ChunkSetNode : public regenny::shared::corelib::containers::FixedSizeHashTable::ListHead {
        // Metadata: utf8*
        char* m_name; // 0x10
        uint64_t m_chunkMaskLo; // 0x18
        uint64_t m_chunkMaskHi; // 0x20
    }; // Size: 0x28

    struct ChunkIdNode : public regenny::shared::corelib::containers::FixedSizeHashTable::ListHead {
        uint32_t m_id; // 0x10
        private: char pad_14[0x4]; public:
        // Metadata: utf8*
        char* m_name; // 0x18
    }; // Size: 0x20

    struct FixedSizeHashTable_corelib_containers_ChunkSetNode {
        regenny::shared::gamelib::level::GameLoading::ChunkSetNode** m_Buckets; // 0x0
        regenny::shared::corelib::containers::FixedSizeHeap m_Pool; // 0x8
        regenny::shared::gamelib::level::GameLoading::ChunkSetNode* m_Head; // 0x60
        uint64_t m_NodeSize; // 0x68
        uint64_t m_RequestedBuckets; // 0x70
        regenny::shared::gamelib::level::GameLoading::ChunkSetNode** m_Begin; // 0x78
        regenny::shared::gamelib::level::GameLoading::ChunkSetNode** m_End; // 0x80
        uint64_t m_Count; // 0x88
        uint32_t m_BucketCountAligned; // 0x90
        regenny::shared::corelib::containers::FixedSizeHashTable::Flags m_PeakAndFlags; // 0x94
    }; // Size: 0x98

    struct ChunkSetHashTable : public FixedSizeHashTable_corelib_containers_ChunkSetNode {
    }; // Size: 0x98

    struct FixedSizeHashTable_corelib_containers_ChunkIdNode {
        regenny::shared::gamelib::level::GameLoading::ChunkIdNode** m_Buckets; // 0x0
        regenny::shared::corelib::containers::FixedSizeHeap m_Pool; // 0x8
        regenny::shared::gamelib::level::GameLoading::ChunkIdNode* m_Head; // 0x60
        uint64_t m_NodeSize; // 0x68
        uint64_t m_RequestedBuckets; // 0x70
        regenny::shared::gamelib::level::GameLoading::ChunkIdNode** m_Begin; // 0x78
        regenny::shared::gamelib::level::GameLoading::ChunkIdNode** m_End; // 0x80
        uint64_t m_Count; // 0x88
        uint32_t m_BucketCountAligned; // 0x90
        regenny::shared::corelib::containers::FixedSizeHashTable::Flags m_PeakAndFlags; // 0x94
    }; // Size: 0x98

    struct ChunkIdHashTable : public FixedSizeHashTable_corelib_containers_ChunkIdNode {
    }; // Size: 0x98

}; // Size: 0x0
#pragma pack(pop)
}
