#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::gamelib::state_script {
struct ScriptCFuncContext;
}
namespace regenny::shared::gamelib::state_script {
#pragma pack(push, 1)
struct CFunctionStack {
    regenny::shared::gamelib::state_script::ScriptCFuncContext* m_pScriptCFuncContext; // 0x0
    uint32_t m_NumArgs; // 0x8
    uint32_t field_c; // 0xc
    uint32_t m_FunctionArgs; // 0x10
    private: char pad_14[0x4]; public:
    uint64_t field_18; // 0x18
    uint64_t field_20; // 0x20
    uint64_t field_28; // 0x28
    bool field_30; // 0x30
    bool m_MakeAllErrorsFatal; // 0x31
    private: char pad_32[0xe]; public:
}; // Size: 0x40
#pragma pack(pop)
}
