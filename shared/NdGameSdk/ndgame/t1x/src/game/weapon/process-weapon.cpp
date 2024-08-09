#include "process-weapon.hpp"
#include "./NdGameSdk/ndgame/t1x/ndgamepatterns.hpp"

namespace NdGameSdk::game::weapon {

	Weapon::Weapon() : ISdkComponent("ProcessWeapon") {}

	ndlib::script::ScriptValue* Weapon::GiveWeaponArt() {
		always_assert(Weapon_GiveWeaponArt == nullptr, "Function pointer was not set!");
		return Weapon_GiveWeaponArt();
	}

	void Weapon::Initialize() {
		static std::once_flag Initialized;

		std::call_once(Initialized, [this] {

			spdlog::info("Initializing {} patterns...", GetName());

			Patterns::SdkPattern findpattern{};
			auto module = Utility::memory::get_executable();

			findpattern = Patterns::Weapon_GiveWeaponArt;
			Weapon_GiveWeaponArt = (Weapon_GiveWeaponArt_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::Weapon_GiveWeaponArt), findpattern.offset);

			if (!Weapon_GiveWeaponArt) {
				throw SdkComponentEx{ "Failed to find game functions!", SdkComponentEx::ErrorCode::PatternFailed };
			}

		});
	}

}
