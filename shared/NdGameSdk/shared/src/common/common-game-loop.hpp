#pragma once

#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/components/SdkSubComponent.hpp"
#include <NdGameSdk/shared/src/ndlib/engine-components.hpp>
#include <NdGameSdk/shared/src/gamelib/debug/nd-dev-menu.hpp>

#include <Utility/helper.hpp>

using namespace NdGameSdk::ndlib;
using namespace NdGameSdk::gamelib::debug;

namespace NdGameSdk::common {

	class CommonGameLoop : public ISdkSubComponent {
	public:
		explicit CommonGameLoop(EngineComponents* pEngineComponents, NdDevMenu* pNdDevMenu);
		void Init() override;
	private:
		EngineComponents* m_EngineComponents;
		NdDevMenu* m_NdDevMenu;
		MidHook m_GameDebugUpdate_DMENU_KeyboardDevMode{};
	};
}