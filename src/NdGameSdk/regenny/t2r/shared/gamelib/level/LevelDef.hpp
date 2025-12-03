#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "LevelSpec.hpp"
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
        char* m_pName; // 0x0
        StringId64 m_id; // 0x8
    }; // Size: 0x10

    struct PackageDef {
        // Metadata: utf8*
        char* m_pName; // 0x0
        StringId64 m_id; // 0x8
        regenny::shared::gamelib::level::LevelSpec::Layer m_layer; // 0x10
        bool m_optional; // 0x11
        private: char pad_12[0x6]; public:
    }; // Size: 0x18

    struct ParticleModuleDef {
        StringId64 m_id; // 0x0
        bool m_ignore; // 0x8
        private: char pad_9[0x7]; public:
    }; // Size: 0x10

    struct SoundBankDef {
        // Metadata: utf8*
        char* m_pName; // 0x0
        uint8_t m_type; // 0x8
        private: char pad_9[0x7]; public:
    }; // Size: 0x10

    struct AsyncTxtLoad {
        regenny::shared::corelib::memory::Allocator* m_allocator; // 0x0
        regenny::shared::ndlib::io::FileSystem::ReadOnlyFileHandle m_handle; // 0x8
        regenny::shared::ndlib::io::FileSystem::ReadOperation m_readOp; // 0x28
        uint64_t m_fileSize; // 0x40
        uint64_t m_bytesRead; // 0x48
        char* m_buffer; // 0x50
    }; // Size: 0x58

    struct StaticArray_corelib_containers_PackageDef {
        regenny::shared::gamelib::level::LevelDef::PackageDef* m_data; // 0x0
        uint32_t m_size; // 0x8
        private: char pad_c[0x4]; public:
    }; // Size: 0x10

    struct StaticArray_corelib_containers_ActorDefs {
        regenny::shared::gamelib::level::LevelDef::ActorDefs* m_data; // 0x0
        uint32_t m_size; // 0x8
        private: char pad_c[0x4]; public:
    }; // Size: 0x10

    struct StaticArray_corelib_containers_StringId64 {
        StringId64* m_data; // 0x0
        uint32_t m_size; // 0x8
        private: char pad_c[0x4]; public:
    }; // Size: 0x10

    struct StaticArray_corelib_containers_ParticleModuleDef {
        regenny::shared::gamelib::level::LevelDef::ParticleModuleDef* m_data; // 0x0
        uint32_t m_size; // 0x8
        private: char pad_c[0x4]; public:
    }; // Size: 0x10

    struct StaticArray_corelib_containers_SoundBankDef {
        regenny::shared::gamelib::level::LevelDef::SoundBankDef* m_data; // 0x0
        uint32_t m_size; // 0x8
        private: char pad_c[0x4]; public:
    }; // Size: 0x10

    private: char pad_0[0x8]; public:
    uint64_t m_field8; // 0x8
    // Metadata: utf8*
    char* m_name; // 0x10
    StringId64 m_id; // 0x18
    StaticArray_corelib_containers_PackageDef m_packageDefs; // 0x20
    StaticArray_corelib_containers_ActorDefs m_actorDefs; // 0x30
    StaticArray_corelib_containers_StringId64 m_caches; // 0x40
    StaticArray_corelib_containers_StringId64 m_moduleIds; // 0x50
    StaticArray_corelib_containers_StringId64 m_renderSettingsForLutTablesIds; // 0x60
    StaticArray_corelib_containers_ParticleModuleDef m_particleModuleDef; // 0x70
    StaticArray_corelib_containers_SoundBankDef m_soundBankDefs; // 0x80
    StaticArray_corelib_containers_SoundBankDef m_voxCharactersSoundBankDefs; // 0x90
    // Metadata: utf8*
    char* m_associatedPartModuleName; // 0xa0
    AsyncTxtLoad* m_AsyncTxtLoad; // 0xa8
    State m_state; // 0xb0
    Flags m_bits; // 0xb4
    private: char pad_b5[0xb]; public:
    vec4 m_boundsMin; // 0xc0
    vec4 m_boundsMax; // 0xd0
}; // Size: 0xe0
#pragma pack(pop)
}
