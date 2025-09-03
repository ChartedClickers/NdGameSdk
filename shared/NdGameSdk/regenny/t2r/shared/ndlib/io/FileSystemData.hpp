#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::ndlib::io {
struct ArchiveSystem;
}
namespace regenny::shared::ndlib::io {
struct StorageCore;
}
namespace regenny::shared::ndlib::io {
#pragma pack(push, 1)
struct FileSystemData {
    struct FsPoolBucket {
        private: char pad_0[0x848]; public:
    }; // Size: 0x848

    private: char pad_0[0x10]; public:
    FsPoolBucket m_pool[128]; // 0x10
    private: char pad_42410[0x10]; public:
    uint64_t m_initFlag; // 0x42420
    regenny::shared::ndlib::io::ArchiveSystem* m_archive; // 0x42428
    regenny::shared::ndlib::io::StorageCore* m_storageCore; // 0x42430
    void* m_grpAnimations; // 0x42438
    void* m_grpAudioScripts; // 0x42440
    void* m_grpDefault; // 0x42448
}; // Size: 0x42450
#pragma pack(pop)
}
