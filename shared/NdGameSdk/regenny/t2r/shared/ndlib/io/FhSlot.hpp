#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::ndlib::io {
#pragma pack(push, 1)
struct FhSlot {
    uint32_t m_fh; // 0x0
    uint32_t m_flags; // 0x4
    void* m_next; // 0x8
}; // Size: 0x10
#pragma pack(pop)
}
