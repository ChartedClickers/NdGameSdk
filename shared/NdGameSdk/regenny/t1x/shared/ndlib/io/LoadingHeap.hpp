#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "..\..\corelib\containers\FixedSizeHeap.hpp"
#include "..\..\corelib\system\platform\ndsys.hpp"
namespace regenny::shared::ndlib::io {
#pragma pack(push, 1)
struct LoadingHeap {
    bool m_drawEnabled; // 0x0
    bool m_failAlloc; // 0x1
    private: char pad_2[0x6]; public:
    regenny::shared::corelib::containers::FixedSizeHeap m_mainHeap; // 0x8
    regenny::shared::corelib::containers::FixedSizeHeap m_overflowHeap; // 0x60
    regenny::shared::corelib::containers::FixedSizeHeap m_debugHeap; // 0xb8
    bool m_initialized; // 0x110
    bool m_overflowActive; // 0x111
    private: char pad_112[0x2]; public:
    uint32_t m_peakMainPages; // 0x114
    uint32_t m_peakCombinedUsage; // 0x118
    uint32_t m_peakDebugPages; // 0x11c
    uint32_t m_peakOverflowUsage; // 0x120
    uint32_t m_mainPageCount; // 0x124
    uint32_t m_hiddenPageCount; // 0x128
    uint32_t m_overflowPageCount; // 0x12c
    uint32_t m_debugPageCount; // 0x130
    private: char pad_134[0x4]; public:
    void* m_mainPhysical; // 0x138
    void* m_overflowPhysical; // 0x140
    void* m_debugPhysical; // 0x148
    uint8_t* m_linearizedLoadingHeapBase; // 0x150
    uint8_t* m_linearizedOverflowHeapBase; // 0x158
    uint8_t* m_linearizedDebugHeapBase; // 0x160
    private: char pad_168[0x8]; public:
    regenny::shared::corelib::system::platform::ndsys::Mutex m_mutex; // 0x170
}; // Size: 0x1b0
#pragma pack(pop)
}
