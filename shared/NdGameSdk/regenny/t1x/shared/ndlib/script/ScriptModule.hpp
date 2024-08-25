#pragma once
#include <NdGameSdk/sdkstringid.hpp>
#include <cstdint>
namespace regenny::shared::ndlib::script::DC {
struct Entry;
}
namespace regenny::shared::ndlib::script::DC {
struct Header;
}
namespace regenny::shared::ndlib::script {
#pragma pack(push, 1)
struct ScriptModule {
    void* vfTable; // 0x0
    uint64_t field_8; // 0x8
    uint64_t field_10; // 0x10
    uint64_t field_18; // 0x18
    uint64_t field_20; // 0x20
    uint64_t field_28; // 0x28
    StringId64 field_30; // 0x30
    uint64_t m_numEntries; // 0x38
    regenny::shared::ndlib::script::DC::Entry* m_Data; // 0x40
    uint64_t field_48; // 0x48
    regenny::shared::ndlib::script::DC::Header* m_header; // 0x50
    uint64_t field_58; // 0x58
    uint32_t field_60; // 0x60
    uint32_t field_64; // 0x64
    uint32_t field_68; // 0x68
    uint32_t m_UpperBound; // 0x6c
}; // Size: 0x70
#pragma pack(pop)
}
