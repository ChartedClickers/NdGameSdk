#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::ndlib::io {
#pragma pack(push, 1)
struct LoadingHeapMgr {
    enum LevelHeapType : uint32_t {
        main = 0,
        gameplay = 1,
        pso_preload = 2,
    };

}; // Size: 0x0
#pragma pack(pop)
}
