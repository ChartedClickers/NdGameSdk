#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::corelib::system::platform {
#pragma pack(push, 1)
struct ndsys {
    struct Thread {
        void* m_nativeThread; // 0x0
        uint32_t m_id; // 0x8
        uint32_t m_joinable; // 0xc
    }; // Size: 0x10

    struct ThreadDesc {
        uint64_t m_stackSize; // 0x0
        uint32_t m_priority; // 0x8
        uint32_t m_affinity; // 0xc
        uint32_t m_flags; // 0x10
        char m_name[256]; // 0x14
        private: char pad_114[0xc]; public:
    }; // Size: 0x120

    struct Fiber {
        void* m_nativeFiber; // 0x0
        void* m_CtxBlock; // 0x8
    }; // Size: 0x10

    struct FiberContext {
        char m_field0[64]; // 0x0
        char m_field40[64]; // 0x40
        char m_field80[64]; // 0x80
        char m_fieldc0[64]; // 0xc0
        char m_field100[64]; // 0x100
        char m_field140[64]; // 0x140
        char m_field180[64]; // 0x180
        char m_field1c0[64]; // 0x1c0
        char m_field200[64]; // 0x200
        char m_field240[64]; // 0x240
    }; // Size: 0x280

    struct Mutex {
        enum Type : uint32_t {
            MUTEX_RECURSIVE = 1,
        };

        void* m_data; // 0x0
        uint32_t m_threadID; // 0x8
        uint32_t m_lockCount; // 0xc
        Type m_type; // 0x10
        bool m_initialized; // 0x14
        private: char pad_15[0x2b]; public:
    }; // Size: 0x40

    struct ConditionVariable {
        void* m_ConditionVar; // 0x0
        bool m_initialized; // 0x8
        private: char pad_9[0x17]; public:
    }; // Size: 0x20

}; // Size: 0x0
#pragma pack(pop)
}
