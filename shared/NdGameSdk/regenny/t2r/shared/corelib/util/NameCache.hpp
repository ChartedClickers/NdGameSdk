#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::corelib::util {
#pragma pack(push, 1)
struct NameCache {
    void* vftable; // 0x0
    void* m_bucketTable; // 0x8
    void* m_nodePool; // 0x10
    void* m_freeList; // 0x18
    void* m_allocator; // 0x20
    uint32_t m_bucketCount; // 0x28
    uint32_t m_entryCount; // 0x2c
    uint32_t m_nameCapacity; // 0x30
    uint32_t m_nameCount; // 0x34
    char* m_writePtr; // 0x38
    uint32_t m_offset; // 0x40
    uint32_t m_stringCount; // 0x44
    uint32_t m_cacheSize; // 0x48
    private: char pad_4c[0x4]; public:
}; // Size: 0x50
#pragma pack(pop)
}
