#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "LevelLoadObserver.hpp"
namespace regenny::shared::gamelib::level {
#pragma pack(push, 1)
struct BlockmeshMgr {
    struct LoadObserver : public regenny::shared::gamelib::level::LevelLoadObserver {
        regenny::shared::gamelib::level::BlockmeshMgr* m_pBlockmeshMgr; // 0x18
    }; // Size: 0x20

    private: char pad_0[0x240]; public:
}; // Size: 0x240
#pragma pack(pop)
}
