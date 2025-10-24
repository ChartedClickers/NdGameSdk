#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "debug\DMENU.hpp"
namespace regenny::shared::corelib::util {
struct StringCache;
}
namespace regenny::shared::ndlib {
#pragma pack(push, 1)
struct NdConfig {
    void* m_pNetInfo; // 0x0
    regenny::shared::ndlib::debug::DMENU* m_DMENU; // 0x8
    regenny::shared::ndlib::debug::DMENU::MenuGroup* m_DevMenu; // 0x10
    uint64_t m_field18; // 0x18
    regenny::shared::ndlib::debug::DMENU::MenuGroup* m_FavoriteDevMenu; // 0x20
    private: char pad_28[0x10]; public:
    regenny::shared::corelib::util::StringCache* m_pNameCache; // 0x38
    private: char pad_40[0x1f8]; public:
}; // Size: 0x238
#pragma pack(pop)
}
