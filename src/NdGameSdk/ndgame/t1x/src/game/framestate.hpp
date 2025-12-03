#pragma once

#include <NdGameSdk/regenny/t1x/ndgame/game/FrameState.hpp>
#include <NdGameSdk/shared/src/ndlib/nd-frame-state.hpp>

using namespace NdGameSdk::ndlib;

namespace NdGameSdk::game {

	class FrameState : public ISdkRegenny<regenny::ndgame::game::FrameState, NdFrameState> {};
	static_assert(sizeof(FrameState) == sizeof(NdFrameState) + 0x160, "Size of FrameState is not correct.");
}