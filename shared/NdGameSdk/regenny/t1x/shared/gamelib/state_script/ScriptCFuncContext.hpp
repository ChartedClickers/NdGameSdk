#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "..\..\ndlib\script\ScriptValue.hpp"
namespace regenny::shared::gamelib::state_script {
#pragma pack(push, 1)
struct ScriptCFuncContext {
    regenny::shared::ndlib::script::ScriptValue m_args; // 0x0
    private: char pad_80[0x10]; public:
    StringId64 m_scriptHash; // 0x90
    private: char pad_98[0xb8]; public:
}; // Size: 0x150
#pragma pack(pop)
}
