#pragma once

#include "sdk.hpp"
#include "config/MemoryCfg.hpp"
#include "config/DevModeCfg.hpp"

#if defined(T1X)
#include "config/PrimServerCfg.hpp"
using namespace NdGameSdk::config;
#endif

namespace NdGameSdk {

    class NdGameSdk_API SdkConfig final {
    public:
        bool Sidbase{};
        std::string SidbasePath{ "sidbase.bin" };

        NdDevMenuCfg NdDevMenu{};

    #if defined(T1X)
        MemoryCfg Memory{};
        PrimServerCfg PrimServer{};
    #endif

    };
}
