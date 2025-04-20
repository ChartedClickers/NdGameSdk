#pragma once
#include "NdGameSdk/components/SdkRegenny.hpp"

#include <NdGameSdk/regenny/t2r/ndgame/game/FrameState.hpp>
#include <NdGameSdk/shared/src/ndlib/nd-frame-state.hpp>

using namespace NdGameSdk::ndlib;

namespace NdGameSdk::game {

	class FrameState : public ISdkRegenny<regenny::ndgame::game::FrameState, NdFrameState> {};
	static_assert(sizeof(FrameState) == sizeof(NdFrameState) + 0x168, "Size of FrameState is not correct.");
}