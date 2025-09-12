#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "..\..\corelib\system\platform\ndsys.hpp"
namespace regenny::shared::ndlib::io {
struct FileSystem;
}
namespace regenny::shared::ndlib::io {
struct PackageMgr;
}
namespace regenny::shared::ndlib::io {
#pragma pack(push, 1)
struct PrefetchMgr {
    struct PrefetchEntry {
        uint8_t m_Flags; // 0x0
        uint8_t m_DirSlot; // 0x1
        uint16_t m_field02; // 0x2
        uint32_t m_field04; // 0x4
        // Metadata: utf8*
        char* m_FileName; // 0x8
    }; // Size: 0x10

    void* m_EntryTable; // 0x0
    void* m_EntryAux; // 0x8
    uint64_t m_PendingBits[94]; // 0x10
    uint32_t m_field300; // 0x300
    uint32_t m_MaxEntries; // 0x304
    regenny::shared::ndlib::io::FileSystem* m_FileSystem; // 0x308
    regenny::shared::ndlib::io::PackageMgr* m_PackageMgr; // 0x310
    private: char pad_318[0x4]; public:
    // Metadata: utf8*
    char m_GameDataPath[1024]; // 0x31c
    uint32_t m_GameDataPathLen; // 0x71c
    bool m_UseGameDataPrefix; // 0x720
    bool m_Paused; // 0x721
    private: char pad_722[0x2e]; public:
    uint32_t m_QueueHead; // 0x750
    uint32_t m_field754; // 0x754
    uint32_t m_FileNamePoolHead; // 0x758
    uint32_t m_DirSlotCount; // 0x75c
    void* m_DirTable; // 0x760
    void* m_FileNamePool; // 0x768
    uint32_t m_FileNamePoolCapacity; // 0x770
    uint32_t m_FileNameHighWater; // 0x774
    uint32_t m_FileNameUsed; // 0x778
    private: char pad_77c[0x4]; public:
    regenny::shared::corelib::system::platform::ndsys::Thread m_Threads[31]; // 0x780
    regenny::shared::corelib::system::platform::ndsys::Mutex m_PrefetchAccessLock; // 0x970
    regenny::shared::corelib::system::platform::ndsys::ConditionVariable m_PrefetchCondVar; // 0x9b0
    bool m_ShutdownRequested; // 0x9d0
    private: char pad_9d1[0xf]; public:
}; // Size: 0x9e0
#pragma pack(pop)
}
