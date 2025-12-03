#include "player.hpp"

#include <NdGameSdk/ndgame/t2r/src/game/weapon/process-weapon.hpp>

namespace NdGameSdk::game::player {

	Player::Player() : ISdkComponent("Player") {}


	void Player::Awake() {
		m_DMENU = GetDependencyComponent<gamelib::debug::NdDevMenu>(ISdkComponent::GetSharedComponents());
		auto pWeaponProcess = GetDependencyComponent<weapon::Weapon>(ISdkComponent::GetNdGameComponents());
		m_PlayerMenu.emplace(pWeaponProcess);
	}

	void Player::Initialize() {

		static std::once_flag Initialized;

		std::call_once(Initialized, [this] {

			spdlog::info("Initializing {} components...", GetName());

			if (m_DMENU->IsGameDebugMenu()) {
				m_PlayerMenu->GiveMenuWeaponItemsPatch();
			}

		});

	}

}
