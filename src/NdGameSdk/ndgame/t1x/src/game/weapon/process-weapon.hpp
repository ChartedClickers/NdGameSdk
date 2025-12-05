#pragma once

#include <helper.hpp>
#include <assertion/assert.hpp>
#include <function_ptr.hpp>

#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/components/SdkComponent.hpp"

#include <NdGameSdk/shared/src/ndlib/script/script-manager-eval.hpp>

namespace NdGameSdk::game::weapon {

	class Weapon : public ISdkComponent {
	public:
		Weapon();
		NdGameSdk_API ndlib::script::ScriptValue* GiveWeaponArt();
	private:
		void Initialize() override;
		MEMBER_FUNCTION_PTR(ndlib::script::ScriptValue*, Weapon_GiveWeaponArt, void);
	};

}
