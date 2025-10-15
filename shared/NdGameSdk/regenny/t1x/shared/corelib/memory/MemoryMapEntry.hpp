#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "Context.hpp"
#include "MapId.hpp"
namespace regenny::shared::corelib::memory {
#pragma pack(push, 1)
struct MemoryMapEntry {
    regenny::shared::corelib::memory::MapId m_id; // 0x0
    regenny::shared::corelib::memory::Context m_context; // 0x4
    uint64_t m_size; // 0x8
    uint64_t m_aligned; // 0x10
    // Metadata: utf8*
    char* m_name; // 0x18
}; // Size: 0x20
#pragma pack(pop)
}
