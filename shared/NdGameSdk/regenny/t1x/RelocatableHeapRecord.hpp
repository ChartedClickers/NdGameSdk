#pragma once
#include <NdGameSdk/sdkstringid.hpp>
#include <cstdint>
namespace regenny {
struct process;
}
namespace regenny {
#pragma pack(push, 1)
struct RelocatableHeapRecord {
    regenny::process* PTR; // 0x0
}; // Size: 0x8
#pragma pack(pop)
}
