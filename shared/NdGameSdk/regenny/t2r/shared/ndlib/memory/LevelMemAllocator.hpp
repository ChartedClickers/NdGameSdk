#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "..\..\corelib\memory\Allocator.hpp"
namespace regenny::shared::ndlib::io {
struct PackageMgr;
}
namespace regenny::shared::ndlib::io {
struct LoadingHeap;
}
namespace regenny::shared::ndlib::io {
struct Package;
}
namespace regenny::shared::ndlib::memory {
#pragma pack(push, 1)
struct LevelMemAllocator : public regenny::shared::corelib::memory::Allocator {
    struct CacheBlock {
        void* m_pBuffer; // 0x0
        void* m_pCursor; // 0x8
        uint64_t m_bufferSize; // 0x10
        uint64_t m_bytesRequested; // 0x18
        uint64_t m_bytesAccounted; // 0x20
    }; // Size: 0x28

    CacheBlock m_cacheBlock[24]; // 0x60
    uint32_t m_blockSize; // 0x420
    bool m_blockAllocatorActive; // 0x424
    private: char pad_425[0x3]; public:
    bool m_useCacheBlocks; // 0x428
    private: char pad_429[0x7]; public:
    regenny::shared::ndlib::io::PackageMgr* m_packageMgr; // 0x430
    regenny::shared::ndlib::io::LoadingHeap* m_LoadingHeap; // 0x438
    regenny::shared::ndlib::io::Package* m_package; // 0x440
    private: char pad_448[0x8]; public:
}; // Size: 0x450
#pragma pack(pop)
}
