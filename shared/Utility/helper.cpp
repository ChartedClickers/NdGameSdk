#include "helper.hpp"
#include "ansi.hpp"
#include "assertion/assert.hpp"

using namespace Utility::memory;
using namespace safetyhook;

namespace Utility {

    void ShowPatchInfo(size_t Patch_Size, Address Patch_Addr, const wchar_t* Patch_Name, uint64_t Patch_Function_Target)
    {
        LOG_INFO(L"Patch Name: %s", Patch_Name);
        LOG_INFO(L"Patch length: %llu bytes", Patch_Size);
        LOG_INFO(L"Patch address: 0x%016llx", (uintptr_t)Patch_Addr);
        if (Patch_Function_Target) { LOG_INFO(L"Patch Function Target: 0x%016llx", Patch_Function_Target); }
    }

    void LogPatternFailed(const wchar_t* Patch_Name, const wchar_t* Patch_Pattern)
    {
        LOG_ERROR(L"" ANSI_RED "%s Pattern Scan Failed. Please adjust your scan patterns and try again" ANSI_RESET "", Patch_Name);
        LOG_INFO(L"Pattern %s", Patch_Pattern);
    }

    Patch::Ptr WritePatchAddress(HMODULE module, Address Patch_Address, const std::vector<int16_t>& Patch_Bytes, const wchar_t* Patch_Name, bool enable)
    {
        uint64_t Patch_Address_Offset = Patch_Address;
        auto patch = Patch::create(Patch_Address_Offset, Patch_Bytes, Patch_Name, enable);
        ShowPatchInfo(patch.get()->GetPatchSize(), patch.get()->GetPatchAddress(), patch.get()->GetName().c_str(), 0x0);
        return patch;
    }


    Patch::Ptr WritePatchPattern(HMODULE module, const wchar_t* Patch_Pattern, const std::vector<int16_t>& Patch_Bytes, const wchar_t* Patch_Name, uint64_t Patch_Offset, bool enable) {
        uint8_t* Address_Result = PatternScan(module, Patch_Pattern, Patch_Name);
        uintptr_t Patch_Address = 0;
        if (Address_Result)
        {
            Patch_Address = (uintptr_t)Address_Result + Patch_Offset;
            auto patch = Patch::create(Patch_Address, Patch_Bytes, Patch_Name, enable);
            ShowPatchInfo(patch.get()->GetPatchSize(), patch.get()->GetPatchAddress(), patch.get()->GetName().c_str(), 0x0);
            return patch;
        }
        else
        {
            LogPatternFailed(Patch_Name, Patch_Pattern);
            return {};
        }

        return {};
    }

    Patch::Ptr WritePatchPattern(HMODULE module, const wchar_t* Patch_Pattern, const unsigned char* Patch_Bytes, size_t Patch_Size, const wchar_t* Patch_Name, uint64_t Patch_Offset, bool enable) {
       
        std::vector<int16_t> pattern(Patch_Size);
        for (size_t i = 0; i < Patch_Size; ++i) {
            pattern[i] = static_cast<int16_t>(Patch_Bytes[i]);
        }

        return WritePatchPattern(module, Patch_Pattern, pattern, Patch_Name, Patch_Offset, enable);
    }

    Patch::Ptr WritePatchNop(HMODULE module, Address Patch_Address, const uint32_t length, const wchar_t* Patch_Name, bool enable)
    {
        uint64_t Patch_Address_Offset = Patch_Address;
        auto patch = Patch::create_nop(Patch_Address_Offset, length, Patch_Name, enable);
        ShowPatchInfo(patch.get()->GetPatchSize(), patch.get()->GetPatchAddress(), patch.get()->GetName().c_str(), 0x0);
        return patch;
    }

    Patch::Ptr WritePatchNop(HMODULE module, const wchar_t* Patch_Pattern, const uint32_t length, const wchar_t* Patch_Name, uint64_t Patch_Offset, bool enable)
    {
        uint8_t* Address_Result = PatternScan(module, Patch_Pattern, Patch_Name);
        uintptr_t Patch_Address = 0;
        if (Address_Result)
        {
            Patch_Address = (uintptr_t)Address_Result + Patch_Offset;
            auto patch = Patch::create_nop(Patch_Address, length, Patch_Name, enable);
            ShowPatchInfo(patch.get()->GetPatchSize(), patch.get()->GetPatchAddress(), patch.get()->GetName().c_str(), 0x0);
            return patch;
        }
        else
        {
            LogPatternFailed(Patch_Name, Patch_Pattern);
            return {};
        }

        return {};
    }

    Patch::Ptr WritePatchAddress_Value(HMODULE module, size_t Patch_Size, const wchar_t* Patch_Pattern, void* Patch_Value, const wchar_t* Patch_Name, uint64_t Patch_Offset)
    {
        return WritePatchPattern(module, Patch_Pattern, (unsigned char*)Patch_Value, Patch_Size, Patch_Name, Patch_Offset);
    }

