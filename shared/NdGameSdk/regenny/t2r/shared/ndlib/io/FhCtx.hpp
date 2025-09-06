#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::ndlib::io {
#pragma pack(push, 1)
struct FhCtx {
    uint64_t m_sizeBytes; // 0x0
    uint64_t m_ctimeSec; // 0x8
    uint64_t m_ctimeNsec; // 0x10
    uint64_t m_atimeSec; // 0x18
    private: char pad_20[0x8]; public:
    uint64_t m_mtimeSec; // 0x28
    uint64_t m_mtimeNsec; // 0x30
    private: char pad_38[0x10]; public:
    uint64_t m_sizeAlt; // 0x48
}; // Size: 0x50
#pragma pack(pop)
}
