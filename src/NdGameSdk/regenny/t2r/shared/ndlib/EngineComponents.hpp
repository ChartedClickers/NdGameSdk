#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::ndlib {
#pragma pack(push, 1)
struct EngineComponents {
    enum Component : uint32_t {
        NdGameInfo = 0,
        NdFrameState = 1,
        PhotoModeManager = 2,
        FileSystem = 3,
        PackageMgr = 4,
        PrefetchMgr = 5,
        LevelMgr = 6,
        LevelStreamingMgr = 7,
        NdMessageManager = 8,
        PSNTelemetry = 10,
        AudioManager = 11,
        NdDialogManager = 14,
        NavMeshMgr = 15,
        musicManager = 13,
        NpcManager = 16,
        AnimMgr = 17,
        FgDrawMgr = 18,
        ProcessMgr = 19,
        ScriptManager = 20,
        AnimStreamManager = 21,
        Gui2 = 23,
        TextureMgrPub = 24,
        ParticleDebug = 29,
    };

    void* m_ptrs[33]; // 0x0
    uint32_t m_sizes[33]; // 0x108
    private: char pad_18c[0x4]; public:
}; // Size: 0x190
#pragma pack(pop)
}
