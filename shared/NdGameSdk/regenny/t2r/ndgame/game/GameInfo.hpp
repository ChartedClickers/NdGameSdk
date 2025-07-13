#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "..\..\shared\ndlib\NdGameInfo.hpp"
namespace regenny::ndgame::game {
#pragma pack(push, 1)
    struct GameInfo : public regenny::shared::ndlib::NdGameInfo {
    private: char pad_4660[0x148]; public:
        // Metadata: bool*
        bool m_enableNpTrophies; // 0x47a8
    private: char pad_47a9[0x42f]; public:
        uint64_t m_field4Bd8; // 0x4bd8
    }; // Size: 0x4be0
#pragma pack(pop)
}
