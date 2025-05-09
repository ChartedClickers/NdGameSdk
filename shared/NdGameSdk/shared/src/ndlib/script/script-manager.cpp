#include "script-manager.hpp"
#include "./NdGameSdk/shared/sharedpatterns.hpp"
#include <NdGameSdk/shared/src/gamelib/debug/nd-dev-menu.hpp>

using namespace boost::placeholders;
using namespace NdGameSdk::gamelib::debug;

namespace NdGameSdk::ndlib::script {

	ScriptManager::ScriptManager() : ISdkComponent(TOSTRING(ScriptManager)) {}

	void ScriptManager::Awake() {
		auto SharedComponents = ISdkComponent::GetSharedComponents();
        m_Memory = SharedComponents->GetComponent<Memory>();
        m_NdDevMenu = SharedComponents->GetComponent<NdDevMenu>();
        m_CommonGame = SharedComponents->GetComponent<CommonGame>();
	}

	void ScriptManager::Initialize()
	{
		static std::once_flag Initialized;
		std::call_once(Initialized, [this] {

			spdlog::info("Initializing {} patterns...", GetName());

			Patterns::SdkPattern findpattern{};
			auto module = Utility::memory::get_executable();

			findpattern = Patterns::ScriptManager_g_ScriptManagerGlobals;
			g_ScriptManagerGlobals = (ScriptManagerGlobals*)Utility::ReadLEA32(module,
				findpattern.pattern, wstr(Patterns::ScriptManager_g_ScriptManagerGlobals), findpattern.offset, 3, 7);

            findpattern = Patterns::ScriptManager_InitializeReturn;
            auto ScriptManagerInitJMP = (void*)Utility::FindAndPrintPattern(module
                , findpattern.pattern, wstr(Patterns::ScriptManager_InitializeReturn), findpattern.offset);

			if (!g_ScriptManagerGlobals ||
                !ScriptManagerInitJMP) {
				throw SdkComponentEx
				{ std::format("Failed to find addresses!"),
					SdkComponentEx::ErrorCode::PatternFailed };
			}

            m_ScriptManagerInitHook = Utility::MakeMidHook(ScriptManagerInitJMP, ScriptManagerInitialized, 
                wstr(Patterns::ScriptManager_InitializeReturn), wstr(ScriptManagerInitJMP));

            if (!m_ScriptManagerInitHook) {
                throw SdkComponentEx{ "Failed to create hooks!", SdkComponentEx::ErrorCode::PatchFailed };
            }

            m_Memory->IncreaseMemoryMap(MemoryMapId::ALLOCATION_DMENU_LOWMEM, MemSize(6.2, SizeUnit::Megabytes));

		});
	}

    void ScriptManager::ScriptManagerInitialized(SafetyHookContext& ctx) {
        ScriptManager* ScriptMgr = Instance<ScriptManager>();

        ScriptMgr->InvokeSdkEvent(ScriptMgr->e_ScriptManagerInitialized);
        return;
    }

    bool ScriptManager::RefreshScriptCFuncInfo(bool UpdateSidBase = false) {

        auto logger = SdkLogger::GetLogger();

        if (!NdGameSdk::DB::IsDataBaseAvailable()) {
            logger->warn("[{}] Database is not available!", TOSTRING(ScriptManager));
            return false;
        }

        try {

            logger->info("[{}] Refreshing ScriptCFunc info...", TOSTRING(ScriptManager));

            auto nativeDump = g_ScriptManagerGlobals->DumpNativeFunctions();
            m_ScriptCFuncs = NdGameSdk::DB::Get<std::map<StringId64, ScriptCFuncInfo>>(
                s_DataBaseFile, "ScriptCFuncs", m_ScriptCFuncs);

            bool changed = false;

            if (UpdateSidBase && NdGameSdk::Sidbase::g_bSidbaseAvailable) {
                for (auto& [hash, info] : m_ScriptCFuncs) {
                    std::string newName = NdGameSdk::Sidbase::StringIdToStringInternal(hash);
                    if (info.Name != newName) {
                        info.Name = std::move(newName);
                        logger->warn("[{}] Updated ScriptCFunc name: {} (hash: {:#x})", TOSTRING(ScriptManager), info.Name, hash);
                        changed = true;
                    }
                }
            }

            for (auto& native : nativeDump) {
                auto [it, inserted] = m_ScriptCFuncs.try_emplace(native.hash, ScriptCFuncInfo{});
                if (inserted) {
                    auto& info = it->second;
                    info.Name = NdGameSdk::Sidbase::StringIdToStringInternal(native.hash);
                    info.Hash = native.hash;
                    logger->debug("[{}] Found new ScriptCFunc: {} (hash: {:#x})", TOSTRING(ScriptManager), info.Name, native.hash);
                    changed = true;
                }
            }

            if (changed) {
                NdGameSdk::DB::Set(s_DataBaseFile, "ScriptCFuncs", m_ScriptCFuncs);
                NdGameSdk::DB::FlushJsonFile(s_DataBaseFile);
                logger->info("[{}] ScriptCFuncs updated ({} entries cached)", TOSTRING(ScriptManager), m_ScriptCFuncs.size());
                return true;
            }

            logger->debug("[{}] No updates needed for ScriptCFuncs", TOSTRING(ScriptManager));
            return true;
		}
        catch (const std::exception& e) {
            logger->error("[{}] Error while refreshing ScriptCFunc info: {}", TOSTRING(ScriptManager), e.what());
            return false;
        }
    }

