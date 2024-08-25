#pragma once
#include <NdGameSdk/sdkstringid.hpp>
#include <cstdint>
namespace regenny::shared::ndlib::script::DC {
#pragma pack(push, 1)
struct Entry {
    StringId64 m_scriptId; // 0x0
    StringId64 m_typeId; // 0x8
    void* m_entryPtr; // 0x10
}; // Size: 0x18
#pragma pack(pop)
}
