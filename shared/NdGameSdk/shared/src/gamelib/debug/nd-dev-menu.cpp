#include "nd-dev-menu.hpp"
#include "./NdGameSdk/shared/sharedpatterns.hpp"

#include <NdGameSdk/shared/src/ndlib/render/dev/debugdraw-common.hpp>
#include <NdGameSdk/shared/src/ndlib/script/script-manager.hpp>
#include <NdGameSdk/shared/src/ndlib/io/package-mgr.hpp>

#include <cstddef> 

using namespace boost::placeholders;
using namespace NdGameSdk::ndlib::script;
using namespace NdGameSdk::ndlib::io;
using namespace NdGameSdk::ndlib::render::dev;

namespace NdGameSdk::gamelib::debug {

	NdDevMenu::NdDevMenu() : m_cfg{ g_SdkConfig.NdDevMenu }, ISdkComponent("DMENU") {
		DMENU::s_NdDevMenu = this;
	}
	
	NdDevMenu::~NdDevMenu() {
		if (IsInitialized()) {
			m_CommonGame->e_GameInitialized.Unsubscribe({ this, &NdDevMenu::OnGameInitialized });
		}
	}
	
	constexpr uint32_t DMENU_CurrentMenuOffset = offsetof(regenny::shared::ndlib::debug::DMENU, m_CurrentMenu);
	constexpr uint32_t DMENU_KeyBoard_CursorIndexOffset = offsetof(regenny::shared::ndlib::debug::DMENU::KeyBoard, m_cursorIndex)
		- sizeof(regenny::shared::ndlib::debug::DMENU::Component);
	constexpr uint32_t DMENU_KeyBoard_isDirtyOffset = offsetof(regenny::shared::ndlib::debug::DMENU::KeyBoard, m_isDirty)
		- sizeof(regenny::shared::ndlib::debug::DMENU::Component);

	uintptr_t FavoriteItemKeyCode_ReturnAddr = NULL;
	void FavoriteItemKeycode_CC();

	uintptr_t KeyboardSearchState_ReturnAddr = NULL;
	void KeyboardSearchState_CC();

	bool NdDevMenu::IsGameDebugMenu() {

		auto& gameinfo = m_EngineComponents->GetNdGameInfo();
		if (gameinfo.Get()) {
			return m_EngineComponents->GetNdGameInfo()->m_DevMode;
		}

		return m_cfg.GameDebugMenu;
	}

	DMENU::Menu* NdDevMenu::Create_DMENU_Menu(std::string pName, HeapArena_Args) {
		auto HeapAllocator = m_Memory->Allocate<DMENU::Menu>(sizeof(DMENU::Menu), 0x10, source_func, source_line, source_file);
		DMENU::Menu* MenuPtr{};
		if (HeapAllocator) {
			memset((void*)HeapAllocator, 0x0, sizeof(DMENU::Menu));
			always_assert(DMENU_Menu == nullptr, "Function pointer was not set!");
			MenuPtr = DMENU_Menu(HeapAllocator, pName.c_str());
			spdlog::debug("Created DMENU::Component::Menu('{:s}') -> {:#x}", MenuPtr->Name(), reinterpret_cast<uintptr_t>(MenuPtr));
			return MenuPtr;
		}
		return nullptr;
	}

	DMENU::String* NdDevMenu::Create_DMENU_String(std::string string, DMENU::Menu* pMenu, const char* pDescription, HeapArena_Args) {
		auto HeapAllocator = m_Memory->Allocate<DMENU::String>(sizeof(DMENU::String), 0x10, source_func, source_line, source_file);
		DMENU::String* StringPtr{};
		if (HeapAllocator) {
			memset((void*)HeapAllocator, 0x0, sizeof(DMENU::String));
			always_assert(DMENU_String == nullptr, "Function pointer was not set!");
			StringPtr = DMENU_String(HeapAllocator, string.c_str(), 0x0, pDescription);
			DMENU_AppendComponent(pMenu, StringPtr);
			spdlog::debug("Created DMENU::Component::String('{:s}') -> {:#x}", StringPtr->Name(), reinterpret_cast<uintptr_t>(StringPtr));
			return StringPtr;
		}
		return nullptr;
	}

	DMENU::KeyBoard* NdDevMenu::Create_DMENU_KeyBoard(std::string pName, DMENU::Menu* pMenu, const char* inputBufferPtr, uint64_t maxInputLength, const char* pDescription, HeapArena_Args) {
		auto HeapAllocator = m_Memory->Allocate<DMENU::KeyBoard>
			(sizeof(DMENU::KeyBoard), 0x10, source_func, source_line, source_file);
		DMENU::KeyBoard* KeyBoardPtr{};
		if (HeapAllocator) {
			memset((void*)HeapAllocator, 0x0, sizeof(DMENU::KeyBoard));
			always_assert(DMENU_KeyBoard == nullptr, "Function pointer was not set!");
#if defined(T2R)
			KeyBoardPtr = DMENU_KeyBoard(HeapAllocator, 0x6, pName.c_str(), 0x0, 0x0, pDescription);
			*reinterpret_cast<uint64_t*>(KeyBoardPtr->Get()) = reinterpret_cast<uint64_t>(DMENU::KeyBoard::VTable);
			KeyBoardPtr->SetBufferPtr(inputBufferPtr);
			KeyBoardPtr->SetMaxInputLength(maxInputLength);
#else
			KeyBoardPtr = DMENU_KeyBoard(HeapAllocator, pName.c_str(), (uint64_t*)inputBufferPtr, maxInputLength, pDescription);
#endif
			DMENU_AppendComponent(pMenu, KeyBoardPtr);
			spdlog::debug("Created DMENU::Component::KeyBoard('{:s}', parent='{:s}', buffer_ptr={:#x}, max_len={:#x}, '{:s}') -> {:#x})",
				KeyBoardPtr->Name(),
				pMenu->Name(),
				reinterpret_cast<uintptr_t>(inputBufferPtr),
				maxInputLength,
				KeyBoardPtr->Description(),
				reinterpret_cast<uintptr_t>(KeyBoardPtr)
			);
			return KeyBoardPtr;
		}
		return nullptr;
	}

