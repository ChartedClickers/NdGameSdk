#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "..\..\corelib\containers\FixedSizeHashTable.hpp"
#include "..\..\corelib\containers\FixedSizeHashTable_StringId64_StringId64.hpp"
#include "..\..\corelib\containers\FixedSizeHeap.hpp"
#include "..\..\corelib\system\platform\ndsys.hpp"
#include "WantLoadInfo.hpp"
#include "..\..\ndlib\io\AssetType.hpp"
#include "..\..\ndlib\script\PointerBase.hpp"
namespace regenny::shared::gamelib::level {
#pragma pack(push, 1)
struct LoadRegistry {
    struct WantLoads {
        struct Node : public regenny::shared::corelib::containers::FixedSizeHashTable::ListHead {
            StringId64 m_KeyNameId; // 0x10
            uint64_t m_RefCount; // 0x18
            regenny::shared::gamelib::level::WantLoadInfo m_Info; // 0x20
        }; // Size: 0x48

        struct ListArray_corelib_containers_WantLoadInfo {
            uint32_t m_size; // 0x0
            uint32_t m_capacity; // 0x4
            regenny::shared::gamelib::level::WantLoadInfo** m_data; // 0x8
        }; // Size: 0x10

        struct FixedSizeHashTable_corelib_containers_Node {
            regenny::shared::gamelib::level::LoadRegistry::WantLoads::Node** m_Buckets; // 0x0
            regenny::shared::corelib::containers::FixedSizeHeap m_Pool; // 0x8
            regenny::shared::gamelib::level::LoadRegistry::WantLoads::Node* m_Head; // 0x60
            uint64_t m_NodeSize; // 0x68
            uint64_t m_RequestedBuckets; // 0x70
            regenny::shared::gamelib::level::LoadRegistry::WantLoads::Node** m_Begin; // 0x78
            regenny::shared::gamelib::level::LoadRegistry::WantLoads::Node** m_End; // 0x80
            uint64_t m_Count; // 0x88
            uint32_t m_BucketCountAligned; // 0x90
            regenny::shared::corelib::containers::FixedSizeHashTable::Flags m_PeakAndFlags; // 0x94
        }; // Size: 0x98

        ListArray_corelib_containers_WantLoadInfo m_list; // 0x0
        FixedSizeHashTable_corelib_containers_Node m_table; // 0x10
    }; // Size: 0xa8

    struct ReloadNode : public regenny::shared::corelib::containers::FixedSizeHashTable::ListHead {
        StringId64 m_NameId; // 0x10
        void* m_Callback; // 0x18
        void* m_UserData; // 0x20
        regenny::shared::ndlib::io::AssetType m_AssetType; // 0x28
        bool m_Dispatched; // 0x2c
    }; // Size: 0x2d

    struct FixedSizeHashTable_corelib_containers_ReloadNode {
        regenny::shared::gamelib::level::LoadRegistry::ReloadNode** m_Buckets; // 0x0
        regenny::shared::corelib::containers::FixedSizeHeap m_Pool; // 0x8
        regenny::shared::gamelib::level::LoadRegistry::ReloadNode* m_Head; // 0x60
        uint64_t m_NodeSize; // 0x68
        uint64_t m_RequestedBuckets; // 0x70
        regenny::shared::gamelib::level::LoadRegistry::ReloadNode** m_Begin; // 0x78
        regenny::shared::gamelib::level::LoadRegistry::ReloadNode** m_End; // 0x80
        uint64_t m_Count; // 0x88
        uint32_t m_BucketCountAligned; // 0x90
        regenny::shared::corelib::containers::FixedSizeHashTable::Flags m_PeakAndFlags; // 0x94
    }; // Size: 0x98

    WantLoads m_WantLoads; // 0x0
    WantLoads m_WantLoadsLocked; // 0xa8
    regenny::shared::corelib::system::platform::ndsys::WaitLock m_WantLoadsLock; // 0x150
    regenny::shared::ndlib::script::PointerBase m_levelsets; // 0x170
    bool m_ChangedThisFrame; // 0x198
    private: char pad_199[0x7]; public:
    FixedSizeHashTable_corelib_containers_ReloadNode m_ReloadMap; // 0x1a0
    regenny::shared::corelib::containers::FixedSizeHashTable_StringId64_StringId64 m_DisplayMap; // 0x238
    uint64_t m_tickAccumulator; // 0x2d0
    private: char pad_2d8[0x8]; public:
    regenny::shared::corelib::system::platform::ndsys::WaitLock m_ReloadLock; // 0x2e0
    bool m_DebugLevelSets_MsgCon; // 0x300
    bool m_DebugLevelSets_ShowNested; // 0x301
    bool m_DebugLevelSets_ShowLevelSetInfo; // 0x302
    bool m_DebugLevelSets_ShowBlockmesh; // 0x303
    bool m_UseColorForArtStatus; // 0x304
    bool m_FreezeLevelSet; // 0x305
    bool m_ShowHelp; // 0x306
    bool m_ShowWantLoads; // 0x307
    bool m_ShowLockedWantLoads; // 0x308
    bool m_ShowMissingWantLoads; // 0x309
    bool m_IncludeBackgrounds; // 0x30a
    bool m_IncludeActors; // 0x30b
    bool m_IncludeFlags; // 0x30c
    bool m_IncludeLayers; // 0x30d
    bool m_field30e; // 0x30e
    bool m_DumpWantLoadChanges; // 0x30f
    bool m_ShowLoadETA; // 0x310
    bool m_DisplayListDirty; // 0x311
    private: char pad_312[0x1]; public:
    bool m_DisableGeometryLayerLoading; // 0x313
    private: char pad_314[0xc]; public:
}; // Size: 0x320
#pragma pack(pop)
}
