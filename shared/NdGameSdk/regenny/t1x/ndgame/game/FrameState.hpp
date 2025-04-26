#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "..\..\shared\ndlib\NdFrameState.hpp"
namespace regenny::ndgame::game {
#pragma pack(push, 1)
struct FrameState : public regenny::shared::ndlib::NdFrameState {
    uint64_t Unk[44]; // 0x288a0
}; // Size: 0x28a00
#pragma pack(pop)
}