	DMENU::ItemPlaceHolder* NdDevMenu::Create_DMENU_ItemPlaceHolder(std::string pName, DMENU::Menu* pMenu, const char* pPlaceHolder, HeapArena_Args) {
		auto HeapAllocator = m_Memory->Allocate<DMENU::ItemPlaceHolder>(sizeof(DMENU::ItemPlaceHolder), 0x10, source_func, source_line, source_file);
		DMENU::ItemPlaceHolder* ItemPlaceHolder{};
		if (HeapAllocator) {
			memset((void*)HeapAllocator, 0x0, sizeof(DMENU::ItemPlaceHolder));
			always_assert(DMENU_ItemPlaceHolder == nullptr, "Function pointer was not set!");
			ItemPlaceHolder = DMENU_ItemPlaceHolder(HeapAllocator, const_cast<char*>(pName.c_str()), const_cast<char*>(pPlaceHolder));
			DMENU_AppendComponent(pMenu, ItemPlaceHolder);
			spdlog::debug("Created DMENU::Component::ItemPlaceHolder('{:s}', parent='{:s}', PlaceHolder={:s})",
				ItemPlaceHolder->Name(),
				pMenu->Name(),
				ItemPlaceHolder->GetContent()
			);
			return ItemPlaceHolder;
		}
		return nullptr;
	}

	DMENU::ItemLine* NdDevMenu::Create_DMENU_ItemLine(DMENU::Menu* pMenu, HeapArena_Args) {
		auto HeapAllocator = m_Memory->Allocate<DMENU::ItemLine>(sizeof(DMENU::ItemLine), 0x10, source_func, source_line, source_file);
		DMENU::ItemLine* LinePtr{};
		if (HeapAllocator) {
			memset((void*)HeapAllocator, 0x0, sizeof(DMENU::ItemLine));
			always_assert(DMENU_ItemLine == nullptr, "Function pointer was not set!");
			LinePtr = DMENU_ItemLine(HeapAllocator);
			spdlog::debug("Created DMENU::Component::ItemLine() -> {:#x}", reinterpret_cast<uintptr_t>(LinePtr));\
			DMENU_AppendComponent(pMenu, LinePtr);
			return LinePtr;
		}
		return nullptr;
	}

	DMENU::ItemSubText* NdDevMenu::Create_DMENU_ItemSubText(std::string pName, DMENU::Menu* pMenu, HeapArena_Args) {
		auto HeapAllocator = m_Memory->Allocate<DMENU::ItemSubText>(sizeof(DMENU::ItemSubText), 0x10, source_func, source_line, source_file);
		DMENU::ItemSubText* SubTextPtr{};
		if (HeapAllocator) {
			memset((void*)HeapAllocator, 0x0, sizeof(DMENU::ItemSubText));
			always_assert(DMENU_ItemSubText == nullptr, "Function pointer was not set!");
			SubTextPtr = DMENU_ItemSubText(HeapAllocator, pName.c_str());
			spdlog::debug("Created DMENU::Component::ItemSubText('{:s}') -> {:#x}", SubTextPtr->Name(), reinterpret_cast<uintptr_t>(SubTextPtr));
			DMENU_AppendComponent(pMenu, SubTextPtr);
			return SubTextPtr;
		}
		return nullptr;
	}

	DMENU::ItemSubmenu* NdDevMenu::Create_DMENU_ItemSubmenu(std::string pName, DMENU::Menu* pRootMenu, DMENU::Menu* pSubmenu, DMENU::ItemSubmenu::SubmenuCallback pCallbackFunct, uint64_t pData, const char* pDescription, HeapArena_Args) {
		auto HeapAllocator = m_Memory->Allocate<DMENU::ItemSubmenu>(sizeof(DMENU::ItemSubmenu), 0x10, source_func, source_line, source_file);
		DMENU::ItemSubmenu* SubmenuPtr{};
		if (HeapAllocator) {
			memset((void*)HeapAllocator, 0x0, sizeof(DMENU::ItemSubmenu));
			always_assert(DMENU_ItemSubmenu == nullptr, "Function pointer was not set!");

			std::string menu_entry_text = std::format("{}...", pName);
			void* SubmenuCallBackPtr = pCallbackFunct != NULL ? 
				reinterpret_cast<void*>(*pCallbackFunct.target<DMENU::ItemSubmenu::SubmenuCallbackPtr>()) : nullptr;

			SubmenuPtr = DMENU_ItemSubmenu(HeapAllocator, menu_entry_text.c_str(), pSubmenu, SubmenuCallBackPtr, pData, pDescription);
			spdlog::debug("Created DMENU::Component::ItemSubmenu('{:s}','DMENU::Component::Menu('{:s}')',{:#x},{:#x},'{:s}') -> {:#x}",
				SubmenuPtr->Name(), pSubmenu->Name(),
				reinterpret_cast<uintptr_t>(SubmenuPtr->CallBackFunct()), SubmenuPtr->Data(), SubmenuPtr->Description(), reinterpret_cast<uintptr_t>(SubmenuPtr));
			DMENU_AppendComponent(pRootMenu, SubmenuPtr);
			return SubmenuPtr;
		}
		return nullptr;
	}

	DMENU::ItemBool* NdDevMenu::Create_DMENU_ItemBool(std::string pName, DMENU::Menu* pMenu, bool* pData, const char* pDescription, HeapArena_Args) {
		auto HeapAllocator = m_Memory->Allocate<DMENU::ItemBool>(sizeof(DMENU::ItemBool), 0x10, source_func, source_line, source_file);
		DMENU::ItemBool* BoolPtr{};
		if (HeapAllocator) {
			memset((void*)HeapAllocator, 0x0, sizeof(DMENU::ItemBool));
			always_assert(DMENU_ItemBool == nullptr, "Function pointer was not set!");
			BoolPtr = DMENU_ItemBool(HeapAllocator, pName.c_str(), pData, pDescription);
			spdlog::debug("Created DMENU::Component::ItemBool('{:s}','{:#x}','{:s}') -> {:#x}",
				BoolPtr->Name(), BoolPtr->Data(), BoolPtr->Description(), reinterpret_cast<uintptr_t>(BoolPtr));
			DMENU_AppendComponent(pMenu, BoolPtr);
			return BoolPtr;
		}
		return nullptr;
	}

