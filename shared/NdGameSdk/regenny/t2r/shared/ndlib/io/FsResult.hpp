#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::ndlib::io {
#pragma pack(push, 1)
struct FsResult {
    uint32_t m_code; // 0x0
    void* m_payload; // 0x4
    private: char pad_c[0x4]; public:
}; // Size: 0x10
#pragma pack(pop)
}
