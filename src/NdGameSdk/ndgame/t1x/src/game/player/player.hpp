#pragma once

#include <Utility/helper.hpp>
#include <Utility/assertion/assert.hpp>
#include <Utility/function_ptr.hpp>

#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/components/SdkComponent.hpp"
#include "player-menu.hpp"

namespace NdGameSdk::game::player {

	class Player : public ISdkComponent {
	public:
		Player();
		SDK_DEPENDENCIES(weapon::Weapon, NdDevMenu);
	private:
		void Initialize() override;
		void Awake() override;

		NdDevMenu* m_DMENU;
		optional<PlayerMenu> m_PlayerMenu;
	};

}