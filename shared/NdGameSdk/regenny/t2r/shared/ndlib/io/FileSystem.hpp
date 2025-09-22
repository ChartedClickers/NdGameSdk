#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "..\..\corelib\containers\FixedSizeHeap.hpp"
#include "..\..\corelib\memory\HeapAllocatorWithOverflow.hpp"
#include "..\..\corelib\system\platform\ndsys.hpp"
#include "FsResult.hpp"
namespace regenny::shared::ndlib::io {
#pragma pack(push, 1)
struct FileSystem {
    enum Priority : uint32_t {
        None = 0,
    };

    struct RamCacheFilterDesc {
        uint64_t m_size; // 0x0
        uint64_t m_workBufSize; // 0x8
        void* m_WorkBuffer; // 0x10
        uint64_t m_field18; // 0x18
        char* m_mountPath; // 0x20
        uint64_t m_field28; // 0x28
        private: char pad_30[0x8]; public:
    }; // Size: 0x38

    struct ReadOnlyFileHandle {
        uint32_t m_ioHandle; // 0x0
        private: char pad_4[0x4]; public:
        uint64_t m_offset; // 0x8
        uint64_t m_size; // 0x10
        bool m_isArchive; // 0x18
        private: char pad_19[0x7]; public:
    }; // Size: 0x20

    struct ReadOperation {
        HANDLE m_hEvent; // 0x0
        regenny::shared::ndlib::io::FsResult m_FsResult; // 0x8
    }; // Size: 0x18

    struct RemapNode {
        regenny::shared::ndlib::io::FileSystem::RemapNode* m_next; // 0x0
        regenny::shared::ndlib::io::FileSystem::RemapNode* m_prev; // 0x8
        uint64_t m_key; // 0x10
        char* m_value; // 0x18
    }; // Size: 0x20

    struct RemapTable {
        regenny::shared::ndlib::io::FileSystem::RemapNode** m_buckets; // 0x0
        regenny::shared::corelib::containers::FixedSizeHeap m_heap; // 0x8
        regenny::shared::ndlib::io::FileSystem::RemapNode* m_sentinel; // 0x60
        uint64_t m_nodeSize; // 0x68
        uint64_t m_capacity; // 0x70
        regenny::shared::ndlib::io::FileSystem::RemapNode** m_bucketsBegin; // 0x78
        regenny::shared::ndlib::io::FileSystem::RemapNode** m_bucketsEnd; // 0x80
        uint64_t m_numEntries; // 0x88
        uint32_t m_bucketCountMinus1; // 0x90
        uint32_t m_flags; // 0x94
    }; // Size: 0x98

    struct FileSystemOverlay {
        bool m_DisplayDataLoadingStatistics; // 0x0
        bool m_showFiosOpsDump; // 0x1
        private: char pad_2[0x2]; public:
        bool m_statsMode; // 0x4
        bool m_statsModePrev; // 0x5
        private: char pad_6[0x2]; public:
        uint32_t m_peakBucketValue; // 0x8
        uint32_t m_peakAvg20; // 0xc
        uint32_t m_bucket[20]; // 0x10
    }; // Size: 0x60

    struct BatchReadItem {
        void* m_dst; // 0x0
        uint32_t m_fh; // 0x8
        uint64_t m_offset; // 0xc
        uint64_t m_length; // 0x14
        void* m_field20; // 0x1c
        private: char pad_24[0x4]; public:
    }; // Size: 0x28

    struct BatchResolveItem {
        // Metadata: utf8*
        char* m_path; // 0x0
        uint32_t* m_outFh; // 0x8
    }; // Size: 0x10

    struct ArchiveMount {
        struct Buffer {
            uint64_t m_archiveId; // 0x0
            // Metadata: utf8*
            char m_indexPath[1024]; // 0x8
            // Metadata: utf8*
            char m_mountPrefix[1024]; // 0x408
        }; // Size: 0x808

        Buffer* m_pMountBuffer; // 0x0
        uint64_t m_sizeBytes; // 0x8
    }; // Size: 0x10

    FileSystemOverlay m_SystemOverlay; // 0x0
    regenny::shared::corelib::system::platform::ndsys::Mutex m_ReadLock; // 0x60
    regenny::shared::corelib::system::platform::ndsys::Mutex m_ReadLock2; // 0xa0
    bool m_initialized; // 0xe0
    private: char pad_e1[0x17]; public:
    uint64_t m_entireRamCacheSize; // 0xf8
    void* m_RamCache; // 0x100
    uint64_t m_workBufSize; // 0x108
    uint64_t m_workBuf; // 0x110
    private: char pad_118[0x8]; public:
    regenny::shared::corelib::memory::HeapAllocatorWithOverflow m_allocator; // 0x120
}; // Size: 0x220
#pragma pack(pop)
}
