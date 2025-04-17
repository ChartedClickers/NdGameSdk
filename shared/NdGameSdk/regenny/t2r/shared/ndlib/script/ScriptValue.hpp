#pragma once
#include <NdGameSdk/sdkstringid.hpp>
#include <cstdint>
namespace regenny::shared::ndlib::script {
#pragma pack(push, 1)
struct ScriptValue {
    uint64_t val[16]; // 0x0
}; // Size: 0x80
#pragma pack(pop)
}
