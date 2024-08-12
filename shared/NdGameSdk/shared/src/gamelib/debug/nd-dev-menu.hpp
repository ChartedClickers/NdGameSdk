#pragma once

#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/components/SdkComponent.hpp"
#include "NdGameSdk/config/DevModeCfg.hpp"

#include <NdGameSdk/shared/src/corelib/memory/memory.hpp>
#include <NdGameSdk/shared/src/common/common-game-init.hpp>
#include <NdGameSdk/shared/src/ndlib/engine-components.hpp>
#include <NdGameSdk/shared/src/ndlib/debug/nd-dmenu.hpp>

#include <map>
#include <Utility/helper.hpp>

using namespace NdGameSdk::corelib::memory;
using namespace NdGameSdk::common;
using namespace NdGameSdk::ndlib;
using namespace NdGameSdk::ndlib::debug;

namespace NdGameSdk::gamelib::debug {

	class NdDevMenu : public ISdkComponent {
	public:
		using AppendSdkDevMenuCallback = boost::function<void(DMENU::Menu*)>;

		enum DmenuComponentType {
			Unknown,
			MenuGroup,
			Menu,
			ItemEntry
		};

		NdDevMenu(NdDevMenuCfg& cfg);

		SdkEvent<NdDevMenu*, DMENU::MenuGroup*> e_AppendMenuGroup;
	    SdkEvent<NdDevMenu*, AppendSdkDevMenuCallback> e_AppendSdkMenu{true};

		NdGameSdk_API bool IsGameDebugMenu();
		NdGameSdk_API bool IsExtendedDebugMenu();

		NdGameSdk_API DmenuComponentType GetComponentType(DMENU::Component* component);

	private:
		void Awake() override;
		void Initialize() override;

		void AppendSdkDevMenus(DMENU::Menu* RootMenu, DMENU::Menu* SdkMenu);

		NdDevMenuCfg m_cfg{};
		MidHook m_SetRootMenuHook{};
#if defined(T1X)
		Patch::Ptr m_GameConfig_DevModePatch{};
		Patch::Ptr m_Assert_UpdateSelectRegionByNameMenuPatch{};
		Patch::Ptr m_Assert_UpdateSelectIgcByNameMenuPatch{};
		Patch::Ptr m_Assert_UpdateSelectSpawnerByNameMenuPatch{};
#endif
		shared_ptr<EngineComponents> m_EngineComponents;
		shared_ptr<Memory> m_Memory;
		shared_ptr<CommonGame> m_CommonGame;

	    std::unordered_map<uintptr_t, DmenuComponentType> m_DmenuComponentTypeMap{};

	};

}