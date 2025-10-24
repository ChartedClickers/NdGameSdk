#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "..\..\corelib\system\platform\ndsys.hpp"
namespace regenny::shared::ndlib::text {
#pragma pack(push, 1)
struct StringIdSelection {
    void* vftable; // 0x0
    private: char pad_8[0x8]; public:
    uint32_t m_capacity; // 0x10
    uint32_t m_count; // 0x14
    StringId64* m_pIds; // 0x18
    regenny::shared::corelib::system::platform::ndsys::WaitLock m_lock; // 0x20
}; // Size: 0x40
#pragma pack(pop)
}
