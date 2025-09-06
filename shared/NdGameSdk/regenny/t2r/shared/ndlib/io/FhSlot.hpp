#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::ndlib::io {
struct FhCtx;
}
namespace regenny::shared::ndlib::io {
#pragma pack(push, 1)
struct FhSlot {
    uint32_t m_fh; // 0x0
    private: char pad_4[0x4]; public:
    regenny::shared::ndlib::io::FhCtx* m_ctx; // 0x8
}; // Size: 0x10
#pragma pack(pop)
}
