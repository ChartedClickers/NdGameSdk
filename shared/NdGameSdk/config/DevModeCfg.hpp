#pragma once
#include "NdGameSdk/sdk.hpp"

namespace NdGameSdk {

    class NdGameSdk_API NdDevMenuCfg {
    public:
        NdDevMenuCfg() {}
        bool GameDebugMenu = SDK_DEBUG;

    #if defined(T1X)
        bool GameDebugConfig{};
        bool ExtendedDebugMenu{};
        float DebugMenuSize{};
    #endif

    };
}