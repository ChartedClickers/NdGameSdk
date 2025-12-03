#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::ndlib::render::text {
#pragma pack(push, 1)
struct DebugStringBase {
    void* vftable; // 0x0
    uint64_t unk08; // 0x8
    vec4 vec; // 0x10
    uint32_t color; // 0x20
    float scale; // 0x24
    uint8_t fade; // 0x28
    private: char pad_29[0x3]; public:
    uint64_t reserved; // 0x2c
    uint32_t field_34; // 0x34
    uint64_t field_38; // 0x38
    // Metadata: utf8*
    char* pText; // 0x40
}; // Size: 0x48
#pragma pack(pop)
}
