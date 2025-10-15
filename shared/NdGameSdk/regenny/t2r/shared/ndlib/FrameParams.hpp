#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::ndlib {
#pragma pack(push, 1)
struct FrameParams {
    struct InitParams {
        regenny::shared::ndlib::FrameParams* m_ringBase; // 0x0
        uint64_t m_poolSlice0; // 0x8
        uint64_t m_poolSlice1; // 0x10
        uint64_t m_poolSlice2; // 0x18
        uint64_t m_poolSlice3; // 0x20
        uint64_t m_poolSlice4; // 0x28
        uint64_t m_poolSlice5; // 0x30
        private: char pad_38[0x330]; public:
    }; // Size: 0x368

    uint64_t m_frameNumber; // 0x0
    private: char pad_8[0x50]; public:
    void* m_gfxEopTick; // 0x58
    private: char pad_60[0x6a20]; public:
    void* m_DynamicRenderContext; // 0x6a80
    private: char pad_6a88[0xca68]; public:
    void* m_pExposureMapComputeContext; // 0x134f0
    void* m_pExposureMapLastLabel; // 0x134f8
    private: char pad_13500[0x30]; public:
    void* m_pRenderCamera; // 0x13530
    private: char pad_13538[0x1d08]; public:
    void* m_pUploadQueue; // 0x15240
    private: char pad_15248[0x2600]; public:
    bool m_ArePackageQueuesBusy; // 0x17848
    private: char pad_17849[0xb7]; public:
}; // Size: 0x17900
#pragma pack(pop)
}
