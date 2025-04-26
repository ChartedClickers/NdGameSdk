#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "..\..\shared\ndlib\NdGameInfo.hpp"
namespace regenny::ndgame::game {
#pragma pack(push, 1)
struct GameInfo : public regenny::shared::ndlib::NdGameInfo {
    private: char pad_45c0[0x148]; public:
    // Metadata: bool*
    bool m_enableNpTrophies; // 0x4708
    private: char pad_4709[0x25f]; public:
    uint64_t Unk_4968; // 0x4968
}; // Size: 0x4970
#pragma pack(pop)
}
