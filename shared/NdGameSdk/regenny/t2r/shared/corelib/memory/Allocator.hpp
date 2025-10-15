#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::corelib::memory {
#pragma pack(push, 1)
struct Allocator {
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

    VTable* vftable; // 0x0
    private: char pad_8[0x28]; public:
    uint16_t m_flags; // 0x30
    uint8_t m_state; // 0x32
    private: char pad_33[0x5]; public:
    void* m_pTracker; // 0x38
    // Metadata: utf8*
    char* m_contextName; // 0x40
    StringId64 m_contextHash; // 0x48
    bool m_initialized; // 0x50
    private: char pad_51[0xf]; public:
}; // Size: 0x60
#pragma pack(pop)
}
