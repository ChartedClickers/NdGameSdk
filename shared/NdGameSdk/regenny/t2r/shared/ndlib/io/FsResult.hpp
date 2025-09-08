#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::ndlib::io {
#pragma pack(push, 1)
struct FsResult {
    uint32_t m_code; // 0x0
    private: char pad_4[0x4]; public:
    void* m_payload; // 0x8
}; // Size: 0x10
#pragma pack(pop)
}
