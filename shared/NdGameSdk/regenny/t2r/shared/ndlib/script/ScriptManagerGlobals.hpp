#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "..\..\corelib\job\JlsContext.hpp"
#include "ModuleBucketMap.hpp"
#include "ModuleRequest.hpp"
#include "ScriptModule.hpp"
namespace regenny::shared::ndlib::script {
#pragma pack(push, 1)
struct ScriptManagerGlobals {
    struct ScriptCFuncMap {
        void* m_FunctionsBaseAddress; // 0x0
        uint64_t m_FunctionsNum; // 0x8
    }; // Size: 0x10

    private: char pad_0[0x10]; public:
    StringId64 m_JlsContext; // 0x10
    regenny::shared::corelib::job::JlsContext m_JlsIndex; // 0x18
    private: char pad_1c[0x24]; public:
    bool m_EnableScriptTrace; // 0x40
    private: char pad_41[0x1]; public:
    bool m_Autoreloadbinfiles; // 0x42
    bool m_DisplayRequestedModules; // 0x43
    bool m_DumploadlisttoTTY; // 0x44
    bool m_Showoverflowedmodules; // 0x45
    bool m_ShowScriptErrors; // 0x46
    bool m_PrintmodulesCon; // 0x47
    bool m_PrintmodulescountsCon; // 0x48
    bool m_ShowDebugBinStatusCon; // 0x49
    private: char pad_4a[0x2]; public:
    bool m_DumpStateScriptsonStackFrameHighWater; // 0x4c
    bool m_EnableScriptModuleCRC32Checks; // 0x4d
    bool m_field4e; // 0x4e
    bool m_ValidateModuleSize; // 0x4f
    bool m_AssertonGlobalSymbolLookup; // 0x50
    bool m_EnableScripts; // 0x51
    bool m_field52; // 0x52
    bool m_field53; // 0x53
    bool m_DisableScriptDebugPrims; // 0x54
    bool m_DisplayGlobalSymbols; // 0x55
    bool m_ModuleIndexInit; // 0x56
    bool m_DisableDebugBinSuppressionforGameTasks; // 0x57
    bool m_field58; // 0x58
    private: char pad_59[0x1]; public:
    bool m_field5a; // 0x5a
    bool m_DisableDebugBins; // 0x5b
    bool m_field5c; // 0x5c
    private: char pad_5d[0x3]; public:
    regenny::shared::ndlib::script::ModuleRequest::ModuleRequestList* m_moduleRequestListActual; // 0x60
    regenny::shared::ndlib::script::ModuleBucketMap m_ModulesBucket; // 0x68
    private: char pad_258[0x30]; public:
    ScriptCFuncMap* m_NativeMap; // 0x288
    regenny::shared::ndlib::script::ScriptModule::Loader* s_SLoadM; // 0x290
    private: char pad_298[0x4e8]; public:
    void* m_field780; // 0x780
    private: char pad_788[0x10]; public:
    regenny::shared::ndlib::script::ModuleBucketMap* m_DebugModulesBucket; // 0x798
}; // Size: 0x7a0
#pragma pack(pop)
}