    bool ScriptManager::TestFunct(DMENU::ItemFunction& pFunction, DMENU::Message pMessage) {
        if (pMessage == DMENU::Message::OnExecute) {
            auto ScriptMgr = reinterpret_cast<ScriptManager*>(pFunction.Data());
            if (ScriptMgr) {
                spdlog::info("TestFunct called!");
                return true;
            }
        }
        return true;
    }

    DMENU::ItemSubmenu* ScriptManager::CreateScriptManagerMenu(NdDevMenu* pdmenu, DMENU::Menu* pMenu) {
        ScriptManager* ScriptMgr = Instance<ScriptManager>();
        if (ScriptMgr) {
            uint64_t ScriptMgrAddr = reinterpret_cast<uint64_t>(static_cast<void*>(ScriptMgr));

            DMENU::Menu* ScriptManagerMenu = pdmenu->Create_DMENU_Menu(TOSTRING(ScriptManager), HeapArena_Source);
            if (ScriptManagerMenu) {

                pdmenu->Create_DMENU_ItemFunction("Test funct", ScriptManagerMenu, &TestFunct, ScriptMgrAddr, false, HeapArena_Source);

                /*ScriptCFuncDebugMenu*/
                ScriptMgr->m_ScriptCFuncDebugMenu = pdmenu->Create_DMENU_Menu("ScriptCFuncs Debugging", HeapArena_Source);

                pdmenu->Create_DMENU_ItemSubmenu(ScriptMgr->m_ScriptCFuncDebugMenu->Name(), ScriptManagerMenu,
                    ScriptMgr->m_ScriptCFuncDebugMenu, OnUpdateScriptCFuncDebugMenu, ScriptMgrAddr, nullptr, HeapArena_Source);
                pdmenu->Create_DMENU_String("// ScriptCFuncDebugMenu [BETA]", ScriptMgr->m_ScriptCFuncDebugMenu, nullptr, HeapArena_Source);
                pdmenu->Create_DMENU_String(ScriptMgr->m_NativeTableEntriesText, ScriptMgr->m_ScriptCFuncDebugMenu, nullptr, HeapArena_Source);

                return pdmenu->Create_DMENU_ItemSubmenu(ScriptManagerMenu->Name(),
                    pMenu, ScriptManagerMenu, NULL, NULL, nullptr, HeapArena_Source);
            }
        }
        return nullptr;
    }

