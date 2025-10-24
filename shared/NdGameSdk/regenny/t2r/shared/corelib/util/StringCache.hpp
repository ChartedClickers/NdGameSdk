#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "..\containers\RobinHoodHashTable.hpp"
namespace regenny::shared::corelib::util {
#pragma pack(push, 1)
struct StringCache {
    struct RobinHoodHashTable_containers_StringId64_uint32_t {
        struct Slot {
            uint64_t m_hash; // 0x0
            StringId64 m_key; // 0x8
            uint32_t m_value; // 0x10
            private: char pad_14[0x4]; public:
        }; // Size: 0x18

        Slot* m_Slots; // 0x0
        regenny::shared::corelib::containers::RobinHoodHashTable::OccMask m_occ; // 0x8
        uint32_t m_numBuckets; // 0x28
        uint32_t m_numElements; // 0x2c
    }; // Size: 0x30

    void* vftable; // 0x0
    RobinHoodHashTable_containers_StringId64_uint32_t m_table; // 0x8
    char* m_writePtr; // 0x38
    uint32_t m_offset; // 0x40
    uint32_t m_stringCount; // 0x44
    uint32_t m_cacheSize; // 0x48
    private: char pad_4c[0x4]; public:
}; // Size: 0x50
#pragma pack(pop)
}
