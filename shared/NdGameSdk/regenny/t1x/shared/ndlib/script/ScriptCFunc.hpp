#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::gamelib::state_script {
struct ScriptCFuncContext;
}
namespace regenny::shared::ndlib::script {
struct ScriptValue;
}
namespace regenny::shared::ndlib::script {
#pragma pack(push, 1)
struct ScriptCFunc {
    struct VTable {
        virtual uint64_t CallScriptCFunc(regenny::shared::gamelib::state_script::ScriptCFuncContext* CFuncContext, uint32_t ArgsNum, regenny::shared::ndlib::script::ScriptValue* return_, uint64_t arg4) = 0;
    }; // Size: 0x8

    VTable* vftable; // 0x0
    void* m_pFunction; // 0x8
}; // Size: 0x10
#pragma pack(pop)
}
