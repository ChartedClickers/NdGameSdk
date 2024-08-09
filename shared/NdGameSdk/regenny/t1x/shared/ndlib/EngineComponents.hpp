#pragma once
#include <NdGameSdk/sdkstringid.hpp>
#include <cstdint>
namespace regenny::shared::ndlib {
#pragma pack(push, 1)
struct EngineComponents {
    enum Component : uint32_t {
        NdGameInfo = 0,
        NdFrameState = 1,
        PhotoModeManager = 2,
        FileSystem = 3,
        PackageMgr = 4,
        LevelMgr = 6,
        LevelStreamingMgr = 7,
        NdMessageManager = 8,
        PSNTelemetry = 10,
        AudioManager = 11,
        NdDialogManager = 14,
        NavMeshMgr = 15,
        NpcManager = 16,
        AnimMgr = 17,
        FgDrawMgr = 18,
        ProcessMgr = 19,
        AnimStreamManager = 21,
        TextureMgrPub = 24,
        ParticleDebug = 29,
    };

}; // Size: 0x0
#pragma pack(pop)
}
