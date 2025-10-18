#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "..\..\ndlib\io\FileSystem.hpp"
namespace regenny::shared::corelib::memory {
struct Allocator;
}
namespace regenny::shared::gamelib::level {
#pragma pack(push, 1)
struct LevelDef {
    enum State : uint32_t {
        Idle = 0,
        Queued = 1,
        ResolveDone = 2,
        SizeKnown = 3,
        Reading = 4,
        ParsePending = 5,
        Ready = 6,
        Failed = 7,
    };

    enum Flags : uint8_t {
        None = 0,
        DisablePartPackages = 1,
    };

    struct ActorDefs {
        // Metadata: utf8*
        char* m_name; // 0x0
        StringId64 m_id; // 0x8
    }; // Size: 0x10

    struct PackageDef {
        enum Kind : uint8_t {
            Base = 1,
            Phys = 2,
            Ingame = 4,
        };

        // Metadata: utf8*
        char* m_name; // 0x0
        StringId64 m_id; // 0x8
        Kind m_kind; // 0x10
        bool m_isDictFallback; // 0x11
        private: char pad_12[0x6]; public:
    }; // Size: 0x18

    struct SoundBankDef {
        // Metadata: utf8*
        char* m_name; // 0x0
        bool m_streamed; // 0x8
        private: char pad_9[0x7]; public:
    }; // Size: 0x10

    struct ModuleRef {
        StringId64 m_id; // 0x0
        void* m_payload; // 0x8
    }; // Size: 0x10

    struct AsyncTxtLoad {
        regenny::shared::corelib::memory::Allocator* m_allocator; // 0x0
        regenny::shared::ndlib::io::FileSystem::ReadOnlyFileHandle m_handle; // 0x8
        regenny::shared::ndlib::io::FileSystem::ReadOperation m_readOp; // 0x28
        uint64_t m_fileSize; // 0x40
        uint64_t m_bytesRead; // 0x48
        char* m_buffer; // 0x50
    }; // Size: 0x58

    private: char pad_0[0x8]; public:
    uint64_t m_field8; // 0x8
    // Metadata: utf8*
    char* m_name; // 0x10
    StringId64 m_id; // 0x18
    PackageDef* m_packages; // 0x20
    uint64_t m_packageCount; // 0x28
    ActorDefs* m_actorPacks; // 0x30
    uint64_t m_actorCount; // 0x38
    StringId64* m_caches; // 0x40
    uint64_t m_cacheCount; // 0x48
    StringId64* m_modules; // 0x50
    uint64_t m_moduleCount; // 0x58
    StringId64* m_renderSettings; // 0x60
    uint64_t m_renderSettingsCount; // 0x68
    ModuleRef* m_particleModules; // 0x70
    uint64_t m_particleModuleCount; // 0x78
    SoundBankDef* m_soundBanks; // 0x80
    uint64_t m_soundBankCount; // 0x88
    ModuleRef* m_voxCharacters; // 0x90
    uint64_t m_voxCharacterCount; // 0x98
    // Metadata: utf8*
    char* m_partModuleName; // 0xa0
    AsyncTxtLoad* m_AsyncTxtLoad; // 0xa8
    State m_state; // 0xb0
    Flags m_flags; // 0xb4
    private: char pad_b5[0xb]; public:
    vec4 m_boundsMin; // 0xc0
    vec4 m_boundsMax; // 0xd0
}; // Size: 0xe0
#pragma pack(pop)
}
