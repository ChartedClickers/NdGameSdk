#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::ndlib {
#pragma pack(push, 1)
struct FrameParams {
    uint64_t m_frameNumber; // 0x0
    private: char pad_8[0x6a78]; public:
    void* m_DynamicRenderContext; // 0x6a80
    private: char pad_6a88[0x1a17f8]; public:
}; // Size: 0x1a8280
#pragma pack(pop)
}
