#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::corelib::system::platform {
#pragma pack(push, 1)
class ndsys {
public:
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
