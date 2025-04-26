#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "ModuleRequest.hpp"
#include "ScriptModuleLoader.hpp"
namespace regenny::shared::ndlib::script {
#pragma pack(push, 1)
struct ScriptManagerGlobals {
    uint64_t field_0; // 0x0
    private: char pad_8[0x8]; public:
    uint64_t field_10; // 0x10
    uint32_t field_18; // 0x18
    private: char pad_1c[0x4]; public:
    uint64_t field_20; // 0x20
    private: char pad_28[0x8]; public:
    uint64_t field_30; // 0x30
    private: char pad_38[0x8]; public:
    bool field_40; // 0x40
    private: char pad_41[0x2]; public:
    bool m_DisplayRequestedModules; // 0x43
    uint32_t field_44; // 0x44
    private: char pad_48[0x2]; public:
    uint32_t field_4a; // 0x4a
    uint16_t field_4e; // 0x4e
    private: char pad_50[0x1]; public:
    uint32_t field_51; // 0x51
    bool m_DisplayGlobalSymbols; // 0x55
    bool field_56; // 0x56
    private: char pad_57[0x1]; public:
    uint32_t field_58; // 0x58
    uint16_t field_5c; // 0x5c
    char field_5e; // 0x5e
    private: char pad_5f[0x1]; public:
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
    regenny::shared::ndlib::script::ScriptModuleLoader s_SLoadM; // 0x2a0
    private: char pad_3370[0x1]; public:
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
