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
using namespace NdGameSdk::corelib::memory::HeapAllocator;
using namespace NdGameSdk::common;
using namespace NdGameSdk::ndlib;
using namespace NdGameSdk::ndlib::debug;

namespace NdGameSdk::gamelib::debug {


	class NdDevMenu : public ISdkComponent {
	public:
		using AppendSdkDevMenuCallback = boost::function<void(DMENU::Menu*)>;

		enum DmenuComponentType { Unknown, MenuGroup, Menu, ItemLine, ItemSubmenu, 
			ItemBool, ItemDouble, ItemFloat, ItemFunction, ItemSelection, ItemSubText
		};

		NdDevMenu(NdDevMenuCfg& cfg);
		~NdDevMenu();

		SdkEvent<NdDevMenu*, DMENU::MenuGroup*> e_AppendMenuGroup;
	    SdkEvent<NdDevMenu*, AppendSdkDevMenuCallback> e_AppendSdkMenu{true};

		NdGameSdk_API bool IsGameDebugMenu();
		NdGameSdk_API bool IsExtendedDebugMenu();

		NdGameSdk_API DMENU::Menu* Create_DMENU_Menu(std::string pName, HeapArena_Args);
		NdGameSdk_API DMENU::ItemSubmenu* Create_DMENU_ItemSubmenu(std::string pName, DMENU::Menu* pMenu, DMENU::Menu* pSubmenu, void* pCallbackFunct, uint64_t pData, const char* pDescription, HeapArena_Args);

		NdGameSdk_API DmenuComponentType GetComponentType(DMENU::Component* component);

	private:
		void Awake() override;
		void Initialize() override;

		template <typename Component = DMENU::Component>
		Component* DMENU_AppendComponent(DMENU::Menu* pRootMenu, DMENU::Component* pComponent) {
			always_assert(DMENU_Menu_AppendComponent == nullptr, "Function pointer was not set!");
			return (Component*)DMENU_Menu_AppendComponent(pRootMenu, pComponent);
		}

		void AppendSdkDevMenus(DMENU::Menu* RootMenu, DMENU::Menu* SdkMenu);
		void OnGameInitialized(bool successful);

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


		MEMBER_FUNCTION_PTR(DMENU::Menu*, DMENU_Menu, DMENU::Menu* Heap, const char* name);
		MEMBER_FUNCTION_PTR(void*, DMENU_Menu_AppendComponent, DMENU::Menu* RootMenu, DMENU::Component* Component);


		MEMBER_FUNCTION_PTR(DMENU::ItemSubmenu*, DMENU_ItemSubmenu, DMENU::ItemSubmenu* Heap, const char* name, DMENU::Menu* pHeader, void* callbackFunct, uint64_t data, const char* pDescription);

	};

}