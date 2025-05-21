#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::ndlib {
#pragma pack(push, 1)
struct NdGameInfo {
    void* vftable; // 0x0
    private: char pad_8[0x110]; public:
    // Metadata: utf8*
    uint64_t m_internalname; // 0x118
    StringId64 m_gametitlehash; // 0x120
    // Metadata: utf8*
    char m_SavePath[1024]; // 0x128
    // Metadata: utf8*
    char m_SavePath_unk[1024]; // 0x528
    // Metadata: utf8*
    char m_GamePath[1024]; // 0x928
    // Metadata: utf8*
    char m_GamePath_unk[1024]; // 0xd28
    // Metadata: utf8*
    char m_NetUserPath[1024]; // 0x1128
    // Metadata: utf8*
    char m_NetPath[1024]; // 0x1528
    // Metadata: utf8*
    char m_GameDataPath[1024]; // 0x1928
    // Metadata: utf8*
    char m_GameDataPath_unk[1024]; // 0x1d28
    // Metadata: utf8*
    char m_BinPath[1024]; // 0x2128
    // Metadata: utf8*
    char m_BinPath_unk[1024]; // 0x2528
    // Metadata: utf8*
    char m_BranchName[64]; // 0x2928
    // Metadata: utf8*
    char m_SrcPath[1024]; // 0x2968
    // Metadata: utf8*
    char m_DbPath[1024]; // 0x2d68
    // Metadata: utf8*
    char m_GamePath_unk2[1024]; // 0x3168
    private: char pad_3568[0x402]; public:
    // Metadata: utf8*
    char m_CfgPath[1024]; // 0x396a
    // Metadata: utf8*
    char m_CfgFolderName[128]; // 0x3d6a
    // Metadata: utf8*
    char m_CfgDefaultsPath[128]; // 0x3dea
    private: char pad_3e6a[0x85]; public:
    uint16_t Unk_3ef0; // 0x3eef
    // Metadata: bool*
    bool m_AssetView; // 0x3ef1
    // Metadata: bool*
    bool m_DevConfig; // 0x3ef2
    // Metadata: bool*
    bool m_onDisc; // 0x3ef3
    // Metadata: bool*
    bool m_onDiscUseManifest; // 0x3ef4
    // Metadata: bool*
    bool Unk_3ef5; // 0x3ef5
    // Metadata: bool*
    bool Unk_3ef6; // 0x3ef6
    // Metadata: bool*
    bool Unk_3ef7; // 0x3ef7
    // Metadata: bool*
    bool Unk_3ef8; // 0x3ef8
    // Metadata: bool*
    bool Unk_3ef9; // 0x3ef9
    // Metadata: bool*
    bool Unk_3efa; // 0x3efa
    // Metadata: bool*
    bool Unk_3efb; // 0x3efb
    // Metadata: bool*
    bool Unk_3efc; // 0x3efc
    // Metadata: bool*
    bool Unk_3efd; // 0x3efd
    // Metadata: bool*
    bool Unk_3efe; // 0x3efe
    // Metadata: bool*
    bool Unk_3eff; // 0x3eff
    // Metadata: bool*
    bool Unk_3f00; // 0x3f00
    // Metadata: bool*
    bool Unk_3f01; // 0x3f01
    // Metadata: bool*
    bool Unk_3f02; // 0x3f02
    // Metadata: bool*
    bool Unk_3f03; // 0x3f03
    // Metadata: bool*
    bool Unk_3f04; // 0x3f04
    // Metadata: bool*
    bool Unk_3f05; // 0x3f05
    // Metadata: bool*
    bool Unk_3f06; // 0x3f06
    // Metadata: bool*
    bool Unk_3f07; // 0x3f07
    // Metadata: bool*
    bool Unk_3f08; // 0x3f08
    // Metadata: bool*
    bool Unk_3f09; // 0x3f09
    // Metadata: bool*
    bool Unk_3f0a; // 0x3f0a
    // Metadata: bool*
    bool Unk_3f0b; // 0x3f0b
    uint32_t m_env; // 0x3f0c
    // Metadata: bool*
    bool Unk_3f10; // 0x3f10
    // Metadata: bool*
    bool Unk_3f11; // 0x3f11
    // Metadata: bool*
    bool Unk_3f12; // 0x3f12
    // Metadata: bool*
    bool Unk_3f13; // 0x3f13
    // Metadata: bool*
    bool Unk_3f14; // 0x3f14
    // Metadata: bool*
    bool Unk_3f15; // 0x3f15
    // Metadata: bool*
    bool Unk_3f16; // 0x3f16
    // Metadata: bool*
    bool Unk_3f17; // 0x3f17
    // Metadata: bool*
    bool Unk_3f18; // 0x3f18
    // Metadata: bool*
    bool Unk_3f19; // 0x3f19
    // Metadata: bool*
    bool Unk_3f1a; // 0x3f1a
    // Metadata: bool*
    bool Unk_3f1b; // 0x3f1b
    // Metadata: bool*
    bool m_IsMultiplayer; // 0x3f1c
    // Metadata: bool*
    bool Unk_3f1d; // 0x3f1d
    // Metadata: bool*
    bool Unk_3f1e; // 0x3f1e
    // Metadata: bool*
    bool Unk_3f1f; // 0x3f1f
    // Metadata: bool*
    bool Unk_3f20; // 0x3f20
    // Metadata: bool*
    bool Unk_3f21; // 0x3f21
    // Metadata: bool*
    bool Unk_3f22; // 0x3f22
    // Metadata: bool*
    bool Unk_3f23; // 0x3f23
    // Metadata: bool*
    bool Unk_3f24; // 0x3f24
    // Metadata: bool*
    bool Unk_3f25; // 0x3f25
    // Metadata: bool*
    bool Unk_3f26; // 0x3f26
    // Metadata: bool*
    bool Unk_3f27; // 0x3f27
    // Metadata: bool*
    bool Unk_3f28; // 0x3f28
    // Metadata: bool*
    bool Unk_3f29; // 0x3f29
    // Metadata: bool*
    bool Unk_3f2a; // 0x3f2a
    // Metadata: bool*
    bool Unk_3f2b; // 0x3f2b
    // Metadata: bool*
    bool Unk_3f2c; // 0x3f2c
    // Metadata: bool*
    bool Unk_3f2d; // 0x3f2d
    // Metadata: bool*
    bool Unk_3f2e; // 0x3f2e
    // Metadata: bool*
    bool m_DevMode; // 0x3f2f
    // Metadata: bool*
    bool Unk_3f30; // 0x3f30
    // Metadata: bool*
    bool Unk_3f31; // 0x3f31
    // Metadata: bool*
    bool Unk_3f32; // 0x3f32
    // Metadata: bool*
    bool Unk_3f33; // 0x3f33
    // Metadata: bool*
    bool Unk_3f34; // 0x3f34
    // Metadata: bool*
    bool Unk_3f35; // 0x3f35
    // Metadata: bool*
    bool Unk_3f36; // 0x3f36
    // Metadata: bool*
    bool Unk_3f37; // 0x3f37
    // Metadata: bool*
    bool Unk_3f38; // 0x3f38
    // Metadata: bool*
    bool Unk_3f39; // 0x3f39
    // Metadata: bool*
    bool Unk_3f3a; // 0x3f3a
    // Metadata: bool*
    bool Unk_3f3b; // 0x3f3b
    // Metadata: bool*
    bool Unk_3f3c; // 0x3f3c
    // Metadata: bool*
    bool m_DebugRendering; // 0x3f3d
    // Metadata: bool*
    bool Unk_3f3e; // 0x3f3e
    // Metadata: bool*
    bool Unk_3f3f; // 0x3f3f
    // Metadata: bool*
    bool Unk_3f40; // 0x3f40
    // Metadata: bool*
    bool Unk_3f41; // 0x3f41
    // Metadata: bool*
    bool Unk_3f42; // 0x3f42
    // Metadata: bool*
    bool Unk_3f43; // 0x3f43
    // Metadata: bool*
    bool Unk_3f44; // 0x3f44
    // Metadata: bool*
    bool Unk_3f45; // 0x3f45
    // Metadata: bool*
    bool Unk_3f46; // 0x3f46
    // Metadata: bool*
    bool Unk_3f47; // 0x3f47
    // Metadata: bool*
    bool Unk_3f48; // 0x3f48
    // Metadata: bool*
    bool Unk_3f49; // 0x3f49
    // Metadata: bool*
    bool Unk_3f4a; // 0x3f4a
    // Metadata: bool*
    bool Unk_3f4b; // 0x3f4b
    // Metadata: bool*
    bool Unk_3f4c; // 0x3f4c
    // Metadata: bool*
    bool Unk_3f4d; // 0x3f4d
    // Metadata: bool*
    bool Unk_3f4e; // 0x3f4e
    // Metadata: bool*
    bool Unk_3f4f; // 0x3f4f
    // Metadata: bool*
    bool Unk_3f50; // 0x3f50
    // Metadata: bool*
    bool Unk_3f51; // 0x3f51
    // Metadata: bool*
    bool Unk_3f52; // 0x3f52
    // Metadata: bool*
    bool Unk_3f53; // 0x3f53
    // Metadata: bool*
    bool Unk_3f54; // 0x3f54
    // Metadata: bool*
    bool Unk_3f55; // 0x3f55
    // Metadata: bool*
    bool Unk_3f56; // 0x3f56
    // Metadata: bool*
    bool Unk_3f57; // 0x3f57
    uint32_t Unk_3f58; // 0x3f58
    // Metadata: bool*
    bool Unk_3f5c; // 0x3f5c
    // Metadata: bool*
    bool Unk_3f5d; // 0x3f5d
    // Metadata: bool*
    bool Unk_3f5e; // 0x3f5e
    // Metadata: bool*
    bool Unk_3f5f; // 0x3f5f
    uint32_t Unk_3f60; // 0x3f60
    // Metadata: bool*
    bool m_DisableFpsStat; // 0x3f64
    // Metadata: bool*
    bool Unk_3f65; // 0x3f65
    // Metadata: bool*
    bool Unk_3f66; // 0x3f66
    // Metadata: bool*
    bool Unk_3f67; // 0x3f67
    // Metadata: bool*
    bool Unk_3f68; // 0x3f68
    // Metadata: bool*
    bool Unk_3f69; // 0x3f69
    // Metadata: bool*
    bool Unk_3f6a; // 0x3f6a
    // Metadata: bool*
    bool Unk_3f6b; // 0x3f6b
    // Metadata: bool*
    bool Unk_3f6c; // 0x3f6c
    // Metadata: bool*
    bool Unk_3f6d; // 0x3f6d
    // Metadata: bool*
    bool Unk_3f6e; // 0x3f6e
    // Metadata: bool*
    bool Unk_3f6f; // 0x3f6f
    // Metadata: bool*
    bool Unk_3f70; // 0x3f70
    // Metadata: bool*
    bool Unk_3f71; // 0x3f71
    // Metadata: bool*
    bool Unk_3f72; // 0x3f72
    // Metadata: bool*
    bool m_showBuildInfo; // 0x3f73
    // Metadata: bool*
    bool Unk_3f74; // 0x3f74
    // Metadata: bool*
    bool Unk_3f75; // 0x3f75
    // Metadata: bool*
    bool Unk_3f76; // 0x3f76
    // Metadata: bool*
    bool Unk_3f77; // 0x3f77
    // Metadata: bool*
    bool Unk_3f78; // 0x3f78
    // Metadata: bool*
    bool Unk_3f79; // 0x3f79
    // Metadata: bool*
    bool Unk_3f7a; // 0x3f7a
    // Metadata: bool*
    bool Unk_3f7b; // 0x3f7b
    // Metadata: bool*
    bool Unk_3f7c; // 0x3f7c
    // Metadata: bool*
    bool Unk_3f7d; // 0x3f7d
    // Metadata: bool*
    bool Unk_3f7e; // 0x3f7e
    // Metadata: bool*
    bool Unk_3f7f; // 0x3f7f
    // Metadata: bool*
    bool Unk_3f80; // 0x3f80
    // Metadata: bool*
    bool Unk_3f81; // 0x3f81
    // Metadata: bool*
    bool Unk_3f82; // 0x3f82
    // Metadata: bool*
    bool Unk_3f83; // 0x3f83
    // Metadata: bool*
    bool Unk_3f84; // 0x3f84
    // Metadata: bool*
    bool Unk_3f85; // 0x3f85
    // Metadata: bool*
    bool Unk_3f86; // 0x3f86
    // Metadata: bool*
    bool Unk_3f87; // 0x3f87
    // Metadata: bool*
    bool Unk_3f88; // 0x3f88
    // Metadata: bool*
    bool Unk_3f89; // 0x3f89
    // Metadata: bool*
    bool Unk_3f8a; // 0x3f8a
    // Metadata: bool*
    bool Unk_3f8b; // 0x3f8b
    // Metadata: bool*
    bool Unk_3f8c; // 0x3f8c
    // Metadata: bool*
    bool Unk_3f8d; // 0x3f8d
    // Metadata: bool*
    bool Unk_3f8e; // 0x3f8e
    // Metadata: bool*
    bool Unk_3f8f; // 0x3f8f
    // Metadata: bool*
    bool Unk_3f90; // 0x3f90
    // Metadata: bool*
    bool Unk_3f91; // 0x3f91
    // Metadata: bool*
    bool Unk_3f92; // 0x3f92
    // Metadata: bool*
    bool Unk_3f93; // 0x3f93
    // Metadata: bool*
    bool Unk_3f94; // 0x3f94
    // Metadata: bool*
    bool Unk_3f95; // 0x3f95
    // Metadata: bool*
    bool Unk_3f96; // 0x3f96
    // Metadata: bool*
    bool Unk_3f97; // 0x3f97
    // Metadata: bool*
    bool Unk_3f98; // 0x3f98
    // Metadata: bool*
    bool Unk_3f99; // 0x3f99
    // Metadata: bool*
    bool Unk_3f9a; // 0x3f9a
    // Metadata: bool*
    bool Unk_3f9b; // 0x3f9b
    // Metadata: bool*
    bool Unk_3f9c; // 0x3f9c
    // Metadata: bool*
    bool Unk_3f9d; // 0x3f9d
    // Metadata: bool*
    bool Unk_3f9e; // 0x3f9e
    // Metadata: bool*
    bool Unk_3f9f; // 0x3f9f
    uint32_t Unk_3fa0; // 0x3fa0
    // Metadata: bool*
    bool Unk_3fa4; // 0x3fa4
    // Metadata: bool*
    bool Unk_3fa5; // 0x3fa5
    // Metadata: bool*
    bool Unk_3fa6; // 0x3fa6
    // Metadata: bool*
    bool Unk_3fa7; // 0x3fa7
    // Metadata: bool*
    bool Unk_3fa8; // 0x3fa8
    // Metadata: bool*
    bool Unk_3fa9; // 0x3fa9
    // Metadata: bool*
    bool Unk_3faa; // 0x3faa
    // Metadata: bool*
    bool Unk_3fab; // 0x3fab
    // Metadata: bool*
    bool Unk_3fac; // 0x3fac
    // Metadata: bool*
    bool Unk_3fad; // 0x3fad
    // Metadata: bool*
    bool Unk_3fae; // 0x3fae
    // Metadata: bool*
    bool Unk_3faf; // 0x3faf
    // Metadata: bool*
    bool Unk_3fb0; // 0x3fb0
    // Metadata: bool*
    bool Unk_3fb1; // 0x3fb1
    // Metadata: bool*
    bool Unk_3fb2; // 0x3fb2
    // Metadata: bool*
    bool Unk_3fb3; // 0x3fb3
    // Metadata: bool*
    bool Unk_3fb4; // 0x3fb4
    // Metadata: bool*
    bool Unk_3fb5; // 0x3fb5
    // Metadata: bool*
    bool Unk_3fb6; // 0x3fb6
    // Metadata: bool*
    bool Unk_3fb7; // 0x3fb7
    // Metadata: bool*
    bool Unk_3fb8; // 0x3fb8
    // Metadata: bool*
    bool Unk_3fb9; // 0x3fb9
    // Metadata: bool*
    bool Unk_3fba; // 0x3fba
    // Metadata: bool*
    bool Unk_3fbb; // 0x3fbb
    uint32_t Unk_3fbc; // 0x3fbc
    // Metadata: bool*
    bool Unk_3fc0; // 0x3fc0
    // Metadata: bool*
    bool Unk_3fc1; // 0x3fc1
    // Metadata: bool*
    bool Unk_3fc2; // 0x3fc2
    // Metadata: bool*
    bool Unk_3fc3; // 0x3fc3
    // Metadata: bool*
    bool Unk_3fc4; // 0x3fc4
    // Metadata: bool*
    bool Unk_3fc5; // 0x3fc5
    // Metadata: bool*
    bool Unk_3fc6; // 0x3fc6
    // Metadata: bool*
    bool Unk_3fc7; // 0x3fc7
    // Metadata: bool*
    bool Unk_3fc8; // 0x3fc8
    // Metadata: bool*
    bool Unk_3fc9; // 0x3fc9
    // Metadata: bool*
    bool Unk_3fca; // 0x3fca
    // Metadata: bool*
    bool Unk_3fcb; // 0x3fcb
    // Metadata: bool*
    bool Unk_3fcc; // 0x3fcc
    // Metadata: bool*
    bool Unk_3fcd; // 0x3fcd
    // Metadata: bool*
    bool Unk_3fce; // 0x3fce
    // Metadata: bool*
    bool Unk_3fcf; // 0x3fcf
    // Metadata: bool*
    bool Unk_3fd0; // 0x3fd0
    // Metadata: bool*
    bool Unk_3fd1; // 0x3fd1
    // Metadata: bool*
    bool Unk_3fd2; // 0x3fd2
    // Metadata: bool*
    bool Unk_3fd3; // 0x3fd3
    // Metadata: bool*
    bool Unk_3fd4; // 0x3fd4
    // Metadata: bool*
    bool Unk_3fd5; // 0x3fd5
    // Metadata: bool*
    bool Unk_3fd6; // 0x3fd6
    // Metadata: bool*
    bool Unk_3fd7; // 0x3fd7
    private: char pad_3fd8[0x30]; public:
    // Metadata: utf8*
    char m_DiscUser[32]; // 0x4008
    private: char pad_4028[0x54]; public:
    // Metadata: utf8*
    char m_StatsBuild[32]; // 0x407c
    private: char pad_409c[0xe4]; public:
    StringId64 AudioStringId; // 0x4180
    private: char pad_4188[0x227]; public:
    // Metadata: bool*
    bool m_ShowStats; // 0x43af
    private: char pad_43b0[0xb3]; public:
    // Metadata: utf8*
    char m_GameStudio[64]; // 0x4463
    private: char pad_44a3[0x11d]; public:
}; // Size: 0x45c0
#pragma pack(pop)
}
