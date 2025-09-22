#pragma once

#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/components/SdkComponent.hpp"

#include "NdGameSdk/config/DevModeCfg.hpp"

#include <NdGameSdk/shared/src/corelib/memory/memory.hpp>
#include <NdGameSdk/shared/src/common/common-game-init.hpp>
#include <NdGameSdk/shared/src/common/common-game-loop.hpp>
#include <NdGameSdk/shared/src/ndlib/engine-components.hpp>
#include <NdGameSdk/shared/src/ndlib/debug/nd-dmenu.hpp>


#include <map>
#include <Utility/helper.hpp>
#include <Utility/system/clipboard.hpp>

using namespace NdGameSdk::corelib::memory;
using namespace NdGameSdk::common;
using namespace NdGameSdk::ndlib;
using namespace NdGameSdk::ndlib::debug;

namespace NdGameSdk::common {
	class CommonGame;
}

namespace NdGameSdk::gamelib::debug {

	class NdDevMenu : public ISdkComponent {
	public:
		#define AppendSdkSubMenus_Args DMENU::Menu* CustomMenu, const char* Description, DMENU::ItemSubmenu::SubmenuCallback SubmenuCallback, uint64_t Data
		using AppendSdkSubMenusCallback = boost::function<void(AppendSdkSubMenus_Args)>;
		template <typename... Args>
		using WrapMenuComponent = boost::function<bool(DMENU::Menu*, Args...)>;

		using NdKeyboardKey = NdFrameState::NdKeyboardLayer::Key;

		enum DmenuComponentType { Unknown, MenuGroup, Menu, String, KeyBoard, ItemPlaceHolder, ItemLine, ItemSubmenu,
			ItemBool, ItemDecimal, ItemFloat, ItemFunction, ItemSelection, ItemSubText
		};

		NdDevMenu();
		~NdDevMenu();

		SdkEvent<NdDevMenu*, DMENU::MenuGroup*> e_AppendMenuGroup;
	    SdkEvent<NdDevMenu*, AppendSdkSubMenusCallback> e_AppendSdkMenu{true};

		SDK_DEPENDENCIES(CommonGame, EngineComponents, Memory);

		NdGameSdk_API bool IsGameDebugMenu();

		NdGameSdk_API DMENU::Menu* Create_DMENU_Menu(std::string pName, HeapArena_Args);
		NdGameSdk_API DMENU::String* Create_DMENU_String(std::string string, DMENU::Menu* pMenu, const char* pDescription, HeapArena_Args);
		NdGameSdk_API DMENU::KeyBoard* Create_DMENU_KeyBoard(std::string pName, DMENU::Menu* pMenu, const char* inputBufferPtr, uint64_t maxInputLength, const char* pDescription, HeapArena_Args);
		NdGameSdk_API DMENU::ItemPlaceHolder* Create_DMENU_ItemPlaceHolder(std::string pName, DMENU::Menu* pMenu, const char* pPlaceHolder, HeapArena_Args);
		NdGameSdk_API DMENU::ItemLine* Create_DMENU_ItemLine(DMENU::Menu* pMenu, HeapArena_Args);
		NdGameSdk_API DMENU::ItemSubText* Create_DMENU_ItemSubText(std::string pName, DMENU::Menu* pMenu, HeapArena_Args);
		NdGameSdk_API DMENU::ItemSubmenu* Create_DMENU_ItemSubmenu(std::string pName, DMENU::Menu* pRootMenu, DMENU::Menu* pSubmenu, DMENU::ItemSubmenu::SubmenuCallback pCallbackFunct, uint64_t pData, const char* pDescription, HeapArena_Args);
		NdGameSdk_API DMENU::ItemBool* Create_DMENU_ItemBool(std::string pName, DMENU::Menu* pMenu, bool* pData, const char* pDescription, HeapArena_Args);
		NdGameSdk_API DMENU::ItemDecimal* Create_DMENU_ItemDecimal(std::string pName, DMENU::Menu* pMenu, int* pData, DMENU::ItemDecimal::ValueParams pValueParams, DMENU::ItemDecimal::StepParams pStepParams, const char* pDescription, HeapArena_Args);
		NdGameSdk_API DMENU::ItemFloat* Create_DMENU_ItemFloat(std::string pName, DMENU::Menu* pMenu, float* pData, DMENU::ItemFloat::ValueParams pValueParams, DMENU::ItemFloat::StepParams pStepParams, const char* pDescription, HeapArena_Args);
		NdGameSdk_API DMENU::ItemFunction* Create_DMENU_ItemFunction(std::string pName, DMENU::Menu* pMenu, DMENU::ItemFunction::FunctionCallback pFunction, uint64_t args, bool pisActive, HeapArena_Args);
		NdGameSdk_API DMENU::ItemSelection* Create_DMENU_ItemSelection(std::string pName, DMENU::Menu* pMenu, DMENU::ItemSelection::Item_selection* pItemSelection, DMENU::ItemSelection::SelectionHandler pCallback, uint64_t* pData, const char* pDescription, HeapArena_Args);
		NdGameSdk_API std::pair<DMENU::ItemLine*, DMENU::ItemSubText*> Create_DMENU_TextLineWrapper(std::string pName, DMENU::Menu* pMenu, HeapArena_Args);

