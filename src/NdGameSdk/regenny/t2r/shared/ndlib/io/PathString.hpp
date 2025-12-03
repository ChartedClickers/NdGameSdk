#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::ndlib::io {
#pragma pack(push, 1)
struct PathString {
    // Metadata: utf16*
    wchar_t* m_pathPtr; // 0x0
    uint64_t m_headHi; // 0x8
    uint64_t m_pathLen; // 0x10
    uint64_t m_pathCap; // 0x18
}; // Size: 0x20
#pragma pack(pop)
}
