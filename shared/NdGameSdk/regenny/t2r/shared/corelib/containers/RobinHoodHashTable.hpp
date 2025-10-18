#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::corelib::containers {
#pragma pack(push, 1)
struct RobinHoodHashTable {
    struct OccMask {
        uint64_t* m_words; // 0x0
        uint64_t m_capacity; // 0x8
        uint64_t m_capacityAligned64; // 0x10
        uint32_t m_wordCount; // 0x18
        private: char pad_1c[0x4]; public:
    }; // Size: 0x20

    struct OccScan {
        regenny::shared::corelib::containers::RobinHoodHashTable::OccMask* m_pbs; // 0x0
        uint64_t m_currWord; // 0x8
        uint32_t m_wordCount; // 0x10
        uint32_t m_wordIdx; // 0x14
        uint32_t m_limit; // 0x18
        uint32_t m_index; // 0x1c
    }; // Size: 0x20

    struct Slot {
        uint64_t m_hash; // 0x0
        void* m_key; // 0x8
        void* m_value; // 0x10
    }; // Size: 0x18

    Slot* m_Slots; // 0x0
    OccMask m_occ; // 0x8
    uint32_t m_numBuckets; // 0x28
    uint32_t m_numElements; // 0x2c
}; // Size: 0x30
#pragma pack(pop)
}
