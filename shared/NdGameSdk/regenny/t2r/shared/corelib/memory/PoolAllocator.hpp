#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "Allocator.hpp"
namespace regenny::shared::corelib::memory {
#pragma pack(push, 1)
struct PoolAllocator : public Allocator {
    struct PoolStack {
        uint32_t m_guard0; // 0x0
        uint32_t m_guard1; // 0x4
        uint32_t m_ticket; // 0x8
        private: char pad_c[0x4]; public:
        void* m_chunkHead; // 0x10
        void* m_chunkFree; // 0x18
        void* m_blockStart; // 0x20
        uint32_t m_blockSize; // 0x28
        uint32_t m_lastOffset; // 0x2c
        uint32_t m_activeCount; // 0x30
        uint32_t m_alignment; // 0x34
        uint32_t m_freeCount; // 0x38
        uint32_t m_hasBlock; // 0x3c
        uint32_t m_hasTail; // 0x40
        uint32_t m_lastTicketIdx; // 0x44
        uint64_t m_waitListLock; // 0x48
        uint8_t m_waitListEnabled; // 0x50
        private: char pad_51[0x17]; public:
    }; // Size: 0x68

    PoolStack m_stack; // 0x60
    private: char pad_c8[0x8]; public:
    void* m_mem; // 0xd0
    uint64_t m_size; // 0xd8
}; // Size: 0xe0
#pragma pack(pop)
}
