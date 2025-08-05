#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::corelib::job {
#pragma pack(push, 1)
struct JlsEntry {
    StringId64 m_contextid; // 0x0
    uint64_t m_payload; // 0x8
}; // Size: 0x10
#pragma pack(pop)
}
