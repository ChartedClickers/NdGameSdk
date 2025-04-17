#include "ndgame.hpp"

#include "src/game/weapon/process-weapon.hpp"
#include "src/game/player/player.hpp"

namespace NdGameSdk {

	void InitNdGameComponents(SdkConfig& cfg)
	{
		auto NdGameComponents = ISdkComponent::GetNdGameComponents();

		NdGameComponents->AddComponent<game::weapon::Weapon>();
		NdGameComponents->AddComponent<game::player::Player>();

		NdGameComponents->InitializeSdkComponents();
	}
}