		NdGameSdk_API int64_t DecimalCallBack(DMENU::Component& component, DMENU::Message message, uint32_t data);

		NdGameSdk_API bool Menu_DeleteItem(DMENU::Menu* pMenu, DMENU::Component* pItem);
		NdGameSdk_API DMENU::Menu* Menu_DeleteAllItems(DMENU::Menu* pMenu, bool pFreeMenu);

		template <typename... Args>
		NdGameSdk_API bool RebuildMenuFromComponent(DMENU::Menu* pMenu, DMENU::Component* pFirstToErase, const std::vector<WrapMenuComponent<Args...>>& wraps, HeapArena_Args, Args&&... args) {
			if (pFirstToErase == nullptr) { return false; }

			m_Memory->PushAllocator(MemoryContextType::kAllocDevMenuLowMem, source_func, source_line, source_file);

			for (auto* component : pFirstToErase->GetNextComponentsRange()) {
				pMenu->DeleteItem(component);
			}
			
			for (const auto& wrap : wraps) {
				if (!wrap(pMenu, std::forward<Args>(args)...)) {
					spdlog::warn("A wrap function at address {} failed while rebuilding the menu.",
						static_cast<const void*>(&wrap));
				}
			}

			m_Memory->PopAllocator();
			spdlog::debug("RebuildMenuFromComponent(RootMenu: 'DMENU::Component::Menu('{:s}')')", pMenu->Name());
			return true;
		}

		template <typename... Args>
		NdGameSdk_API bool RebuildMenu(DMENU::Menu* pMenu, bool pFreeMenu, const std::vector<WrapMenuComponent<Args...>>& wraps, HeapArena_Args, Args&&... args) {
			m_Memory->PushAllocator(MemoryContextType::kAllocDevMenuLowMem, source_func, source_line, source_file);

			Menu_DeleteAllItems(pMenu, pFreeMenu);
			for (const auto& wrap : wraps) {
				if (!wrap(pMenu, std::forward<Args>(args)...)) {
					spdlog::warn("A wrap function at address {} failed while rebuilding the menu.",
						static_cast<const void*>(&wrap));
				}
			}

			m_Memory->PopAllocator();
			spdlog::debug("RebuildMenu(RootMenu: 'DMENU::Component::Menu('{:s}')')", pMenu->Name());
			return true;
		}

		NdGameSdk_API DmenuComponentType GetComponentType(DMENU::Component* component);

	private:
		void Awake() override;
		void Initialize() override;

		template <typename Component = DMENU::Component>
		Component* DMENU_AppendComponent(DMENU::Menu* pMenu, DMENU::Component* pComponent) {
			if (pMenu) {
				always_assert(DMENU_Menu_AppendComponent == nullptr, "Function pointer was not set!");
				Component* component = (Component*)DMENU_Menu_AppendComponent(pMenu, pComponent);
				spdlog::debug("DMENU_Menu_AppendComponent(RootMenu: 'DMENU::Component::Menu('{:s}')', ParentComponent: 'DMENU::Component('{:s}')')",
					pMenu->Name(), component->Name());
				return component;
			}
		}

		void DMENU_Menu_Update(DMENU* DMENU);
		DMENU::Menu* CreateNdGameSdkMenu();
		void AppendSdkSubMenus(DMENU::Menu* RootMenu, AppendSdkSubMenus_Args);
		void OnGameInitialized(bool successful);

		NdDevMenuCfg m_cfg{};

		MidHook m_SetRootMenuHook{};
		MidHook m_KeyBoard_ClipBoardHook{};
		FunctionHook::Ptr m_FavoriteItemKeyCodeHook{};
		FunctionHook::Ptr m_KeyboardSearchStateHook{};
		Patch::Ptr m_GameConfig_DevModePatch{};
#if defined(T1X)
		Patch::Ptr m_Assert_UpdateSelectRegionByNameMenuPatch{};
		Patch::Ptr m_Assert_UpdateSelectIgcByNameMenuPatch{};
		Patch::Ptr m_Assert_UpdateSelectSpawnerByNameMenuPatch{};
#endif

		DMENU::Menu* m_NdGameSdkMenu{};
		std::vector<DMENU::ItemSubmenu*> m_SdkCustomSubmenus{};

		std::unordered_map<uintptr_t, DmenuComponentType> m_DmenuComponentTypeMap{};

		EngineComponents* m_EngineComponents;
		Memory* m_Memory;
		CommonGame* m_CommonGame;

		static void DMENU_KeyBoard_ClipBoardHook(SafetyHookContext& ctx);

		/*Extern variables*/
		static bool* s_IsKeyboardSearchActive;
		static bool* s_IsKeyboardComponentActive;

