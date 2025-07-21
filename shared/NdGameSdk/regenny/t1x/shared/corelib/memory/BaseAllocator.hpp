#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::corelib::memory {
#pragma pack(push, 1)
struct BaseAllocator {
    void* vftable; // 0x0
    private: char pad_8[0x30]; public:
    void* m_pTracker; // 0x38
    char* m_context_name; // 0x40
    StringId64 m_context_hash; // 0x48
    bool m_Initialized; // 0x50
    private: char pad_51[0x7]; public:
}; // Size: 0x58
#pragma pack(pop)
}
