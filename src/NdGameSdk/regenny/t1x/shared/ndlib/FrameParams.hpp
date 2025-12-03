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
    }; // Size: 0x38

    struct DeviceContextHandle {
        void* m_pContext; // 0x0
        uint64_t m_field8; // 0x8
    }; // Size: 0x10

    struct DynamicContext {
        void* m_pContext; // 0x0
        uint64_t m_field8; // 0x8
    }; // Size: 0x10

    uint64_t m_frameNumber; // 0x0
    private: char pad_8[0x48]; public:
    void* m_gfxEopTick; // 0x50
    private: char pad_58[0x6a20]; public:
    DeviceContextHandle* m_pGfxContext; // 0x6a78
    DynamicContext* m_DynamicRenderContext; // 0x6a80
    private: char pad_6a88[0xccd0]; public:
    void* m_pRenderCamera; // 0x13758
    private: char pad_13760[0x1758]; public:
    void* m_pUploadQueue; // 0x14eb8
    private: char pad_14ec0[0x26c0]; public:
}; // Size: 0x17580
#pragma pack(pop)
}
