#pragma once
#include <NdGameSdk/sdkstringid.hpp>
#include <cstdint>
namespace regenny::shared::ndlib::script {
#pragma pack(push, 1)
struct relocatableModule {
    void* vfTable; // 0x0
    uint64_t m_pRecord; // 0x8
    uint64_t field_10; // 0x10
    uint64_t field_18; // 0x18
    uint16_t field_20; // 0x20
}; // Size: 0x22
#pragma pack(pop)
}
