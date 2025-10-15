#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "JlsEntry.hpp"
namespace regenny::shared::corelib::job {
#pragma pack(push, 1)
struct JlsBlock {
    regenny::shared::corelib::job::JlsEntry slots[32]; // 0x0
}; // Size: 0x200
#pragma pack(pop)
}