    bool ScriptManager::WrapScriptCFuncDebugMenu(DMENU::Menu* pMenu, ScriptCFuncDebugMenuProperties* pProperties) {
        ScriptManager* ScriptMgr = Instance<ScriptManager>();
		NdDevMenu* NdDevMenu = ScriptMgr->m_NdDevMenu.get();

        ScriptMgr->m_ScriptCFuncInput = nullptr;
        ScriptMgr->m_ScriptCFuncDebugMenuProperties.ScriptCFuncInfo = nullptr;

        static DMENU::ItemFunction::FunctionCallback bShowAllScriptCFuncs =
            +[](DMENU::ItemFunction& item, DMENU::Message msg)->bool {
            if (msg == DMENU::Message::OnExecute) {
                ScriptManager* ScriptMgr = Instance<ScriptManager>();

                if (ScriptMgr->m_Memory->GetMemSize(MemoryMapId::ALLOCATION_DMENU_LOWMEM) < MemSize(5, SizeUnit::Megabytes)) {
                    spdlog::error("[{}] Memory DMENU_LOWMEM size is not correct!", TOSTRING(ScriptManager));
                    return false;
                }

                auto MenuProperties = &ScriptMgr->m_ScriptCFuncDebugMenuProperties;
                MenuProperties->showAllScriptCFuncs = !MenuProperties->showAllScriptCFuncs;
                item.SetActive(MenuProperties->showAllScriptCFuncs);
                ScriptMgr->m_CFuncDebugRefresh = true;
                return true;
            }
            return true;
        };

        static DMENU::ItemSubmenu::SubmenuCallback CFuncDebugExecuteMenu =
            +[](DMENU::ItemSubmenu& pSubmenu, DMENU::Message msg)->bool {
            if (msg == DMENU::Message::OnExecute) {
                ScriptManager* ScriptMgr = Instance<ScriptManager>();                
                auto ScriptCFunc = ScriptMgr->m_ScriptCFuncs.find(StringId64{ pSubmenu.Data() });
				if (ScriptCFunc == ScriptMgr->m_ScriptCFuncs.end()) {
					spdlog::error("[{}] ScriptCFunc {:#x} not found!", TOSTRING(ScriptManager), pSubmenu.Data());
                    ScriptMgr->m_ScriptCFuncDebugMenuProperties.ScriptCFuncInfo = nullptr;
                }
                else {
                    ScriptMgr->m_ScriptCFuncDebugMenuProperties.ScriptCFuncInfo = &ScriptCFunc->second;
                }

                ScriptMgr->m_NdDevMenu->RebuildMenu(pSubmenu.MenuEntry(), false, { &WrapScriptCFuncExecutorMenu }, HeapArena_Source,
                    &ScriptMgr->m_ScriptCFuncDebugMenuProperties, false);
                return true;
            }
            return true;
        };

        NdDevMenu->Create_DMENU_ItemLine(pMenu, HeapArena_Source);
        NdDevMenu->Create_DMENU_ItemFunction("Show All ScriptCFuncs", pMenu, bShowAllScriptCFuncs, 0x0, 
            pProperties->showAllScriptCFuncs, HeapArena_Source);
		NdDevMenu->Create_DMENU_ItemBool("Update Sidbase", pMenu, &pProperties->UpdateSidBase, "Update Sidbase for ScriptCFunc names", HeapArena_Source);
		NdDevMenu->Create_DMENU_ItemBool("Refresh ScriptCFunc", pMenu, &ScriptMgr->m_CFuncDebugRefreshData, "Refresh ScriptCFunc info", HeapArena_Source);
        NdDevMenu->Create_DMENU_ItemFunction("Force Save DataBase", pMenu,
            +[](DMENU::ItemFunction& pFunction, DMENU::Message pMessage)->bool {
                if (pMessage == DMENU::Message::OnExecute) {
                    ScriptManager* ScriptMgr = Instance<ScriptManager>();
					return DB::FlushJsonFile(ScriptMgr->s_DataBaseFile);
                }
                return true;
            }, 0x0, false, HeapArena_Source);

        if (!pProperties->showAllScriptCFuncs) {
            ScriptMgr->m_ScriptCFuncInput = NdDevMenu->Create_DMENU_KeyBoard("ScriptCFunc", pMenu,
                pProperties->ScriptCFuncInputText, sizeof(pProperties->ScriptCFuncInputText), nullptr, HeapArena_Source);
            WrapScriptCFuncExecutorMenu(pMenu, pProperties);
            return true;
        } else {
            ScriptMgr->m_ScriptCFuncDebugExecuteMenu = NdDevMenu->Create_DMENU_Menu("ScriptCFunc Executor", HeapArena_Source);
            NdDevMenu->Create_DMENU_TextLineWrapper("ScriptCFunc Executor", pMenu, HeapArena_Source);
			for (auto& [hash, info] : ScriptMgr->m_ScriptCFuncs) {
                NdDevMenu->Create_DMENU_ItemSubmenu(info.Name, pMenu,
                    ScriptMgr->m_ScriptCFuncDebugExecuteMenu, CFuncDebugExecuteMenu, info.Hash, nullptr, HeapArena_Source);
			}
            return true;
        }

        return false;
    }

