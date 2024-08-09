#include <chrono>
#include <mutex>
#include <thread>
#include <windows.h>
#include <winternl.h>
#include <fstream>
#include <spdlog/spdlog.h>
#include <psapi.h>

#include "NdTestModule.hpp"

#if _DEBUG
#define BUILD_MODE "Debug"
#else
#define BUILD_MODE "Release"
#endif

#include <NdGameSdk/sdk.hpp>

void startup_thread(HMODULE dllModule) {


}


extern "C" __declspec(dllexport) BOOL InitializeModule(bool test)
{
    HMODULE baseModule = GetModuleHandle(NULL);

    CHAR moduleName[MAX_PATH];
    GetModuleBaseNameA(GetCurrentProcess(), baseModule, moduleName, MAX_PATH);

    g_ndtestmodule = std::make_unique<NdTestModule>(baseModule);

    NdGameSdk::RegisterSdkModule(g_ndtestmodule.get());

    return TRUE;
}
  
 
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {

    (void)ul_reason_for_call;
    (void)lpReserved;
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        
    }

    return TRUE;
}
