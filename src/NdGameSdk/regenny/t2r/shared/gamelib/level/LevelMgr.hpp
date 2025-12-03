#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "..\..\corelib\containers\FixedSizeHashTable.hpp"
#include "..\..\corelib\containers\FixedSizeHeap.hpp"
#include "..\..\corelib\system\platform\ndsys.hpp"
#include "BlockmeshMgr.hpp"
#include "LevelLoadObserver.hpp"
#include "..\..\ndlib\render\Background.hpp"
#include "..\..\ndlib\render\interface\BgGeometry.hpp"
#include "..\..\ndlib\text\StringIdSelection.hpp"
namespace regenny::shared::gamelib::level {
struct Level;
}
namespace regenny::shared::gamelib::level {
struct WantLoadInfo;
}
namespace regenny::shared::gamelib::level {
#pragma pack(push, 1)
struct LevelMgr {
    struct Configuration {
        uint32_t m_wantLoadReserve; // 0x0
        uint32_t m_wantLoadLockedReserve; // 0x4
        uint32_t m_levelRequestReserve; // 0x8
        uint32_t m_maxDependentNodeCount; // 0xc
    }; // Size: 0x10

    struct LevelLookupNode : public regenny::shared::corelib::containers::FixedSizeHashTable::ListHead {
        StringId64 m_Key; // 0x10
        regenny::shared::gamelib::level::Level* m_Level; // 0x18
    }; // Size: 0x20

    struct Request {
        enum LoadingType : uint32_t {
            Unload = 0,
            Load = 1,
            ChangeFlags = 2,
            Update = 3,
        };

        regenny::shared::gamelib::level::Level* m_level; // 0x0
        regenny::shared::gamelib::level::WantLoadInfo* m_WantLoadInfo; // 0x8
        LoadingType m_loadingType; // 0x10
        bool m_processed; // 0x14
        private: char pad_15[0x3]; public:
    }; // Size: 0x18

    struct SoundBankInfos {
        void** m_items; // 0x0
        uint32_t m_count; // 0x8
        uint32_t m_capacity; // 0xc
        void* m_inline[128]; // 0x10
    }; // Size: 0x410

    struct MiniSoundBankInfos {
        void** m_items; // 0x0
        uint32_t m_count; // 0x8
        uint32_t m_capacity; // 0xc
        void* m_inline[8]; // 0x10
    }; // Size: 0x50

    struct ListArray_corelib_containers_Request {
        uint32_t m_size; // 0x0
        uint32_t m_capacity; // 0x4
        regenny::shared::gamelib::level::LevelMgr::Request** m_data; // 0x8
    }; // Size: 0x10

    struct ListArray_corelib_containers_WantLoadInfo {
        uint32_t m_size; // 0x0
        uint32_t m_capacity; // 0x4
        regenny::shared::gamelib::level::WantLoadInfo** m_data; // 0x8
    }; // Size: 0x10

    struct FixedSizeHashTable_corelib_containers_LevelLookupNode {
        regenny::shared::gamelib::level::LevelMgr::LevelLookupNode** m_Buckets; // 0x0
        regenny::shared::corelib::containers::FixedSizeHeap m_Pool; // 0x8
        regenny::shared::gamelib::level::LevelMgr::LevelLookupNode* m_Head; // 0x60
        uint64_t m_NodeSize; // 0x68
        uint64_t m_RequestedBuckets; // 0x70
        regenny::shared::gamelib::level::LevelMgr::LevelLookupNode** m_Begin; // 0x78
        regenny::shared::gamelib::level::LevelMgr::LevelLookupNode** m_End; // 0x80
        uint64_t m_Count; // 0x88
        uint32_t m_BucketCountAligned; // 0x90
        regenny::shared::corelib::containers::FixedSizeHashTable::Flags m_PeakAndFlags; // 0x94
    }; // Size: 0x98

    struct ListArray_corelib_containers_Level {
        uint32_t m_size; // 0x0
        uint32_t m_capacity; // 0x4
        regenny::shared::gamelib::level::Level** m_data; // 0x8
    }; // Size: 0x10

    struct BitArray_corelib_containers__4096 {
        uint64_t m_bits[64]; // 0x0
    }; // Size: 0x200

    struct BitArray_corelib_containers__2048 {
        uint64_t m_bits[32]; // 0x0
    }; // Size: 0x100

    struct BitArray_corelib_containers__160 {
        uint64_t m_bits[3]; // 0x0
    }; // Size: 0x18

    struct ListArray_corelib_containers_StringId64 {
        uint32_t m_size; // 0x0
        uint32_t m_capacity; // 0x4
        StringId64** m_data; // 0x8
    }; // Size: 0x10

