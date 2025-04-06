#include <chrono>
#include <mutex>
#include <thread>
#include <windows.h>
#include <winternl.h>
#include <psapi.h>
#include <fstream>

#include <spdlog/spdlog.h>
#include <Utility/helper.hpp>

#include <NdGameSdk/sdk.hpp>
#include <NdGameSdk/sdkconfig.hpp>

#include "NdModClient.hpp"
#include "Utils/config.hpp"

void startup_thread(HMODULE dllModule) {
    g_ndmodclient->Initialize();
}

BOOL Initialize(HMODULE dllModule) {

    HMODULE baseModule = GetModuleHandle(NULL);
    std::string moduleName = Utility::memory::get_module_name(baseModule).value();
    std::wstring exePath = Utility::memory::get_module_pathw(baseModule).value();
    std::wstring VerProductName = Utility::memory::get_version_product_name(baseModule).value_or(L"UNKNOW");

    if (moduleName != std::string(GAME_MODULE_NAME) ||
        !Utils::Config::InitDefaultConfig()) {
        return FALSE;
    }

    Utils::Logger::InitConsole();
    Utils::Config cfg{};

    cfg.LogConfigParse();
    SPDLOG_INFO("Game module: {}", moduleName);
    SPDLOG_INFO(L"Game Path: {}", exePath);
    SPDLOG_INFO(L"Game Name: {}", VerProductName);

    std::this_thread::sleep_for(std::chrono::seconds(3));

    g_ndmodclient = std::make_unique<NdModClient>(baseModule);

    // will use values from Config ini.
    SdkConfig pSdkCfg{};
    pSdkCfg.Sidbase = true;
    
    pSdkCfg.NdDevMenu.GameDebugMenu = true;
    pSdkCfg.Memory.DebugMemory = false;

#if defined(T1X)
    pSdkCfg.NdDevMenu.ExtendedDebugMenu = true;
    pSdkCfg.PrimServer.PrimServerCreate = true;
#endif

    NdGameSdk::InitializeSdk(&pSdkCfg);
    NdGameSdk::RegisterSdkModule(g_ndmodclient.get());
    return TRUE; 
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {

    (void)ul_reason_for_call;
    (void)lpReserved;
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        bool Initialized = Initialize(hModule);

        if (Initialized) {
            CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)startup_thread, hModule, 0, nullptr);
        }

        return Initialized;
    }

    return TRUE;
}
