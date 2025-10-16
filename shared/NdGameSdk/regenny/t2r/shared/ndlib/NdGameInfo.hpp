#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::ndlib {
#pragma pack(push, 1)
struct NdGameInfo {
    void* vftable; // 0x0
    private: char pad_8[0x110]; public:
    // Metadata: utf8*
    char* m_internalname; // 0x118
    StringId64 m_gametitlehash; // 0x120
    // Metadata: utf8*
    char m_buidtype[296]; // 0x128
    private: char pad_250[0x2f8]; public:
    // Metadata: utf8*
    char m_SavePath[1024]; // 0x548
    // Metadata: utf8*
    char m_GamePath[1024]; // 0x948
    // Metadata: utf8*
    char m_GamePath_unk[1024]; // 0xd48
    // Metadata: utf8*
    char m_NetUserPath[1024]; // 0x1148
    // Metadata: utf8*
    char m_NetPath[1024]; // 0x1548
    // Metadata: utf8*
    char m_GameDataPath[1024]; // 0x1948
    // Metadata: utf8*
    char m_GameDataPath_unk[1024]; // 0x1d48
    // Metadata: utf8*
    char m_BinPath[1024]; // 0x2148
    // Metadata: utf8*
    char m_BinPath_unk[1024]; // 0x2548
    // Metadata: utf8*
    char m_BranchName[64]; // 0x2948
    // Metadata: utf8*
    char m_SrcPath[1024]; // 0x2988
    // Metadata: utf8*
    char m_DbPath[1024]; // 0x2d88
    // Metadata: utf8*
    char m_GameInernalPath[1024]; // 0x3188
    private: char pad_3588[0x402]; public:
    // Metadata: utf8*
    char m_CfgPath[1024]; // 0x398a
    // Metadata: utf8*
    char m_CfgFolderName[128]; // 0x3d8a
    // Metadata: utf8*
    char m_CfgDefaultsPath[128]; // 0x3e0a
    private: char pad_3e8a[0x82]; public:
    uint32_t m_env; // 0x3f0c
    private: char pad_3f10[0x1]; public:
    // Metadata: bool*
    bool m_AssetView; // 0x3f11
    // Metadata: bool*
    bool m_DevConfig; // 0x3f12
    // Metadata: bool*
    bool m_onDisc; // 0x3f13
    // Metadata: bool*
    bool m_onDiscUseManifest; // 0x3f14
    private: char pad_3f15[0x27]; public:
    // Metadata: bool*
    bool m_IsMultiplayer; // 0x3f3c
    private: char pad_3f3d[0x13]; public:
    // Metadata: bool*
    bool m_DevMode; // 0x3f50
    private: char pad_3f51[0xd]; public:
    // Metadata: bool*
    bool m_DebugRendering; // 0x3f5e
    private: char pad_3f5f[0x29]; public:
    // Metadata: bool*
    bool m_DisableFpsStat; // 0x3f88
    private: char pad_3f89[0x11]; public:
    // Metadata: bool*
    bool m_showBuildInfo; // 0x3f9a
    private: char pad_3f9b[0xd]; public:
    // Metadata: bool*
    bool m_MsgConDrawBuffers; // 0x3fa8
    private: char pad_3fa9[0x87]; public:
    // Metadata: utf8*
    char m_DiscUser[32]; // 0x4030
    private: char pad_4050[0x54]; public:
    // Metadata: utf8*
    char m_StatsBuild[32]; // 0x40a4
    private: char pad_40c4[0xec]; public:
    StringId64 AudioStringId; // 0x41b0
    private: char pad_41b8[0x277]; public:
    // Metadata: bool*
    bool m_ShowStats; // 0x442f
    private: char pad_4430[0xb3]; public:
    // Metadata: utf8*
    char m_GameStudio[64]; // 0x44e3
    private: char pad_4523[0x135]; public:
    uint64_t Unk_4658; // 0x4658
}; // Size: 0x4660
#pragma pack(pop)
}
