#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
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

    struct ChunkSetNode {
        regenny::shared::gamelib::level::GameLoading::ChunkSetNode* m_next; // 0x0
        regenny::shared::gamelib::level::GameLoading::ChunkSetNode* m_prev; // 0x8
        // Metadata: utf8*
        char* m_name; // 0x10
        uint64_t m_chunkMaskLo; // 0x18
        uint64_t m_chunkMaskHi; // 0x20
        private: char pad_28[0x8]; public:
    }; // Size: 0x30

    struct ChunkIdNode {
        regenny::shared::gamelib::level::GameLoading::ChunkIdNode* m_next; // 0x0
        regenny::shared::gamelib::level::GameLoading::ChunkIdNode* m_prev; // 0x8
        uint32_t m_id; // 0x10
        private: char pad_14[0x4]; public:
        // Metadata: utf8*
        char* m_name; // 0x18
    }; // Size: 0x20

}; // Size: 0x0
#pragma pack(pop)
}
