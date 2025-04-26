#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::ndlib::script {
struct ScriptModule;
}
namespace regenny::shared::ndlib::script {
#pragma pack(push, 1)
struct ModuleInfo {
    uint64_t field_0; // 0x0
    uint64_t field_8; // 0x8
    // Metadata: utf8*
    char* m_name; // 0x10
    StringId64 hash; // 0x18
    size_t m_size; // 0x20
    uint64_t m_pCollection; // 0x28
    uint32_t m_pNumModules; // 0x30
    private: char pad_34[0x4]; public:
    uint64_t m_pUnkCollection; // 0x38
    uint32_t m_pUnkNumModules; // 0x40
    private: char pad_44[0x4]; public:
    regenny::shared::ndlib::script::ScriptModule* m_ScriptModule; // 0x48
    uint64_t field_50; // 0x50
    uint32_t field_58; // 0x58
    bool field_5c; // 0x5c
    bool field_5d; // 0x5d
    bool field_5e; // 0x5e
    bool m_isLoaded; // 0x5f
}; // Size: 0x60
#pragma pack(pop)
}
