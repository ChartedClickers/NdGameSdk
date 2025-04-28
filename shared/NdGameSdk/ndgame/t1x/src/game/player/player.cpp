#include "player.hpp"

#include <NdGameSdk/ndgame/t1x/src/game/weapon/process-weapon.hpp>

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

			auto MissingDependencies = CheckSdkComponents
				<NdDevMenu>({ m_DMENU.get() });

			if (MissingDependencies.has_value()) {
				throw SdkComponentEx
				{ std::format("Missing necessary dependencies: {:s}", MissingDependencies.value()),
					SdkComponentEx::ErrorCode::DependenciesFailed };
			}

			if (m_DMENU->IsGameDebugMenu()) {
				m_PlayerMenu->GiveMenuWeaponItemsPatch();
			}

		});

	}

}
