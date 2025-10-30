#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "..\gamelib\level\DataLoading.hpp"
#include "debug\DMENU.hpp"
namespace regenny::shared::gamelib::level {
struct LevelDefCollection;
}
namespace regenny::shared::gamelib::level {
struct LoadRegistry;
}
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
    regenny::shared::gamelib::level::LoadRegistry* m_LoadRegistry; // 0x28
    regenny::shared::gamelib::level::LevelDefCollection* m_LevelDefCollection; // 0x30
    regenny::shared::corelib::util::StringCache* m_pNameCache; // 0x38
    uint64_t m_field40; // 0x40
    uint64_t m_field48; // 0x48
    uint64_t m_field50; // 0x50
    uint64_t m_field58; // 0x58
    uint64_t m_field60; // 0x60
    uint64_t m_field68; // 0x68
    void* m_RedisJSONRpcServer; // 0x70
    uint64_t m_field78; // 0x78
    uint64_t m_field80; // 0x80
    uint32_t m_field88; // 0x88
    uint32_t m_PakManifestId; // 0x8c
    uint32_t m_ActorManifestId; // 0x90
    uint32_t m_field94; // 0x94
    uint32_t m_field98; // 0x98
    uint32_t m_field9c; // 0x9c
    uint32_t m_fielda0; // 0xa0
    uint32_t m_fielda4; // 0xa4
    uint32_t m_fielda8; // 0xa8
    uint32_t m_fieldac; // 0xac
    private: char pad_b0[0xc]; public:
    uint32_t m_buildId; // 0xbc
    uint64_t m_RpcController; // 0xc0
    uint64_t m_NdGameTitle; // 0xc8
    bool m_fieldd0; // 0xd0
    bool m_Profiling; // 0xd1
    bool m_gameConfigComplete; // 0xd2
    bool m_fieldd3; // 0xd3
    private: char pad_d4[0x2c]; public:
    uint64_t m_field100; // 0x100
    private: char pad_108[0xe]; public:
    bool m_field116; // 0x116
    private: char pad_117[0x6a]; public:
    uint64_t m_field181; // 0x181
    private: char pad_189[0xe]; public:
    bool m_field197; // 0x197
    bool m_field198; // 0x198
    private: char pad_199[0xaf]; public:
    regenny::shared::gamelib::level::DataLoading::Config m_pDataConfig; // 0x248
    private: char pad_268[0x8]; public:
}; // Size: 0x270
#pragma pack(pop)
}
