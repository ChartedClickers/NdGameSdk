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

		#define AppendSdkSubMenus_Args DMENU::Menu* CustomMenu, const char* Description, DMENU::ItemSubmenu::SubmenuCallback SubmenuCallback, uint64_t Data
		using AppendSdkSubMenusCallback = boost::function<void(AppendSdkSubMenus_Args)>;

		enum DmenuComponentType { Unknown, MenuGroup, Menu, ItemLine, ItemSubmenu, 
			ItemBool, ItemDecimal, ItemFloat, ItemFunction, ItemSelection, ItemSubText
		};

		NdDevMenu(NdDevMenuCfg& cfg);
		~NdDevMenu();

		SdkEvent<NdDevMenu*, DMENU::MenuGroup*> e_AppendMenuGroup;
	    SdkEvent<NdDevMenu*, AppendSdkSubMenusCallback> e_AppendSdkMenu{true};

		NdGameSdk_API bool IsGameDebugMenu();

		NdGameSdk_API DMENU::Menu* Create_DMENU_Menu(std::string pName, HeapArena_Args);
		NdGameSdk_API DMENU::ItemLine* Create_DMENU_ItemLine(DMENU::Menu* pMenu, HeapArena_Args);
		NdGameSdk_API DMENU::ItemSubText* Create_DMENU_ItemSubText(std::string pName, DMENU::Menu* pMenu, HeapArena_Args);
		NdGameSdk_API DMENU::ItemSubmenu* Create_DMENU_ItemSubmenu(std::string pName, DMENU::Menu* pRootMenu, DMENU::Menu* pSubmenu, DMENU::ItemSubmenu::SubmenuCallback pCallbackFunct, uint64_t pData, const char* pDescription, HeapArena_Args);
		NdGameSdk_API DMENU::ItemBool* Create_DMENU_ItemBool(std::string pName, DMENU::Menu* pMenu, bool* pData, const char* pDescription, HeapArena_Args);
		NdGameSdk_API DMENU::ItemDecimal* Create_DMENU_ItemDecimal(std::string pName, DMENU::Menu* pMenu, int* pData, DMENU::ItemDecimal::ValueParams pValueParams, DMENU::ItemDecimal::StepParams pStepParams, const char* pDescription, HeapArena_Args);
		NdGameSdk_API DMENU::ItemFloat* Create_DMENU_ItemFloat(std::string pName, DMENU::Menu* pMenu, float* pData, DMENU::ItemFloat::ValueParams pValueParams, DMENU::ItemFloat::StepParams pStepParams, const char* pDescription, HeapArena_Args);
		NdGameSdk_API DMENU::ItemFunction* Create_DMENU_ItemFunction(std::string pName, DMENU::Menu* pMenu, DMENU::ItemFunction::FunctionCallback pFunction, uint64_t args, bool pisActive, HeapArena_Args);
		NdGameSdk_API DMENU::ItemSelection* Create_DMENU_ItemSelection(std::string pName, DMENU::Menu* pMenu, DMENU::ItemSelection::Item_selection* pItemSelection, uint64_t* pData, const char* pDescription, HeapArena_Args);
		NdGameSdk_API std::pair<DMENU::ItemLine*, DMENU::ItemSubText*> Create_DMENU_TextLineWrapper(std::string pName, DMENU::Menu* pMenu, HeapArena_Args);

		NdGameSdk_API DmenuComponentType GetComponentType(DMENU::Component* component);

	private:
		void Awake() override;
		void Initialize() override;

		template <typename Component = DMENU::Component>
		Component* DMENU_AppendComponent(DMENU::Menu* pMenu, DMENU::Component* pComponent) {
			always_assert(DMENU_Menu_AppendComponent == nullptr, "Function pointer was not set!");
			Component* component = (Component*)DMENU_Menu_AppendComponent(pMenu, pComponent);
			spdlog::debug("DMENU_Menu_AppendComponent(RootMenu: 'DMENU::Component::Menu('{:s}')', SubMenu: 'DMENU::Component('{:s}')')",
				pMenu->Name(), component->Name());
			return component;
		}

		DMENU::Menu* CreateNdGameSdkMenu();

		void AppendSdkSubMenus(DMENU::Menu* RootMenu, AppendSdkSubMenus_Args);

		void OnGameInitialized(bool successful);

		NdDevMenuCfg m_cfg{};

		MidHook m_SetRootMenuHook{};
		Patch::Ptr m_GameConfig_DevModePatch{};
