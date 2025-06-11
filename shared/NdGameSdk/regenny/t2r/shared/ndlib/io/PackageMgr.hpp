#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "..\..\corelib\memory\Context.hpp"
#include "LoadingHeapMgr.hpp"
namespace regenny::shared::ndlib::io {
struct Package;
}
namespace regenny::shared::ndlib::io {
struct PackageProcessingInfo;
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
        uint64_t* m_PackageLoginResFunc; // 0x38
        regenny::shared::ndlib::io::LoadingHeapMgr::LevelHeapType m_levelheaptype; // 0x40
        private: char pad_44[0xc]; public:
    }; // Size: 0x50

    struct PkgNameLookupHdr {
        void* buckets; // 0x0
        void* bitMaskWords; // 0x8
        void* freeList; // 0x10
        void* allocator; // 0x18
        uint32_t bucketMask; // 0x20
        private: char pad_24[0x4]; public:
        uint32_t capacity; // 0x28
        uint32_t size; // 0x2c
    }; // Size: 0x30

    uint32_t m_freepackageslots; // 0x0
    uint32_t m_allocationRingBufferSize; // 0x4
    uint32_t m_field8; // 0x8
    regenny::shared::corelib::memory::Context m_memcontext; // 0xc
    private: char pad_10[0x30]; public:
    regenny::shared::ndlib::io::LoadingHeapMgr::LevelHeapType m_levelheaptype; // 0x40
    private: char pad_44[0xc]; public:
    uint32_t m_field50; // 0x50
    private: char pad_54[0xc]; public:
    uint64_t m_field60; // 0x60
    regenny::shared::ndlib::io::Package* m_packages; // 0x68
    uint64_t m_field70; // 0x70
    PkgNameLookupHdr m_pakNameLookup; // 0x78
    PkgNameLookupHdr m_nickNameLookup; // 0xa8
    private: char pad_d8[0x10]; public:
    uint32_t m_PackageWantedCount; // 0xe8
    private: char pad_ec[0x4]; public:
    regenny::shared::ndlib::io::PackageProcessingInfo** m_packageinfos; // 0xf0
    private: char pad_f8[0x448]; public:
    uint64_t m_numPackagesAwaitingUnload; // 0x540
    private: char pad_548[0x4a28]; public:
}; // Size: 0x4f70
#pragma pack(pop)
}