	DMENU::ItemDecimal* NdDevMenu::Create_DMENU_ItemDecimal(std::string pName, DMENU::Menu* pMenu, int* pData,
		DMENU::ItemDecimal::ValueParams pValueParams, DMENU::ItemDecimal::StepParams pStepParams, const char* pDescription, HeapArena_Args) {
		auto HeapAllocator = m_Memory->Allocate<DMENU::ItemDecimal>(sizeof(DMENU::ItemDecimal), 0x10, source_func, source_line, source_file);
		DMENU::ItemDecimal* DoublePtr{};
		if (HeapAllocator) {
			memset((void*)HeapAllocator, 0x0, sizeof(DMENU::ItemDecimal));
			always_assert(DMENU_ItemDecimal == nullptr, "Function pointer was not set!");
		#if defined(T2R)
			DoublePtr = DMENU_ItemDecimal(HeapAllocator, pName.c_str(), reinterpret_cast<uint64_t*>(pData),
				&pValueParams, &pStepParams, pDescription, true);
		#else
			DoublePtr = DMENU_ItemDecimal(HeapAllocator, pName.c_str(), reinterpret_cast<uint64_t*>(pData),
				&pValueParams, &pStepParams, pDescription);
		#endif
			spdlog::debug("Created DMENU::Component::ItemDecimal('{:s}','{:#x}','{:d},{:d}','{:d},{:d},'{:s}') -> {:#x}",
				DoublePtr->Name(), DoublePtr->Data(), DoublePtr->GetValueParams().MinValue, DoublePtr->GetValueParams().MaxValue,
				DoublePtr->GetStepParams().StepValue, DoublePtr->GetStepParams().DoubleStepValue, DoublePtr->Description(), reinterpret_cast<uintptr_t>(DoublePtr));
			DMENU_AppendComponent(pMenu, DoublePtr);
			return DoublePtr;
		}
		return nullptr;
	}


	DMENU::ItemFloat* NdDevMenu::Create_DMENU_ItemFloat(std::string pName, DMENU::Menu* pMenu, float* pData, DMENU::ItemFloat::ValueParams pValueParams, DMENU::ItemFloat::StepParams pStepParams, const char* pDescription, HeapArena_Args) {
		auto HeapAllocator = m_Memory->Allocate<DMENU::ItemFloat>(sizeof(DMENU::ItemFloat), 0x10, source_func, source_line, source_file);
		DMENU::ItemFloat* FloatPtr{};
		if (HeapAllocator) {
			memset((void*)HeapAllocator, 0x0, sizeof(DMENU::ItemFloat));
			always_assert(DMENU_ItemFloat == nullptr, "Function pointer was not set!");
		#if defined(T2R)
			FloatPtr = DMENU_ItemFloat(HeapAllocator, pName.c_str(), reinterpret_cast<uint64_t*>(pData), 
				&pValueParams, &pStepParams, pDescription, NULL, true);
		#else
			FloatPtr = DMENU_ItemFloat(HeapAllocator, pName.c_str(), reinterpret_cast<uint64_t*>(pData),
				&pValueParams, &pStepParams, pDescription, NULL);
		#endif
			spdlog::debug("Created DMENU::Component::ItemFloat('{:s}','{:#x}','{:.2f},{:.2f}','{:.2f},{:.2f},'{:s}') -> {:#x}",
				FloatPtr->Name(), reinterpret_cast<uintptr_t>(pData), FloatPtr->GetValueParams().MinValue, FloatPtr->GetValueParams().MaxValue,
				FloatPtr->GetStepParams().StepValue, FloatPtr->GetStepParams().DoubleStepValue, FloatPtr->Description(), reinterpret_cast<uintptr_t>(FloatPtr));
			DMENU_AppendComponent(pMenu, FloatPtr);
			return FloatPtr;
		}
		return nullptr;
	}

	DMENU::ItemFunction* NdDevMenu::Create_DMENU_ItemFunction(std::string pName, DMENU::Menu* pMenu, DMENU::ItemFunction::FunctionCallback pFunction, uint64_t args, bool pIsActive, HeapArena_Args) {
		auto HeapAllocator = m_Memory->Allocate<DMENU::ItemFunction>(sizeof(DMENU::ItemFunction), 0x10, source_func, source_line, source_file);
		DMENU::ItemFunction* FunctionPtr{};
		if (HeapAllocator) {
			memset((void*)HeapAllocator, 0x0, sizeof(DMENU::ItemFunction));
			always_assert(DMENU_ItemFunction == nullptr, "Function pointer was not set!");

			// We can only support free functions! For member functions consider using wrapped shells.
			auto funcCallBackPtr = *pFunction.target<DMENU::ItemFunction::FunctionCallbackPtr>();
			always_assert(funcCallBackPtr == nullptr, "FunctionCallback pointer was not set!");

			FunctionPtr = DMENU_ItemFunction(HeapAllocator, pName.c_str(), reinterpret_cast<void*>(funcCallBackPtr), args, pIsActive);
			spdlog::debug("Created DMENU::Component::ItemFunction('{:s}','{:#x}','{:#x}','{}') -> {:#x}",
				FunctionPtr->Name(), reinterpret_cast<uintptr_t>(FunctionPtr->CallBackFunct()), FunctionPtr->Data(),
				FunctionPtr->IsActive(), reinterpret_cast<uintptr_t>(FunctionPtr));
			DMENU_AppendComponent(pMenu, FunctionPtr);
			return FunctionPtr;
		}
		return nullptr;
	}

	DMENU::ItemSelection* NdDevMenu::Create_DMENU_ItemSelection(std::string pName, DMENU::Menu* pMenu, DMENU::ItemSelection::Item_selection* pItemSelection, DMENU::ItemSelection::SelectionHandler pCallback, uint64_t* pData, const char* pDescription, HeapArena_Args) {
		auto HeapAllocator = m_Memory->Allocate<DMENU::ItemSelection>(sizeof(DMENU::ItemSelection), 0x10, source_func, source_line, source_file);
		DMENU::ItemSelection* SelectionPtr{};
		if (HeapAllocator) {
			memset((void*)HeapAllocator, 0x0, sizeof(DMENU::ItemSelection));
			always_assert(DMENU_ItemSelection == nullptr, "Function pointer was not set!");
			void* SelectionCallBackPtr = pCallback != NULL ?
				reinterpret_cast<void*>(*pCallback.target<DMENU::ItemSelection::SelectionHandlerPtr>()) : (void*)DMENU_Menu_DecimalCallBack;
		#if defined(T2R)
			SelectionPtr = DMENU_ItemSelection(HeapAllocator, pName.c_str(), pItemSelection, SelectionCallBackPtr,
				pData, NULL, NULL, NULL, pDescription, true);
		#else
			SelectionPtr = DMENU_ItemSelection(HeapAllocator, pName.c_str(), pItemSelection, SelectionCallBackPtr,
				pData, NULL, NULL, NULL, pDescription);
		#endif
			spdlog::debug("Created DMENU::Component::ItemSelection('{:s}','{:#x}','{:#x}','{:#x}','{:s}') -> {:#x}",
				SelectionPtr->Name(), reinterpret_cast<uintptr_t>(&SelectionPtr->ItemSelections()), reinterpret_cast<uintptr_t>(SelectionPtr->CallBackFunct()), 
				SelectionPtr->Data(), SelectionPtr->Description(), reinterpret_cast<uintptr_t>(SelectionPtr));
			DMENU_AppendComponent(pMenu, SelectionPtr);
			return SelectionPtr;
		}
		return nullptr;
	}

