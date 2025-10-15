#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "..\..\ndlib\script\ScriptValue.hpp"
namespace regenny::shared::gamelib::state_script {
#pragma pack(push, 1)
struct ScriptCFuncContext {
    regenny::shared::ndlib::script::ScriptValue m_args; // 0x0
    private: char pad_80[0x188]; public:
}; // Size: 0x208
#pragma pack(pop)
}
