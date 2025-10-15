#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "..\..\corelib\containers\FixedSizeHeap.hpp"
namespace regenny::shared::gamelib::level {
#pragma pack(push, 1)
struct LevelMgr {
    struct Configuration {
        uint32_t m_field0; // 0x0
        uint32_t m_field4; // 0x4
        uint32_t m_field8; // 0x8
        uint32_t m_fieldc; // 0xc
    }; // Size: 0x10

    regenny::shared::corelib::containers::FixedSizeHeap m_heap; // 0x0
    private: char pad_58[0x8]; public:
    void* m_field60; // 0x60
    private: char pad_68[0x481eb8]; public:
}; // Size: 0x481f20
#pragma pack(pop)
}
