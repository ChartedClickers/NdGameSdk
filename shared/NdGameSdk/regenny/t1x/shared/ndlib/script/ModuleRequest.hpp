#pragma once
#include <NdGameSdk/sdkstringid.hpp>
#include <cstdint>
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
    StringId64 hash; // 0x10
    uint64_t field_18; // 0x18
    regenny::shared::corelib::memory::Context MemContext; // 0x20
    uint32_t field_24; // 0x24
    size_t size; // 0x28
    uint64_t field_30; // 0x30
    bool field_38; // 0x38
    bool field_39; // 0x39
    bool field_3a; // 0x3a
    uint16_t field_3b; // 0x3b
    bool m_requested; // 0x3d
}; // Size: 0x3e
#pragma pack(pop)
}
