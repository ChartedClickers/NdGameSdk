#pragma once

#include <Utility/helper.hpp>
#include <Utility/assertion/assert.hpp>
#include <Utility/function_ptr.hpp>

#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/components/SdkComponent.hpp"

#include <NdGameSdk/shared/src/gamelib/debug/nd-dev-menu.hpp>
#include <NdGameSdk/ndgame/t2r/src/game/weapon/process-weapon.hpp>

namespace NdGameSdk::game::player {

	class Player;
	class PlayerMenu {
	public:
		explicit PlayerMenu(weapon::Weapon* pWeaponProcess);
	private:
		void GiveMenuWeaponItemsPatch(/*DMENU::Menu* pMenu*/);

		weapon::Weapon* m_WeaponProcess;

		FunctionHook::Ptr m_GiveMenuWeaponMainHook{};
		FunctionHook::Ptr m_GiveMenuWeaponSubMenuHook{};
		FunctionHook::Ptr m_GiveMenuWeaponEntryHook{};
		FunctionHook::Ptr m_GiveMenuWeaponSubSectionHook{};

		friend Player;
	};

}