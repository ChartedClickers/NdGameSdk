#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "BaseAllocator.hpp"
namespace regenny::shared::corelib::memory {
#pragma pack(push, 1)
struct Allocator : public BaseAllocator {
    struct VTable {
        virtual ~VTable() = default;
        private: virtual void virtual_function_1() = 0; public:
        private: virtual void virtual_function_2() = 0; public:
        private: virtual void virtual_function_3() = 0; public:
        private: virtual void virtual_function_4() = 0; public:
        private: virtual void virtual_function_5() = 0; public:
        private: virtual void virtual_function_6() = 0; public:
        virtual uint64_t PostAllocate(uint64_t pSize, uint64_t pAlignment, char* pFunction, uint32_t pLine, char* pFilePath) = 0;
    }; // Size: 0x8

    private: char pad_58[0x58]; public:
    void* m_Data; // 0xb0
    private: char pad_b8[0x10]; public:
    uint64_t m_size; // 0xc8
}; // Size: 0xd0
#pragma pack(pop)
}
