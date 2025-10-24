#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::gamelib::level {
#pragma pack(push, 1)
struct LevelLoadObserver {
    void* m_vtable; // 0x0
    regenny::shared::gamelib::level::LevelLoadObserver* m_next; // 0x8
    regenny::shared::gamelib::level::LevelLoadObserver* m_prev; // 0x10
}; // Size: 0x18
#pragma pack(pop)
}
