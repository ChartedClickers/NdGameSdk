#pragma once
#include "NdGameSdk/components/SdkRegenny.hpp"

#include <NdGameSdk/regenny/t2r/ndgame/game/GameInfo.hpp>
#include <NdGameSdk/shared/src/ndlib/nd-game-info.hpp>

using namespace NdGameSdk::ndlib;

namespace NdGameSdk::game {

	class GameInfo : public ISdkRegenny<regenny::ndgame::game::GameInfo, NdGameInfo> {};
	static_assert(sizeof(GameInfo) == sizeof(NdGameInfo) + 0x580, "Size of GameInfo is not correct.");
}