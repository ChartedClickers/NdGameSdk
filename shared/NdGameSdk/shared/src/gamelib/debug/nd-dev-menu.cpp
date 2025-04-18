#include "nd-dev-menu.hpp"
#include "./NdGameSdk/shared/sharedpatterns.hpp"

using namespace boost::placeholders;

namespace NdGameSdk::gamelib::debug {

	NdDevMenu::NdDevMenu(NdDevMenuCfg& cfg) : m_cfg{ std::move(cfg) }, ISdkComponent("DMENU") {}
	
	NdDevMenu::~NdDevMenu() {
		if (IsInitialized()) {
			m_CommonGame->e_GameInitialized.Unsubscribe({ this, &NdDevMenu::OnGameInitialized });
		}
	}

	bool NdDevMenu::IsGameDebugMenu() {

		auto& gameinfo = m_EngineComponents->GetNdGameInfo();
		if (gameinfo.Get()) {
			return m_EngineComponents->GetNdGameInfo()->m_DevMode;
		}

		return m_cfg.GameDebugMenu;
	}

	DMENU::Menu* NdDevMenu::Create_DMENU_Menu(std::string pName, HeapArena_Args) {
		auto HeapAllocator = m_Memory->m_HeapArena.Allocate<DMENU::Menu>
			(sizeof(DMENU::Menu), MemoryContextType::kAllocDebugDevMenu, source_func, source_line, source_file);
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

	DMENU::ItemLine* NdDevMenu::Create_DMENU_ItemLine(DMENU::Menu* pMenu, HeapArena_Args) {
		auto HeapAllocator = m_Memory->m_HeapArena.Allocate<DMENU::ItemLine>
			(sizeof(DMENU::ItemLine), MemoryContextType::kAllocDebugDevMenu, source_func, source_line, source_file);
		DMENU::ItemLine* LinePtr{};
		if (HeapAllocator) {
			memset((void*)HeapAllocator, 0x0, sizeof(DMENU::ItemLine));
			always_assert(DMENU_ItemLine == nullptr, "Function pointer was not set!");
			LinePtr = DMENU_ItemLine(HeapAllocator);
			spdlog::debug("Created DMENU::Component::ItemLine() -> {:#x}", reinterpret_cast<uintptr_t>(LinePtr));
			DMENU_AppendComponent(pMenu, LinePtr);
			return LinePtr;
		}
		return nullptr;
	}

	DMENU::ItemSubText* NdDevMenu::Create_DMENU_ItemSubText(std::string pName, DMENU::Menu* pMenu, HeapArena_Args) {
		auto HeapAllocator = m_Memory->m_HeapArena.Allocate<DMENU::ItemSubText>
			(sizeof(DMENU::ItemSubText), MemoryContextType::kAllocDebugDevMenu, source_func, source_line, source_file);
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
		auto HeapAllocator = m_Memory->m_HeapArena.Allocate<DMENU::ItemSubmenu>
			(sizeof(DMENU::ItemSubmenu), MemoryContextType::kAllocDebugDevMenu, source_func, source_line, source_file);
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
		auto HeapAllocator = m_Memory->m_HeapArena.Allocate<DMENU::ItemBool>
			(sizeof(DMENU::ItemBool), MemoryContextType::kAllocDebugDevMenu, source_func, source_line, source_file);
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
		auto HeapAllocator = m_Memory->m_HeapArena.Allocate<DMENU::ItemDecimal>
			(sizeof(DMENU::ItemDecimal), MemoryContextType::kAllocDebugDevMenu, source_func, source_line, source_file);
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
		auto HeapAllocator = m_Memory->m_HeapArena.Allocate<DMENU::ItemFloat>
			(sizeof(DMENU::ItemFloat), MemoryContextType::kAllocDebugDevMenu, source_func, source_line, source_file);
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
		auto HeapAllocator = m_Memory->m_HeapArena.Allocate<DMENU::ItemFunction>
			(sizeof(DMENU::ItemFunction), MemoryContextType::kAllocDebugDevMenu, source_func, source_line, source_file);
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

	DMENU::ItemSelection* NdDevMenu::Create_DMENU_ItemSelection(std::string pName, DMENU::Menu* pMenu, DMENU::ItemSelection::Item_selection* pItemSelection, uint64_t* pData, const char* pDescription, HeapArena_Args) {
		auto HeapAllocator = m_Memory->m_HeapArena.Allocate<DMENU::ItemSelection>
			(sizeof(DMENU::ItemSelection), MemoryContextType::kAllocDebugDevMenu, source_func, source_line, source_file);
		DMENU::ItemSelection* SelectionPtr{};
		if (HeapAllocator) {
			memset((void*)HeapAllocator, 0x0, sizeof(DMENU::ItemSelection));
			always_assert(DMENU_ItemSelection == nullptr, "Function pointer was not set!");
		#if defined(T2R)
			SelectionPtr = DMENU_ItemSelection(HeapAllocator, pName.c_str(), pItemSelection, (void*)DMENU_Menu_DecimalCallBack,
				pData, NULL, NULL, NULL, pDescription, true);
		#else
			SelectionPtr = DMENU_ItemSelection(HeapAllocator, pName.c_str(), pItemSelection, (void*)DMENU_Menu_DecimalCallBack, 
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

	NdDevMenu::DmenuComponentType NdDevMenu::GetComponentType(DMENU::Component* component) {
		uintptr_t vftablePtr = (uintptr_t)component->Get()->vftable;
		auto ComponentType = m_DmenuComponentTypeMap.find(vftablePtr);
		if (ComponentType != m_DmenuComponentTypeMap.end()) {
			return ComponentType->second;
		}

		return DmenuComponentType::Unknown;
	}

	DMENU::Menu* NdDevMenu::CreateNdGameSdkMenu() {
		// Create main menu for NdGameSdk
		DMENU::Menu* NdGameSdkMenu = Create_DMENU_Menu(SDK_NAME, HeapArena_Source);

		static int test_int = 0;
		auto itemdecimal = Create_DMENU_ItemDecimal("Work in progress :)", NdGameSdkMenu, &test_int,
			DMENU::ItemDecimal::ValueParams{ 1, 10 }, DMENU::ItemDecimal::StepParams{ 1, 2 }, "Test component", HeapArena_Source);

		itemdecimal->SetColor(Color(0xFF00FF00));

		//ScriptManager::CreateScriptManagerMenu(this,NdGameSdkMenu);

		//TODO: Here must be the main controls of sdk and the possibility of spawning menus from other sdkcomponents 
		// like this happening in the NdGames. 

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
		m_Memory = SharedComponents->GetComponent<Memory>();
		m_EngineComponents = SharedComponents->GetComponent<EngineComponents>();
		m_CommonGame = SharedComponents->GetComponent<CommonGame>();
	}

	void NdDevMenu::Initialize() {
		static std::once_flag Initialized;

		std::call_once(Initialized, [this] {

			spdlog::info("Initializing {} patterns...", GetName());

			auto MissingDependencies = CheckSdkComponents
				<Memory, CommonGame, EngineComponents>
				({ m_Memory.get(), m_CommonGame.get(), m_EngineComponents.get() });

			if (MissingDependencies.has_value()) {
				throw SdkComponentEx
				{ std::format("Missing necessary dependencies: {:s}", MissingDependencies.value()),
					SdkComponentEx::ErrorCode::DependenciesFailed };
			}

			Patterns::SdkPattern findpattern{};
			auto module = Utility::memory::get_executable();

#if defined(T2R)
			constexpr unsigned char m_DevMode_1[] = { 0xb2, 0x01, 0x90 };
			constexpr size_t SetRootMenuHook_Offset = 0x95;
#elif defined(T1X)
			constexpr unsigned char m_DevMode_1[] = { 0xb9, 0x00, 0x00, 0x00, 0x00, 0x90 };
			constexpr size_t SetRootMenuHook_Offset = 0x93;
#endif

			findpattern = Patterns::NdDevMenu_GameConfig_DevMode;
			m_GameConfig_DevModePatch = Utility::WritePatchPattern(module, findpattern.pattern, m_DevMode_1, sizeof(m_DevMode_1),
				wstr(Patterns::NdDevMenu_GameConfig_DevMode), findpattern.offset, m_cfg.GameDebugMenu);

			if (!m_GameConfig_DevModePatch) {
				throw SdkComponentEx{ "Failed to patch game functions!", SdkComponentEx::ErrorCode::PatchFailed };
			}

			if (m_GameConfig_DevModePatch->IsEnable()) {
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

			findpattern = Patterns::NdDevMenu_DMENU_MenuGroup_SetRootMenu;
			auto SetRootMenuJMP = (void*)Utility::FindAndPrintPattern(module
				, findpattern.pattern, wstr(Patterns::NdDevMenu_DMENU_MenuGroup_SetRootMenu), findpattern.offset + SetRootMenuHook_Offset);

			findpattern = Patterns::NdDevMenu_DMENU_Menu;
			DMENU_Menu = (DMENU_Menu_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::NdDevMenu_DMENU_Menu), findpattern.offset);

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

			findpattern = Patterns::NdDevMenu_DMENU_DecimalCallBack;
			DMENU_Menu_DecimalCallBack = (DMENU_Menu_DecimalCallBack_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::NdDevMenu_DMENU_DecimalCallBack), findpattern.offset);

			if (!SetRootMenuJMP ||
				!DMENU_Menu ||
				!DMENU_ItemLine ||
				!DMENU_ItemSubText ||
				!DMENU_ItemSubmenu ||
				!DMENU_ItemBool ||
				!DMENU_ItemDecimal ||
				!DMENU_ItemFloat ||
				!DMENU_ItemFunction ||
				!DMENU_ItemSelection ||
				!DMENU_Menu_AppendComponent ||
				!DMENU_Menu_DecimalCallBack) {
				throw SdkComponentEx{ std::format("Failed to find {}:: game functions!", GetName()), SdkComponentEx::ErrorCode::PatternFailed };
			}

			constexpr size_t DMENU_Component_VTableOffset = 0x1a;
			constexpr size_t DMENU_MenuGroup_VTableOffset = 0x1a;
			constexpr size_t DMENU_Menu_VTableOffset = 0x15;
			constexpr size_t DMENU_ItemSubmenu_VTableOffset = 0x34;
			constexpr size_t DMENU_ItemBool_VTableOffset = 0x2b;
			constexpr size_t DMENU_ItemSubText_VTableOffset = 0x35;
#if defined(T2R)
			constexpr size_t DMENU_ItemLine_VTableOffset = 0x56;
			constexpr size_t DMENU_ItemDecimal_VTableOffset = 0x5c;
			constexpr size_t DMENU_ItemFloat_VTableOffset = 0x5c;
			constexpr size_t DMENU_ItemFunction_VTableOffset = 0x28;
			constexpr size_t DMENU_ItemSelection_VTableOffset = 0x4a;
#elif defined(T1X)
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

			if (!DMENU::Component::VTable ||
				!DMENU::MenuGroup::VTable ||
				!DMENU::Menu::VTable ||
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
				{ reinterpret_cast<uintptr_t>(DMENU::ItemLine::VTable), DmenuComponentType::ItemLine },
				{ reinterpret_cast<uintptr_t>(DMENU::ItemSubmenu::VTable), DmenuComponentType::ItemSubmenu },
				{ reinterpret_cast<uintptr_t>(DMENU::ItemBool::VTable), DmenuComponentType::ItemBool },
				{ reinterpret_cast<uintptr_t>(DMENU::ItemDecimal::VTable), DmenuComponentType::ItemDecimal },
				{ reinterpret_cast<uintptr_t>(DMENU::ItemFloat::VTable), DmenuComponentType::ItemFloat },
				{ reinterpret_cast<uintptr_t>(DMENU::ItemFunction::VTable), DmenuComponentType::ItemFunction },
				{ reinterpret_cast<uintptr_t>(DMENU::ItemSelection::VTable), DmenuComponentType::ItemSelection },
				{ reinterpret_cast<uintptr_t>(DMENU::ItemSubText::VTable), DmenuComponentType::ItemSubText },
			};

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
							NdGameSdkMenu, NULL, NULL, nullptr, HeapArena_Source)->SubMenu();
					}

					NdDevMenuComponent->InvokeSdkEvent(NdDevMenuComponent->e_AppendMenuGroup, NdDevMenuComponent.get(), MenuGroup);

				}, wstr(Patterns::NdDevMenu_DMENU_MenuGroup_SetRootMenu), wstr(SetRootMenuJMP));

		});
	}
}