    bool ScriptManager::WrapScriptCFuncExecutorMenu(DMENU::Menu* pMenu, ScriptCFuncDebugMenuProperties* pProperties, bool pSwitchMode) {
        ScriptManager* ScriptMgr = Instance<ScriptManager>();
        NdDevMenu* NdDevMenu = ScriptMgr->m_NdDevMenu.get();

        static auto ExecutorModeHandler = &ScriptManager::OnExecuteRebuild<DMENU::ItemSelection>;
        static auto ArgumentsHandler = &ScriptManager::OnExecuteRebuild<DMENU::ItemDecimal>;

        ScriptCFuncInfo* CFuncInfo = pProperties->ScriptCFuncInfo;
		static bool RebuildExecutorMenu = false;
        if (!pSwitchMode) {

            if (pMenu != ScriptMgr->m_ScriptCFuncDebugExecuteMenu) {
                NdDevMenu->Create_DMENU_TextLineWrapper("ScriptCFunc Executor", pMenu, HeapArena_Source);
            }

            if (CFuncInfo != nullptr) {
                std::string formattedText = std::vformat("// ScriptCFunc: {} (hash: {:#x})",
                    std::make_format_args(CFuncInfo->Name, CFuncInfo->Hash));
                NdDevMenu->Create_DMENU_String(formattedText, pMenu, nullptr, HeapArena_Source);
                if (!CFuncInfo->Description.empty()) {
                    std::string formattedDesc = std::vformat("// Description: {}", std::make_format_args(CFuncInfo->Description));
                    NdDevMenu->Create_DMENU_String(formattedDesc, pMenu, nullptr, HeapArena_Source);
                }

                NdDevMenu->Create_DMENU_ItemSelection("Mode", pMenu, ScriptCFuncDebugMode_selection, ExecutorModeHandler,
                    (uint64_t*)&pProperties->ScriptCFuncDebugMode, nullptr, HeapArena_Source);
            } else {
                NdDevMenu->Create_DMENU_String("// No ScriptCFunc selected", pMenu, nullptr, HeapArena_Source)->SetColor(BasicColors::Yellow);
                return false;
            }
        }

        if (CFuncInfo != nullptr) {

            if(pProperties->ScriptCFuncDebugMode != ScriptCFuncDebugMode::Editor)
				RebuildExecutorMenu = false;

            switch (pProperties->ScriptCFuncDebugMode)
            {
			case ScriptCFuncDebugMode::Execute: {

                if (!CFuncInfo->Args.empty()) {
                    NdDevMenu->Create_DMENU_ItemLine(pMenu, HeapArena_Source);

                    for (auto& arg : CFuncInfo->Args) {
                        switch (arg.Type)
                        {
                        case ScriptCFuncInfo::TypeOf::Bool: {
                            NdDevMenu->Create_DMENU_ItemBool(arg.Name, pMenu, (bool*)arg.Data, arg.Description.c_str(), HeapArena_Source);
                            break;
                        }
                        case ScriptCFuncInfo::TypeOf::Int: {
                            NdDevMenu->Create_DMENU_ItemDecimal(arg.Name, pMenu, (int*)arg.Data, { 0, 5000 }, { 1, 2 }, arg.Description.c_str(), HeapArena_Source);
                            break;
                        }
                        case ScriptCFuncInfo::TypeOf::Float: {
                            NdDevMenu->Create_DMENU_ItemFloat(arg.Name, pMenu, (float*)arg.Data, { 0.0f, 5000.0f }, { 0.1f, 5.0f }, arg.Description.c_str(), HeapArena_Source);
                            break;
                        }
                        case ScriptCFuncInfo::TypeOf::StringId:
                        case ScriptCFuncInfo::TypeOf::String: {
                        default:
                            NdDevMenu->Create_DMENU_KeyBoard(arg.Name, pMenu, (char*)arg.Data, 100, arg.Description.c_str(), HeapArena_Source);
                            break;
                        }
                        }
                    }
                }

                NdDevMenu->Create_DMENU_String("Execute", pMenu, nullptr, HeapArena_Source);
				break;
			}
            case ScriptCFuncDebugMode::Editor: {

                if (!pProperties->CFuncEditor) { 
                    pProperties->CFuncEditor = std::make_unique<ScriptCFuncDebugMenuProperties::ScriptCFuncEditor>(); 
                }

                auto CFuncEditor = pProperties->CFuncEditor.get();

                if (!RebuildExecutorMenu) {

                    SyncCFuncEditorBuffers(*CFuncInfo, *CFuncEditor, true);
                    NdDevMenu->Create_DMENU_ItemLine(pMenu, HeapArena_Source);
                    NdDevMenu->Create_DMENU_KeyBoard("Description", pMenu, CFuncEditor->DescriptionBuf, sizeof(CFuncEditor->DescriptionBuf), nullptr, HeapArena_Source);
                    NdDevMenu->Create_DMENU_ItemDecimal("Arguments", pMenu, &CFuncEditor->NumArgs, { 0, 10 }, { 1, 1 }, nullptr, HeapArena_Source)
                        ->SetHandler((DMENU::ItemDecimal::DecimalHandler*)ArgumentsHandler);
					RebuildExecutorMenu = true;
                }

                CFuncEditor->EditedArgs.resize(CFuncEditor->NumArgs);
                for (int i = 0; i < CFuncEditor->NumArgs; i++) {
					auto& arg = CFuncEditor->EditedArgs[i];

                    NdDevMenu->Create_DMENU_ItemSubText(std::vformat("Argument {}",
                        std::make_format_args(i)), pMenu, HeapArena_Source);

                    NdDevMenu->Create_DMENU_KeyBoard("Name", pMenu, arg.Name, sizeof(arg.Name), nullptr, HeapArena_Source);
                    NdDevMenu->Create_DMENU_KeyBoard("Description", pMenu, arg.Description, sizeof(arg.Description), nullptr, HeapArena_Source);
                    NdDevMenu->Create_DMENU_ItemSelection("Type", pMenu, ScriptCFuncTypeOf_selection, 0x0, (uint64_t*)&arg.type, nullptr, HeapArena_Source);

                }

                NdDevMenu->Create_DMENU_ItemLine(pMenu, HeapArena_Source);
				NdDevMenu->Create_DMENU_ItemFunction("SAVE", pMenu, 
                    +[](DMENU::ItemFunction& pFunction, DMENU::Message pMessage)->bool {
					if (pMessage == DMENU::Message::OnExecute) {
                        ScriptManager* ScriptMgr = Instance<ScriptManager>();
                        ScriptCFuncInfo* CFuncInfo = ScriptMgr->m_ScriptCFuncDebugMenuProperties.ScriptCFuncInfo;
                        auto* CFuncEditor = reinterpret_cast<ScriptCFuncDebugMenuProperties::ScriptCFuncEditor*>(pFunction.Data());

						if (CFuncInfo && CFuncEditor) {
                            SyncCFuncEditorBuffers(*CFuncInfo, *CFuncEditor, false); 
                            NdGameSdk::DB::Set(s_DataBaseFile, "ScriptCFuncs", ScriptMgr->m_ScriptCFuncs);
                            return true;
						}
                        return false;
					}
					return true;
					}, reinterpret_cast<uint64_t>(pProperties->CFuncEditor.get()), false, HeapArena_Source);
                break;
            }
            default:
                return false;
            }
        }

        return true;
    }