	std::pair<DMENU::ItemLine*, DMENU::ItemSubText*> NdDevMenu::Create_DMENU_TextLineWrapper(std::string pName, DMENU::Menu* pMenu, HeapArena_Args) {
		return {
		Create_DMENU_ItemLine(pMenu,source_func,source_line,source_file),
		Create_DMENU_ItemSubText(pName,pMenu,source_func,source_line,source_file)
		};
	}

	int64_t NdDevMenu::DecimalCallBack(DMENU::Component& component, DMENU::Message message, uint32_t data) {
		always_assert(DMENU_Menu_DecimalCallBack == nullptr, "Function pointer was not set!");
		return DMENU_Menu_DecimalCallBack(&component, message, data);
	}

	NdDevMenu::DmenuComponentType NdDevMenu::GetComponentType(DMENU::Component* component) {
		uintptr_t vftablePtr = (uintptr_t)component->Get()->vftable;
		auto ComponentType = m_DmenuComponentTypeMap.find(vftablePtr);
		if (ComponentType != m_DmenuComponentTypeMap.end()) {
			return ComponentType->second;
		}

		return DmenuComponentType::Unknown;
	}

	bool NdDevMenu::Menu_DeleteItem(DMENU::Menu* pMenu, DMENU::Component* pItem) {
		always_assert(DMENU_Menu_DeleteItem == nullptr, "Function pointer was not set!");
		if (pMenu) {
			auto ComponentName = pItem->Name();
			// Consider that this delete also includes internal linked components
			DMENU_Menu_DeleteItem(pMenu, pItem);
			spdlog::debug("DMENU_Menu_DeleteItem(RootMenu: 'DMENU::Component::Menu('{:s}')', 'DMENU::Item('{:s}')')",
				pMenu->Name(), ComponentName);
			return true;
		}
		return false;
	}

	DMENU::Menu* NdDevMenu::Menu_DeleteAllItems(DMENU::Menu* pMenu, bool pFreeMenu) {
		always_assert(DMENU_Menu_DeleteAllItems == nullptr, "Function pointer was not set!");
		if (pMenu) {
			auto ComponentName = pMenu->Name();
			// pFreeMenu - Deallocates pMenu block of memory
			DMENU_Menu_DeleteAllItems(pMenu, pFreeMenu);
			spdlog::debug("DMENU_Menu_DeleteAllItems(RootMenu: 'DMENU::Component::Menu('{:s}')')", ComponentName);
			return pMenu;
		}
		return nullptr;
	}

	void NdDevMenu::DMENU_Menu_Update(DMENU* DMENU) {
		always_assert(DMENU_Menu_UpdateKeyboard == nullptr, "Function pointer was not set!");
		DMENU_Menu_UpdateKeyboard(DMENU);
	}

	DMENU::Menu* NdDevMenu::CreateNdGameSdkMenu() {
		// Create main menu for NdGameSdk
		DMENU::Menu* NdGameSdkMenu = Create_DMENU_Menu(SDK_NAME, HeapArena_Source);

		static int test_int = 0;
		auto itemdecimal = Create_DMENU_ItemDecimal("Work in progress :)", NdGameSdkMenu, &test_int,
			DMENU::ItemDecimal::ValueParams{ 1, 10 }, DMENU::ItemDecimal::StepParams{ 1, 2 }, "Test component", HeapArena_Source);

		itemdecimal->SetColor(Color(0xFF00FF00));

		DebugDrawCommon::CreateDebugDrawMenu(this, NdGameSdkMenu);
		ScriptManager::CreateScriptManagerMenu(this, NdGameSdkMenu);
#if defined(T2R)
		PackageManager::CreatePackageManagerMenu(this, NdGameSdkMenu);
#endif
		return NdGameSdkMenu;
	}

	void NdDevMenu::AppendSdkSubMenus(DMENU::Menu* RootMenu, AppendSdkSubMenus_Args) {
		always_assert(CustomMenu == nullptr, "CustomMenu pointer was not set!");

		if (m_SdkCustomSubmenus.empty()) {
			Create_DMENU_TextLineWrapper(std::string(SDK_NAME) + " Menus", RootMenu, HeapArena_Source);
		}

		auto module_menu = Create_DMENU_ItemSubmenu(CustomMenu->Name(), RootMenu, CustomMenu, SubmenuCallback,
			Data, Description, HeapArena_Source);

		m_SdkCustomSubmenus.push_back(module_menu);
	}

	void NdDevMenu::OnGameInitialized(bool successful) {
		if (successful) {
			auto& DMENU = m_EngineComponents->m_ndConfig.GetDmenu();

			auto DevMenu = DMENU.DevMenu()->RootMenu();
			AppendSdkSubMenusCallback AppendCallback = boost::bind(&NdDevMenu::AppendSdkSubMenus, this, DevMenu, 
				_1, _2, _3, _4);
			InvokeSdkEvent(e_AppendSdkMenu, this, AppendCallback);
		}
	}

	void NdDevMenu::Awake() {
		auto SharedComponents = ISdkComponent::GetSharedComponents();
		m_Memory = GetDependencyComponent<Memory>(SharedComponents);
		m_EngineComponents = GetDependencyComponent<EngineComponents>(SharedComponents);
		m_CommonGame = GetDependencyComponent<CommonGame>(SharedComponents);
	}

