#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "ModuleRequest.hpp"
#include "ScriptModule.hpp"
namespace regenny::shared::ndlib::script {
#pragma pack(push, 1)
struct ScriptManagerGlobals {
    uint64_t field_0; // 0x0
    private: char pad_8[0x8]; public:
    StringId64 m_hash; // 0x10
    uint32_t field_18; // 0x18
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
    bool DisplayGlobalSymbols; // 0x55
    bool m_field56; // 0x56
    bool m_DisableDebugBinSuppressionforGameTasks; // 0x57
    bool m_field58; // 0x58
    uint16_t field_5c; // 0x59
    char field_5e; // 0x5b
    private: char pad_5c[0x4]; public:
    uint32_t field_60; // 0x60
    private: char pad_64[0x4]; public:
    uint64_t field_68; // 0x68
    regenny::shared::ndlib::script::ModuleRequest::ModuleRequestList* m_moduleRequestListActual; // 0x70
    uint64_t field_78; // 0x78
    private: char pad_80[0x68]; public:
    uint64_t field_e8; // 0xe8
    private: char pad_f0[0x10]; public:
    uint64_t field_100; // 0x100
    uint32_t field_108; // 0x108
    uint32_t field_10c; // 0x10c
    uint64_t field_110; // 0x110
    uint64_t field_118; // 0x118
    uint64_t field_120; // 0x120
    private: char pad_128[0x88]; public:
    uint32_t field_1b0; // 0x1b0
    private: char pad_1b4[0x4]; public:
    uint32_t field_1b8; // 0x1b8
    private: char pad_1bc[0x4]; public:
    uint64_t field_1c0; // 0x1c0
    uint64_t field_1c8; // 0x1c8
    uint64_t field_1d0; // 0x1d0
    private: char pad_1d8[0x88]; public:
    uint32_t field_260; // 0x260
    uint32_t field_264; // 0x264
    private: char pad_268[0x20]; public:
    uint64_t field_288; // 0x288
    uint64_t field_290; // 0x290
    uint64_t m_pNativeMap; // 0x298
    regenny::shared::ndlib::script::ScriptModule::Loader* s_SLoadM; // 0x2a0
    private: char pad_2a8[0x2bd8]; public:
    uint64_t field_2e80; // 0x2e80
    private: char pad_2e88[0x4b0]; public:
    uint64_t field_3338; // 0x3338
    bool field_3340; // 0x3340
    private: char pad_3341[0x2a]; public:
    bool m_moduleLoader; // 0x336b
    bool field_336c; // 0x336c
    bool field_336d; // 0x336d
    private: char pad_336e[0x3]; public:
    bool field_3371; // 0x3371
    private: char pad_3372[0xe]; public:
    uint32_t field_3380; // 0x3380
    private: char pad_3384[0x4]; public:
    uint64_t field_3388; // 0x3388
    uint64_t field_3390; // 0x3390
    uint64_t field_3398; // 0x3398
    uint32_t field_33a0; // 0x33a0
    private: char pad_33a4[0x4]; public:
    uint64_t field_33a8; // 0x33a8
}; // Size: 0x33b0
#pragma pack(pop)
}
