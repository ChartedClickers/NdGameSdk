#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "..\..\corelib\containers\RobinHoodHashTable.hpp"
#include "..\..\corelib\memory\PoolAllocator.hpp"
#include "LevelDef.hpp"
#include "LevelDefLoader.hpp"
namespace regenny::shared::gamelib::level {
#pragma pack(push, 1)
struct LevelDefCollection {
    struct FixedArray_corelib_util_level___LevelDef_ptr___3000 {
        regenny::shared::gamelib::level::LevelDef* m_items[3000]; // 0x0
        uint32_t m_count; // 0x5dc0
    }; // Size: 0x5dc4

    struct RobinHoodHashTable_corelib_containers_StringId64_LevelDef {
        struct Slot {
            uint64_t m_hash; // 0x0
            StringId64 m_key; // 0x8
            regenny::shared::gamelib::level::LevelDef m_value; // 0x10
        }; // Size: 0xf0

        Slot* m_Slots; // 0x0
        regenny::shared::corelib::containers::RobinHoodHashTable::OccMask m_occ; // 0x8
        uint32_t m_numBuckets; // 0x28
        uint32_t m_numElements; // 0x2c
    }; // Size: 0x30

    bool m_UseLevelDefAsyncLoad; // 0x0
    private: char pad_1[0x7]; public:
    FixedArray_corelib_util_level___LevelDef_ptr___3000 m_pendingQueue; // 0x8
    private: char pad_5dcc[0x4]; public:
    void* m_allocatorBacking; // 0x5dd0
    RobinHoodHashTable_corelib_containers_StringId64_LevelDef m_table; // 0x5dd8
    private: char pad_5e08[0x8]; public:
    regenny::shared::corelib::memory::PoolAllocator m_allocator; // 0x5e10
    bool m_DisablePoolAlloc; // 0x5ef0
    private: char pad_5ef1[0xf]; public:
    regenny::shared::gamelib::level::LevelDefLoader m_DefLoader; // 0x5f00
    uint64_t m_field7590; // 0x7590
    private: char pad_7598[0x8]; public:
    uint64_t m_field75a0; // 0x75a0
    private: char pad_75a8[0x8]; public:
}; // Size: 0x75b0
#pragma pack(pop)
}