		MEMBER_FUNCTION_PTR(DMENU::Menu*, DMENU_Menu, DMENU::Menu* Heap, const char* name);
		MEMBER_FUNCTION_PTR(DMENU::ItemLine*, DMENU_ItemLine, DMENU::ItemLine* Heap);
		MEMBER_FUNCTION_PTR(DMENU::String*, DMENU_String, DMENU::String* Heap, const char* name, uint64_t* data, const char* pDescription);
#if defined(T2R)
		MEMBER_FUNCTION_PTR(DMENU::KeyBoard*, DMENU_KeyBoard, DMENU::KeyBoard* Heap, uint64_t ExtraArg, const char* name, uint64_t* pdata, int32_t pPagePointer, const char* pDescription);
#else
		MEMBER_FUNCTION_PTR(DMENU::KeyBoard*, DMENU_KeyBoard, DMENU::KeyBoard* Heap, const char* name, uint64_t* pInputBuffer, uint64_t MaxInputLength, const char* pDescription);
#endif
		MEMBER_FUNCTION_PTR(DMENU::ItemPlaceHolder*, DMENU_ItemPlaceHolder, DMENU::ItemPlaceHolder* Heap, const char* name, const char* pPlaceHolder);

		MEMBER_FUNCTION_PTR(DMENU::ItemSubText*, DMENU_ItemSubText, DMENU::ItemSubText* Heap, const char* name);
		MEMBER_FUNCTION_PTR(DMENU::ItemSubmenu*, DMENU_ItemSubmenu, DMENU::ItemSubmenu* Heap, const char* name, DMENU::Menu* pHeader, void* callbackFunct, uint64_t data, const char* pDescription);
		MEMBER_FUNCTION_PTR(DMENU::ItemBool*, DMENU_ItemBool, DMENU::ItemBool* Heap, const char* name, bool* data, const char* pDescription);
#if defined(T2R)
		MEMBER_FUNCTION_PTR(DMENU::ItemDecimal*, DMENU_ItemDecimal, DMENU::ItemDecimal* Heap, const char* name, uint64_t* data, DMENU::ItemDecimal::ValueParams* Value, DMENU::ItemDecimal::StepParams* Step, const char* pDescription, bool handle);
		MEMBER_FUNCTION_PTR(DMENU::ItemFloat*, DMENU_ItemFloat, DMENU::ItemFloat* Heap, const char* name, uint64_t* data, DMENU::ItemFloat::ValueParams* Value, DMENU::ItemFloat::StepParams* Step, const char* pDescription, uint64_t arg7, bool handle);
		MEMBER_FUNCTION_PTR(DMENU::ItemSelection*, DMENU_ItemSelection, DMENU::ItemSelection* Heap, const char* name, DMENU::ItemSelection::Item_selection* SelectionStruct, void* SelectionHandler, uint64_t* SelectionVar, uint64_t arg6, uint64_t arg7, uint32_t arg8, const char* pDescription, bool handle);
#else
		MEMBER_FUNCTION_PTR(DMENU::ItemDecimal*, DMENU_ItemDecimal, DMENU::ItemDecimal* Heap, const char* name, uint64_t* data, DMENU::ItemDecimal::ValueParams* Value, DMENU::ItemDecimal::StepParams* Step, const char* pDescription);
		MEMBER_FUNCTION_PTR(DMENU::ItemFloat*, DMENU_ItemFloat, DMENU::ItemFloat* Heap, const char* name, uint64_t* data, DMENU::ItemFloat::ValueParams* Value, DMENU::ItemFloat::StepParams* Step, const char* pDescription, uint64_t arg7);
		MEMBER_FUNCTION_PTR(DMENU::ItemSelection*, DMENU_ItemSelection, DMENU::ItemSelection* Heap, const char* name, DMENU::ItemSelection::Item_selection* SelectionStruct, void* SelectionHandler, uint64_t* SelectionVar, uint64_t arg6, uint64_t arg7, uint32_t arg8, const char* pDescription);
#endif
		MEMBER_FUNCTION_PTR(DMENU::ItemFunction*, DMENU_ItemFunction, DMENU::ItemFunction* Heap, const char* name, void* callbackFunct, uint64_t data, bool isActive);

		MEMBER_FUNCTION_PTR(void*, DMENU_Menu_AppendComponent, DMENU::Menu* RootMenu, DMENU::Component* Component);
		MEMBER_FUNCTION_PTR(int64_t, DMENU_Menu_DeleteItem, DMENU::Menu* Menu, DMENU::Component* pItem);
		MEMBER_FUNCTION_PTR(DMENU::Menu*, DMENU_Menu_DeleteAllItems, DMENU::Menu* Menu, bool pFreeMenu);
		MEMBER_FUNCTION_PTR(int64_t, DMENU_Menu_DecimalCallBack, DMENU::Component* component, DMENU::Message message, uint32_t data);
		MEMBER_FUNCTION_PTR(void*, DMENU_Menu_UpdateKeyboard, DMENU* DMENU);

		friend DMENU;
		friend CommonGameLoop;
		friend void FavoriteItemKeycode_CC();
	};

}