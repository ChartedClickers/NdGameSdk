#include "player.hpp"

#include <NdGameSdk/ndgame/t1x/src/game/weapon/process-weapon.hpp>

namespace NdGameSdk::game::player {

	Player::Player() : ISdkComponent("Player") {}

	void Player::Initialize() {

		static std::once_flag Initialized;

		std::call_once(Initialized, [this] {

			spdlog::info("Initializing {} components...", GetName());

		});

	}

}
