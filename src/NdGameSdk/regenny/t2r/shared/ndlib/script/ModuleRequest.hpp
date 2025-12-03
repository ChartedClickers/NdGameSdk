#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "..\..\corelib\memory\Context.hpp"
namespace regenny::shared::ndlib::script {
#pragma pack(push, 1)
struct ModuleRequest {
    struct ModuleRequestList {
        regenny::shared::ndlib::script::ModuleRequest* m_head; // 0x0
        regenny::shared::ndlib::script::ModuleRequest* m_tail; // 0x8
    }; // Size: 0x10

    regenny::shared::ndlib::script::ModuleRequest* m_NextModuleRequest; // 0x0
    regenny::shared::ndlib::script::ModuleRequest* m_PrevModuleRequest; // 0x8
    StringId64 m_hash; // 0x10
    uint64_t m_field18; // 0x18
    regenny::shared::corelib::memory::Context m_MemContext; // 0x20
    uint32_t m_index; // 0x24
    size_t m_size; // 0x28
    uint64_t m_field30; // 0x30
    bool m_field38; // 0x38
    bool m_field39; // 0x39
    bool m_field3a; // 0x3a
    bool m_field3b; // 0x3b
    bool m_field3c; // 0x3c
    bool m_requested; // 0x3d
    private: char pad_3e[0x2]; public:
}; // Size: 0x40
#pragma pack(pop)
}
