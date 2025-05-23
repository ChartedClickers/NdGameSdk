#pragma once

#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/components/SdkSubComponent.hpp"
#include <NdGameSdk/shared/src/ndlib/engine-components.hpp>
#include <NdGameSdk/shared/src/ndlib/nd-frame-state.hpp>
#include <NdGameSdk/shared/src/gamelib/debug/nd-dev-menu.hpp>

#include <Utility/helper.hpp>

using namespace NdGameSdk::ndlib;
using namespace NdGameSdk::gamelib::debug;

namespace NdGameSdk::common {

	class CommonGameLoop : public ISdkSubComponent {
	public:
		explicit CommonGameLoop(EngineComponents* pEngineComponents);
		void Init() override;
	private:

		static void GameLoopUpdate(SafetyHookContext& ctx);
		static void GameDebugUpdate(SafetyHookContext& ctx);

		EngineComponents* m_EngineComponents;
		MidHook m_GameLoopUpdate{};
		MidHook m_GameDebugUpdate{};
	};
}