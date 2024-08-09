#pragma once

#include <Utility/helper.hpp>
#include <Utility/assertion/assert.hpp>
#include <Utility/function_ptr.hpp>

#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/components/SdkComponent.hpp"

namespace NdGameSdk::game::player {

	class Player : public ISdkComponent {
	public:
		Player();
	private:
		void Initialize() override;
	};

}