	void NdDevMenu::Initialize() {
		static std::once_flag Initialized;

		std::call_once(Initialized, [this] {

			spdlog::info("Initializing {} patterns...", GetName());

			Patterns::SdkPattern findpattern{};
			auto module = Utility::memory::get_executable();

#if defined(T2R)
			constexpr unsigned char m_DevMode_1[] = { 0xb2, 0x01, 0x90 };
			constexpr size_t SetRootMenuHook_Offset = 0x95;

			// Disable FavoriteItem keycode handler if any DMENU keyboard component is active
			findpattern = Patterns::NdDevMenu_DMENU_Menu_UpdateItems_FavoriteItemKeyCode;
			auto pFavoriteItemKeyCode = Utility::FindAndPrintPattern(module
				, findpattern.pattern, wstr(Patterns::NdDevMenu_DMENU_Menu_UpdateItems_FavoriteItemKeyCode), findpattern.offset);

#elif defined(T1X)
			constexpr unsigned char m_DevMode_1[] = { 0xb9, 0x00, 0x00, 0x00, 0x00, 0x90 };
			constexpr size_t SetRootMenuHook_Offset = 0x93;
#endif
			findpattern = Patterns::NdDevMenu_DMENU_MenuGroup_SetRootMenu;
			auto SetRootMenuJMP = (void*)Utility::FindAndPrintPattern(module, 
				findpattern.pattern, wstr(Patterns::NdDevMenu_DMENU_MenuGroup_SetRootMenu), findpattern.offset + SetRootMenuHook_Offset);

			findpattern = Patterns::NdDevMenu_DMENU_KeyBoard_Handler_ClipBoardHook;
			auto pKeyboardClipBoardJMP = (void*)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::NdDevMenu_DMENU_KeyBoard_Handler_ClipBoardHook), findpattern.offset);

			// Enable Ctrl + F combination if only DMENU is active, otherwise keep locked.
			findpattern = Patterns::NdDevMenu_DMENU_Menu_Update_KeyboardSearchState;
			auto pKeyboardSearchState = Utility::FindAndPrintPattern(module
				, findpattern.pattern, wstr(Patterns::NdDevMenu_DMENU_Menu_Update_KeyboardSearchState), findpattern.offset);

			findpattern = Patterns::NdDevMenu_DMENU_s_IsKeyboardSearchActive;
			auto IsKeyboardSearchActive = Utility::ReadLEA32(module,
				findpattern.pattern, wstr(Patterns::NdDevMenu_DMENU_s_IsKeyboardSearchActive), findpattern.offset, 3, 7);

			findpattern = Patterns::NdDevMenu_DMENU_s_IsKeyboardComponentActive;
			auto IsKeyboardComponentActive = Utility::ReadLEA32(module,
				findpattern.pattern, wstr(Patterns::NdDevMenu_DMENU_s_IsKeyboardComponentActive), findpattern.offset, 2, 7);

			if (!SetRootMenuJMP ||
				!pKeyboardSearchState ||
				!IsKeyboardSearchActive ||
				!IsKeyboardComponentActive ||
			#if defined(T2R)
				!pFavoriteItemKeyCode ||
			#endif 
				
				!pKeyboardClipBoardJMP
				) {
				throw SdkComponentEx
				{ std::format("Failed to find addresses!"),
					SdkComponentEx::ErrorCode::PatternFailed };
			}

			s_IsKeyboardSearchActive = reinterpret_cast<bool*>(IsKeyboardSearchActive);
			s_IsKeyboardComponentActive = reinterpret_cast<bool*>(IsKeyboardComponentActive);

			if (IsGameDebugMenu()) {
				spdlog::info("GameDebugMenu is enabled!");
			}

			if (m_Memory->IsDebugMemoryAvailable()) {
			#if defined(T1X)
				findpattern = Patterns::NdDevMenu_Assert_UpdateSelectRegionByNameMenu;
				m_Assert_UpdateSelectRegionByNameMenuPatch = Utility::WritePatchNop(module, findpattern.pattern, 0x1,
					wstr(Patterns::NdDevMenu_Assert_UpdateSelectRegionByNameMenu), findpattern.offset);

				findpattern = Patterns::NdDevMenu_Assert_UpdateSelectIgcByNameMenu;
				m_Assert_UpdateSelectIgcByNameMenuPatch = Utility::WritePatchNop(module, findpattern.pattern, 0x1,
					wstr(Patterns::NdDevMenu_Assert_UpdateSelectIgcByNameMenu), findpattern.offset);

				findpattern = Patterns::NdDevMenu_Assert_UpdateSelectSpawnerByNameMenu;
				m_Assert_UpdateSelectSpawnerByNameMenuPatch = Utility::WritePatchNop(module, findpattern.pattern, 0x1,
					wstr(Patterns::NdDevMenu_Assert_UpdateSelectSpawnerByNameMenu), findpattern.offset);
			#endif

				spdlog::info("ExtendedDebugMenu is enabled!");
			}

			findpattern = Patterns::NdDevMenu_DMENU_Menu;
			DMENU_Menu = (DMENU_Menu_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::NdDevMenu_DMENU_Menu), findpattern.offset);

