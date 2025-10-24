#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "FixedSizeHashTable.hpp"
namespace regenny::shared::corelib::containers {
#pragma pack(push, 1)
struct Node_StringId64_StringId64 : public FixedSizeHashTable::ListHead {
    StringId64 m_key; // 0x10
    StringId64 m_value; // 0x18
}; // Size: 0x20
#pragma pack(pop)
}
