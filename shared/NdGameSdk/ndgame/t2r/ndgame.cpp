#include "ndgame.hpp"

namespace NdGameSdk {

	void InitNdGameComponents(SdkConfig& cfg)
	{
		auto NdGameComponents = ISdkComponent::GetNdGameComponents();

		/*Game Components*/

		NdGameComponents->InitializeSdkComponents();
	}
}
