#pragma once
#include <NdGameSdk/sdkstringid.hpp>
#include <cstdint>
#include "..\..\shared\ndlib\NdFrameState.hpp"
namespace regenny::ndgame::game {
#pragma pack(push, 1)
struct FrameState : public regenny::shared::ndlib::NdFrameState {
    uint64_t Unk[45]; // 0x29518
}; // Size: 0x29680
#pragma pack(pop)
}
