#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "..\containers\FixedSizeHeap.hpp"
namespace regenny::shared::corelib::job {
#pragma pack(push, 1)
struct JobHeap {
    regenny::shared::corelib::containers::FixedSizeHeap m_Heap; // 0x0
    private: char pad_58[0x30]; public:
    uint64_t m_field88; // 0x88
    uint32_t m_field90; // 0x90
    uint32_t m_field94; // 0x94
}; // Size: 0x98
#pragma pack(pop)
}
