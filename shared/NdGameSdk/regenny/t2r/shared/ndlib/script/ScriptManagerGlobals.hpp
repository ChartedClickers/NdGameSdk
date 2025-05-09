#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
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
    StringId64 m_hash; // 0x10
    private: char pad_18[0x28]; public:
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
    bool field4e; // 0x4e
    bool m_ValidateModuleSize; // 0x4f
    bool m_AssertonGlobalSymbolLookup; // 0x50
    bool m_EnableScripts; // 0x51
    bool field52; // 0x52
    bool field53; // 0x53
    bool m_DisableScriptDebugPrims; // 0x54
    bool m_DisplayGlobalSymbols; // 0x55
    bool field56; // 0x56
    bool m_DisableDebugBinSuppressionforGameTasks; // 0x57
    bool field58; // 0x58
    private: char pad_59[0x7]; public:
    regenny::shared::ndlib::script::ModuleRequest::ModuleRequestList* m_moduleRequestListActual; // 0x60
    void* field68; // 0x68
    private: char pad_70[0x48]; public:
    void* fieldb8; // 0xb8
    private: char pad_c0[0x50]; public:
    void* field110; // 0x110
    private: char pad_118[0x170]; public:
    ScriptCFuncMap* m_NativeMap; // 0x288
    regenny::shared::ndlib::script::ScriptModule::Loader* SLoadM; // 0x290
    private: char pad_298[0x4e8]; public:
    void* field780; // 0x780
    private: char pad_788[0x18]; public:
}; // Size: 0x7a0
#pragma pack(pop)
}
