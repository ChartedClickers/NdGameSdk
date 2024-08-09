#pragma once
#include "NdGameSdk/sdk.hpp"

namespace NdGameSdk {

#if defined(T1X)
    class NdGameSdk_API PrimServerCfg {
    public:
        PrimServerCfg() {}
        bool PrimServerCreate{false};
    };
#endif
}