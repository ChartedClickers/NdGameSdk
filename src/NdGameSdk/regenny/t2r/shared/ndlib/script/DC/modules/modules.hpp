#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::ndlib::script::DC::modules {
#pragma pack(push, 1)
struct modules {
    struct ModuleUnkCollection {
        uint64_t m_num; // 0x0
        StringId64* m_pArray; // 0x8
    }; // Size: 0x10

    struct ModuleCollection {
        uint64_t m_num; // 0x0
        StringId64* m_modules; // 0x8
    }; // Size: 0x10

    struct ModuleInfo {
        // Metadata: utf8*
        char* m_name; // 0x0
        StringId64 m_hash; // 0x8
        uint64_t m_size; // 0x10
        regenny::shared::ndlib::script::DC::modules::modules::ModuleCollection* m_pCollection; // 0x18
        regenny::shared::ndlib::script::DC::modules::modules::ModuleUnkCollection* m_unkCollection; // 0x20
    }; // Size: 0x28

    struct ModuleInfoArray {
        uint64_t m_numModules; // 0x0
        regenny::shared::ndlib::script::DC::modules::modules::ModuleInfo* m_modules; // 0x8
    }; // Size: 0x10

}; // Size: 0x0
#pragma pack(pop)
}
