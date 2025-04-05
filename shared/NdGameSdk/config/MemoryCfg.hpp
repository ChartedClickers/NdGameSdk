#pragma once

#if defined(T1X)
#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/shared/src/corelib/memory/memory-map.hpp"

using SizeUnit = NdGameSdk::corelib::memory::SizeUnit;
using MemSize = NdGameSdk::corelib::memory::MemSize;

namespace NdGameSdk::config {

    class NdGameSdk_API MemoryCfg {
    public:
        MemoryCfg() {}

        void ModifyMemoryMapEntry(MemoryMapId id, MemSize size) {
            ModifiedMapEntries[id] = size;
        }

        bool DebugMemory{ SDK_DEBUG };
        std::unordered_map<MemoryMapId, MemSize> ModifiedMapEntries;
    };
}
#endif