#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::corelib::job {
#pragma pack(push, 1)
struct WorkerThreadDesc {
    struct Config {
        private: char pad_0[0x8]; public:
        uint64_t m_workerPriority; // 0x8
        private: char pad_10[0x20]; public:
    }; // Size: 0x30

    void* m_listHead; // 0x0
    void* m_listTail; // 0x8
    void* m_next; // 0x10
    void* m_prev; // 0x18
    void* m_waitNext; // 0x20
    void* m_waitPrev; // 0x28
    void* m_tlsBlock; // 0x30
    uint32_t m_flags; // 0x38
    private: char pad_3c[0x3c]; public:
    uint64_t m_context; // 0x78
    Config m_config; // 0x80
    private: char pad_b0[0x8]; public:
    uint8_t m_scheduler[128]; // 0xb8
    void* m_nativeHandle; // 0x138
    uint32_t m_threadId; // 0x140
    uint32_t m_joinable; // 0x144
    void* m_threadTLS; // 0x148
    uint64_t m_waitCookie; // 0x150
    uint8_t m_shuttingDown; // 0x158
    private: char pad_159[0xa7]; public:
}; // Size: 0x200
#pragma pack(pop)
}