			findpattern = Patterns::NdDevMenu_DMENU_String;
			DMENU_String = (DMENU_String_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::NdDevMenu_DMENU_String), findpattern.offset);

			findpattern = Patterns::NdDevMenu_DMENU_KeyBoard;
			DMENU_KeyBoard = (DMENU_KeyBoard_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::NdDevMenu_DMENU_KeyBoard), findpattern.offset);

			findpattern = Patterns::NdDevMenu_DMENU_ItemPlaceHolder;
			DMENU_ItemPlaceHolder = (DMENU_ItemPlaceHolder_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::NdDevMenu_DMENU_ItemPlaceHolder), findpattern.offset);

			findpattern = Patterns::NdDevMenu_DMENU_ItemLine;
			DMENU_ItemLine = (DMENU_ItemLine_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::NdDevMenu_DMENU_ItemLine), findpattern.offset);

			findpattern = Patterns::NdDevMenu_DMENU_ItemSubText;
			DMENU_ItemSubText = (DMENU_ItemSubText_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::NdDevMenu_DMENU_ItemSubText), findpattern.offset);

			findpattern = Patterns::NdDevMenu_DMENU_ItemSubmenu;
			DMENU_ItemSubmenu = (DMENU_ItemSubmenu_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::NdDevMenu_DMENU_ItemSubmenu), findpattern.offset);

			findpattern = Patterns::NdDevMenu_DMENU_ItemBool;
			DMENU_ItemBool = (DMENU_ItemBool_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::NdDevMenu_DMENU_ItemBool), findpattern.offset);

			findpattern = Patterns::NdDevMenu_DMENU_ItemDecimal;
			DMENU_ItemDecimal = (DMENU_ItemDecimal_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::NdDevMenu_DMENU_ItemDecimal), findpattern.offset);

			findpattern = Patterns::NdDevMenu_DMENU_ItemFloat;
			DMENU_ItemFloat = (DMENU_ItemFloat_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::NdDevMenu_DMENU_ItemFloat), findpattern.offset);

			findpattern = Patterns::NdDevMenu_DMENU_ItemFunction;
			DMENU_ItemFunction = (DMENU_ItemFunction_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::NdDevMenu_DMENU_ItemFunction), findpattern.offset);

			findpattern = Patterns::NdDevMenu_DMENU_ItemSelection;
			DMENU_ItemSelection = (DMENU_ItemSelection_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::NdDevMenu_DMENU_ItemSelection), findpattern.offset);

			findpattern = Patterns::NdDevMenu_DMENU_Menu_AppendComponent;
			DMENU_Menu_AppendComponent = (DMENU_Menu_AppendComponent_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::NdDevMenu_DMENU_Menu_AppendComponent), findpattern.offset);

			findpattern = Patterns::NdDevMenu_DMENU_Menu_DeleteItem;
			DMENU_Menu_DeleteItem = (DMENU_Menu_DeleteItem_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::NdDevMenu_DMENU_Menu_DeleteItem), findpattern.offset);

			findpattern = Patterns::NdDevMenu_DMENU_Menu_DeleteAllItems;
			DMENU_Menu_DeleteAllItems = (DMENU_Menu_DeleteAllItems_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::NdDevMenu_DMENU_Menu_DeleteAllItems), findpattern.offset);

			findpattern = Patterns::NdDevMenu_DMENU_DecimalCallBack;
			DMENU_Menu_DecimalCallBack = (DMENU_Menu_DecimalCallBack_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::NdDevMenu_DMENU_DecimalCallBack), findpattern.offset);

			findpattern = Patterns::NdDevMenu_DMENU_Menu_UpdateKeyboard;
			DMENU_Menu_UpdateKeyboard = (DMENU_Menu_UpdateKeyboard_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::NdDevMenu_DMENU_Menu_UpdateKeyboard), findpattern.offset);

			if (!DMENU_Menu ||
				!DMENU_String ||
				!DMENU_KeyBoard ||
				!DMENU_ItemPlaceHolder ||
				!DMENU_ItemLine ||
				!DMENU_ItemSubText ||
				!DMENU_ItemSubmenu ||
				!DMENU_ItemBool ||
				!DMENU_ItemDecimal ||
				!DMENU_ItemFloat ||
				!DMENU_ItemFunction ||
				!DMENU_ItemSelection ||
				!DMENU_Menu_AppendComponent ||
				!DMENU_Menu_DeleteItem ||
				!DMENU_Menu_DeleteAllItems ||
				!DMENU_Menu_DecimalCallBack ||
				!DMENU_Menu_UpdateKeyboard) {
				throw SdkComponentEx{ std::format("Failed to find {}:: game functions!", GetName()), SdkComponentEx::ErrorCode::PatternFailed };
			}

			constexpr size_t DMENU_Component_VTableOffset = 0x1a;
			constexpr size_t DMENU_MenuGroup_VTableOffset = 0x1a;
			constexpr size_t DMENU_Menu_VTableOffset = 0x15;
			constexpr size_t DMENU_String_VTableOffset = 0x1d;
			constexpr size_t DMENU_ItemSubmenu_VTableOffset = 0x34;
			constexpr size_t DMENU_ItemBool_VTableOffset = 0x2b;
			constexpr size_t DMENU_ItemSubText_VTableOffset = 0x35;
			constexpr size_t DMENU_ItemPlaceHolder_VTableOffset = 0x35;
#if defined(T2R)
			constexpr size_t DMENU_KeyBoard_VTableOffset = 0x1f;
			constexpr size_t DMENU_ItemLine_VTableOffset = 0x56;
			constexpr size_t DMENU_ItemDecimal_VTableOffset = 0x5c;
			constexpr size_t DMENU_ItemFloat_VTableOffset = 0x5c;
			constexpr size_t DMENU_ItemFunction_VTableOffset = 0x28;
			constexpr size_t DMENU_ItemSelection_VTableOffset = 0x4a;
#elif defined(T1X)
			constexpr size_t DMENU_KeyBoard_VTableOffset = 0x36;
			constexpr size_t DMENU_ItemLine_VTableOffset = 0x5A;
			constexpr size_t DMENU_ItemDecimal_VTableOffset = 0x50;
			constexpr size_t DMENU_ItemFloat_VTableOffset = 0x61;
			constexpr size_t DMENU_ItemFunction_VTableOffset = 0x25;
			constexpr size_t DMENU_ItemSelection_VTableOffset = 0x35;