    void ScriptManager::SyncCFuncEditorBuffers(ScriptCFuncInfo& CFuncInfo, 
        ScriptCFuncDebugMenuProperties::ScriptCFuncEditor& CFuncEditor,
        bool toEditor
    ) {
        if (toEditor) {

            std::strncpy(CFuncEditor.DescriptionBuf,
                CFuncInfo.Description.c_str(),
                sizeof(CFuncEditor.DescriptionBuf) - 1);
            CFuncEditor.DescriptionBuf[sizeof(CFuncEditor.DescriptionBuf) - 1] = '\0';

            CFuncEditor.EditedArgs.clear();
            CFuncEditor.NumArgs = static_cast<int>(CFuncInfo.Args.size());
            if (!CFuncInfo.Args.empty()) {
                CFuncEditor.EditedArgs.resize(CFuncInfo.Args.size());
                for (size_t i = 0; i < CFuncInfo.Args.size(); ++i) {
                    auto const& src = CFuncInfo.Args[i];
                    auto& dst = CFuncEditor.EditedArgs[i];

                    std::strncpy(dst.Name,
                        src.Name.c_str(),
                        sizeof(dst.Name) - 1);
                    dst.Name[sizeof(dst.Name) - 1] = '\0';

                    std::strncpy(dst.Description,
                        src.Description.c_str(),
                        sizeof(dst.Description) - 1);
                    dst.Description[sizeof(dst.Description) - 1] = '\0';

                    dst.type = src.Type;
                }
            }
        }
        else {
            CFuncInfo.Description.assign(CFuncEditor.DescriptionBuf);
            CFuncInfo.Args.clear();
            CFuncInfo.Args.reserve(CFuncEditor.EditedArgs.size());
            for (auto const& e : CFuncEditor.EditedArgs) {
                ScriptCFuncInfo::Arguments a;
                a.Type = e.type;
                a.Name = e.Name;
                a.Description = e.Description;
                CFuncInfo.Args.push_back(std::move(a));
            }
        }
    }


