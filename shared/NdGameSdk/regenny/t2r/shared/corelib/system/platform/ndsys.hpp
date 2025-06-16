#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::corelib::system::platform {
#pragma pack(push, 1)
class ndsys {
public:
    class Mutex {
    public:
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

    class ConditionVariable {
        private: char pad_0[0x20]; public:
    }; // Size: 0x20

}; // Size: 0x0
#pragma pack(pop)
}
