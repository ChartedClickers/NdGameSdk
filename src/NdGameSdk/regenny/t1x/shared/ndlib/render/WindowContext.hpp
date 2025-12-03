#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "WindowContextType.hpp"
namespace regenny::shared::ndlib::render {
#pragma pack(push, 1)
struct WindowContext {
    regenny::shared::ndlib::render::WindowContextType m_ContextType; // 0x0
    uint32_t m_flags; // 0x4
    void* m_pContextSlot; // 0x8
    void* m_pQueueHead; // 0x10
    void* m_pQueueTail; // 0x18
    uint32_t m_status; // 0x20
    private: char pad_24[0x4]; public:
    uint64_t m_field28; // 0x28
}; // Size: 0x30
#pragma pack(pop)
}
