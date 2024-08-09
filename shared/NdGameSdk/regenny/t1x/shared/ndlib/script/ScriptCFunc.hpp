#pragma once
#include <NdGameSdk/sdkstringid.hpp>
#include <cstdint>
namespace regenny::shared::ndlib::script {
#pragma pack(push, 1)
struct ScriptCFunc {
    void** c_func_caller; // 0x0
    void* c_script_func; // 0x8
}; // Size: 0x10
#pragma pack(pop)
}
