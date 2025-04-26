#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::ndlib::script {
#pragma pack(push, 1)
struct ScriptCFunc {
    void** c_func_caller; // 0x0
    void* c_script_func; // 0x8
}; // Size: 0x10
#pragma pack(pop)
}
