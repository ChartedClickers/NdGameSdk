#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "..\..\corelib\system\platform\ndsys.hpp"
#include "..\..\ndlib\io\FileSystem.hpp"
namespace regenny::shared::corelib::memory {
struct PoolAllocator;
}
namespace regenny::shared::gamelib::level {
struct LevelDef;
}
namespace regenny::shared::gamelib::level {
#pragma pack(push, 1)
struct LevelDefLoader {
    enum State : uint32_t {
        Idle = 0,
        Loading = 1,
        Completed = 2,
    };

    struct BatchRequest {
        uint32_t m_pendingResolveIds[16]; // 0x0
        regenny::shared::ndlib::io::FileSystem::BatchResolveItem m_resolveItems[16]; // 0x40
        regenny::shared::ndlib::io::FileSystem::BatchReadItem m_readItems[16]; // 0x140
        uint32_t m_releaseIds[16]; // 0x3c0
        void* m_fileBuffers[16]; // 0x400
        uint64_t m_fileSizes[16]; // 0x480
        void* m_readOps[16]; // 0x500
        regenny::shared::gamelib::level::LevelDef* m_levelDefs[16]; // 0x580
    }; // Size: 0x600

    private: char pad_0[0x1000]; public:
    BatchRequest m_batchRequest; // 0x1000
    uint32_t m_batchKey; // 0x1600
    uint32_t m_batchCount; // 0x1604
    State m_state; // 0x1608
    private: char pad_160c[0x4]; public:
    regenny::shared::corelib::system::platform::ndsys::Thread m_thread; // 0x1610
    regenny::shared::corelib::system::platform::ndsys::Mutex m_mutex; // 0x1620
    regenny::shared::corelib::memory::PoolAllocator* m_allocator; // 0x1660
    bool m_stopRequested; // 0x1668
    private: char pad_1669[0x7]; public:
    regenny::shared::corelib::system::platform::ndsys::ConditionVariable m_batchReadyCv; // 0x1670
}; // Size: 0x1690
#pragma pack(pop)
}
