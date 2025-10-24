#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "LevelSpec.hpp"
namespace regenny::shared::gamelib::level {
struct LevelDef;
}
namespace regenny::shared::gamelib::level {
#pragma pack(push, 1)
struct WantLoadInfo {
    enum Flags : uint8_t {
        Portal = 1,
        Spawn = 2,
        FGVisible = 8,
        Propagate = 16,
        Locked = 32,
        Display = 64,
    };

    enum Type : uint8_t {
        None = 0,
        Level = 1,
        Actor = 2,
        TaskGraph = 4,
    };

    // Metadata: utf8*
    char* m_name; // 0x0
    StringId64 m_nameId; // 0x8
    regenny::shared::gamelib::level::LevelDef* m_pLevelDef; // 0x10
    void* m_onLoadedCallback; // 0x18
    Type m_type; // 0x20
    private: char pad_21[0x1]; public:
    Flags m_flags; // 0x22
    private: char pad_23[0x1]; public:
    regenny::shared::gamelib::level::LevelSpec::Layer m_layerMask; // 0x24
    private: char pad_25[0x3]; public:
}; // Size: 0x28
#pragma pack(pop)
}
