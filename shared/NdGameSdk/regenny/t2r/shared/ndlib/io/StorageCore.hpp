#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "FileRecord.hpp"
namespace regenny::shared::ndlib::io {
#pragma pack(push, 1)
struct StorageCore {
    regenny::shared::ndlib::io::FileRecord::RBTreeHeader* m_recordTreeHead; // 0x0
    uint64_t m_mapCount; // 0x8
    regenny::shared::ndlib::io::FileRecord** m_openBegin; // 0x10
    regenny::shared::ndlib::io::FileRecord** m_openEnd; // 0x18
    regenny::shared::ndlib::io::FileRecord** m_openCap; // 0x20
    CRITICAL_SECTION m_cs; // 0x28
    private: char pad_50[0x10]; public:
    void* m_dsFactory; // 0x60
    void* m_dsQueue; // 0x68
    bool m_useDirectStorage; // 0x70
    private: char pad_71[0x97]; public:
    void* m_OnProcessSpawnedFunc; // 0x108
    private: char pad_110[0x10]; public:
}; // Size: 0x120
#pragma pack(pop)
}
