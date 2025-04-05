#pragma once
#include <NdGameSdk/sdkstringid.hpp>
#include <cstdint>
#include "..\..\shared\ndlib\NdGameInfo.hpp"
namespace regenny::ndgame::game {
#pragma pack(push, 1)
struct GameInfo : public regenny::shared::ndlib::NdGameInfo {
    private: char pad_4660[0x148]; public:
    // Metadata: bool*
    bool m_enableNpTrophies; // 0x47a8
    private: char pad_47a9[0x41f]; public:
    uint64_t Unk_4BC8; // 0x4bc8
}; // Size: 0x4bd0
#pragma pack(pop)
}
