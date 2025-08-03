#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "..\..\corelib\containers\FixedSizeHeap.hpp"
namespace regenny::shared::ndlib::profiling {
#pragma pack(push, 1)
struct ProfileMgr {
    private: char pad_0[0x420]; public:
    uint64_t m_numWorkerThreads; // 0x420
    private: char pad_428[0x1990]; public:
    regenny::shared::corelib::containers::FixedSizeHeap m_FixedSizeHeap; // 0x1db8
    private: char pad_1e10[0x40]; public:
}; // Size: 0x1e50
#pragma pack(pop)
}
