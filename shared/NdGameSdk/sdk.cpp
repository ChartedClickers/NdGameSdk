#include "sdk.hpp"
#include "sdkconfig.hpp"
#include "components/SdkModule.hpp"
#include "sidbase/sidbase.hpp"

#include "shared/shared.hpp"
#if defined(T1X)
#include "ndgame/t1x/ndgame.hpp"
#elif defined(T2R)
#include "ndgame/t2r/ndgame.hpp"
#endif

#include "shared/src/common/common-game-init.hpp"
#include "shared/src/corelib/memory/memory.hpp"

#if defined(T1X)
#include "shared/src/gamelib/debug/nd-dev-menu.hpp"
#endif

#include <windows.h>
#include <unordered_map>
#include <memory>

namespace NdGameSdk {

    HMODULE g_SdkModuleHandle{};
    bool g_SdkInitialized{};

    void InitializeSdk(const SdkConfig* cfg) {

        if (g_SdkInitialized) { return; }

        auto sdklogger = SdkLogger::GetLogger();
        auto sdkcfg = cfg ? std::move(*cfg) : SdkConfig{};

        set_default_logger(sdklogger);

        InitSharedComponents(sdkcfg);
        InitNdGameComponents(sdkcfg);

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
        auto SharedComponents = ISdkComponent::GetSharedComponents();

        ISdkComponent::SubscribeSdkEvent<corelib::memory::Memory>(
            SharedComponents,
            &corelib::memory::Memory::e_MemoryMapMapped,
            &ISdkModule::OnMemoryMapped,
            SdkModule
        );

        ISdkComponent::SubscribeSdkEvent<common::CommonGame>(
            SharedComponents,
            &common::CommonGame::e_GameInitialized,
            &ISdkModule::OnGameInitialized,
            SdkModule
        );

        #if defined(T1X)
        ISdkComponent::SubscribeSdkEvent<gamelib::debug::NdDevMenu>(
            SharedComponents,
            &gamelib::debug::NdDevMenu::e_AppendSdkMenu,
            &ISdkModule::OnAppendSdkDevMenu,
            SdkModule
        );
        #endif

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
        auto SharedComponents = ISdkComponent::GetSharedComponents();

        ISdkComponent::UnsubscribeSdkEvent<corelib::memory::Memory>(
            SharedComponents,
            &corelib::memory::Memory::e_MemoryMapMapped,
            &ISdkModule::OnMemoryMapped,
            SdkModule
        );

        ISdkComponent::UnsubscribeSdkEvent<common::CommonGame>(
            SharedComponents,
            &common::CommonGame::e_GameInitialized,
            &ISdkModule::OnGameInitialized,
            SdkModule
        );

        #if defined(T1X)
        ISdkComponent::UnsubscribeSdkEvent<gamelib::debug::NdDevMenu>(
            SharedComponents,
            &gamelib::debug::NdDevMenu::e_AppendSdkMenu,
            &ISdkModule::OnAppendSdkDevMenu,
            SdkModule
        );
        #endif

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

