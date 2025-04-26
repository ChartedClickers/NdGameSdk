#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::ndlib::script::DC {
struct Entry;
}
namespace regenny::shared::ndlib::script::DC {
#pragma pack(push, 1)
struct Header {
    uint32_t m_magic; // 0x0
    uint32_t m_versionNumber; // 0x4
    uint32_t m_textSize; // 0x8
    uint32_t unk; // 0xc
    uint32_t unk1; // 0x10
    uint32_t m_numEntries; // 0x14
    regenny::shared::ndlib::script::DC::Entry* m_pStartOfData; // 0x18
}; // Size: 0x20
#pragma pack(pop)
}
