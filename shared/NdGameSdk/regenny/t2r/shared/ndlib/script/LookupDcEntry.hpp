#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::ndlib::script {
struct ModuleInfo;
}
namespace regenny::shared::ndlib::script {
#pragma pack(push, 1)
struct LookupDcEntry {
    void* m_entryPtr; // 0x0
    regenny::shared::ndlib::script::ModuleInfo* m_module; // 0x8
    StringId64 m_scriptId; // 0x10
    StringId64 m_typeId; // 0x18
    uint32_t m_field20; // 0x20
    uint8_t m_field24; // 0x24
    private: char pad_25[0x3]; public:
}; // Size: 0x28
#pragma pack(pop)
}