#endif

			findpattern = Patterns::NdDevMenu_DMENU_Component;
			DMENU::Component::VTable = (regenny::shared::ndlib::debug::DMENU::Component::VTable*)Utility::ReadLEA32(module,
				findpattern.pattern, wstr(Patterns::NdDevMenu_DMENU_Component), findpattern.offset + DMENU_Component_VTableOffset, 3, 7);

			findpattern = Patterns::NdDevMenu_DMENU_MenuGroup;
			DMENU::MenuGroup::VTable = (regenny::shared::ndlib::debug::DMENU::MenuGroup::VTable*)Utility::ReadLEA32(module,
				findpattern.pattern, wstr(Patterns::NdDevMenu_DMENU_MenuGroup), findpattern.offset + DMENU_MenuGroup_VTableOffset, 3, 7);

			findpattern = Patterns::NdDevMenu_DMENU_Menu;
			DMENU::Menu::VTable = (regenny::shared::ndlib::debug::DMENU::Menu::VTable*)Utility::ReadLEA32(module,
				findpattern.pattern, wstr(Patterns::NdDevMenu_DMENU_Menu), findpattern.offset + DMENU_Menu_VTableOffset, 3, 7);

			findpattern = Patterns::NdDevMenu_DMENU_String;
			DMENU::String::VTable = (regenny::shared::ndlib::debug::DMENU::String::VTable*)Utility::ReadLEA32(module,
				findpattern.pattern, wstr(Patterns::NdDevMenu_DMENU_String), findpattern.offset + DMENU_String_VTableOffset, 3, 7);

			findpattern = Patterns::NdDevMenu_DMENU_KeyBoard;
			DMENU::KeyBoard::VTable = (regenny::shared::ndlib::debug::DMENU::KeyBoard::VTable*)Utility::ReadLEA32(module,
				findpattern.pattern, wstr(Patterns::NdDevMenu_DMENU_KeyBoard), findpattern.offset + DMENU_KeyBoard_VTableOffset, 3, 7);

			findpattern = Patterns::NdDevMenu_DMENU_ItemPlaceHolder;
			DMENU::ItemPlaceHolder::VTable = (regenny::shared::ndlib::debug::DMENU::ItemPlaceHolder::VTable*)Utility::ReadLEA32(module,
				findpattern.pattern, wstr(Patterns::NdDevMenu_DMENU_ItemPlaceHolder), findpattern.offset + DMENU_ItemPlaceHolder_VTableOffset, 3, 7);

			findpattern = Patterns::NdDevMenu_DMENU_ItemLine;
			DMENU::ItemLine::VTable = (regenny::shared::ndlib::debug::DMENU::ItemLine::VTable*)Utility::ReadLEA32(module,
				findpattern.pattern, wstr(Patterns::NdDevMenu_DMENU_ItemLine), findpattern.offset + DMENU_ItemLine_VTableOffset, 3, 7);

			findpattern = Patterns::NdDevMenu_DMENU_ItemSubmenu;
			DMENU::ItemSubmenu::VTable = (regenny::shared::ndlib::debug::DMENU::ItemSubmenu::VTable0*)Utility::ReadLEA32(module,
				findpattern.pattern, wstr(Patterns::NdDevMenu_DMENU_ItemSubmenu), findpattern.offset + DMENU_ItemSubmenu_VTableOffset, 3, 7);

			findpattern = Patterns::NdDevMenu_DMENU_ItemBool;
			DMENU::ItemBool::VTable = (regenny::shared::ndlib::debug::DMENU::ItemBool::VTable0*)Utility::ReadLEA32(module,
				findpattern.pattern, wstr(Patterns::NdDevMenu_DMENU_ItemBool), findpattern.offset + DMENU_ItemBool_VTableOffset, 3, 7);

			findpattern = Patterns::NdDevMenu_DMENU_ItemDecimal;
			DMENU::ItemDecimal::VTable = (regenny::shared::ndlib::debug::DMENU::ItemDecimal::VTable0*)Utility::ReadLEA32(module,
				findpattern.pattern, wstr(Patterns::NdDevMenu_DMENU_ItemDecimal), findpattern.offset + DMENU_ItemDecimal_VTableOffset, 3, 7);

			findpattern = Patterns::NdDevMenu_DMENU_ItemFloat;
			DMENU::ItemFloat::VTable = (regenny::shared::ndlib::debug::DMENU::ItemFloat::VTable0*)Utility::ReadLEA32(module,
				findpattern.pattern, wstr(Patterns::NdDevMenu_DMENU_ItemFloat), findpattern.offset + DMENU_ItemFloat_VTableOffset, 3, 7);

			findpattern = Patterns::NdDevMenu_DMENU_ItemFunction;
			DMENU::ItemFunction::VTable = (regenny::shared::ndlib::debug::DMENU::ItemFunction::VTable0*)Utility::ReadLEA32(module,
				findpattern.pattern, wstr(Patterns::NdDevMenu_DMENU_ItemFunction), findpattern.offset + DMENU_ItemFunction_VTableOffset, 3, 7);

			findpattern = Patterns::NdDevMenu_DMENU_ItemSelection;
			DMENU::ItemSelection::VTable = (regenny::shared::ndlib::debug::DMENU::ItemSelection::VTable0*)Utility::ReadLEA32(module,
				findpattern.pattern, wstr(Patterns::NdDevMenu_DMENU_ItemSelection), findpattern.offset + DMENU_ItemSelection_VTableOffset, 3, 7);

			findpattern = Patterns::NdDevMenu_DMENU_ItemSubText;
			DMENU::ItemSubText::VTable = (regenny::shared::ndlib::debug::DMENU::ItemSubText::VTable0*)Utility::ReadLEA32(module,
				findpattern.pattern, wstr(Patterns::NdDevMenu_DMENU_ItemSubText), findpattern.offset + DMENU_ItemSubText_VTableOffset, 3, 7);

#if defined(T2R)
			// Fix Vtable offsets
			DMENU::KeyBoard::VTable = reinterpret_cast<decltype(DMENU::KeyBoard::VTable)>(
				reinterpret_cast<uint8_t*>(DMENU::KeyBoard::VTable) + (0x25a * 0x8));
#endif
		

			if (!DMENU::Component::VTable ||
				!DMENU::MenuGroup::VTable ||
				!DMENU::Menu::VTable ||
				!DMENU::String::VTable ||
				!DMENU::KeyBoard::VTable ||
				!DMENU::ItemPlaceHolder::VTable ||
				!DMENU::ItemLine::VTable ||
				!DMENU::ItemSubmenu::VTable ||
				!DMENU::ItemBool::VTable ||
				!DMENU::ItemDecimal::VTable ||
				!DMENU::ItemFloat::VTable ||
				!DMENU::ItemFunction::VTable ||
				!DMENU::ItemSelection::VTable ||
				!DMENU::ItemSubText::VTable) {
				throw SdkComponentEx
				{ std::format("Failed to find VTables of DMENU Components!"),
					SdkComponentEx::ErrorCode::PatternFailed };
			}

			m_DmenuComponentTypeMap = {
				{ reinterpret_cast<uintptr_t>(DMENU::MenuGroup::VTable), DmenuComponentType::MenuGroup },
				{ reinterpret_cast<uintptr_t>(DMENU::Menu::VTable), DmenuComponentType::Menu },
				{ reinterpret_cast<uintptr_t>(DMENU::String::VTable), DmenuComponentType::String },
				{ reinterpret_cast<uintptr_t>(DMENU::KeyBoard::VTable), DmenuComponentType::KeyBoard },
				{ reinterpret_cast<uintptr_t>(DMENU::ItemPlaceHolder::VTable), DmenuComponentType::ItemPlaceHolder },
				{ reinterpret_cast<uintptr_t>(DMENU::ItemLine::VTable), DmenuComponentType::ItemLine },
				{ reinterpret_cast<uintptr_t>(DMENU::ItemSubmenu::VTable), DmenuComponentType::ItemSubmenu },
				{ reinterpret_cast<uintptr_t>(DMENU::ItemBool::VTable), DmenuComponentType::ItemBool },
				{ reinterpret_cast<uintptr_t>(DMENU::ItemDecimal::VTable), DmenuComponentType::ItemDecimal },
				{ reinterpret_cast<uintptr_t>(DMENU::ItemFloat::VTable), DmenuComponentType::ItemFloat },
				{ reinterpret_cast<uintptr_t>(DMENU::ItemFunction::VTable), DmenuComponentType::ItemFunction },
				{ reinterpret_cast<uintptr_t>(DMENU::ItemSelection::VTable), DmenuComponentType::ItemSelection },
				{ reinterpret_cast<uintptr_t>(DMENU::ItemSubText::VTable), DmenuComponentType::ItemSubText },
			};

			/* KeyBoard Patches */

			m_KeyboardSearchStateHook = Utility::MakeFunctionHook((void*)(pKeyboardSearchState),
				(void*)KeyboardSearchState_CC, wstr(m_KeyboardSearchStateHook));

			m_KeyBoard_ClipBoardHook = Utility::MakeMidHook(pKeyboardClipBoardJMP, DMENU_KeyBoard_ClipBoardHook,
				wstr(Patterns::NdDevMenu_DMENU_KeyBoard_Handler_ClipBoardHook), wstr(pKeyboardClipBoardJMP));

