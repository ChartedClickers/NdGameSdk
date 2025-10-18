#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::ndlib::render {
struct WindowContext;
}
namespace regenny::shared::ndlib::render::text {
struct DebugStringBase;
}
namespace regenny::shared::ndlib {
struct FrameParams;
}
namespace regenny::shared::ndlib::render::util {
#pragma pack(push, 1)
struct PrimServer {
    struct VTable {
        private: char pad_8[0x208]; public:
        virtual ~VTable() = default;
        virtual char* Render(regenny::shared::ndlib::render::WindowContext* WindowContext) = 0;
        virtual void Render2D(regenny::shared::ndlib::render::WindowContext* WindowContext) = 0;
        virtual void Render3D(regenny::shared::ndlib::render::WindowContext* WindowContext) = 0;
        private: virtual void virtual_function_4() = 0; public:
        private: virtual void virtual_function_5() = 0; public:
        private: virtual void virtual_function_6() = 0; public:
        private: virtual void virtual_function_7() = 0; public:
        private: virtual void virtual_function_8() = 0; public:
        private: virtual void virtual_function_9() = 0; public:
        private: virtual void virtual_function_10() = 0; public:
        private: virtual void virtual_function_11() = 0; public:
        private: virtual void virtual_function_12() = 0; public:
        private: virtual void virtual_function_13() = 0; public:
        private: virtual void virtual_function_14() = 0; public:
        private: virtual void virtual_function_15() = 0; public:
        private: virtual void virtual_function_16() = 0; public:
        private: virtual void virtual_function_17() = 0; public:
        private: virtual void virtual_function_18() = 0; public:
        private: virtual void virtual_function_19() = 0; public:
        private: virtual void virtual_function_20() = 0; public:
        private: virtual void virtual_function_21() = 0; public:
        private: virtual void virtual_function_22() = 0; public:
        private: virtual void virtual_function_23() = 0; public:
        private: virtual void virtual_function_24() = 0; public:
        virtual uint64_t RenderString(regenny::shared::ndlib::render::text::DebugStringBase* header, void* DebugPrimParams, void* BoundFrame) = 0;
        private: virtual void virtual_function_26() = 0; public:
        private: virtual void virtual_function_27() = 0; public:
        private: virtual void virtual_function_28() = 0; public:
        private: virtual void virtual_function_29() = 0; public:
        private: virtual void virtual_function_30() = 0; public:
        private: virtual void virtual_function_31() = 0; public:
        private: virtual void virtual_function_32() = 0; public:
        private: virtual void virtual_function_33() = 0; public:
        private: virtual void virtual_function_34() = 0; public:
        private: virtual void virtual_function_35() = 0; public:
        private: virtual void virtual_function_36() = 0; public:
        private: virtual void virtual_function_37() = 0; public:
        private: virtual void virtual_function_38() = 0; public:
        private: virtual void virtual_function_39() = 0; public:
        private: virtual void virtual_function_40() = 0; public:
        private: virtual void virtual_function_41() = 0; public:
        private: virtual void virtual_function_42() = 0; public:
        private: virtual void virtual_function_43() = 0; public:
        private: virtual void virtual_function_44() = 0; public:
        private: virtual void virtual_function_45() = 0; public:
        private: virtual void virtual_function_46() = 0; public:
        private: virtual void virtual_function_47() = 0; public:
        private: virtual void virtual_function_48() = 0; public:
        private: virtual void virtual_function_49() = 0; public:
        private: virtual void virtual_function_50() = 0; public:
        private: virtual void virtual_function_51() = 0; public:
        private: virtual void virtual_function_52() = 0; public:
        private: virtual void virtual_function_53() = 0; public:
        private: virtual void virtual_function_54() = 0; public:
        virtual void InitFrameParams(regenny::shared::ndlib::FrameParams* RenderFrameParams) = 0;
        virtual void ClearAll() = 0;
        virtual void ReleaseMem() = 0;
        virtual void ReleaseFrameHeap() = 0;
        virtual void SetPaused(bool arg2, bool arg3, int arg4) = 0;
        virtual void CullStale() = 0;
    }; // Size: 0x210

    struct InitParams {
        uint32_t m_memoryBufferSize[19]; // 0x0
    }; // Size: 0x4c

    VTable* vftable; // 0x0
    private: char pad_8[0x1378]; public:
}; // Size: 0x1380
#pragma pack(pop)
}
