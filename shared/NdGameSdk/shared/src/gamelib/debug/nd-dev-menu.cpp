#include "nd-dev-menu.hpp"
#include "./NdGameSdk/shared/sharedpatterns.hpp"

namespace NdGameSdk::gamelib::debug {

	NdDevMenu::NdDevMenu(NdDevMenuCfg& cfg) : m_cfg{ std::move(cfg) }, ISdkComponent("DMENU") {}
	
	NdDevMenu::~NdDevMenu() {
		if (m_CommonGame) {
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

	bool NdDevMenu::IsExtendedDebugMenu() {
		return m_cfg.ExtendedDebugMenu;
	}

	DMENU::Menu* NdDevMenu::Create_DMENU_Menu(std::string pName, HeapArena_Args) {
		auto HeapAllocator = m_Memory->m_HeapArena.Allocate<DMENU::Menu>
			(sizeof(DMENU::Menu), MemoryContextType::kAllocDebugDevMenu, source_func, source_line, source_file);
		DMENU::Menu* MenuPtr{};
		if (HeapAllocator) {
			memset((void*)HeapAllocator, 0, sizeof(DMENU::Menu));
			always_assert(DMENU_Menu == nullptr, "Function pointer was not set!");
			MenuPtr = DMENU_Menu(HeapAllocator, pName.c_str());
			spdlog::debug("Created DMENU::Component::Menu('{:s}') -> {:#x}", MenuPtr->Name(), reinterpret_cast<uintptr_t>(MenuPtr));
			return MenuPtr;
		}
		return nullptr;
	}


	DMENU::ItemSubmenu* NdDevMenu::Create_DMENU_ItemSubmenu(std::string pName, DMENU::Menu* pRootMenu, DMENU::Menu* pSubmenu, void* pCallbackFunct, uint64_t pData, const char* pDescription, HeapArena_Args) {
		auto HeapAllocator = m_Memory->m_HeapArena.Allocate<DMENU::ItemSubmenu>
			(sizeof(DMENU::ItemSubmenu), MemoryContextType::kAllocDebugDevMenu, source_func, source_line, source_file);
		DMENU::ItemSubmenu* SubmenuPtr{};
		if (HeapAllocator) {
			memset((void*)HeapAllocator, 0, sizeof(DMENU::ItemSubmenu));
			always_assert(DMENU_ItemSubmenu == nullptr, "Function pointer was not set!");
			std::string menu_entry_text = std::format("{}...", pName);
			SubmenuPtr = DMENU_ItemSubmenu(HeapAllocator, menu_entry_text.c_str(), pSubmenu, pCallbackFunct, pData, pDescription);
			spdlog::debug("Created DMENU::Component::ItemSubmenu('{:s}','{:s}','DMENU::Component::Menu('{:s}')', {:#x}, {:#x}) -> {:#x}",
				SubmenuPtr->Name(), SubmenuPtr->Description(), pSubmenu->Name(),
				reinterpret_cast<uintptr_t>(SubmenuPtr->CallBackFunct()), SubmenuPtr->Data(), reinterpret_cast<uintptr_t>(SubmenuPtr));

			DMENU_AppendComponent(pRootMenu, SubmenuPtr);
			return SubmenuPtr;
		}
		return nullptr;
	}

	NdDevMenu::DmenuComponentType NdDevMenu::GetComponentType(DMENU::Component* component) {
		uintptr_t vftablePtr = (uintptr_t)component->Get()->vftable;
		auto ComponentType = m_DmenuComponentTypeMap.find(vftablePtr);
		if (ComponentType != m_DmenuComponentTypeMap.end()) {
			return ComponentType->second;
		}

		return DmenuComponentType::Unknown;
	}

	void NdDevMenu::AppendSdkDevMenus(DMENU::Menu* RootMenu, DMENU::Menu* CustomMenu) {
		//always_assert(CustomMenu == nullptr, "CustomMenu pointer was not set!");
		// will find the best place for Custom Dev Menus!
	}

	void NdDevMenu::OnGameInitialized(bool successful) {
		if (successful) {
			auto& DMENU = GetSharedComponents()->
				GetComponent<NdDevMenu>()->m_EngineComponents->m_ndConfig.GetDmenu();

			auto DevMenu = DMENU.DevMenu()->RootMenu();
			DevMenu->SetName((DevMenu->Name() + std::format(" [{}]", SDK_NAME)).c_str());
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

			const unsigned char mov_ecx_0[] = { 0xb9, 0x00, 0x00, 0x00, 0x00, 0x90 };

			findpattern = Patterns::NdDevMenu_GameConfig_DevMode;
			m_GameConfig_DevModePatch = Utility::WritePatchPattern(module, findpattern.pattern, mov_ecx_0, sizeof(mov_ecx_0),
				wstr(Patterns::NdDevMenu_GameConfig_DevMode), findpattern.offset, m_cfg.GameDebugMenu);

			if (!m_GameConfig_DevModePatch) {
				throw SdkComponentEx{ "Failed to patch game functions!", SdkComponentEx::ErrorCode::PatchFailed };
			}

			if (m_GameConfig_DevModePatch->IsEnable()) {
				spdlog::info("GameDebugMenu is enabled!");

	#if defined(T1X)
				if (m_cfg.ExtendedDebugMenu && m_Memory->IsDebugMemoryAvailable()) {

					findpattern = Patterns::NdDevMenu_Assert_UpdateSelectRegionByNameMenu;
					m_Assert_UpdateSelectRegionByNameMenuPatch = Utility::WritePatchNop(module, findpattern.pattern, 0x1,
						wstr(Patterns::NdDevMenu_Assert_UpdateSelectRegionByNameMenu), findpattern.offset);

					findpattern = Patterns::NdDevMenu_Assert_UpdateSelectIgcByNameMenu;
					m_Assert_UpdateSelectIgcByNameMenuPatch = Utility::WritePatchNop(module, findpattern.pattern, 0x1,
						wstr(Patterns::NdDevMenu_Assert_UpdateSelectIgcByNameMenu), findpattern.offset);

					findpattern = Patterns::NdDevMenu_Assert_UpdateSelectSpawnerByNameMenu;
					m_Assert_UpdateSelectSpawnerByNameMenuPatch = Utility::WritePatchNop(module, findpattern.pattern, 0x1,
						wstr(Patterns::NdDevMenu_Assert_UpdateSelectSpawnerByNameMenu), findpattern.offset);

					spdlog::info("ExtendedDebugMenu is enabled!");
				}
	#endif

				findpattern = Patterns::NdDevMenu_DMENU_MenuGroup_SetRootMenu;
				auto SetRootMenuJMP = (void*)Utility::FindAndPrintPattern(module
					, findpattern.pattern, wstr(Patterns::NdDevMenu_DMENU_MenuGroup_SetRootMenu), findpattern.offset + 0x93);

				findpattern = Patterns::NdDevMenu_DMENU_Menu;
				DMENU_Menu = (DMENU_Menu_ptr)Utility::FindAndPrintPattern(module,
					findpattern.pattern, wstr(Patterns::NdDevMenu_DMENU_Menu), findpattern.offset);

				findpattern = Patterns::NdDevMenu_DMENU_Menu_AppendComponent;
				DMENU_Menu_AppendComponent = (DMENU_Menu_AppendComponent_ptr)Utility::FindAndPrintPattern(module,
					findpattern.pattern, wstr(Patterns::NdDevMenu_DMENU_Menu_AppendComponent), findpattern.offset);

				findpattern = Patterns::NdDevMenu_DMENU_ItemSubmenu;
				DMENU_ItemSubmenu = (DMENU_ItemSubmenu_ptr)Utility::FindAndPrintPattern(module,
					findpattern.pattern, wstr(Patterns::NdDevMenu_DMENU_ItemSubmenu), findpattern.offset);

				if (!SetRootMenuJMP ||
					!DMENU_Menu ||
					!DMENU_Menu_AppendComponent ||
					!DMENU_ItemSubmenu) {
					throw SdkComponentEx{ std::format("Failed to find {}:: game functions!", GetName()), SdkComponentEx::ErrorCode::PatternFailed };
				}

				findpattern = Patterns::NdDevMenu_DMENU_Component;
				DMENU::Component::VTable = (regenny::shared::ndlib::debug::DMENU::Component::VTable*)Utility::ReadLEA32(module,
					findpattern.pattern, wstr(Patterns::NdDevMenu_DMENU_Component), findpattern.offset + 0x1a, 3, 7);

				findpattern = Patterns::NdDevMenu_DMENU_MenuGroup;
				DMENU::MenuGroup::VTable = (regenny::shared::ndlib::debug::DMENU::MenuGroup::VTable*)Utility::ReadLEA32(module,
					findpattern.pattern, wstr(Patterns::NdDevMenu_DMENU_MenuGroup), findpattern.offset + 0x1b, 3, 7);

				findpattern = Patterns::NdDevMenu_DMENU_Menu;
				DMENU::Menu::VTable =  (regenny::shared::ndlib::debug::DMENU::Menu::VTable*)Utility::ReadLEA32(module,
					findpattern.pattern, wstr(Patterns::NdDevMenu_DMENU_Menu), findpattern.offset + 0x15, 3, 7);

				findpattern = Patterns::NdDevMenu_DMENU_ItemLine;
				DMENU::ItemLine::VTable = (regenny::shared::ndlib::debug::DMENU::ItemLine::VTable*)Utility::ReadLEA32(module,
					findpattern.pattern, wstr(Patterns::NdDevMenu_DMENU_ItemLine), findpattern.offset + 0x5A, 3, 7);

				findpattern = Patterns::NdDevMenu_DMENU_ItemSubmenu;
				DMENU::ItemSubmenu::VTable = (regenny::shared::ndlib::debug::DMENU::ItemSubmenu::VTable0*)Utility::ReadLEA32(module,
					findpattern.pattern, wstr(Patterns::NdDevMenu_DMENU_ItemSubmenu), findpattern.offset + 0x34, 3, 7);

				findpattern = Patterns::NdDevMenu_DMENU_ItemBool;
				DMENU::ItemBool::VTable = (regenny::shared::ndlib::debug::DMENU::ItemBool::VTable0*)Utility::ReadLEA32(module,
					findpattern.pattern, wstr(Patterns::NdDevMenu_DMENU_ItemBool), findpattern.offset + 0x2b, 3, 7);

				findpattern = Patterns::NdDevMenu_DMENU_ItemDouble;
				DMENU::ItemDouble::VTable = (regenny::shared::ndlib::debug::DMENU::ItemDouble::VTable0*)Utility::ReadLEA32(module,
					findpattern.pattern, wstr(Patterns::NdDevMenu_DMENU_ItemDouble), findpattern.offset + 0x50, 3, 7);

				findpattern = Patterns::NdDevMenu_DMENU_ItemFloat;
				DMENU::ItemFloat::VTable = (regenny::shared::ndlib::debug::DMENU::ItemFloat::VTable0*)Utility::ReadLEA32(module,
					findpattern.pattern, wstr(Patterns::NdDevMenu_DMENU_ItemFloat), findpattern.offset + 0x61, 3, 7);

				findpattern = Patterns::NdDevMenu_DMENU_ItemFunction;
				DMENU::ItemFunction::VTable = (regenny::shared::ndlib::debug::DMENU::ItemFunction::VTable0*)Utility::ReadLEA32(module,
					findpattern.pattern, wstr(Patterns::NdDevMenu_DMENU_ItemFunction), findpattern.offset + 0x25, 3, 7);

				findpattern = Patterns::NdDevMenu_DMENU_ItemSelection;
				DMENU::ItemSelection::VTable = (regenny::shared::ndlib::debug::DMENU::ItemSelection::VTable0*)Utility::ReadLEA32(module,
					findpattern.pattern, wstr(Patterns::NdDevMenu_DMENU_ItemSelection), findpattern.offset + 0x35, 3, 7);

				findpattern = Patterns::NdDevMenu_DMENU_ItemSubText;
				DMENU::ItemSubText::VTable = (regenny::shared::ndlib::debug::DMENU::ItemSubText::VTable0*)Utility::ReadLEA32(module,
					findpattern.pattern, wstr(Patterns::NdDevMenu_DMENU_ItemSubText), findpattern.offset + 0x35, 3, 7);

				if (!DMENU::Component::VTable ||
					!DMENU::MenuGroup::VTable ||
					!DMENU::Menu::VTable || 
					!DMENU::ItemLine::VTable ||
					!DMENU::ItemSubmenu::VTable ||
					!DMENU::ItemBool::VTable ||
					!DMENU::ItemDouble::VTable ||
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
					{ reinterpret_cast<uintptr_t>(DMENU::ItemDouble::VTable), DmenuComponentType::ItemDouble },
					{ reinterpret_cast<uintptr_t>(DMENU::ItemFloat::VTable), DmenuComponentType::ItemFloat },
					{ reinterpret_cast<uintptr_t>(DMENU::ItemFunction::VTable), DmenuComponentType::ItemFunction },
					{ reinterpret_cast<uintptr_t>(DMENU::ItemSelection::VTable), DmenuComponentType::ItemSelection },
					{ reinterpret_cast<uintptr_t>(DMENU::ItemSubText::VTable), DmenuComponentType::ItemSubText },
				};

				m_CommonGame->e_GameInitialized.Subscribe(this,&NdDevMenu::OnGameInitialized);

				m_SetRootMenuHook = Utility::MakeMidHook(SetRootMenuJMP,
					[](SafetyHookContext& ctx)
					{
						auto NdDevMenuComponent = GetSharedComponents()->GetComponent<NdDevMenu>();
						DMENU::MenuGroup* NdDevMenu = &NdDevMenuComponent->m_EngineComponents->m_ndConfig.GetNdDevMenu();

						DMENU::MenuGroup* MenuGroup = reinterpret_cast<DMENU::MenuGroup*>(ctx.rdi);
						DMENU::Menu* Menu = reinterpret_cast<DMENU::Menu*>(ctx.rbx);

						NdDevMenuComponent->InvokeSdkEvent(NdDevMenuComponent->e_AppendMenuGroup, NdDevMenuComponent.get(), MenuGroup);
						
						if (MenuGroup == NdDevMenu) {
							AppendSdkDevMenuCallback AppendCallback = boost::bind(&NdDevMenu::AppendSdkDevMenus, NdDevMenuComponent ,MenuGroup->RootMenu(), boost::placeholders::_1);
							NdDevMenuComponent->InvokeSdkEvent(NdDevMenuComponent->e_AppendSdkMenu, NdDevMenuComponent.get(), AppendCallback);

							//Test
							auto _menu = NdDevMenuComponent->Create_DMENU_Menu("TEST MENU", HeapArena_Source);
							NdDevMenuComponent->Create_DMENU_ItemSubmenu(_menu->Name(), MenuGroup->RootMenu(), _menu, nullptr, 0x0, "Test menu", HeapArena_Source);
						}

					}, wstr(Patterns::NdDevMenu_DMENU_MenuGroup_SetRootMenu), wstr(SetRootMenuJMP));
			}
		});
	}
}