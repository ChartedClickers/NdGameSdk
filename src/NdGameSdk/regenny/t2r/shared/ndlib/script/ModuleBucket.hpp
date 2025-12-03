#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "..\..\corelib\containers\FixedSizeHeap.hpp"
namespace regenny::shared::ndlib::script {
#pragma pack(push, 1)
struct ModuleBucket {
    uint64_t m_data; // 0x0
    regenny::shared::corelib::containers::FixedSizeHeap m_heap; // 0x8
    uint64_t m_data2; // 0x60
    uint32_t m_elementSize; // 0x68
    uint64_t m_capacity; // 0x6c
    uint64_t m_data3; // 0x74
    uint64_t field_80; // 0x7c
    uint64_t field_88; // 0x84
    uint32_t field_90; // 0x8c
    uint32_t m_flags; // 0x90
    private: char pad_94[0x4]; public:
}; // Size: 0x98
#pragma pack(pop)
}
