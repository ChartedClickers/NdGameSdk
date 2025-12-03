#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::ndlib::io {
#pragma pack(push, 1)
enum AssetType : uint32_t {
    Actor = 0,
    Level = 1,
    SoundBank = 2,
    IrPack = 3,
    Music = 4,
    Speech = 5,
    Movie = 6,
    Text = 7,
    Misc = 8,
    Gameplay = 9,
    Dc = 10,
    Shaders = 11,
    PipelineExecutables = 12,
};
#pragma pack(pop)
}
