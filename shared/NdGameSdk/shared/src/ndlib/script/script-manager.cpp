#include "script-manager.hpp"
#include "./NdGameSdk/shared/sharedpatterns.hpp"
#include <NdGameSdk/shared/src/gamelib/debug/nd-dev-menu.hpp>

using namespace NdGameSdk::gamelib::debug;

namespace NdGameSdk::ndlib::script {

	ScriptManager::ScriptManager() : ISdkComponent(TOSTRING(ScriptManager)) {}

	void ScriptManager::Awake() {
		auto SharedComponents = ISdkComponent::GetSharedComponents();
        m_Memory = GetDependencyComponent<Memory>(SharedComponents);
        m_NdDevMenu = GetDependencyComponent<NdDevMenu>(SharedComponents);
        m_CommonGame = GetDependencyComponent<CommonGame>(SharedComponents);
	}

	void ScriptManager::Initialize() {
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

            findpattern = Patterns::ScriptManager_InitializeModuleIndexReturn;
            auto InitializeModuleIndexJMP = (void*)Utility::FindAndPrintPattern(module
                , findpattern.pattern, wstr(Patterns::ScriptManager_InitializeModuleIndexReturn), findpattern.offset);

#if defined(T2R)
            findpattern = Patterns::ScriptManager_GetDebugModuleBucket;
            auto GetDebugModuleBucket = Utility::FindAndPrintPattern(module,
                findpattern.pattern, wstr(Patterns::ScriptManager_GetDebugModuleBucket), findpattern.offset);
#endif

			if (!g_ScriptManagerGlobals ||
                !ScriptManagerInitJMP ||
                !InitializeModuleIndexJMP
                #if defined(T2R)
                || !GetDebugModuleBucket
                #endif
                ) 
            {
				throw SdkComponentEx
				{ std::format("Failed to find addresses!"),
					SdkComponentEx::ErrorCode::PatternFailed };
			}

            findpattern = Patterns::ScriptManager_ScriptModuleAdd;
            ScriptManager_ScriptModuleAdd = (ScriptManager_ScriptModuleAdd_ptr)Utility::FindAndPrintPattern(module,
                findpattern.pattern, wstr(Patterns::ScriptManager_ScriptModuleAdd), findpattern.offset);
            
            findpattern = Patterns::ScriptManager_ScriptModuleRemove;
            ScriptManager_ScriptModuleRemove = (ScriptManager_ScriptModuleRemove_ptr)Utility::FindAndPrintPattern(module,
                findpattern.pattern, wstr(Patterns::ScriptManager_ScriptModuleRemove), findpattern.offset);

            findpattern = Patterns::ScriptManager_RemoveModule;
            ScriptManager_RemoveModule = (ScriptManager_RemoveModule_ptr)Utility::FindAndPrintPattern(module,
                findpattern.pattern, wstr(Patterns::ScriptManager_RemoveModule), findpattern.offset);

            findpattern = Patterns::ScriptManager_AddModuleInfo;
            ScriptManager_AddModuleInfo = (ScriptManager_AddModuleInfo_ptr)Utility::FindAndPrintPattern(module,
                findpattern.pattern, wstr(Patterns::ScriptManager_AddModuleInfo), findpattern.offset);

            findpattern = Patterns::ScriptManager_FindExportingModule;
            ScriptManager_FindExportingModule = (ScriptManager_FindExportingModule_ptr)Utility::FindAndPrintPattern(module,
                findpattern.pattern, wstr(Patterns::ScriptManager_FindExportingModule), findpattern.offset);

            findpattern = Patterns::ScriptManager_IsLoadModule;
            ScriptManager_IsLoadModule = (ScriptManager_IsLoadModule_ptr)Utility::FindAndPrintPattern(module,
                findpattern.pattern, wstr(Patterns::ScriptManager_IsLoadModule), findpattern.offset);

            findpattern = Patterns::ScriptManager_AddModuleRequest;
            ScriptManager_AddModuleRequest = (ScriptManager_AddModuleRequest_ptr)Utility::FindAndPrintPattern(module,
                findpattern.pattern, wstr(Patterns::ScriptManager_AddModuleRequest), findpattern.offset);

            findpattern = Patterns::ScriptManager_ReloadModule;
            ScriptManager_ReloadModule = (ScriptManager_ReloadModule_ptr)Utility::FindAndPrintPattern(module,
                findpattern.pattern, wstr(Patterns::ScriptManager_ReloadModule), findpattern.offset);

            findpattern = Patterns::ScriptManager_LoadModuleFromFile;
            ScriptManager_LoadModuleFromFile = (ScriptManager_LoadModuleFromFile_ptr)Utility::FindAndPrintPattern(module,
                findpattern.pattern, wstr(Patterns::ScriptManager_LoadModuleFromFile), findpattern.offset);

            findpattern = Patterns::ScriptManager_LookupSymbol;
            ScriptManager_LookupSymbol = (ScriptManager_LookupSymbol_ptr)Utility::FindAndPrintPattern(module,
                findpattern.pattern, wstr(Patterns::ScriptManager_LookupSymbol), findpattern.offset);

            findpattern = Patterns::ScriptManager_LookupInModule;
            ScriptManager_LookupInModule = (ScriptManager_LookupInModule_ptr)Utility::FindAndPrintPattern(module,
                findpattern.pattern, wstr(Patterns::ScriptManager_LookupInModule), findpattern.offset);

            findpattern = Patterns::ScriptManager_BindValue;
            ScriptManager_BindValue = (ScriptManager_BindValue_ptr)Utility::FindAndPrintPattern(module,
                findpattern.pattern, wstr(Patterns::ScriptManager_BindValue), findpattern.offset);

            findpattern = Patterns::ScriptManager_UnbindValue;
			ScriptManager_UnbindValue = (ScriptManager_UnbindValue_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::ScriptManager_UnbindValue), findpattern.offset);

