#pragma once

#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/components/SdkComponent.hpp"

#include <cstdint>
#include <string>
#include <format>
#include <spdlog/spdlog.h>
#include <Utility/assertion/assert.hpp>

#if defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/ndlib/EngineComponents.hpp>
#include "NdGameSdk/ndgame/t1x/src/game/gameinfo.hpp"
#include "NdGameSdk/ndgame/t1x/src/game/framestate.hpp"
#endif

#include "nd-game-info.hpp"
#include "nd-config.hpp"

using EngineComponent = ::regenny::shared::ndlib::EngineComponents::Component;

namespace NdGameSdk::ndlib {

    class EngineComponents : public ISdkComponent {
	public:
		EngineComponents();

		NdGameSdk_API game::GameInfo& GetGameInfo();
		NdGameSdk_API ndlib::NdGameInfo& GetNdGameInfo();

		NdGameSdk_API game::FrameState& GetFrameState();
		NdGameSdk_API ndlib::NdFrameState& GetNdFrameState();

		template <typename TComponent>
		NdGameSdk_API TComponent* GetEngineComponent(EngineComponent index) {
			always_assert(m_ptrs == nullptr, "m_ptrs was not set!");
			return (TComponent*)(m_ptrs[index]);
		}

		NdConfig m_ndConfig{};
	private:
		void Initialize() override;

		// m_ptrs+0xEngineComponent*8
		uintptr_t** m_ptrs{};
	};

}