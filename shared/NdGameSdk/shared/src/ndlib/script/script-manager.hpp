#pragma once

#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/components/SdkComponent.hpp"

#if defined(T1X)

#include <NdGameSdk/shared/src/ndlib/debug/nd-dmenu.hpp>

#include <Utility/helper.hpp>

#if defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/ndlib/script/ScriptManagerGlobals.hpp>
#endif

using namespace NdGameSdk::gamelib::debug;
using namespace NdGameSdk::ndlib::debug;

namespace NdGameSdk::ndlib::script {

	class ScriptManagerGlobals;

	class ScriptManager : public ISdkComponent {
	public:
		ScriptManager();
		static DMENU::ItemSubmenu* CreateScriptManagerMenu(NdDevMenu* pdmenu, DMENU::Menu* pMenu);
	private:
		void Initialize() override;
		void Awake() override;

		static bool TestFunct(DMENU::ItemFunction& pFunction, DMENU::Message pMessage);

		ScriptManagerGlobals* g_scriptGlobals{};
	};

	class NdGameSdk_API ScriptManagerGlobals : public ISdkRegenny<regenny::shared::ndlib::script::ScriptManagerGlobals> {};
	static_assert(sizeof(ScriptManagerGlobals) == 0x33b0, "Size of ScriptManagerGlobals is not correct.");
}

#endif