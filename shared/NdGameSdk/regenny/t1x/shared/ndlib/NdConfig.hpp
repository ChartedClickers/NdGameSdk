#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::ndlib {
#pragma pack(push, 1)
struct NdConfig {
    enum Config : uint32_t {
        NetInfo = 0,
        DMENU = 1,
        NdDevMenu = 2,
        NameCache = 7,
        BUILD_NUMBER = 30,
        GameTitle = 32,
        Profiling = 209,
        IsGameConfigured = 210,
    };

}; // Size: 0x0
#pragma pack(pop)
}