    Patch::Ptr WritePatchAddress_Value(HMODULE module, size_t Patch_Size, Address Patch_Address, void* Patch_Value, const wchar_t* Patch_Name)
    {
        const unsigned char* Patch_Bytes = (unsigned char*)Patch_Value;

        std::vector<int16_t> pattern(Patch_Size);
        for (size_t i = 0; i < Patch_Size; ++i) {
            pattern[i] = static_cast<int16_t>(Patch_Bytes[i]);
        }

        return WritePatchAddress(module, Patch_Address, pattern, Patch_Name);
    }

    uintptr_t FindAndPrintPattern(HMODULE module, const wchar_t* Patch_Pattern, const wchar_t* Pattern_Name, size_t offset)
    {
        Pattern patternBytes{ Patch_Pattern, Pattern_Name };
        uintptr_t Address_Result = (uintptr_t)patternBytes.find(module);
        uintptr_t Patch_Address = 0;
        if (Address_Result)
        {
            if (offset)
            {
                Patch_Address = offset + Address_Result;
                LOG_INFO(L"%s: 0x%016llx -> 0x%llx = 0x%016llx", patternBytes.patternName().c_str(), Address_Result, offset, Patch_Address);
            }
            else
            {
                Patch_Address = Address_Result;
                LOG_INFO(L"%s: 0x%016llx", patternBytes.patternName().c_str(), Patch_Address);
            }
            return Patch_Address;
        }
        else
        {
            LogPatternFailed(patternBytes.patternName().c_str(), Patch_Pattern);
        }

        return NULL;
    }

    uintptr_t ReadLEA32(HMODULE module, const wchar_t* Patch_Pattern, const wchar_t* Pattern_Name, size_t offset, size_t lea_size, size_t lea_opcode_size)
    {
        uintptr_t Address_Result = (uintptr_t)PatternScan(module, Patch_Pattern, Pattern_Name);
        uintptr_t Patch_Address = 0;
        int32_t lea_offset = 0;
        uintptr_t New_Offset = 0;
        if (Address_Result)
        {
            if (offset)
            {
                Patch_Address = offset + Address_Result;
                lea_offset = *(int32_t*)(lea_size + Patch_Address);
                New_Offset = Patch_Address + lea_offset + lea_opcode_size;
            }
            else
            {
                Patch_Address = Address_Result;
                lea_offset = *(int32_t*)(lea_size + Address_Result);
                New_Offset = Patch_Address + lea_offset + lea_opcode_size;
            }

            LOG_INFO(L"%s: 0x%016llx -> 0x%016llx\n", Pattern_Name, Address_Result, New_Offset);
            return New_Offset;
        }
        else
        {
            LogPatternFailed(Pattern_Name, Patch_Pattern);
        }

        return NULL;
    }

    MidHook MakeMidHook(void* source_target, MidHookFn target_jmp, const wchar_t* source_name, const wchar_t* hook_name)
    {
		if (!source_target || !target_jmp)
		{
			always_assert(!source_target || !target_jmp, nullptr);
		}

		auto mid_hook = MidHook::create(source_target, target_jmp);

		if (!mid_hook.has_value()) {
			LOG_ERROR(L"Failed to create MidHook for %s: %d", hook_name, static_cast<uint8_t>(mid_hook.error().type));
			return {};
		}

		LOG_INFO(L"Created MidHook %s (0x%016llx) to %s (0x%016llx)\n", source_name, mid_hook->target_address(), hook_name, (uintptr_t)mid_hook->destination());
        return std::move(*mid_hook);
    }

    FunctionHook::Ptr MakeFunctionHook(void* source_target, void* target_jmp, const wchar_t* hook_name)
    {
        auto hook = make_unique<FunctionHook>(source_target, target_jmp, hook_name);

        if (!hook->create()) {
            LOG_ERROR(L"Failed to create FunctionHook for %s", hook->GetName());
            return {};
        }

        LOG_INFO(L"%s Hook Info:\n", hook->GetName());
        LOG_INFO(L"Start address: 0x%016llx\n", (uintptr_t)hook->GetTarget());
        LOG_INFO(L"Return address: 0x%016llx\n", hook->get_original());
        LOG_INFO(L"Function target address: 0x%016llx\n", (uintptr_t)hook->GetDestination());
        return hook;
    }

    FunctionHook::Ptr WritePatchPattern_Hook(HMODULE module, const wchar_t* Patch_Pattern, const wchar_t* Patch_Name, uint64_t Patch_Offset, void* Function_Target)
    {
        uint8_t* Address_Result = nullptr;
        Address_Result = PatternScan(module, Patch_Pattern, Patch_Name);
        if (Address_Result)
        {
            uint64_t Patch_Address = (uintptr_t)Address_Result + Patch_Offset;
            return MakeFunctionHook((void*)Patch_Address, Function_Target, Patch_Name);
        }
        else
        {
            LogPatternFailed(Patch_Name, Patch_Pattern);
        }

        return {};
    }

}
