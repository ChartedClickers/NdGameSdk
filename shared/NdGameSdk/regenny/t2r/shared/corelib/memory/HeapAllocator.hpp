#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "HeapAllocatorWithOverflow.hpp"
namespace regenny::shared::corelib::memory {
#pragma pack(push, 1)
struct HeapAllocator : public HeapAllocatorWithOverflow {
    // Metadata: utf8*
    char* m_file; // 0x100
    // Metadata: utf8*
    char* m_function; // 0x108
    uint32_t m_line; // 0x110
    bool m_field114; // 0x114
    private: char pad_115[0xb]; public:
}; // Size: 0x120
#pragma pack(pop)
}
