#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::ndgame::game::weapon {
#pragma pack(push, 1)
struct ScriptWeaponArt {
    struct WeaponArt {
        // Metadata: utf8*
        char* m_category; // 0x0
        uint64_t m_processid; // 0x8
    }; // Size: 0x10

    uint64_t m_num; // 0x0
    uint64_t* m_hashs; // 0x8
    WeaponArt** m_defs; // 0x10
}; // Size: 0x18
#pragma pack(pop)
}
