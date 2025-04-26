#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::corelib::memory {
#pragma pack(push, 1)
struct Allocator {
    void* vftable; // 0x0
    private: char pad_8[0x38]; public:
    // Metadata: utf8*
    char* m_context_name; // 0x40
    StringId64 m_context_hash; // 0x48
    private: char pad_50[0x10]; public:
    uintptr_t m_start_addr; // 0x60
    uintptr_t m_end_addr; // 0x68
    size_t m_heap_size; // 0x70
}; // Size: 0x78
#pragma pack(pop)
}