    regenny::shared::corelib::containers::FixedSizeHeap m_levelPool; // 0x0
    ListArray_corelib_containers_Request m_requests; // 0x58
    ListArray_corelib_containers_WantLoadInfo m_wantLoadsTmp; // 0x68
    FixedSizeHashTable_corelib_containers_LevelLookupNode m_activeLevelMap; // 0x78
    FixedSizeHashTable_corelib_containers_LevelLookupNode m_pendingLevelMap; // 0x110
    ListArray_corelib_containers_Level m_loadedLevels; // 0x1a8
    ListArray_corelib_containers_Level m_pendingLevels; // 0x1b8
    ListArray_corelib_containers_Level m_displayReadyLevels; // 0x1c8
    ListArray_corelib_containers_Level m_entitySpawnerLevels; // 0x1d8
    uint32_t m_loadedLevelCursor; // 0x1e8
    private: char pad_1ec[0x4]; public:
    regenny::shared::corelib::system::platform::ndsys::WaitLock m_updateLock; // 0x1f0
    regenny::shared::corelib::system::platform::ndsys::WaitLock m_activeMapLock; // 0x210
    uint32_t m_maxLevelSlots; // 0x230
    private: char pad_234[0x4]; public:
    StringId64* m_levelSelectionStorage; // 0x238
    StringId64* m_levelSelectionStorage2; // 0x240
    regenny::shared::gamelib::level::Level* m_pendingReloadLevel; // 0x248
    bool m_reloadSkippedThisFrame; // 0x250
    private: char pad_251[0xf]; public:
    regenny::shared::ndlib::text::StringIdSelection m_field260; // 0x260
    regenny::shared::ndlib::text::StringIdSelection m_field2a0; // 0x2a0
    uint32_t m_spawnedLevelsThisFrame; // 0x2e0
    uint32_t m_maxSpawnedLevelsPerFrame; // 0x2e4
    uint32_t m_prevFrameSpawnedCount; // 0x2e8
    private: char pad_2ec[0x4]; public:
    SoundBankInfos m_soundBankSlots[4096]; // 0x2f0
    BitArray_corelib_containers__4096 m_aSoundBankInfoBits; // 0x4102f0
    MiniSoundBankInfos m_miniSoundBankSlots[2048]; // 0x4104f0
    BitArray_corelib_containers__2048 m_aMiniSoundBankInfoBits; // 0x4384f0
    regenny::shared::ndlib::render::Background m_backgrounds[160]; // 0x4385f0
    BitArray_corelib_containers__160 m_backgroundInUseBits; // 0x446bf0
    regenny::shared::ndlib::render::interface::BgGeometry m_bgGeometries[160]; // 0x446c08
    float m_criticalLoadBudgetSec; // 0x481308
    uint64_t m_nextPumpGateTicks; // 0x48130c
    void* m_field481318; // 0x481314
    uint64_t m_lastTodoListTicks; // 0x48131c
    regenny::shared::gamelib::level::BlockmeshMgr m_BlockmeshMgr; // 0x481324
    regenny::shared::gamelib::level::LevelLoadObserver m_levelLoadObserver; // 0x481564
    void* m_commandHistory; // 0x48157c
    private: char pad_481584[0xc]; public:
    vec4 m_blockmeshViewRow0; // 0x481590
    vec4 m_blockmeshViewRow1; // 0x4815a0
    uint32_t m_blockmeshRefreshCountdown; // 0x4815b0
    private: char pad_4815b4[0xc]; public:
    regenny::shared::corelib::system::platform::ndsys::WaitLock m_criticalLoadLock; // 0x4815c0
    ListArray_corelib_containers_StringId64 m_criticalLoadIds; // 0x4815e0
    uint64_t m_pendingPackageMask[256]; // 0x4815f0
    bool m_pumpRespectFrameBudget; // 0x481df0
    bool m_pumpEnableBgDriven; // 0x481df1
    bool m_pumpUseDynamicBudget; // 0x481df2
    bool m_field481df3; // 0x481df3
    bool m_levelSelectionDirty; // 0x481df4
    private: char pad_481df5[0x10e]; public:
    bool m_showVerboseLevelLogin; // 0x481f03
    bool m_debugAutoSpawn; // 0x481f04
    bool m_showSuperVerboseLevelLogin; // 0x481f05
    private: char pad_481f06[0x3]; public:
    bool m_forceLoadArtLevels; // 0x481f09
    bool m_showLoadingRequests; // 0x481f0a
    private: char pad_481f0b[0x5]; public:
    uint32_t m_pumpMaxWorkCount; // 0x481f10
    private: char pad_481f14[0xc]; public:
}; // Size: 0x481f20
#pragma pack(pop)
}
