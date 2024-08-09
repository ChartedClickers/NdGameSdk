#pragma once

#include <iostream>
#include <vector>
#include <array>
#include <ppl.h>
#include <string>

#include <spdlog/spdlog.h>
#include <spdlog/fmt/bundled/printf.h>

#include <safetyhook.hpp>
#include <safetyhook/inline_hook.hpp>

#include "memory/proc-memory.hpp"
#include "memory/Pattern.hpp"
#include "memory/Patch.hpp"
#include "memory/Module.hpp"
#include "memory/FunctionHook.hpp"

#define SPDLOG_LOGGER_PRINTF(logger, level, ...) \
    loglineprintf(logger, level, spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, __VA_ARGS__)

#define LOG_ERROR(...) SPDLOG_LOGGER_PRINTF(spdlog::default_logger(), spdlog::level::err, __VA_ARGS__)
#define LOG_INFO(...) SPDLOG_LOGGER_PRINTF(spdlog::default_logger(), spdlog::level::info, __VA_ARGS__)

using namespace std;

namespace Utility
{
    template <class loggerPtr, class... Args>
    void loglineprintf(loggerPtr  logger,
        spdlog::level::level_enum level,
        spdlog::source_loc        loc,
        const wchar_t* fmt,
        const Args&... args) noexcept
    {
        if (logger && logger->should_log(level))
        {
            logger->log(loc, level, L"{}", fmt::sprintf(fmt, args...));
        }
    }

    memory::Patch::Ptr WritePatchAddress(HMODULE module, memory::Address Patch_Address, const vector<int16_t>& Patch_Bytes, const wchar_t* Patch_Name, bool enable = true);
    memory::Patch::Ptr WritePatchPattern(HMODULE module, const wchar_t* Patch_Pattern, const vector<int16_t>& Patch_Bytes, const wchar_t* Patch_Name, uint64_t Patch_Offset, bool enable = true);
    memory::Patch::Ptr WritePatchPattern(HMODULE module, const wchar_t* Patch_Pattern, const unsigned char* Patch_Bytes, size_t Patch_Size, const wchar_t* Patch_Name, uint64_t Patch_Offset, bool enable = true);
    
    memory::Patch::Ptr WritePatchNop(HMODULE module, memory::Address Patch_Address, const uint32_t length, const wchar_t* Patch_Name, bool enable = true);
    memory::Patch::Ptr WritePatchNop(HMODULE module, const wchar_t* Patch_Pattern, const uint32_t length, const wchar_t* Patch_Name, uint64_t Patch_Offset, bool enable = true);

    memory::Patch::Ptr WritePatchAddress_Value(HMODULE module, size_t Patch_Size, const wchar_t* Patch_Pattern, void* Patch_Value, const wchar_t* Patch_Name, uint64_t Patch_Offset);
    memory::Patch::Ptr WritePatchAddress_Value(HMODULE module, size_t Patch_Size, memory::Address Patch_Address, void* Patch_Value, const wchar_t* Patch_Name);

    uintptr_t FindAndPrintPattern(HMODULE module, const wchar_t* Patch_Pattern, const wchar_t* Pattern_Name, size_t offset = 0);
    uintptr_t ReadLEA32(HMODULE module, const wchar_t* Patch_Pattern, const wchar_t* Pattern_Name, size_t offset, size_t lea_size, size_t lea_opcode_size);

    MidHook MakeMidHook(void* source_target, MidHookFn target_jmp, const wchar_t* source_name, const wchar_t* hook_name);

    memory::FunctionHook::Ptr MakeFunctionHook(void* source_target, void* target_jmp, const wchar_t* hook_name);
    memory::FunctionHook::Ptr WritePatchPattern_Hook(HMODULE module, const wchar_t* Patch_Pattern, const wchar_t* Patch_Name, uint64_t Patch_Offset, void* Function_Target);
}
