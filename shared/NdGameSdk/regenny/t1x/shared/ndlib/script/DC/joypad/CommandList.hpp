#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::ndlib::script::DC::joypad {
#pragma pack(push, 1)
struct CommandList {
    uint64_t m_size; // 0x0
    StringId64* m_commands; // 0x8
}; // Size: 0x10
#pragma pack(pop)
}
