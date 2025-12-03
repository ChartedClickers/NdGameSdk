#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::gamelib::level {
#pragma pack(push, 1)
struct LevelSpec {
    enum Layer : uint8_t {
        Base = 1,
        Phys = 2,
        Ingame = 4,
    };

}; // Size: 0x0
#pragma pack(pop)
}
