#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "..\..\corelib\containers\FixedSizeHeap.hpp"
namespace regenny::shared::ndlib::script {
struct ModuleInfo;
}
namespace regenny::shared::ndlib::script {
struct ScriptModule;
}
namespace regenny::shared::ndlib::script {
struct ModuleBucket;
}
namespace regenny::shared::ndlib::script {
#pragma pack(push, 1)
struct ModuleBucketMap {
    private: char pad_0[0x8]; public:
    regenny::shared::corelib::containers::FixedSizeHeap m_SymbolsHeap; // 0x8
    uint64_t* field_60; // 0x60
    uint64_t field_68; // 0x68
    uint64_t m_maxGlobalSymbols; // 0x70
    void* m_SymbolsHead; // 0x78
    void* m_SymbolsTail; // 0x80
    uint64_t m_numGlobalSymbols; // 0x88
    uint64_t* m_symbolBuckets; // 0x90
    regenny::shared::ndlib::script::ModuleInfo* m_ModulesHead; // 0x98
    regenny::shared::ndlib::script::ModuleInfo* m_ModulesTail; // 0xa0
    regenny::shared::ndlib::script::ModuleBucket* m_ModuleBucket; // 0xa8
    regenny::shared::corelib::containers::FixedSizeHeap m_ModulesHeap; // 0xb0
    private: char pad_108[0x10]; public:
    uint64_t m_maxModules; // 0x118
    private: char pad_120[0x10]; public:
    uint64_t m_numModules; // 0x130
    private: char pad_138[0x8]; public:
    uint64_t m_ScriptModuleCapacity; // 0x140
    regenny::shared::ndlib::script::ScriptModule* m_ScriptModulesHead; // 0x148
    regenny::shared::ndlib::script::ScriptModule* m_ScriptModulesTail; // 0x150
    regenny::shared::ndlib::script::ModuleBucket* m_ScriptModuleBucket; // 0x158
    regenny::shared::corelib::containers::FixedSizeHeap m_ScriptModuleHeap; // 0x160
    private: char pad_1b8[0x10]; public:
    uint64_t m_maxScriptModules; // 0x1c8
    private: char pad_1d0[0x10]; public:
    uint64_t m_numScriptModules; // 0x1e0
    uint32_t m_bucketCount; // 0x1e8
    uint32_t m_lookupFlags; // 0x1ec
}; // Size: 0x1f0
#pragma pack(pop)
}
