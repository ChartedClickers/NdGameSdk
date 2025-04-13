#pragma once
#include "NdGameSdk/sdk.hpp"

namespace NdGameSdk {

    class NdGameSdk_API NdDevMenuCfg {
    public:
        NdDevMenuCfg() {}
        bool GameDebugMenu = SDK_DEBUG;
    };
}