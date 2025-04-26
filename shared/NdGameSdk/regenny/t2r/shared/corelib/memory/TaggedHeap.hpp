#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::corelib::memory {
#pragma pack(push, 1)
struct TaggedHeap {
    struct VTable {
        virtual ~VTable() = default;
        private: virtual void virtual_function_1() = 0; public:
        private: virtual void virtual_function_2() = 0; public:
        private: virtual void virtual_function_3() = 0; public:
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
        private: virtual void virtual_function_25() = 0; public:
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
        virtual uint64_t GetBlockSize() = 0;
    }; // Size: 0x8

    VTable* vftable; // 0x0
    private: char pad_8[0xdb300]; public:
}; // Size: 0xdb308
#pragma pack(pop)
}
