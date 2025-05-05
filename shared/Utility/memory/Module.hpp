#pragma once

#include <optional>
#include <string>
#include <vector>
#include <Windows.h>

#include "Address.hpp"

using namespace std;

namespace Utility::memory
{
    optional<size_t> get_module_size(HMODULE module);
    optional<size_t> get_module_size(const string& module);

    optional<HMODULE> get_module_within(Address address);
    optional<uintptr_t> get_dll_imagebase(Address dll);

    optional<wstring> get_module_pathw(HMODULE module = nullptr);
    optional<string> get_module_path(HMODULE module = nullptr);
    optional<wstring> get_module_directoryw(HMODULE module = nullptr);

    optional<wstring> get_version_product_name(HMODULE module = nullptr);

    optional<string> get_module_name(HMODULE module);
    
    optional<std::string> get_module_hash(HMODULE module);
    optional<string> get_module_hash_from_memory(HMODULE module);

    HMODULE get_executable();
    HMODULE get_this_dll_handle();
}