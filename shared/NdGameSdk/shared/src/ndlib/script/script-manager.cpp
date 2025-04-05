#include "script-manager.hpp"
#include "./NdGameSdk/shared/sharedpatterns.hpp"

#if defined(T1X)


#include <NdGameSdk/shared/src/gamelib/debug/nd-dev-menu.hpp>

using namespace NdGameSdk::gamelib::debug;

namespace NdGameSdk::ndlib::script {

	ScriptManager::ScriptManager() : ISdkComponent(TOSTRING(ScriptManager)) {}

	bool ScriptManager::TestFunct(DMENU::ItemFunction& pFunction, DMENU::Message pMessage) {
		
		if(pMessage == DMENU::Message::OnExecute) {
			auto ScriptMgr = reinterpret_cast<ScriptManager*>(pFunction.Data());

			// There will be tests of script stuff...

		}

		return true;
	}

	DMENU::ItemSubmenu* ScriptManager::CreateScriptManagerMenu(NdDevMenu* pdmenu, DMENU::Menu* pMenu) {
		auto ScriptMgr = GetSharedComponents()->GetComponent<ScriptManager>();
		if (ScriptMgr) {
			DMENU::Menu* ScriptManagerMenu = pdmenu->Create_DMENU_Menu(TOSTRING(ScriptManager), HeapArena_Source);
			
			if (ScriptManagerMenu) {
				pdmenu->Create_DMENU_ItemFunction("Test funct", ScriptManagerMenu, &TestFunct, 
					reinterpret_cast<uint64_t>(&ScriptMgr), false, HeapArena_Source);
				return pdmenu->Create_DMENU_ItemSubmenu(ScriptManagerMenu->Name(),
					pMenu, ScriptManagerMenu, NULL, NULL, nullptr, HeapArena_Source);
			}

		}

		return nullptr;
	}

	void ScriptManager::Awake() {
		auto SharedComponents = ISdkComponent::GetSharedComponents();
	}

	void ScriptManager::Initialize()
	{
		static std::once_flag Initialized;
		std::call_once(Initialized, [this] {

			spdlog::info("Initializing {} patterns...", GetName());

			Patterns::SdkPattern findpattern{};
			auto module = Utility::memory::get_executable();

			findpattern = Patterns::ScriptManager_ScriptGlobals;
			g_scriptGlobals = (ScriptManagerGlobals*)Utility::ReadLEA32(module,
				findpattern.pattern, wstr(Patterns::ScriptManager_ScriptGlobals), findpattern.offset, 3, 7);

			if (!g_scriptGlobals) {
				throw SdkComponentEx
				{ std::format("Failed to find addresses!"),
					SdkComponentEx::ErrorCode::PatternFailed };
			}

		});
	}

}
#endif