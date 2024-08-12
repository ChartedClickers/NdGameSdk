#include "sdk.hpp"
#include "sdkconfig.hpp"
#include "components/SdkModule.hpp"
#include "sidbase/sidbase.hpp"

#include "shared/shared.hpp"
#if defined(T1X)
#include "ndgame/t1x/ndgame.hpp"
#endif

#include "shared/src/common/common-game-init.hpp"
#include "shared/src/corelib/memory/memory.hpp"
#include "shared/src/gamelib/debug/nd-dev-menu.hpp"

#include <windows.h>
#include <unordered_map>
#include <memory>

namespace NdGameSdk {

    HMODULE g_SdkModuleHandle{};
    bool g_SdkInitialized{};

    corelib::memory::Memory* Memory{};
    common::CommonGame* CommonGame{};
    gamelib::debug::NdDevMenu* NdDevMenu{};

    void InitializeSdk(const SdkConfig* cfg) {

        if (g_SdkInitialized) { return; }

        auto sdklogger = SdkLogger::GetLogger();
        auto sdkcfg = cfg ? std::move(*cfg) : SdkConfig{};

        if (sdkcfg.NdDevMenu.ExtendedDebugMenu) {
            sdkcfg.Memory.DebugMemory = true;
        }

        set_default_logger(sdklogger);

        InitSharedComponents(sdkcfg);
        InitNdGameComponents(sdkcfg);

        auto SharedComponents = ISdkComponent::GetSharedComponents();
        Memory = SharedComponents->GetComponent<corelib::memory::Memory>().get();
        CommonGame = SharedComponents->GetComponent<common::CommonGame>().get();
        NdDevMenu = SharedComponents->GetComponent<gamelib::debug::NdDevMenu>().get();

        auto MissingComponents = ISdkComponent::CheckSdkComponents
            <corelib::memory::Memory, common::CommonGame, gamelib::debug::NdDevMenu>
            ({ Memory, CommonGame, NdDevMenu });

        if (MissingComponents.has_value()) {
            throw NdGameSdkException
            { std::format("Missing important SdkComponents to initialize SDK: {:s}", MissingComponents.value()) };
        }

        if (sdkcfg.Sidbase) {
            Sidbase::InitSidbase(sdkcfg.SidbasePath.c_str());
        }

        g_SdkInitialized = true;
        spdlog::info("NdGameSdk was successfully initialized!");
    }
    
     void RegisterSdkModule(ISdkModule* SdkModule) {

         if (!g_SdkInitialized) {
             throw NdGameSdkException { "Sdk is not initialized for this operation" };
         }

         HMODULE Hmodule = SdkModule->GetModule();
         auto SdkModules = ISdkModule::GetSdkModules();

         if (SdkModules->find(Hmodule) != SdkModules->end())
         {
             SdkModule = SdkModules->at(Hmodule);
             throw SdkModuleException {
                 std::format("Module {} already registered as {}",
                 reinterpret_cast<uintptr_t>(Hmodule), SdkModule->GetModuleName()),
                SdkModuleException::ErrorCode::AlreadyRegistered };
         }
        
         // Registering main sdk events
         Memory->e_MemoryMapMapped.Subscribe(SdkModule, &ISdkModule::OnMemoryMapped);
         CommonGame->e_GameInitialized.Subscribe(SdkModule, &ISdkModule::OnGameInitialized);
         NdDevMenu->e_AppendSdkMenu.Subscribe(SdkModule, &ISdkModule::OnAppendSdkDevMenu);
         SdkModule->e_OnUnregister.Subscribe(UnregisterSdkModule);

         if (SdkModule->m_logger) {
             SdkLogger::LinkFileSink(*SdkModule->m_logger.get());
         }

         SdkModules->insert({ Hmodule, SdkModule });
		 SdkModule->m_registered = true;
         SdkModule->OnModuleRegistered();

         spdlog::info("Module {} has been registered!", SdkModule->GetModuleName());
     }

     void UnregisterSdkModule(ISdkModule* SdkModule) {

         if (!g_SdkInitialized) {
             throw NdGameSdkException { "Sdk is not initialized for this operation" };
         }

         HMODULE Hmodule = SdkModule->GetModule();
         auto SdkModules = ISdkModule::GetSdkModules();

         if (SdkModules->find(Hmodule) == SdkModules->end())
         {
             SdkModule = SdkModules->at(Hmodule);
             throw SdkModuleException{
                 std::format("Module {} not registered", SdkModule->GetModuleName()),
                SdkModuleException::ErrorCode::NotRegistered };
         }

         // Unregistering main sdk events
         Memory->e_MemoryMapMapped.Unsubscribe({ SdkModule, &ISdkModule::OnMemoryMapped});
         CommonGame->e_GameInitialized.Unsubscribe({ SdkModule, &ISdkModule::OnGameInitialized });
         NdDevMenu->e_AppendSdkMenu.Unsubscribe({ SdkModule, &ISdkModule::OnAppendSdkDevMenu });
         SdkModule->e_OnUnregister.Unsubscribe(UnregisterSdkModule);

         if (SdkModule->m_logger) {
             SdkLogger::UnlinkFileSink(*SdkModule->m_logger.get());
         }

         SdkModule->m_registered = false;
         SdkModules->erase(SdkModule->GetModule());

         spdlog::info("Module {} has been unregistered!", SdkModule->GetModuleName());
     }
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        NdGameSdk::g_SdkModuleHandle = hModule;
    }
    return TRUE;
}