#if defined(T2R)
			m_FavoriteItemKeyCodeHook = Utility::MakeFunctionHook((void*)(pFavoriteItemKeyCode),
				(void*)FavoriteItemKeycode_CC, wstr(m_FavoriteItemKeyCodeHook));
#endif

			if (!m_KeyboardSearchStateHook ||
				#if defined(T2R)
				!m_FavoriteItemKeyCodeHook ||
				#endif 
				!m_KeyBoard_ClipBoardHook
				) {
				throw SdkComponentEx{ std::format("Failed to create hooks!"),
					SdkComponentEx::ErrorCode::PatchFailed };
			}

			KeyboardSearchState_ReturnAddr = m_KeyboardSearchStateHook->get_original();
#if defined(T2R)
			FavoriteItemKeyCode_ReturnAddr = m_FavoriteItemKeyCodeHook->get_original();
#endif

			m_CommonGame->e_GameInitialized.Subscribe(this, &NdDevMenu::OnGameInitialized);

			m_SetRootMenuHook = Utility::MakeMidHook(SetRootMenuJMP,
				[](SafetyHookContext& ctx)
				{
					auto NdDevMenuComponent = GetSharedComponents()->GetComponent<NdDevMenu>();
					DMENU::MenuGroup* NdDevMenu = &NdDevMenuComponent->m_EngineComponents->m_ndConfig.GetNdDevMenu();

					DMENU::MenuGroup* MenuGroup = reinterpret_cast<DMENU::MenuGroup*>(ctx.rdi);
					DMENU::Menu* Menu = reinterpret_cast<DMENU::Menu*>(ctx.rbx);

					if (MenuGroup == NdDevMenu) {
						DMENU::Menu* NdGameSdkMenu = NdDevMenuComponent->CreateNdGameSdkMenu();
						NdDevMenuComponent->m_NdGameSdkMenu = NdDevMenuComponent->Create_DMENU_ItemSubmenu(NdGameSdkMenu->Name(), MenuGroup->RootMenu(),
							NdGameSdkMenu, NULL, NULL, nullptr, HeapArena_Source)->MenuEntry();
					}

					NdDevMenuComponent->InvokeSdkEvent(NdDevMenuComponent->e_AppendMenuGroup, NdDevMenuComponent, MenuGroup);

				}, wstr(Patterns::NdDevMenu_DMENU_MenuGroup_SetRootMenu), wstr(SetRootMenuJMP));

		});
	}

	void NdDevMenu::DMENU_KeyBoard_ClipBoardHook(SafetyHookContext& ctx) {
		static NdDevMenu* pNdDevMenu = GetSharedComponents()->GetComponent<NdDevMenu>();
	#if defined(T2R)
		constexpr std::ptrdiff_t kSkipInputData = 0x5C;
	#elif defined(T1X)
		constexpr std::ptrdiff_t kSkipInputData = 0x60;
	#else
		static_assert(false, "define kSkipInputData for this build");
	#endif

		constexpr size_t kMaxPaste = 
			std::extent_v<decltype(regenny::shared::ndlib::debug::DMENU::KeyBoard::m_inputBuffer)>;

	#if defined(T2R)
		auto* frame = reinterpret_cast<NdFrameState*>(ctx.r13);
	#elif defined(T1X)
		auto* frame = reinterpret_cast<NdFrameState*>(ctx.r15);
	#endif

		auto* kbDmenu = reinterpret_cast<void*>(ctx.rbx);
		char* buf = const_cast<char*>(reinterpret_cast<const char*>(ctx.r14));

		auto* kbIme = frame->GetIMEKeyboard();
		if (!(kbIme->isCtrlDown() && kbIme->wasPressed(NdKeyboardKey::V))) return;

		std::string clip = Utility::sys::GetClipboardAnsi();
		if (clip.empty()) return;
		if (clip.size() > kMaxPaste) clip.resize(kMaxPaste);

		uint32_t& CursorIndex = *reinterpret_cast<uint32_t*>(
			static_cast<std::byte*>(kbDmenu) + DMENU_KeyBoard_CursorIndexOffset);
		uint8_t& isDirty = *reinterpret_cast<uint8_t*>(
			static_cast<std::byte*>(kbDmenu) + DMENU_KeyBoard_isDirtyOffset);

		if (isDirty) {
			*buf = 0;
			CursorIndex = 0;
			isDirty = false;
		}

		size_t len = strnlen(buf, kMaxPaste - 1);
		if (CursorIndex > len) CursorIndex = static_cast<uint32_t>(len);
		size_t n = (std::min)(kMaxPaste - 1 - len, clip.size());

		memmove(buf + CursorIndex + n, buf + CursorIndex, (len - CursorIndex) + 1);
		memcpy(buf + CursorIndex, clip.data(), n);
		CursorIndex += static_cast<uint32_t>(n);

		*reinterpret_cast<uintptr_t*>(ctx.trampoline_rsp) = 
			pNdDevMenu->m_KeyBoard_ClipBoardHook.target_address() + kSkipInputData;
		return;
	}

	void __attribute__((naked)) KeyboardSearchState_CC()
	{
		__asm
		{
			test al, al;
			je exit_;
			mov rcx, DMENU_CurrentMenuOffset
			// if (!DMENU->m_CurrentMenu)
#if defined(T2R)
			cmp qword ptr[rsi + rcx], 0;
#elif defined(T1X)
			cmp qword ptr[r14 + rcx], 0;
#endif
			jne exit_;
			mov al, 0x0;
		exit_:;
			jmp qword ptr[KeyboardSearchState_ReturnAddr]
		}
	}

#if defined(T2R)
	void __attribute__((naked)) FavoriteItemKeycode_CC()
	{
		__asm
		{
			mov rcx, qword ptr[NdDevMenu::s_IsKeyboardSearchActive];
			cmp byte ptr[rcx], 0
			jnz disablehotkey_;
			mov rcx, qword ptr[NdDevMenu::s_IsKeyboardComponentActive];
			cmp byte ptr[rcx], 0
			jz exit_;
		disablehotkey_:;
			mov al, 0x1;
		exit_:;
			jmp[rip + FavoriteItemKeyCode_ReturnAddr];
		}
	}
#endif

	bool* NdDevMenu::s_IsKeyboardSearchActive = nullptr;
	bool* NdDevMenu::s_IsKeyboardComponentActive = nullptr;


}