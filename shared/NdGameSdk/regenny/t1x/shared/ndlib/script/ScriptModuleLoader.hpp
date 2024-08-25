#pragma once
#include <NdGameSdk/sdkstringid.hpp>
#include <cstdint>
#include "..\..\corelib\memory\Context.hpp"
namespace regenny::shared::ndlib::script {
struct ModuleInfo;
}
namespace regenny::shared::ndlib::script {
#pragma pack(push, 1)
struct ScriptModuleLoader {
    private: char pad_0[0x3018]; public:
    regenny::shared::ndlib::script::ModuleInfo* m_moduleinfo; // 0x3018
    uint64_t m_moduleName; // 0x3020
    regenny::shared::corelib::memory::Context m_moduleMemContext; // 0x3028
    uint32_t field_302c; // 0x302c
    uint64_t field_3030; // 0x3030
    private: char pad_3038[0x58]; public:
    uint64_t field_3090; // 0x3090
    uint64_t field_3098; // 0x3098
    private: char pad_30a0[0x28]; public:
    bool field_30c8; // 0x30c8
    bool field_30c9; // 0x30c9
    bool field_30ca; // 0x30ca
    uint16_t field_30cb; // 0x30cb
    uint8_t field_30cd; // 0x30cd
    bool field_30ce; // 0x30ce
    private: char pad_30cf[0x1]; public:
}; // Size: 0x30d0
#pragma pack(pop)
}
