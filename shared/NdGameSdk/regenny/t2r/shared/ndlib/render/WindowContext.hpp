#pragma once
#include <NdGameSdk/sdkstringid.hpp>
#include <cstdint>
#include "WindowContextType.hpp"
namespace regenny::shared::ndlib::render {
#pragma pack(push, 1)
struct WindowContext {
    regenny::shared::ndlib::render::WindowContextType m_ContextType; // 0x0
    void* FrameParams; // 0x4
    uint64_t field_10; // 0xc
    uint64_t field_18; // 0x14
    uint64_t field_20; // 0x1c
    uint64_t field_28; // 0x24
    private: char pad_2c[0x4]; public:
}; // Size: 0x30
#pragma pack(pop)
}