#if defined(T1X)
		Patch::Ptr m_Assert_UpdateSelectRegionByNameMenuPatch{};
		Patch::Ptr m_Assert_UpdateSelectIgcByNameMenuPatch{};
		Patch::Ptr m_Assert_UpdateSelectSpawnerByNameMenuPatch{};
#endif

		DMENU::Menu* m_NdGameSdkMenu{};
		std::vector<DMENU::ItemSubmenu*> m_SdkCustomSubmenus{};

		std::unordered_map<uintptr_t, DmenuComponentType> m_DmenuComponentTypeMap{};

		shared_ptr<EngineComponents> m_EngineComponents;
		shared_ptr<Memory> m_Memory;
		shared_ptr<CommonGame> m_CommonGame;

		MEMBER_FUNCTION_PTR(DMENU::Menu*, DMENU_Menu, DMENU::Menu* Heap, const char* name);
		MEMBER_FUNCTION_PTR(DMENU::ItemLine*, DMENU_ItemLine, DMENU::ItemLine* Heap);

		MEMBER_FUNCTION_PTR(DMENU::ItemSubText*, DMENU_ItemSubText, DMENU::ItemSubText* Heap, const char* name);
		MEMBER_FUNCTION_PTR(DMENU::ItemSubmenu*, DMENU_ItemSubmenu, DMENU::ItemSubmenu* Heap, const char* name, DMENU::Menu* pHeader, void* callbackFunct, uint64_t data, const char* pDescription);
		MEMBER_FUNCTION_PTR(DMENU::ItemBool*, DMENU_ItemBool, DMENU::ItemBool* Heap, const char* name, bool* data, const char* pDescription);
		
#if defined(T2R)
		MEMBER_FUNCTION_PTR(DMENU::ItemDecimal*, DMENU_ItemDecimal, DMENU::ItemDecimal* Heap, const char* name, uint64_t* data, DMENU::ItemDecimal::ValueParams* Value, DMENU::ItemDecimal::StepParams* Step, const char* pDescription, bool handle);
		MEMBER_FUNCTION_PTR(DMENU::ItemFloat*, DMENU_ItemFloat, DMENU::ItemFloat* Heap, const char* name, uint64_t* data, DMENU::ItemFloat::ValueParams* Value, DMENU::ItemFloat::StepParams* Step, const char* pDescription, uint64_t arg7, bool handle);
		MEMBER_FUNCTION_PTR(DMENU::ItemSelection*, DMENU_ItemSelection, DMENU::ItemSelection* Heap, const char* name, DMENU::ItemSelection::Item_selection* SelectionStruct, void* SelectionCallback, uint64_t* SelectionVar, uint64_t arg6, uint64_t arg7, uint32_t arg8, const char* pDescription, bool handle);
#else
		MEMBER_FUNCTION_PTR(DMENU::ItemDecimal*, DMENU_ItemDecimal, DMENU::ItemDecimal* Heap, const char* name, uint64_t* data, DMENU::ItemDecimal::ValueParams* Value, DMENU::ItemDecimal::StepParams* Step, const char* pDescription);
		MEMBER_FUNCTION_PTR(DMENU::ItemFloat*, DMENU_ItemFloat, DMENU::ItemFloat* Heap, const char* name, uint64_t* data, DMENU::ItemFloat::ValueParams* Value, DMENU::ItemFloat::StepParams* Step, const char* pDescription, uint64_t arg7);
		MEMBER_FUNCTION_PTR(DMENU::ItemSelection*, DMENU_ItemSelection, DMENU::ItemSelection* Heap, const char* name, DMENU::ItemSelection::Item_selection* SelectionStruct, void* SelectionCallback, uint64_t* SelectionVar, uint64_t arg6, uint64_t arg7, uint32_t arg8, const char* pDescription);
#endif
		MEMBER_FUNCTION_PTR(DMENU::ItemFunction*, DMENU_ItemFunction, DMENU::ItemFunction* Heap, const char* name, void* callbackFunct, uint64_t data, bool isActive);

		MEMBER_FUNCTION_PTR(void*, DMENU_Menu_AppendComponent, DMENU::Menu* RootMenu, DMENU::Component* Component);
		MEMBER_FUNCTION_PTR(bool*, DMENU_Menu_DecimalCallBack, DMENU::Menu* Menu, DMENU::Message message, int32_t format);

	};

}