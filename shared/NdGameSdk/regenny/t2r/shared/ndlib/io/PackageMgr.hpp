#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "..\..\corelib\containers\RobinHoodHashTable.hpp"
#include "..\..\corelib\memory\Context.hpp"
#include "..\..\corelib\system\platform\ndsys.hpp"
#include "..\..\gamelib\level\DataLoading.hpp"
#include "LoadingHeapMgr.hpp"
namespace regenny::shared::ndlib::io {
struct Package;
}
namespace regenny::shared::ndlib::io {
struct PackageProcessingInfo;
}
namespace regenny::shared::gamelib::level {
struct Level;
}
namespace regenny::shared::ndlib::io {
#pragma pack(push, 1)
struct PackageMgr {
    enum PackageCategory : uint32_t {
        Initial = 0,
        GlobalPak = 1,
        LevelPak = 2,
        DictPak = 3,
        PsoDictPak = 4,
    };

    struct Configuration {
        uint32_t m_freepackageslots; // 0x0
        uint32_t m_allocationRingBufferSize; // 0x4
        regenny::shared::corelib::memory::Context m_RingBufferContext; // 0x8
        regenny::shared::corelib::memory::Context m_memoryContext; // 0xc
        private: char pad_10[0x10]; public:
        void* m_GetGameFrameNumber; // 0x20
        private: char pad_28[0x10]; public:
        uint64_t* m_PackageLoginResFuncs; // 0x38
        regenny::shared::ndlib::io::LoadingHeapMgr::LevelHeapType m_levelheaptype; // 0x40
        bool m_field44; // 0x44
        bool m_AllowDebugPages; // 0x45
        bool m_field46; // 0x46
        private: char pad_47[0x9]; public:
    }; // Size: 0x50

    struct PkgNameLookupEntry {
        regenny::shared::ndlib::io::PackageMgr::PkgNameLookupEntry* m_next; // 0x0
        StringId64 m_key; // 0x8
        StringId64 m_hash; // 0x10
        private: char pad_18[0x8]; public:
        uint64_t m_field20; // 0x20
        uint64_t m_field28; // 0x28
        uint64_t m_capacity; // 0x30
    }; // Size: 0x38

    struct PackageRequest {
        enum RequestType : uint32_t {
            Login = 0,
            Logout = 1,
        };

        RequestType m_RequestType; // 0x0
        private: char pad_4[0x4]; public:
        StringId64 m_packid; // 0x8
        // Metadata: utf8*
        char m_name[128]; // 0x10
        regenny::shared::ndlib::io::PackageMgr::PackageCategory m_category; // 0x90
        uint32_t m_isNumberedPart; // 0x94
        regenny::shared::gamelib::level::Level* m_Level; // 0x98
    }; // Size: 0xa0

    struct PackageRequestInfo {
        uint32_t m_totalrequested; // 0x0
        uint32_t m_overallrequested; // 0x4
        uint32_t m_numPackagesRequested; // 0x8
        uint32_t m_maxrequestlimit; // 0xc
        regenny::shared::ndlib::io::PackageMgr::PackageRequest* m_PackagesRequested; // 0x10
    }; // Size: 0x18

    struct ProcessingRingBuffer {
        uint32_t m_head; // 0x0
        uint32_t m_tail; // 0x4
        uint32_t m_numQueued; // 0x8
        uint32_t m_capacity; // 0xc
        regenny::shared::ndlib::io::PackageProcessingInfo** m_slots; // 0x10
    }; // Size: 0x18

    struct IOStagingRing {
        uint32_t m_userFileOffset; // 0x0
        uint32_t m_streamBytesProduced; // 0x4
        uint32_t m_ringUsedBytes; // 0x8
        uint32_t m_streamSubmitOffset; // 0xc
        uint32_t m_ringTail; // 0x10
        uint32_t m_ringHead; // 0x14
        uint8_t* m_RingBuffer; // 0x18
    }; // Size: 0x20

    struct RobinHoodHashTable_corelib_containers_StringId64_uint32_t {
        struct Slot {
            uint64_t m_hash; // 0x0
            StringId64 m_key; // 0x8
            uint32_t m_value; // 0x10
            private: char pad_14[0x4]; public:
        }; // Size: 0x18

        Slot* m_Slots; // 0x0
        regenny::shared::corelib::containers::RobinHoodHashTable::OccMask m_occ; // 0x8
        uint32_t m_numBuckets; // 0x28
        uint32_t m_numElements; // 0x2c
    }; // Size: 0x30

    uint32_t m_freepackageslots; // 0x0
    uint32_t m_allocationRingBufferSize; // 0x4
    regenny::shared::corelib::memory::Context m_RingBufferContext; // 0x8
    regenny::shared::corelib::memory::Context m_memoryContext; // 0xc
    private: char pad_10[0x20]; public:
    void* m_field30; // 0x30
    regenny::shared::gamelib::level::DataLoading::PackageDataLoadingVTable* m_PackageLoginResFuncs; // 0x38
    regenny::shared::ndlib::io::LoadingHeapMgr::LevelHeapType m_levelheaptype; // 0x40
    bool m_field44; // 0x44
    bool m_AllowDebugPages; // 0x45
    bool m_field46; // 0x46
    private: char pad_47[0x1]; public:
    bool m_field48; // 0x48
    private: char pad_49[0x3]; public:
    uint32_t m_filed4c; // 0x4c
    PackageRequestInfo m_RequestInfo; // 0x50
    regenny::shared::ndlib::io::Package* m_packages; // 0x68
    regenny::shared::ndlib::io::PackageProcessingInfo* m_packageinfos; // 0x70
    RobinHoodHashTable_corelib_containers_StringId64_uint32_t m_pakNameLookup; // 0x78
    RobinHoodHashTable_corelib_containers_StringId64_uint32_t m_nickNameLookup; // 0xa8
    private: char pad_d8[0x8]; public:
    ProcessingRingBuffer m_processingLoadQueue; // 0xe0
    ProcessingRingBuffer m_processingUpdateQueue; // 0xf8
    private: char pad_110[0x20]; public:
    ProcessingRingBuffer m_processingUnloadQueue; // 0x130
    uint32_t m_loginStageFence; // 0x148
    bool m_forceReleaseVirtualMemory; // 0x14c
    private: char pad_14d[0x333]; public:
    regenny::shared::corelib::system::platform::ndsys::Mutex m_LoadingLock; // 0x480
    regenny::shared::corelib::system::platform::ndsys::ConditionVariable m_ConditionVariable; // 0x4c0
    regenny::shared::corelib::system::platform::ndsys::Mutex m_LoginLock; // 0x4e0
    IOStagingRing m_ioStagingRing; // 0x520
    uint32_t m_PendingPackageVramReleaseCount; // 0x540
    private: char pad_544[0x4]; public:
    regenny::shared::ndlib::io::PackageProcessingInfo** m_PendingPackageVramRelease; // 0x548
    private: char pad_550[0x4211]; public:
    bool m_filed4761; // 0x4761
    bool m_field4762; // 0x4762
    private: char pad_4763[0x80d]; public:
}; // Size: 0x4f70
#pragma pack(pop)
}
