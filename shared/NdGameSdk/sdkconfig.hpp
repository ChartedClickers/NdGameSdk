#pragma once

#include "sdk.hpp"
#include "config/MemoryCfg.hpp"
#include "config/DevModeCfg.hpp"

using namespace NdGameSdk::config;

namespace NdGameSdk {

    class NdGameSdk_API SdkConfig final {
    public:
        bool Sidbase{};
        std::string SidbasePath{ "sidbase.bin" };

        NdDevMenuCfg NdDevMenu{};
        MemoryCfg Memory{};

    };
}
