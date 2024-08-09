#pragma once

#include <Utility/helper.hpp>
#include <Utility/assertion/assert.hpp>
#include <Utility/function_ptr.hpp>

#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/components/SdkComponent.hpp"

#include <NdGameSdk/shared/src/gamelib/debug/nd-dev-menu.hpp>
#include <NdGameSdk/ndgame/t1x/src/game/weapon/process-weapon.hpp>

namespace NdGameSdk::game::player {

	class PlayerMenu : public ISdkComponent {
	public:
		PlayerMenu();
	private:
		void Awake();
		void Initialize();

		shared_ptr<gamelib::debug::NdDevMenu> m_DMENU;
		shared_ptr<weapon::Weapon> m_WeaponProcess;

		FunctionHook::Ptr m_GiveMenuWeaponMainHook{};
		FunctionHook::Ptr m_GiveMenuWeaponSubMenuHook{};
		FunctionHook::Ptr m_GiveMenuWeaponEntryHook{};
		FunctionHook::Ptr m_GiveMenuWeaponSubSectionHook{};
	};

}