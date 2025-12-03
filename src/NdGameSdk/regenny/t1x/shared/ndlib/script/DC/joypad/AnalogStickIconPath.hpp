#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::ndlib::script::DC::joypad {
#pragma pack(push, 1)
struct AnalogStickIconPath {
    // Metadata: utf8*
    char* m_Path; // 0x0
    // Metadata: utf8*
    char* m_Path2; // 0x8
    StringId64 m_hash; // 0x10
}; // Size: 0x18
#pragma pack(pop)
}
