#include "player.hpp"

#include <NdGameSdk/ndgame/t2r/src/game/weapon/process-weapon.hpp>

namespace NdGameSdk::game::player {

	Player::Player() : ISdkComponent("Player") {}


	void Player::Awake() {
		m_DMENU = ISdkComponent::GetSharedComponents()->GetComponent<gamelib::debug::NdDevMenu>();
		auto pWeaponProcess = ISdkComponent::GetNdGameComponents()->GetComponent<weapon::Weapon>();
		m_PlayerMenu.emplace(pWeaponProcess.get());
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
