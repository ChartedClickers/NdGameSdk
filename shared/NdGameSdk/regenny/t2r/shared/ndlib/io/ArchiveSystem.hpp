#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "PSARC\HeaderBE.hpp"
namespace regenny::shared::ndlib::io {
struct StorageCore;
}
namespace regenny::shared::ndlib::io {
#pragma pack(push, 1)
struct ArchiveSystem {
    enum PriorityGroup : uint32_t {
        High = 0,
        Low = 1,
    };

    struct Archive {
        uint64_t m_id; // 0x0
        regenny::shared::ndlib::io::ArchiveSystem::PriorityGroup m_priority; // 0x8
        uint32_t m_ioHandle; // 0xc
        // Metadata: utf8*
        char m_mountPrefix[1024]; // 0x10
        uint32_t m_mountPrefixLen; // 0x410
        private: char pad_414[0x4]; public:
        regenny::shared::ndlib::io::PSARC::HeaderBE m_psarcHeader; // 0x418
        private: char pad_44a[0x6]; public:
        void* m_heapBlock; // 0x450
        void* m_auxPtr; // 0x458
        void* m_lookupRoot; // 0x460
    }; // Size: 0x468

    struct File {
        uint32_t m_ioHandle; // 0x0
        uint64_t m_offset; // 0x4
        uint64_t m_size; // 0xc
        private: char pad_14[0x4]; public:
    }; // Size: 0x18

    uint32_t m_count; // 0x0
    uint32_t m_capacity; // 0x4
    Archive* m_table; // 0x8
    uint32_t m_ptrCount; // 0x10
    uint32_t m_ptrCap; // 0x14
    Archive** m_ptrs; // 0x18
    regenny::shared::ndlib::io::StorageCore* m_storageCore; // 0x20
    void* m_grpDefault; // 0x28
    uint64_t m_nextId; // 0x30
    private: char pad_38[0x8]; public:
    void* m_rwLock; // 0x40
    private: char pad_48[0x8]; public:
}; // Size: 0x50
#pragma pack(pop)
}
