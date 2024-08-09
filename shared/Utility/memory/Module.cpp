#include "Module.hpp"
#include "../assertion/assert.hpp"

#include <shlwapi.h>
#include <Psapi.h>

#pragma comment(lib,"shlwapi.lib")
#pragma comment(lib,"Version.lib")

namespace Utility::memory
{
    optional<size_t> get_module_size(HMODULE module)
    {
        if (module == nullptr) { return {}; }

        auto dosHeader = (PIMAGE_DOS_HEADER)module;

        if (dosHeader->e_magic != IMAGE_DOS_SIGNATURE) {
            return {};
        }

        auto ntHeaders = (PIMAGE_NT_HEADERS)((uintptr_t)dosHeader + dosHeader->e_lfanew);

        if (ntHeaders->Signature != IMAGE_NT_SIGNATURE) {
            return {};
        }

        return ntHeaders->OptionalHeader.SizeOfImage;
    }

	optional<size_t> get_module_size(const std::string& module)
	{
		return get_module_size(GetModuleHandle(module.c_str()));
	}

    optional<HMODULE> get_module_within(Address address)
    {
        HMODULE module = nullptr;
        if (GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS
            | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, address.as<LPCSTR>(), &module)) {
            return module;
        }

        return {};
    }

    optional<uintptr_t> get_dll_imagebase(Address dll)
    {
        if (dll == nullptr) { return {}; }

        auto dosHeader = dll.as<PIMAGE_DOS_HEADER>();

        auto ntHeaders = (PIMAGE_NT_HEADERS)((uintptr_t)dosHeader + dosHeader->e_lfanew);

        if (ntHeaders->Signature != IMAGE_NT_SIGNATURE) { return {}; }

        return ntHeaders->OptionalHeader.ImageBase;
    }


    optional<wstring> get_module_pathw(HMODULE module)
    {
        wchar_t filename[MAX_PATH]{ 0 };
        if (GetModuleFileNameW(module, filename, MAX_PATH) >= MAX_PATH) {
            return {};
        }

        return filename;
    }

    optional<string> get_module_path(HMODULE module)
    {
        char filename[MAX_PATH];
        if (GetModuleFileName(module, filename, MAX_PATH) >= MAX_PATH) {
            return {};
        }

        return filename;
    }

    optional<wstring> get_module_directoryw(HMODULE module)
    {
        wchar_t filename[MAX_PATH]{ 0 };
        if (GetModuleFileNameW(module, filename, MAX_PATH) >= MAX_PATH) {
            return {};
        }

        PathRemoveFileSpecW(filename);
        return filename;
    }

    optional<wstring> get_version_product_name(HMODULE module)
    {
        auto modulePath = get_module_path(module);

        if (modulePath.has_value()) {
           
            DWORD handle = 0;
            DWORD size = GetFileVersionInfoSize(modulePath->c_str(), &handle);
            if (size == 0) {
                return {};
            }

            std::vector<BYTE> buffer(size);
            if (!GetFileVersionInfo(modulePath->c_str(), handle, size, buffer.data())) {
                return {};
            }

            LPVOID productNameBuffer = nullptr;
            UINT productNameSize = 0;
            if (VerQueryValueW(buffer.data(), L"\\StringFileInfo\\040904B0\\ProductName", &productNameBuffer, &productNameSize)) {
                return std::wstring(static_cast<wchar_t*>(productNameBuffer), productNameSize);
            }

        }

        return {};
    }

    optional<string> get_module_name(HMODULE module) {
        CHAR moduleName[MAX_PATH];
        GetModuleBaseNameA(GetCurrentProcess(), module, moduleName, MAX_PATH);
        return moduleName;
    }

    HMODULE get_executable()
    {
        return GetModuleHandle(NULL);
    }

    HMODULE get_this_dll_handle()
    {
        MEMORY_BASIC_INFORMATION info;
        size_t len = VirtualQueryEx(GetCurrentProcess(), (void*)get_this_dll_handle, &info, sizeof(info));
        always_assert(len != sizeof(info), nullptr);
        return len ? (HMODULE)info.AllocationBase : NULL;
    }

}