    bool ScriptManager::OnUpdateScriptCFuncDebugMenu(DMENU::ItemSubmenu& pSubMenu, DMENU::Message pMessage) {

        ScriptManager* ScriptMgr = reinterpret_cast<ScriptManager*>(pSubMenu.Data());
        ScriptCFuncDebugMenuProperties* MenuProperties = &ScriptMgr->m_ScriptCFuncDebugMenuProperties;
		
        static bool IsMenuInit = false;
        static bool CFuncExecutorUpdate = false;
		const int CFuncDebugMenuStart = 0x1;

        DMENU::Menu* pMenu = pSubMenu.MenuEntry();

        switch (pMessage) {
        case DMENU::Message::OnUpdate: {

            if (pMenu->IsActive()) {
                if (ScriptMgr->m_CFuncDebugRefresh) {
                    ScriptMgr->m_CFuncDebugRefresh = false;
                    if (!ScriptMgr->m_ScriptCFuncs.empty()) {
                        pMenu->SetPagePointer(0);
                        ScriptMgr->m_NdDevMenu->RebuildMenuFromComponent(pMenu, pMenu->GetComponent(CFuncDebugMenuStart),
                            { &WrapScriptCFuncDebugMenu }, HeapArena_Source, MenuProperties);
                    }
                    else {
						ScriptMgr->m_CFuncDebugRefreshData = true;
                    }
                }
                else if (ScriptMgr->m_CFuncDebugRefreshData) {

                    ScriptMgr->m_Memory->PushAllocator(MemoryContextType::kAllocDevMenuLowMem, HeapArena_Source);
                    for (auto* component : pMenu->GetComponent(CFuncDebugMenuStart)->GetNextComponentsRange()) {
                        pMenu->DeleteItem(component);
                    }

                    ScriptMgr->m_NdDevMenu->Create_DMENU_String("DataBase is loading...", pMenu, nullptr, HeapArena_Source);
                    ScriptMgr->m_CFuncDebugRefreshData = false;
                    std::thread([=]() mutable {
                        if (ScriptMgr->RefreshScriptCFuncInfo(MenuProperties->UpdateSidBase))
                            ScriptMgr->m_CFuncDebugRefresh = true;
                        }).detach();

                    ScriptMgr->m_Memory->PopAllocator();
                }

                if (ScriptMgr->m_ScriptCFuncInput && !MenuProperties->showAllScriptCFuncs) {

                    auto& KeyBoard = *ScriptMgr->m_ScriptCFuncInput;

					// Not perfect cuz need to fix some issues with the NdDevMode keyboard
					// implemented for demonstration of real-time input
                    if (KeyBoard.HasInputSettled()) {
                        auto text = KeyBoard.GetInputBuffer();
                        if (text && *text) {
                            if (auto info = ScriptMgr->FindScriptCFuncByInput(text)) {
                                MenuProperties->ScriptCFuncInfo = info;
                                KeyBoard.SetColor(BasicColors::Green);
                            }
                            else {
                                MenuProperties->ScriptCFuncInfo = nullptr;
                                KeyBoard.SetColor(BasicColors::Red);
                            }

                            CFuncExecutorUpdate = true;
                        }

                    } else if (CFuncExecutorUpdate && !KeyBoard.GetState().isEditing) {
                        ScriptMgr->m_NdDevMenu->RebuildMenuFromComponent(pMenu, &KeyBoard,
                            { &WrapScriptCFuncExecutorMenu }, HeapArena_Source, MenuProperties, false);
                        CFuncExecutorUpdate = false;
                    }
                }
            }
			
            return true;
        }
		case DMENU::Message::OnExecute: {
            if (!IsMenuInit) {
                ScriptMgr->m_Memory->PushAllocator(MemoryContextType::kAllocDevMenuLowMem, HeapArena_Source);

                auto FunctionsNums = ScriptMgr->g_ScriptManagerGlobals->GetNativeMap()->m_FunctionsNum;
                std::string formattedText = std::vformat(ScriptMgr->m_NativeTableEntriesText, std::make_format_args(FunctionsNums));

                pMenu->GetComponent<DMENU::String>(1)->ChangeName(formattedText.c_str());
                ScriptMgr->m_NdDevMenu->Create_DMENU_String("ScriptCFuncs is loading...", pMenu, nullptr, HeapArena_Source);

                ScriptMgr->m_Memory->PopAllocator();
                ScriptMgr->m_CFuncDebugRefresh = true;
                IsMenuInit = true;
            }
            else if (MenuProperties->showAllScriptCFuncs) {
                pMenu->SetPagePointer(0);
            }
			return true;
		}
		case DMENU::Message::OnClose: {
			if (MenuProperties->CFuncEditor && !pMenu->IsActive()) {
				MenuProperties->CFuncEditor.reset();
			}
			return true;
		}
        case DMENU::Message::OnSaveConfig: {
            return false;
        }
        default:
            return true;
        }

    }

