#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::ndlib::render::ndgi::win {
#pragma pack(push, 1)
struct WinInitOptions {
    uint64_t m_loaderCount; // 0x0
    private: char pad_8[0x10]; public:
    uint64_t m_deformerChunkBytes; // 0x18
    uint32_t m_shaderBudgetMiB; // 0x20
    uint8_t m_enablePsoCache; // 0x24
    private: char pad_25[0xb]; public:
    uint32_t m_shaderParallelism; // 0x30
    uint32_t m_computeBudgetMiB; // 0x34
    uint32_t m_computeParallelism; // 0x38
    uint32_t m_computeIterCount; // 0x3c
    uint32_t m_dxilBudgetMiB; // 0x40
    uint32_t m_dxilParallelism; // 0x44
    private: char pad_48[0x40]; public:
}; // Size: 0x88
#pragma pack(pop)
}
