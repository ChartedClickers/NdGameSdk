#pragma once
#include <NdGameSdk/sdkstringid.hpp>
#include <cstdint>
namespace regenny::shared::ndlib {
#pragma pack(push, 1)
struct NdConfig {
    enum Config : uint32_t {
        NetInfo = 0,
        DMENU = 1,
        NdDevMenu = 2,
        NameCache = 7,
    };

}; // Size: 0x0
#pragma pack(pop)
}
