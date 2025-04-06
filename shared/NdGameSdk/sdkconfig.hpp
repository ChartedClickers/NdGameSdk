#pragma once

#include "sdk.hpp"
#include "config/MemoryCfg.hpp"
#include "config/DevModeCfg.hpp"

#if defined(T1X)
#include "config/PrimServerCfg.hpp"
#endif

using namespace NdGameSdk::config;

namespace NdGameSdk {

    class NdGameSdk_API SdkConfig final {
    public:
        bool Sidbase{};
        std::string SidbasePath{ "sidbase.bin" };

        NdDevMenuCfg NdDevMenu{};
        MemoryCfg Memory{};

    #if defined(T1X)
        PrimServerCfg PrimServer{};
    #endif

    };
}
