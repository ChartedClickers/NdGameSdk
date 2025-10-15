#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::ndlib::render {
#pragma pack(push, 1)
enum WindowContextType : uint32_t {
    Invalid = 4294967295,
    GameDebugDynamic = 1,
    GuiOffscreenOverride = 2,
    GameDebugDynTable = 3,
    DMenuThread = 4,
    MouseThread = 5,
    Hud2dOffscreen = 6,
    Hud3d = 7,
    Hud2d = 8,
    DebugOverDMenu = 9,
    UnderBlurBackbuffer = 16,
};
#pragma pack(pop)
}
