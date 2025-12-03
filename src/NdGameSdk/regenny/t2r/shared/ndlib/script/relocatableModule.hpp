#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::ndlib::script {
#pragma pack(push, 1)
struct relocatableModule {
    void* vfTable; // 0x0
    uint64_t m_pRecord; // 0x8
    uint64_t m_field10; // 0x10
    uint64_t m_field18; // 0x18
    // Metadata: utf8*
    char* m_ModuleInfoArray; // 0x20
    // Metadata: utf8*
    char* m_ModuleInfoArrayDebug; // 0x28
}; // Size: 0x30
#pragma pack(pop)
}
