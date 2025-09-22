#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "Allocator.hpp"
#include "HeapArena.hpp"
namespace regenny::shared::corelib::memory {
#pragma pack(push, 1)
struct HeapAllocatorWithOverflow : public Allocator {
    regenny::shared::corelib::memory::HeapArena m_HeapArena; // 0x60
    void* m_Data; // 0xb0
    private: char pad_b8[0x10]; public:
    uint64_t m_size; // 0xc8
    private: char pad_d0[0x30]; public:
}; // Size: 0x100
#pragma pack(pop)
}