    ScriptCFuncInfo* ScriptManager::FindScriptCFuncByInput(const char* input) {
        if (!input || *input == '\0') {
            return nullptr;
        }

        std::string_view sv{ input };

        if (sv.size() > 2 && (sv.rfind("0x", 0) == 0 || sv.rfind("0X", 0) == 0)) {
            auto hexPart = sv.substr(2);
            uint64_t hash = 0;
            try {
                hash = std::stoull(std::string(hexPart), nullptr, 16);
            }
            catch (...) {
                return nullptr;
            }

            auto it = m_ScriptCFuncs.find(StringId64{ hash });
            return it != m_ScriptCFuncs.end() ? &it->second : nullptr;
        }

        for (auto& kv : m_ScriptCFuncs) {
            if (kv.second.Name == sv)
                return &kv.second;
        }

        return nullptr;
    }

    std::vector<ScriptManagerGlobals::NativeFuncEntry> ScriptManagerGlobals::DumpNativeFunctions() {

        std::vector<NativeFuncEntry> Dump{};

        auto NativeMap = GetNativeMap();
        if (!NativeMap) {
            spdlog::error("[{}] NativeMap is null", TOSTRING(ScriptManager));
            return Dump;
        }

        spdlog::info("[{}] Native table contains {} entries", TOSTRING(ScriptManager), NativeMap->m_FunctionsNum);

        const auto num = static_cast<std::size_t>(NativeMap->m_FunctionsNum);
        auto* base = reinterpret_cast<const NativeFuncEntry*>(NativeMap->m_FunctionsBaseAddress);

        if (base == nullptr || num == 0) {
            spdlog::warn("[{}] Native table is empty", TOSTRING(ScriptManager));
            return Dump;
        }

        Dump.reserve(num);
        for (std::size_t i = 0; i < num; ++i) {
            Dump.emplace_back(base[i]);
        }

        return Dump;
    }

    ScriptManagerGlobals::ScriptCFuncMap* ScriptManagerGlobals::GetNativeMap() {
        return this->Get()->m_NativeMap;
    }

    std::string ScriptManager::s_DataBaseFile{"ScriptManager.json"};
}