#pragma once

#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/components/SdkSubComponent.hpp"
#include <NdGameSdk/shared/src/ndlib/engine-components.hpp>
#include <NdGameSdk/shared/src/ndlib/nd-config.hpp>
#include <NdGameSdk/shared/src/ndlib/nd-frame-state.hpp>
#include <NdGameSdk/shared/src/gamelib/debug/nd-dev-menu.hpp>

#include <Utility/helper.hpp>

using namespace NdGameSdk::ndlib;
using namespace NdGameSdk::gamelib::debug;

namespace NdGameSdk::common {

	class CommonGameLoop : public ISdkSubComponent {
	public:
		explicit CommonGameLoop();
	private:
		void Awake() override;
		void Init() override;

		/*Extern Functs*/
		// void __cdecl GameLoopUpdate(unsigned __int64)
		static void GameLoopUpdate(SafetyHookContext& ctx);
		// void __cdecl GameDebugUpdate(bool)
		static void GameDebugUpdate(SafetyHookContext& ctx);

		EngineComponents* m_EngineComponents{ nullptr };
		MidHook m_GameLoopUpdate{};
		MidHook m_GameDebugUpdate{};
	};
}
