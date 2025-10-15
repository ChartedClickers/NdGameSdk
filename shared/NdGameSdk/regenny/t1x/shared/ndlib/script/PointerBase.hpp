#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::ndlib::script {
struct ModuleInfo;
}
namespace regenny::shared::ndlib::script {
#pragma pack(push, 1)
struct PointerBase {
    void* m_ptr; // 0x0
    regenny::shared::ndlib::script::ModuleInfo* m_module; // 0x8
    StringId64 m_symbolId; // 0x10
    StringId64 m_moduleId; // 0x18
    uint32_t m_field20; // 0x20
    bool m_resolveAttempted; // 0x24
    private: char pad_25[0x3]; public:
}; // Size: 0x28
#pragma pack(pop)
}