			findpattern = Patterns::ScriptManager_ModuleInfo_LookupModuleByDcEntry;
			ModuleInfo_LookupModuleByDcEntry = (ModuleInfo_LookupModuleByDcEntry_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::ScriptManager_ModuleInfo_LookupModuleByDcEntry), findpattern.offset);

			findpattern = Patterns::ScriptManager_ModuleInfo_LookupDcEntry;
			ModuleInfo_LookupDcEntry = (ModuleInfo_LookupDcEntry_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::ScriptManager_ModuleInfo_LookupDcEntry), findpattern.offset);

            findpattern = Patterns::ScriptManager_ModuleInfo_FetchModule;
			ModuleInfo_FetchModule = (ModuleInfo_FetchModule_ptr)Utility::FindAndPrintPattern(module,
                findpattern.pattern, wstr(Patterns::ScriptManager_ModuleInfo_FetchModule), findpattern.offset);

			findpattern = Patterns::ScriptManager_ScriptModule_FetchScriptModuleEntry;
			ScriptModule_FetchScriptModuleEntry = (ScriptModule_FetchScriptModuleEntry_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::ScriptManager_ScriptModule_FetchScriptModuleEntry), findpattern.offset);

            if (!ScriptManager_ScriptModuleAdd ||
                !ScriptManager_ScriptModuleRemove ||
                !ScriptManager_RemoveModule ||
                !ScriptManager_AddModuleInfo ||
                !ScriptManager_FindExportingModule ||
                !ScriptManager_IsLoadModule ||
                !ScriptManager_AddModuleRequest ||
                !ScriptManager_ReloadModule ||
                !ScriptManager_LoadModuleFromFile ||
                !ScriptManager_LookupSymbol ||
                !ScriptManager_LookupInModule ||
                !ScriptManager_BindValue ||
                !ScriptManager_UnbindValue ||
                !ModuleInfo_LookupModuleByDcEntry ||
                !ModuleInfo_LookupDcEntry ||
				!ModuleInfo_FetchModule ||
                !ScriptModule_FetchScriptModuleEntry
            ) {
                throw SdkComponentEx{ std::format("Failed to find {}:: game functions!", GetName()), SdkComponentEx::ErrorCode::PatternFailed };
            }

            m_ScriptManagerInitHook = Utility::MakeMidHook(ScriptManagerInitJMP, ScriptManagerInitialized, 
                wstr(Patterns::ScriptManager_InitializeReturn), wstr(ScriptManagerInitJMP));

            m_InitializeModuleIndexHook = Utility::MakeMidHook(InitializeModuleIndexJMP, ModuleIndexInitialized,
                wstr(Patterns::ScriptManager_InitializeModuleIndexReturn), wstr(InitializeModuleIndexJMP));

            if (!m_ScriptManagerInitHook ||
                !m_InitializeModuleIndexHook) {
                throw SdkComponentEx{ "Failed to create hooks!", SdkComponentEx::ErrorCode::PatchFailed };
            }

        #if defined(T2R)

			m_GetDebugModulesHook = Utility::MakeSafetyHookInline((void*)GetDebugModuleBucket,
              ScriptManager::GetDebugModuleBucket, wstr(Patterns::ScriptManager_Lookup), wstr(GetDebugModules));

            if (!m_GetDebugModulesHook) {
				throw SdkComponentEx{ "Failed to create InlineHooks!", SdkComponentEx::ErrorCode::PatchFailed };
            }

        #endif

            if (m_Memory->IsDebugMemoryAvailable()) {
                m_Memory->IncreaseMemoryMap(Memory::MapId::ALLOCATION_DMENU_LOWMEM, MemSize(6.2, SizeUnit::Megabytes));
            }

		});
	}

    void ScriptManager::ScriptManagerInitialized(SafetyHookContext& ctx) {
        ScriptManager* ScriptMgr = Instance<ScriptManager>();

        if (ScriptMgr->m_Memory->IsDebugMemoryAvailable()) {
            ScriptCFunc* CFunc = ScriptMgr->LookupCFunc(SID("is-final-build?"));
            if (CFunc) {
				// Activate Debug possibilities for state script functions
                ScriptMgr->m_ScriptCFuncIsFinalBuildHook = CFunc->InlinePatchCfunc(ScriptCFunc_IsFinalBuild, L"is-final-build?", L"ScriptCFunc_IsFinalBuild->false");
				spdlog::info("Patched CFunc `is-final-build?` to return false");
            }
        }

        ScriptMgr->InvokeSdkEvent(ScriptMgr->e_ScriptManagerInitialized, ScriptMgr);
        return;
    }

    void ScriptManager::ModuleIndexInitialized(SafetyHookContext& ctx) {
        ScriptManager* ScriptMgr = Instance<ScriptManager>();

        //ScriptMgr->PrintModuleInfos(true);
        ScriptMgr->InvokeSdkEvent(ScriptMgr->e_ModuleIndexInitialized);
        return;
    }


    ModuleBucketMap* ScriptManager::GetDebugModuleBucket(ScriptManagerGlobals* pScriptManagerGlobals) {
        if (pScriptManagerGlobals->IsDebugBins()) {
			auto moduleBucket = pScriptManagerGlobals->GetBucketDebugModules();
			if (moduleBucket) {
				return moduleBucket;
			}
        }

        return nullptr;
    }

    uint64_t* ScriptManager::ScriptCFunc_IsFinalBuild(uint64_t* _return) {
        *_return = false;
        return _return;
    }

    void ScriptManager::PrintModuleInfos(bool PrintDebugModules) {

        auto* retailBucket = g_ScriptManagerGlobals->GetBucketModules();
        auto* debugBucket = g_ScriptManagerGlobals->GetBucketDebugModules();

        auto printModules = [](ModuleBucketMap* bucket, const char* label) {
            if (!bucket) return;
            std::size_t moduleIdx = 0;
            spdlog::debug("{} Modules:", label);
            spdlog::debug("{:>3} | {:>8} | {:^6} | {:^9} | {:^7} | {}",
                "Idx", "SizeKiB", "Debug", "IsLocal", "Loaded", "Name");
            spdlog::debug("{:-<3}-+-{:-<8}-+-{:-<6}-+-{:-<9}-+-{:-<7}-+-{:-<32}",
                "", "", "", "", "", "");
            for (const auto& mi : bucket->Modules()) {
                spdlog::debug("{:>3} | {:>8} | {:^6} | {:^9} | {:^7} | {}",
                    moduleIdx++,
                    mi ? (mi->GetModuleSize() + 1023) / 1024 : 0,
                    (mi && mi->IsDebugModule()) ? "Y" : "N",
                    (mi && mi->IsLocal()) ? "Y" : "N",
                    (mi && mi->IsLoaded()) ? "Y" : "N",
                    mi ? mi->GetModuleName() : "<null>");
            }
        };

        printModules(retailBucket, "Retail");
        if (PrintDebugModules) {
            printModules(debugBucket, "Debug");
        }
    }

    void ScriptManager::PrintScriptModules(bool PrintDebugModules) {

        auto* retailBucket = g_ScriptManagerGlobals->GetBucketModules();
        auto* debugBucket = g_ScriptManagerGlobals->GetBucketDebugModules();

        auto printModules = [](ModuleBucketMap* bucket, const char* label) {
            if (!bucket) return;
            std::size_t moduleIdx = 0;
            spdlog::debug("{} ScriptModules:", label);
            spdlog::debug("{:>3} | {:>8} | {:>14} | {:^6} | {:^9} | {}", "Idx", "SizeKiB", "Load Time(s)", "Debug", "Promoted", "Name");
            spdlog::debug("{:-<3}-+-{:-<8}-+-{:-<10}-+-{:-<6}-+-{:-<9}-+-{:-<32}", "", "", "", "", "", "");
            for (const auto& sm : bucket->ScriptModules()) {
                auto* mi = sm->GetModuleInfo();
                bool promoted = sm >= bucket->ScriptModuleHead() && sm < bucket->ScriptModuleTail();
                spdlog::debug("{:>3} | {:>8} | {:>14.1f}s | {:^6} | {:^9} | {}",
                    moduleIdx++,
                    mi ? (mi->GetModuleSize() + 1023) / 1024 : 0,
                    sm->GetLoadTimeSec(),
                    (mi && mi->IsDebugModule()) ? "Y" : "N",
                    promoted ? "Y" : "N",
                    mi ? mi->GetModuleName() : "<null>");
            }
        };

        printModules(retailBucket, "Retail");
        if (PrintDebugModules) {
            printModules(debugBucket, "Debug");
        }
    }

    bool ScriptManager::RefreshScriptCFuncInfo(bool UpdateSidBase = false) {

        auto logger = SdkLogger::GetLogger();

        if (!NdGameSdk::DB::IsDataBaseAvailable()) {
            logger->warn("[{}] Database is not available!", GetName());
            return false;
        }

        try {

            logger->info("[{}] Refreshing ScriptCFunc info...", GetName());

            auto nativeDump = g_ScriptManagerGlobals->DumpNativeFunctions();

            if (!m_ScriptCFuncs.empty()) {
                NdGameSdk::DB::ClearJsonFile(s_DataBaseFile, false);
            }

            m_ScriptCFuncs = NdGameSdk::DB::Get<std::map<StringId64, ScriptCFuncInfo>>(
                s_DataBaseFile, "ScriptCFuncs", m_ScriptCFuncs);

            bool changed = false;

            if (UpdateSidBase && NdGameSdk::Sidbase::g_bSidbaseAvailable) {
                for (auto& [hash, info] : m_ScriptCFuncs) {
                    std::string newName = NdGameSdk::Sidbase::StringIdToStringInternal(hash);
                    if (info.Name != newName) {
                        info.Name = std::move(newName);
                        logger->warn("[{}] Updated ScriptCFunc name: {} (hash: {:#x})", GetName(), info.Name, hash);
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
                    logger->debug("[{}] Found new ScriptCFunc: {} (hash: {:#x})", GetName(), info.Name, native.hash);
                    changed = true;
                }
            }

            if (changed) {
                NdGameSdk::DB::Set(s_DataBaseFile, "ScriptCFuncs", m_ScriptCFuncs);
                NdGameSdk::DB::FlushJsonFile(s_DataBaseFile);
                logger->info("[{}] ScriptCFuncs updated ({} entries cached)", GetName(), m_ScriptCFuncs.size());
                return true;
            }

            logger->debug("[{}] No updates needed for ScriptCFuncs", GetName());
            return true;
		}
        catch (const std::exception& e) {
            logger->error("[{}] Error while refreshing ScriptCFunc info: {}", GetName(), e.what());
            return false;
        }
    }

    bool ScriptManager::TestFunct(DMENU::ItemFunction& pFunction, DMENU::Message pMessage) {  
       if (pMessage == DMENU::Message::OnExecute) {  
           auto ScriptMgr = reinterpret_cast<ScriptManager*>(pFunction.Data());  
           if (ScriptMgr) {  
               spdlog::info("TestFunct called!");
               //ScriptMgr->AddModuleRequest(SID("test-tasks"), Memory::Context::kAllocDevCpu, true, true, "test-tasks");
               return true;  
           }  
       }  
       return true;  
    }

    ModuleInfo* ScriptManager::FindExportingModule(StringId64 pSymbol, bool pRestrictToModule, StringId64 pModule) {
		always_assert(ScriptManager_FindExportingModule == nullptr, "Function pointer was not set!");
		return ScriptManager_FindExportingModule(pSymbol, pRestrictToModule, pModule);
    }

    void ScriptManager::ScriptModuleAdd(StringId64 module, ScriptModule* pScriptModule) {
		always_assert(ScriptManager_ScriptModuleAdd == nullptr, "Function pointer was not set!");
		spdlog::debug("[{}] ScriptModuleAdd: {:#x} ({})", GetName(), module, pScriptModule->GetModuleName());
		ScriptManager_ScriptModuleAdd(module, pScriptModule);
    }

    void ScriptManager::ScriptModuleRemove(StringId64 module) {
		always_assert(ScriptManager_ScriptModuleRemove == nullptr, "Function pointer was not set!");
		spdlog::debug("[{}] ScriptModuleRemove: {:#x}", GetName(), module);
		ScriptManager_ScriptModuleRemove(module);
    }

    bool ScriptManager::AddModuleInfo(ModuleInfo* pModule) {
		always_assert(ScriptManager_AddModuleInfo == nullptr, "Function pointer was not set!");
		spdlog::debug("[{}] AddModuleInfo: {:#x} ({})", GetName(), pModule->GetModuleId(), pModule->GetModuleName());
		return ScriptManager_AddModuleInfo(pModule);
    }

    void ScriptManager::RemoveModuleInfo(StringId64 pModule, bool pUpdateRelocatableHeap, bool pForce) {
		always_assert(ScriptManager_RemoveModule == nullptr, "Function pointer was not set!");
		spdlog::debug("[{}] RemoveModuleInfo: {:#x} (updateRelocatableHeap: {}, force: {})", GetName(), pModule, 
            pUpdateRelocatableHeap, pForce);
		ScriptManager_RemoveModule(pModule, pUpdateRelocatableHeap, pForce);
    }

    bool ScriptManager::AddModuleRequest(StringId64 pModule, Memory::Context pContext,
        bool pForceLoad, bool pIncludeDependities, std::string pModuleName) {
        bool FetchModule = ModuleInfo::FetchModule(pModule, pContext);
        always_assert(ScriptManager_AddModuleRequest == nullptr, "Function pointer was not set!");

        spdlog::debug("[{}] AddModuleRequest: {:#x} (ctx: {:#x}, force={}, deps={}, fetch={})", GetName(), pModule,
            (uintptr_t)pContext, pForceLoad, pIncludeDependities, FetchModule);
        return ScriptManager_AddModuleRequest(pModule, &pContext, pForceLoad, pIncludeDependities, FetchModule, 0, pModuleName.c_str());
    }

    bool ScriptManager::AddModuleRequest(ModuleInfo* pModule, Memory::Context pContext,
        bool pForceLoad, bool pIncludeDependities) {
        always_assert(pModule == nullptr, "ModuleInfo is null!");

        StringId64 id = pModule->GetModuleId();
        const char* name = pModule->GetModuleName().c_str();
        bool FetchModule = pModule->FetchModule(pContext);

        always_assert(ScriptManager_AddModuleRequest == nullptr, "Function pointer was not set!");
        spdlog::debug("[{}] AddModuleRequest: {:#x} (ctx: {:#x}, force={}, deps={}, fetch={})", GetName(), id,
            (uintptr_t)pContext, pForceLoad, pIncludeDependities, FetchModule);
        return ScriptManager_AddModuleRequest(id, &pContext, pForceLoad, pIncludeDependities, FetchModule, 0, name);

    }

    bool ScriptManager::IsModuleLoaded(StringId64 pModule) {
		always_assert(ScriptManager_IsLoadModule == nullptr, "Function pointer was not set!");
		return ScriptManager_IsLoadModule(pModule);
    }

    bool ScriptManager::ReloadModule(StringId64 pModule, Memory::Context pContext, bool pLoadDebug) {
		always_assert(ScriptManager_ReloadModule == nullptr, "Function pointer was not set!");
		spdlog::debug("[{}] ReloadModule: {:#x} (ctx: {:#x}, loadDebug={})", GetName(), pModule,
			(uintptr_t)pContext, pLoadDebug);
    #if defined(T1X)
        return ScriptManager_ReloadModule(pModule, pContext);
    #else
        return ScriptManager_ReloadModule(pModule, pContext, pLoadDebug);
    #endif
    }

    bool ScriptManager::LoadModuleFromFile(StringId64 pModule, char* pFilePath, uint32_t pSize, Memory::Context* pContextType, 
        bool pIsDebugModule, uint32_t pUpdateAndDispatch) {
		always_assert(ScriptManager_LoadModuleFromFile == nullptr, "Function pointer was not set!");
		spdlog::debug("[{}] LoadModuleFromFile: {:#x} (ctx: {:#x}, debug={})", GetName(), pModule,
			(uintptr_t)pContextType, pIsDebugModule);
    #if defined(T1X)
		return ScriptManager_LoadModuleFromFile(pModule, false, pFilePath);
    #else
		return ScriptManager_LoadModuleFromFile(pModule, pFilePath, nullptr, pSize, pContextType, pIsDebugModule, pUpdateAndDispatch);
    #endif
    }

#if defined(T2R)
    bool ScriptManager::LoadModuleFromBuffer(StringId64 pModule, void* pUserBuffer, uint32_t pSize, Memory::Context* pContextType, bool pIsDebugModule, uint32_t pUpdateAndDispatch) {
		always_assert(ScriptManager_LoadModuleFromFile == nullptr, "Function pointer was not set!");
		spdlog::debug("[{}] LoadModuleFromBuffer: {:#x} (ctx: {:#x}, debug={})", GetName(), pModule,
			(uintptr_t)pContextType, pIsDebugModule);
		return ScriptManager_LoadModuleFromFile(pModule, nullptr, pUserBuffer, pSize, pContextType, pIsDebugModule, pUpdateAndDispatch);
    }
#endif

    ScriptCFunc* ScriptManager::LookupCFunc(StringId64 Hash) {
		always_assert(ScriptManager_LookupSymbol == nullptr, "Function pointer was not set!");
        return reinterpret_cast<ScriptCFunc*>(ScriptManager_LookupSymbol(Hash, nullptr));
    }

    DMENU::ItemSubmenu* ScriptManager::CreateScriptManagerMenu(NdDevMenu* pdmenu, DMENU::Menu* pMenu) {
        ScriptManager* ScriptMgr = Instance<ScriptManager>();
        if (ScriptMgr) {
            uint64_t ScriptMgrAddr = reinterpret_cast<uint64_t>(static_cast<void*>(ScriptMgr));

            DMENU::Menu* ScriptManagerMenu = pdmenu->Create_DMENU_Menu(ScriptMgr->GetName().data(), HeapArena_Source);
            if (ScriptManagerMenu) {
				auto RetailModulesCount = ScriptMgr->g_ScriptManagerGlobals->GetBucketModules()->NumModules();
                pdmenu->Create_DMENU_String(std::vformat("// Retail Modules: {:d}", std::make_format_args(RetailModulesCount)), ScriptManagerMenu, nullptr, HeapArena_Source);
                if (ScriptMgr->g_ScriptManagerGlobals->GetBucketDebugModules()) {
                    auto DebugModulesCount = ScriptMgr->g_ScriptManagerGlobals->GetBucketDebugModules()->NumModules();
                    pdmenu->Create_DMENU_String(std::vformat("// Debug Modules: {:d}", std::make_format_args(DebugModulesCount)), ScriptManagerMenu, nullptr, HeapArena_Source);
                }

                /*ScriptCFuncDebugMenu*/
                ScriptMgr->m_ScriptCFuncDebugMenu = pdmenu->Create_DMENU_Menu("ScriptCFuncs Debugging", HeapArena_Source);

                pdmenu->Create_DMENU_ItemSubmenu(ScriptMgr->m_ScriptCFuncDebugMenu->Name(), ScriptManagerMenu,
                    ScriptMgr->m_ScriptCFuncDebugMenu, OnUpdateScriptCFuncDebugMenu, ScriptMgrAddr, nullptr, HeapArena_Source);
                pdmenu->Create_DMENU_String("// ScriptCFuncDebugMenu [BETA]", ScriptMgr->m_ScriptCFuncDebugMenu, nullptr, HeapArena_Source);
                pdmenu->Create_DMENU_String(ScriptMgr->m_NativeTableEntriesText, ScriptMgr->m_ScriptCFuncDebugMenu, nullptr, HeapArena_Source);

            #if SDK_DEBUG
                pdmenu->Create_DMENU_ItemFunction("Test funct", ScriptManagerMenu, &TestFunct, ScriptMgrAddr, false, HeapArena_Source);
            #endif

				// TODO: Implement debug menu for API functions

                return pdmenu->Create_DMENU_ItemSubmenu(ScriptManagerMenu->Name(),
                    pMenu, ScriptManagerMenu, NULL, NULL, nullptr, HeapArena_Source);
            }
        }
        return nullptr;
    }

    bool ScriptManager::WrapScriptCFuncDebugMenu(DMENU::Menu* pMenu, ScriptCFuncDebugMenuProperties* pProperties) {
        ScriptManager* ScriptMgr = Instance<ScriptManager>();
		NdDevMenu* NdDevMenu = ScriptMgr->m_NdDevMenu;

        ScriptMgr->m_ScriptCFuncInput = nullptr;
        ScriptMgr->m_ScriptCFuncDebugMenuProperties.ScriptCFuncInfo = nullptr;

        static DMENU::ItemFunction::FunctionCallback bShowAllScriptCFuncs =
            +[](DMENU::ItemFunction& item, DMENU::Message msg)->bool {
            if (msg == DMENU::Message::OnExecute) {
                ScriptManager* ScriptMgr = Instance<ScriptManager>();

                if (ScriptMgr->m_Memory->GetMemSize(MemoryMapId::ALLOCATION_DMENU_LOWMEM) < MemSize(5, SizeUnit::Megabytes)) {
                    spdlog::error("[{}] Memory DMENU_LOWMEM size is not correct!", ScriptMgr->GetName());
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
					spdlog::error("[{}] ScriptCFunc {:#x} not found!", ScriptMgr->GetName(), pSubmenu.Data());
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
					return DB::FlushJsonFile(ScriptMgr->s_DataBaseFile, false);
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
        NdDevMenu* NdDevMenu = ScriptMgr->m_NdDevMenu;

        static auto ExecutorModeHandler = &ScriptManager::OnExecuteRebuild<DMENU::ItemSelection>;
        static auto ArgumentsHandler = &ScriptManager::OnExecuteRebuild<DMENU::ItemDecimal>;

        ScriptCFuncInfo* CFuncInfo = pProperties->ScriptCFuncInfo;
		static bool RebuildExecutorMenu = false;
        if (!pSwitchMode) {

            pProperties->CFuncEditor.reset();

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

                NdDevMenu->Create_DMENU_ItemFunction("Save Data", pMenu,
                    +[](DMENU::ItemFunction& pFunction, DMENU::Message pMessage)->bool {
                        if (pMessage == DMENU::Message::OnExecute) {
                            ScriptManager* ScriptMgr = Instance<ScriptManager>();
                            ScriptCFuncInfo* CFuncInfo = ScriptMgr->m_ScriptCFuncDebugMenuProperties.ScriptCFuncInfo;

                            if (CFuncInfo) {
                                NdGameSdk::DB::Set(s_DataBaseFile, "ScriptCFuncs", ScriptMgr->m_ScriptCFuncs);
                                return true;
                            }
                            return false;
                            
                        }
                        return true;
                    }, 0x0, false, HeapArena_Source);

                NdDevMenu->Create_DMENU_ItemFunction("Print ScriptCFuncAddress", pMenu,
                    +[](DMENU::ItemFunction& pFunction, DMENU::Message pMessage)->bool {
                        if (pMessage == DMENU::Message::OnExecute) {
                            ScriptManager* ScriptMgr = Instance<ScriptManager>();
                            auto* CFuncInfo = reinterpret_cast<ScriptCFuncInfo*>(pFunction.Data());

                            if (CFuncInfo) {
                                ScriptCFunc* CFunc = ScriptMgr->LookupCFunc(CFuncInfo->Hash);
                                if (CFunc) {
                                    spdlog::info("[{}] ScriptCFuncAddress {:#x}", ScriptMgr->GetName(), reinterpret_cast<uintptr_t>(CFunc->GetFunc()));
                                    return true;
                                }
                                else {
                                    spdlog::error("[{}] ScriptCFunc {} not found!", ScriptMgr->GetName(), CFuncInfo->Name);
                                    return false;
                                }
                            }
                            return false;

                        }
                        return true;
                    }, reinterpret_cast<uint64_t>(pProperties->ScriptCFuncInfo), false, HeapArena_Source);

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
                        case ScriptCFuncInfo::TypeOf::CFuncValue: {
							NdDevMenu->Create_DMENU_String(arg.Name, pMenu, arg.Description.c_str(), HeapArena_Source);
                            break;
                        }
                        case ScriptCFuncInfo::TypeOf::StringId: {
                        default:
                            NdDevMenu->Create_DMENU_KeyBoard(arg.Name, pMenu, (char*)arg.Data, 100, arg.Description.c_str(), HeapArena_Source);
                            break;
                        }
                        }
                    }
                }

                NdDevMenu->Create_DMENU_ItemFunction("Execute", pMenu,
                    +[](DMENU::ItemFunction& pFunction, DMENU::Message pMessage)->bool {
                        if (pMessage == DMENU::Message::OnExecute) {
                            ScriptManager* ScriptMgr = Instance<ScriptManager>();
                            auto* CFuncInfo = reinterpret_cast<ScriptCFuncInfo*>(pFunction.Data());

                            if (CFuncInfo) {
                                ScriptCFunc* CFunc = ScriptMgr->LookupCFunc(CFuncInfo->Hash);
								if (CFunc) {
                                    for (auto& arg : CFuncInfo->Args) {
                                        if (arg.Type == ScriptCFuncInfo::TypeOf::CFuncValue) {

                                            StringId64 CFuncHash = ParseStringToStringId(arg.Name.c_str());
                                            auto ScriptCFuncArg = ScriptMgr->m_ScriptCFuncs.find(CFuncHash);
                                            if (ScriptCFuncArg == ScriptMgr->m_ScriptCFuncs.end()) {
                                                spdlog::error("[{}] ScriptCFunc {} not found!", ScriptMgr->GetName(), pFunction.Name());
                                                return false;
                                            }

                                            ScriptCFuncInfo* CFuncInfo = &ScriptCFuncArg->second;
                                            ScriptCFunc* CFunc = ScriptMgr->LookupCFunc(CFuncInfo->Hash);
                                            if (CFunc) {
                                                ScriptValue _returnvalue{};
                                                CFunc->CallScriptCFunc(CFuncInfo->makeScriptArgs(), static_cast<uint32_t>(CFuncInfo->Args.size()), &_returnvalue);
                                                spdlog::info("[{}] ScriptCFunc {} executed!", ScriptMgr->GetName(), CFuncInfo->Name);
                                                auto ret = _returnvalue.val<uint64_t>(0);
                                                if (ret != 0) {
                                                    arg.Data[0] = ret;
                                                    spdlog::info("[{}] Return value: {:#x}", ScriptMgr->GetName(), ret);
                                                }
                                                else {
                                                    spdlog::error("[{}] {}->ScriptValue[0] returned nothing!", ScriptMgr->GetName(), CFuncInfo->Name);
                                                    return false;
                                                }
                                            }
                                            else {
                                                spdlog::error("[{}] ScriptCFunc {} not found!", ScriptMgr->GetName(), CFuncInfo->Name);
                                                return false;
                                            }

                                        }
                                    }

									ScriptValue _returnvalue{};
									CFunc->CallScriptCFunc(CFuncInfo->makeScriptArgs(), static_cast<uint32_t>(CFuncInfo->Args.size()), &_returnvalue);
									spdlog::info("[{}] ScriptCFunc {} executed!", ScriptMgr->GetName(), CFuncInfo->Name);
                                    uint32_t i = 0;
                                    for (auto v : _returnvalue->val) {
                                        if (v == 0) break;
                                        spdlog::info("[{}] Return[{}] = {:#x}", ScriptMgr->GetName(), i++, v);
                                    }
                                    return true;
								}
								else {
									spdlog::error("[{}] ScriptCFunc {} not found!", ScriptMgr->GetName(), CFuncInfo->Name);
                                    return false;
								}
                            }
                            return false;
                        }
                        return true;
                    }, reinterpret_cast<uint64_t>(pProperties->ScriptCFuncInfo), false, HeapArena_Source);

				break;
			}
            case ScriptCFuncDebugMode::Editor: {

                if (!pProperties->CFuncEditor) { 
                    pProperties->CFuncEditor = std::make_unique<ScriptCFuncDebugMenuProperties::ScriptCFuncEditor>(); 
                }

                auto CFuncEditor = pProperties->CFuncEditor.get();
                uint32_t MaxArgs = 0x10;

                if (!RebuildExecutorMenu) {

                    SyncCFuncEditorBuffers(*CFuncInfo, *CFuncEditor, true);
                    NdDevMenu->Create_DMENU_ItemLine(pMenu, HeapArena_Source);
                    NdDevMenu->Create_DMENU_KeyBoard("Description", pMenu, CFuncEditor->DescriptionBuf, sizeof(CFuncEditor->DescriptionBuf), nullptr, HeapArena_Source);
                    NdDevMenu->Create_DMENU_ItemDecimal("Arguments", pMenu, &CFuncEditor->NumArgs, { 0, MaxArgs }, {1, 1}, nullptr, HeapArena_Source)
                        ->SetHandler((DMENU::ItemDecimal::DecimalHandler*)ArgumentsHandler);
					RebuildExecutorMenu = true;
                }
                
				if (CFuncEditor->NumArgs > MaxArgs) {
					CFuncEditor->NumArgs = MaxArgs;
				}
				else if (CFuncEditor->NumArgs < 0) {
					CFuncEditor->NumArgs = 0;
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
        StringId64 hash = ParseStringToStringId(sv.data());

        if (hash != 0x0) {
            auto it = m_ScriptCFuncs.find(StringId64{ hash });
            return it != m_ScriptCFuncs.end() ? &it->second : nullptr;
        }

        for (auto& kv : m_ScriptCFuncs) {
            if (kv.second.Name == sv)
                return &kv.second;
        }

        return nullptr;
    }

    FixedSizeHeap* ModuleBucketMap::GetSymbolsHeap() const {
        return reinterpret_cast<FixedSizeHeap*>(&this->Get()->m_SymbolsHeap);
    }

    FixedSizeHeap* ModuleBucketMap::GetModulesHeap() const {
        return reinterpret_cast<FixedSizeHeap*>(&this->Get()->m_ModulesHeap);
    }

    FixedSizeHeap* ModuleBucketMap::GetScriptModuleHeap() const {
        return reinterpret_cast<FixedSizeHeap*>(&this->Get()->m_ScriptModuleHeap);
    }

    uint64_t ModuleBucketMap::MaxGlobalSymbols() const {
        return this->Get()->m_maxGlobalSymbols;
    }

    uint64_t ModuleBucketMap::NumGlobalSymbols() const {
        return this->Get()->m_numGlobalSymbols;
    }

    uint64_t ModuleBucketMap::MaxModules() const {
        return this->Get()->m_maxModules;
    }

    uint64_t ModuleBucketMap::NumModules() const {
        return this->Get()->m_numModules;
    }

    uint64_t ModuleBucketMap::MaxScriptModules() const {
        return this->Get()->m_maxScriptModules;
    }

    uint64_t ModuleBucketMap::NumScriptModules() const {
        return this->Get()->m_numScriptModules;
    }

    ModuleInfo* ModuleBucketMap::ModuleHead() {
        return reinterpret_cast<ModuleInfo*>(this->Get()->m_ModulesHead);
    }

    const ModuleInfo* ModuleBucketMap::ModuleHead() const {
		return reinterpret_cast<const ModuleInfo*>(this->Get()->m_ModulesHead);
    }

    ScriptModule* ModuleBucketMap::ScriptModuleHead() {
        return reinterpret_cast<ScriptModule*>(this->Get()->m_ScriptModulesHead);
    }

    const ScriptModule* ModuleBucketMap::ScriptModuleHead() const {
		return reinterpret_cast<const ScriptModule*>(this->Get()->m_ScriptModulesHead);
    }

    ScriptModule* ModuleBucketMap::ScriptModuleTail() {
		return reinterpret_cast<ScriptModule*>(this->Get()->m_ScriptModulesTail);
    }

    std::vector<ScriptManagerGlobals::NativeFuncEntry> ScriptManagerGlobals::DumpNativeFunctions() {

        std::vector<NativeFuncEntry> Dump{};

        auto NativeMap = GetNativeMap();
        if (!NativeMap) {
            spdlog::error("[{}] NativeMap is null", TOSTRING(ScriptManagerGlobals));
            return Dump;
        }

        spdlog::info("[{}] Native table contains {} entries", TOSTRING(ScriptManagerGlobals), NativeMap->m_FunctionsNum);

        const auto num = static_cast<std::size_t>(NativeMap->m_FunctionsNum);
        auto* base = reinterpret_cast<const NativeFuncEntry*>(NativeMap->m_FunctionsBaseAddress);

        if (base == nullptr || num == 0) {
            spdlog::warn("[{}] Native table is empty", TOSTRING(ScriptManagerGlobals));
            return Dump;
        }

        Dump.reserve(num);
        for (std::size_t i = 0; i < num; ++i) {
            Dump.emplace_back(base[i]);
        }

        return Dump;
    }

    bool ScriptManagerGlobals::IsDebugBins() {
        return !this->Get()->m_DisableDebugBins;
    }

    ModuleBucketMap* ScriptManagerGlobals::GetBucketModules() {
        return reinterpret_cast<ModuleBucketMap*>(&this->Get()->m_ModulesBucket);
    }

    ModuleBucketMap* ScriptManagerGlobals::GetBucketDebugModules() {
    #if defined(T2R)
        return reinterpret_cast<ModuleBucketMap*>(this->Get()->m_DebugModulesBucket);
    #else
        // For T1X, we need to implement a manual allocation and implementation (Not in the priority)
		return nullptr;
    #endif
    }

    ScriptManagerGlobals::ScriptCFuncMap* ScriptManagerGlobals::GetNativeMap() {
        return this->Get()->m_NativeMap;
    }

    std::string ScriptManager::s_DataBaseFile{"ScriptManager.json"};

}