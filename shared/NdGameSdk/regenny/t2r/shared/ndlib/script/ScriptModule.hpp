#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "..\..\corelib\memory\Context.hpp"
namespace regenny::shared::ndlib::script::DC {
struct Entry;
}
namespace regenny::shared::ndlib::script::DC {
struct Header;
}
namespace regenny::shared::ndlib::script {
struct ModuleInfo;
}
namespace regenny::shared::ndlib::script {
#pragma pack(push, 1)
struct ScriptModule {
    struct Loader {
        private: char pad_0[0x440]; public:
        regenny::shared::ndlib::script::ModuleInfo* m_moduleinfo; // 0x440
        uint64_t m_moduleName; // 0x448
        regenny::shared::corelib::memory::Context m_moduleMemContext; // 0x450
        private: char pad_454[0x2c]; public:
        void* Data; // 0x480
        private: char pad_488[0x38]; public:
        uint64_t field_4c0; // 0x4c0
        uint64_t field_4c8; // 0x4c8
        bool field_4d0; // 0x4d0
        bool field_4d1; // 0x4d1
        bool field_4d2; // 0x4d2
        uint16_t field_4d3; // 0x4d3
        bool field_4d5; // 0x4d5
        bool field_4d6; // 0x4d6
        private: char pad_4d7[0x9]; public:
    }; // Size: 0x4e0

    void* vfTable; // 0x0
    uint64_t field_8; // 0x8
    uint64_t field_10; // 0x10
    uint64_t field_18; // 0x18
    uint64_t field_20; // 0x20
    StringId64 m_modulehash; // 0x28
    StringId64 field_30; // 0x30
    uint32_t m_numEntries; // 0x38
    private: char pad_3c[0x4]; public:
    regenny::shared::ndlib::script::DC::Entry* m_Data; // 0x40
    uint64_t field_48; // 0x48
    regenny::shared::ndlib::script::DC::Header* m_header; // 0x50
    uint64_t field_58; // 0x58
    uint32_t field_60; // 0x60
    uint32_t field_64; // 0x64
    uint32_t field_68; // 0x68
    uint32_t m_size; // 0x6c
}; // Size: 0x70
#pragma pack(pop)
}
