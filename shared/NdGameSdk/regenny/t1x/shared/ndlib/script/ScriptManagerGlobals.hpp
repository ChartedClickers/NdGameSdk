#pragma once
#include <NdGameSdk/sdkregenny.hpp>
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

    uint64_t field_0; // 0x0
    private: char pad_8[0x8]; public:
    StringId64 m_JlsContext; // 0x10
    regenny::shared::corelib::job::JlsContext m_JlsIndex; // 0x18
    private: char pad_1c[0x4]; public:
    uint64_t field_20; // 0x20
    private: char pad_28[0x8]; public:
    uint64_t field_30; // 0x30
    private: char pad_38[0x8]; public:
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
    private: char pad_5d[0x1]; public:
    char m_field5e; // 0x5e
    private: char pad_5f[0x1]; public:
    uint32_t m_field60; // 0x60
    private: char pad_64[0x4]; public:
    uint64_t m_field68; // 0x68
    regenny::shared::ndlib::script::ModuleRequest::ModuleRequestList* m_moduleRequestListActual; // 0x70
    regenny::shared::ndlib::script::ModuleBucketMap m_ModulesBucket; // 0x78
    private: char pad_268[0x30]; public:
    ScriptCFuncMap* m_NativeMap; // 0x298
    regenny::shared::ndlib::script::ScriptModule::Loader* s_SLoadM; // 0x2a0
    private: char pad_2a8[0x2bd8]; public:
    uint64_t m_field2e80; // 0x2e80
    private: char pad_2e88[0x4b0]; public:
    uint64_t m_field3338; // 0x3338
    bool m_field3340; // 0x3340
    private: char pad_3341[0x2a]; public:
    bool m_moduleLoader; // 0x336b
    bool m_field336c; // 0x336c
    bool m_field336d; // 0x336d
    private: char pad_336e[0x3]; public:
    bool m_field3371; // 0x3371
    private: char pad_3372[0xe]; public:
    uint32_t m_field3380; // 0x3380
    private: char pad_3384[0x4]; public:
    uint64_t m_field3388; // 0x3388
    uint64_t m_field3390; // 0x3390
    uint64_t m_field3398; // 0x3398
    uint32_t m_field33a0; // 0x33a0
    private: char pad_33a4[0x4]; public:
    uint64_t m_field33a8; // 0x33a8
}; // Size: 0x33b0
#pragma pack(pop)
}
