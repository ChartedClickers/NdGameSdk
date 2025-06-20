#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
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
    struct Configuration {
        uint32_t m_freepackageslots; // 0x0
        uint32_t m_allocationRingBufferSize; // 0x4
        private: char pad_8[0x4]; public:
        regenny::shared::corelib::memory::Context m_memcontext; // 0xc
        private: char pad_10[0x10]; public:
        void* m_GetGameFrameNumber; // 0x20
        private: char pad_28[0x10]; public:
        uint64_t* m_PackageLoginResFuncs; // 0x38
        regenny::shared::ndlib::io::LoadingHeapMgr::LevelHeapType m_levelheaptype; // 0x40
        private: char pad_44[0xc]; public:
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

    struct PkgNameLookupHdr {
        regenny::shared::ndlib::io::PackageMgr::PkgNameLookupEntry** m_buckets; // 0x0
        uint64_t* m_bitMask; // 0x8
        regenny::shared::ndlib::io::PackageMgr::PkgNameLookupEntry* m_freeList; // 0x10
        void* m_allocator; // 0x18
        uint32_t m_bucketMask; // 0x20
        private: char pad_24[0x4]; public:
        uint32_t m_capacity; // 0x28
        uint32_t m_size; // 0x2c
    }; // Size: 0x30

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
        uint32_t m_field90; // 0x90
        uint32_t m_field94; // 0x94
        regenny::shared::gamelib::level::Level* m_Level; // 0x98
    }; // Size: 0xa0

    struct PackageRequestInfo {
        uint32_t m_totalrequested; // 0x0
        uint32_t m_overallrequested; // 0x4
        uint32_t m_numPackagesRequested; // 0x8
        uint32_t m_maxrequestlimit; // 0xc
        regenny::shared::ndlib::io::PackageMgr::PackageRequest* m_PackagesRequested; // 0x10
    }; // Size: 0x18

    uint32_t m_freepackageslots; // 0x0
    uint32_t m_allocationRingBufferSize; // 0x4
    uint32_t m_field8; // 0x8
    regenny::shared::corelib::memory::Context m_memcontext; // 0xc
    private: char pad_10[0x20]; public:
    void* m_field30; // 0x30
    regenny::shared::gamelib::level::DataLoading::PackageDataLoadingVTable* m_PackageLoginResFuncs; // 0x38
    regenny::shared::ndlib::io::LoadingHeapMgr::LevelHeapType m_levelheaptype; // 0x40
    private: char pad_44[0x8]; public:
    uint32_t m_filed4c; // 0x4c
    PackageRequestInfo m_RequestInfo; // 0x50
    regenny::shared::ndlib::io::Package* m_packages; // 0x68
    uint64_t m_field70; // 0x70
    PkgNameLookupHdr m_pakNameLookup; // 0x78
    PkgNameLookupHdr m_nickNameLookup; // 0xa8
    private: char pad_d8[0x8]; public:
    uint32_t m_fielde0; // 0xe0
    uint32_t m_filede4; // 0xe4
    uint32_t m_LoadQueue; // 0xe8
    uint32_t m_filedec; // 0xec
    regenny::shared::ndlib::io::PackageProcessingInfo** m_packageinfos; // 0xf0
    private: char pad_f8[0x8]; public:
    uint32_t m_numPackagesAwaitingUpdate; // 0x100
    uint32_t m_field104; // 0x104
    uint64_t m_filed108; // 0x108
    private: char pad_110[0x20]; public:
    uint32_t m_filed130; // 0x130
    uint32_t m_filed134; // 0x134
    uint32_t m_numPackagesAwaitingLogout; // 0x138
    uint32_t m_filed13c; // 0x13c
    uint64_t m_filed140; // 0x140
    uint32_t m_filed148; // 0x148
    bool m_forceReleaseVirtualMemory; // 0x14c
    private: char pad_14d[0x333]; public:
    regenny::shared::corelib::system::platform::ndsys::Mutex m_LoadingLock; // 0x480
    regenny::shared::corelib::system::platform::ndsys::ConditionVariable m_ConditionVariable; // 0x4c0
    regenny::shared::corelib::system::platform::ndsys::Mutex m_LoginLock; // 0x4e0
    private: char pad_520[0x8]; public:
    uint32_t m_field528; // 0x528
    uint32_t m_field52c; // 0x52c
    uint32_t m_field530; // 0x530
    uint32_t m_field534; // 0x534
    void* m_RingBuffer; // 0x538
    uint64_t m_numPackagesAwaitingUnload; // 0x540
    private: char pad_548[0x4219]; public:
    bool m_filed4761; // 0x4761
    bool m_field4762; // 0x4762
    private: char pad_4763[0x80d]; public:
}; // Size: 0x4f70
#pragma pack(pop)
}
