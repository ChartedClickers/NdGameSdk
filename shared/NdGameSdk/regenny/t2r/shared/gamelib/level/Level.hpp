#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "LevelSpec.hpp"
namespace regenny::shared::gamelib::level {
struct LevelDef;
}
namespace regenny::shared::ndlib::lights {
struct LightTable;
}
namespace regenny::shared::gamelib::level {
#pragma pack(push, 1)
struct Level {
    enum TypeFlags : uint16_t {
        None = 0,
        StreamingWorld = 2,
        BackgroundLevel = 4,
        DisplayLevel = 8,
        SubtypeMask = 12,
    };

    enum LevelDisplayControl : uint16_t {
        DisplayRequested = 1,
        BlockDisplay = 4,
        IsWantPreload = 64,
    };

    enum StateFlagBits : uint8_t {
        SpawnerWorkQueued = 2,
        UnloadRequested = 4,
        LoginInProgress = 8,
        DependentsActive = 16,
        PackagesPinned = 32,
        PreloadLock = 64,
    };

    enum RuntimeBits : uint8_t {
        TreatAsLoaded = 1,
        DisplayControlDirty = 2,
        BackgroundStreamActive = 32,
        BackgroundLoginQueued = 64,
    };

    enum Status : uint64_t {
        Empty = 0,
    };

    struct Info {
        enum Flags : uint32_t {
            BgDrivenByFgLogin = 1,
            BackgroundConfig02 = 4,
            BackgroundConfig05 = 32,
            BackgroundConfig06 = 64,
            BackgroundConfig07 = 128,
            BlockDisplay = 512,
            BackgroundConfig0A = 1024,
        };

        Flags m_value; // 0x0
        private: char pad_4[0x4]; public:
    }; // Size: 0x8

    struct DependentProcessNode {
        void* m_ProcessRef; // 0x0
        uint32_t m_ProcessId; // 0x8
        private: char pad_c[0x4]; public:
        regenny::shared::gamelib::level::Level::DependentProcessNode* m_pNext; // 0x10
        regenny::shared::gamelib::level::Level::DependentProcessNode* m_ppPrev; // 0x18
    }; // Size: 0x20

    struct SoundBankTable {
        uint64_t m_numSoundBanks; // 0x0
        // Metadata: utf8**
        char* m_soundBanks; // 0x8
    }; // Size: 0x10

    struct ListArray_corelib_containers_StringId64 {
        uint32_t m_size; // 0x0
        uint32_t m_capacity; // 0x4
        StringId64** m_data; // 0x8
    }; // Size: 0x10

    TypeFlags m_typeFlags; // 0x0
    LevelDisplayControl m_displayControlFlags; // 0x2
    regenny::shared::gamelib::level::LevelSpec::Layer m_activeContentFlags; // 0x4
    regenny::shared::gamelib::level::LevelSpec::Layer m_desiredContentFlags; // 0x5
    StateFlagBits m_stateFlag; // 0x6
    RuntimeBits m_runtimeFlags; // 0x7
    uint32_t m_featureDbIndex; // 0x8
    uint32_t m_navMeshLoginIndex; // 0xc
    private: char pad_10[0x4]; public:
    uint32_t m_voxelizationIndex; // 0x14
    uint32_t m_coverActionPackIndex; // 0x18
    uint32_t m_featurePerchIndex; // 0x1c
    private: char pad_20[0x10]; public:
    vec4 m_backgroundLoginOffset; // 0x30
    Status m_state; // 0x40
    // Metadata: utf8*
    char* m_LevelName; // 0x48
    StringId64 m_LevelId; // 0x50
    ListArray_corelib_containers_StringId64 m_PackageNameIds; // 0x58
    uint64_t m_packagesFinalizedCount; // 0x68
    void* m_pSoundBankInfo; // 0x70
    void* m_pLevelSoundBankInfo; // 0x78
    void* m_pVoxSoundBankInfo; // 0x80
    regenny::shared::gamelib::level::LevelDef* m_pLevelDef; // 0x88
    uint64_t m_dependentsLock; // 0x90
    private: char pad_98[0x18]; public:
    DependentProcessNode* m_dependentProcHead; // 0xb0
    uint32_t m_reloadTicket; // 0xb8
    private: char pad_bc[0x4]; public:
    uint64_t m_loginStartTicks; // 0xc0
    uint64_t m_fieldc8; // 0xc8
    uint64_t m_loginStartFrame; // 0xd0
    uint64_t m_lastBgDrivenUpdateTicks; // 0xd8
    uint64_t m_audioWaitFrame; // 0xe0
    void* m_pMaterial; // 0xe8
    void* m_pTextureVram; // 0xf0
    void* m_pFgGeometry; // 0xf8
    void* m_pEntitySpawners; // 0x100
    void* m_pRegionTable; // 0x108
    void* m_field110; // 0x110
    regenny::shared::ndlib::lights::LightTable* m_pLightTable; // 0x118
    void* m_field120; // 0x120
    void* m_field128; // 0x128
    void* m_pBackground; // 0x130
    void* m_pNavMeshTable; // 0x138
    void* m_pVoxelizationArray; // 0x140
    uint8_t m_lightTableSlotCount; // 0x148
    uint8_t m_featureDbCount; // 0x149
    private: char pad_14a[0x6]; public:
    void* m_featureDbSlots[8]; // 0x150
    void* m_featureDbRuntimes[16]; // 0x190
    uint32_t m_coverActionPackCapacity; // 0x210
    uint32_t m_perchActionPackCapacity; // 0x214
    void* m_pCoverActionPackPool; // 0x218
    void* m_pPerchActionPackPool; // 0x220
    void* m_VisSphere; // 0x228
    uint32_t m_VisJointIndex; // 0x230
    uint32_t m_CubemapJointIndex; // 0x234
    StringId64 m_ParentingJoint; // 0x238
    SoundBankTable* m_soundBankTable; // 0x240
    void* m_onLoadedCallBack; // 0x248
    void* m_Populator; // 0x250
    float m_loginAccumTime; // 0x258
    uint32_t m_pLoadDistance; // 0x25c
    Info m_levelInfo; // 0x260
    uint64_t m_unloadReadyFrame; // 0x268
    uint32_t m_stateTicks; // 0x270
    bool m_navMeshReady; // 0x274
    bool m_backgroundLogoutPending; // 0x275
    bool m_navMeshesRegistered; // 0x276
    private: char pad_277[0x1]; public:
    uint32_t m_voxCharacterCount; // 0x278
    bool m_resetPending; // 0x27c
    private: char pad_27d[0x3]; public:
    uint64_t m_loginTableFlags[256]; // 0x280
    StringId64 m_PackageNameIdsBuffer[7]; // 0xa80
    void* m_pCollisionDebugInfo; // 0xab8
}; // Size: 0xac0
#pragma pack(pop)
}
