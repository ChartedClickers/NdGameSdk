#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::gamelib::level {
#pragma pack(push, 1)
struct Level {
    private: char pad_0[0x48]; public:
    // Metadata: utf8*
    char* m_PackageName; // 0x48
    StringId64 m_PackageId; // 0x50
    private: char pad_58[0xa0]; public:
    void* m_pFgGeometry; // 0xf8
    void* m_pEntitySpawners; // 0x100
    void* m_field108; // 0x108
    void* m_field110; // 0x110
    void* m_ppLightTables; // 0x118
    void* m_field120; // 0x120
    void* m_field128; // 0x128
    void* m_pBackground; // 0x130
    private: char pad_138[0x988]; public:
}; // Size: 0xac0
#pragma pack(pop)
}
