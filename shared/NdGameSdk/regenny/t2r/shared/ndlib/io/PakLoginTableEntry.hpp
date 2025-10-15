#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "Package.hpp"
namespace regenny::shared::ndlib::io {
#pragma pack(push, 1)
struct PakLoginTableEntry : public Package::ResItem {
    struct ResourcePair {
        uint32_t m_pageIdx; // 0x0
        uint32_t m_itemOfs; // 0x4
    }; // Size: 0x8

    uint32_t m_MaxResources; // 0x30
    private: char pad_34[0x4]; public:
    ResourcePair m_wantedPage; // 0x38
}; // Size: 0x40
#pragma pack(pop)
}
