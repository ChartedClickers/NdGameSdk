#pragma once

/*
CSGOSimple's pattern scan
https://github.com/OneshotGH/CSGOSimple-master/blob/master/CSGOSimple/helpers/utils.cpp
kananlib
https://github.com/cursey/kananlib
*/

#include <iostream>
#include <optional>
#include <vector>
#include <mutex>
#include <ppl.h>
#include <string>
#include <windows.h>

#include <safetyhook.hpp>
#include <safetyhook/inline_hook.hpp>

#include "Pattern.hpp"

namespace Utility::memory {

    template <typename CharT>
    uint8_t* PatternScan(HMODULE module, const CharT* signature, const std::wstring name) {
        Pattern patternBytes{ signature, name };
        return patternBytes.find(module);
    }

    template <typename DataT>
    uint8_t* scan_data(HMODULE module, const uint8_t* data, size_t size) {

        auto dosHeader = reinterpret_cast<PIMAGE_DOS_HEADER>(module);
        auto ntHeaders = reinterpret_cast<PIMAGE_NT_HEADERS>((uint8_t*)module + dosHeader->e_lfanew);
        auto sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;
        auto scanBytes = reinterpret_cast<uint8_t*>(module);

        for (size_t i = 0; i < sizeOfImage - size; ++i) {
            DataT currentValue = reinterpret_cast<DataT>(&scanBytes[i]);
            if (memcmp(currentValue, data, size) == 0) {
                return &scanBytes[i];
            }
        }

        return nullptr;
    }

    template <typename DataT>
    uint8_t* scan_value(HMODULE module, const DataT value) {

        auto dosHeader = reinterpret_cast<PIMAGE_DOS_HEADER>(module);
        auto ntHeaders = reinterpret_cast<PIMAGE_NT_HEADERS>((uint8_t*)module + dosHeader->e_lfanew);
        auto sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;
        auto scanBytes = reinterpret_cast<uint8_t*>(module);

        for (size_t i = 0; i < sizeOfImage - sizeof(DataT); ++i) {
            DataT currentValue = *reinterpret_cast<DataT*>(&scanBytes[i]);
            if (currentValue == value) {
                return &scanBytes[i];
            }
        }

        return nullptr;
    }


    uintptr_t ReadMultiLevelPointer(uintptr_t base, const std::vector<uint32_t>& offsets);
    PIMAGE_RUNTIME_FUNCTION_ENTRY FindFunctionEntry(uintptr_t middle);
    std::optional<uintptr_t> FindFunctionStart(uintptr_t middle);
    uint8_t* char_Scan(HMODULE module, const char* value);
    uint8_t* u32_Scan(HMODULE module, uint32_t value);
    uint8_t* u64_Scan(HMODULE module, uint64_t value);

}