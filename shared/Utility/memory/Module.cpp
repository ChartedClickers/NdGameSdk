#include "Module.hpp"
#include "../assertion/assert.hpp"

#include <shlwapi.h>
#include <wincrypt.h>
#include <Psapi.h>
#include <unordered_map>
#include <mutex>

#pragma comment(lib,"shlwapi.lib")
#pragma comment(lib,"Version.lib")
#pragma comment(lib, "Crypt32.lib")
#define CALG_SHA256 (ALG_CLASS_HASH | ALG_TYPE_ANY | ALG_SID_SHA_256)  

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

    optional<std::string> get_module_hash(HMODULE module)
    {
        static std::unordered_map<HMODULE, std::string> hashCache;
        static std::mutex cacheMutex;

        if (module == nullptr) { return {}; }
        {
            std::lock_guard<std::mutex> lock(cacheMutex);
            auto it = hashCache.find(module);
            if (it != hashCache.end()) {
                return it->second;
            }
        }

        auto modulePath = get_module_path(module);
        if (!modulePath.has_value()) { return {}; }

        HANDLE file = CreateFileA(modulePath->c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
        if (file == INVALID_HANDLE_VALUE) { return {}; }

        DWORD fileSize = GetFileSize(file, nullptr);
        if (fileSize == INVALID_FILE_SIZE) {
            CloseHandle(file);
            return {};
        }

        std::vector<BYTE> fileData(fileSize);
        DWORD bytesRead = 0;
        if (!ReadFile(file, fileData.data(), fileSize, &bytesRead, nullptr) || bytesRead != fileSize) {
            CloseHandle(file);
            return {};
        }

        CloseHandle(file);

        HCRYPTPROV hProv = 0;
        HCRYPTHASH hHash = 0;
        if (!CryptAcquireContext(&hProv, nullptr, nullptr, PROV_RSA_AES, CRYPT_VERIFYCONTEXT)) {
            return {};
        }

        if (!CryptCreateHash(hProv, CALG_SHA256, 0, 0, &hHash)) {
            CryptReleaseContext(hProv, 0);
            return {};
        }

        if (!CryptHashData(hHash, fileData.data(), fileSize, 0)) {
            CryptDestroyHash(hHash);
            CryptReleaseContext(hProv, 0);
            return {};
        }

        DWORD hashSize = 0;
        DWORD hashSizeLen = sizeof(DWORD);

        if (!CryptGetHashParam(hHash, HP_HASHSIZE, (BYTE*)&hashSize, &hashSizeLen, 0)) {
            CryptDestroyHash(hHash);
            CryptReleaseContext(hProv, 0);
            return {};
        }

        std::vector<BYTE> hash(hashSize);
        if (!CryptGetHashParam(hHash, HP_HASHVAL, hash.data(), &hashSize, 0)) {
            CryptDestroyHash(hHash);
            CryptReleaseContext(hProv, 0);
            return {};
        }

        CryptDestroyHash(hHash);
        CryptReleaseContext(hProv, 0);

        DWORD base64Size = 0;
        if (!CryptBinaryToStringA(hash.data(), hashSize, CRYPT_STRING_BASE64 | CRYPT_STRING_NOCRLF, nullptr, &base64Size)) {
            return {};
        }

        std::string base64Hash(base64Size, '\0');
        if (!CryptBinaryToStringA(hash.data(), hashSize, CRYPT_STRING_BASE64 | CRYPT_STRING_NOCRLF, base64Hash.data(), &base64Size)) {
            return {};
        }

        std::lock_guard<std::mutex> lock(cacheMutex);
        hashCache[module] = base64Hash;

        return base64Hash;
    }

    optional<string> get_module_hash_from_memory(HMODULE module) {
        if (!module) return {};

        auto optSize = get_module_size(module);
        if (!optSize.has_value()) return {};
        size_t imageSize = *optSize;

        auto base = reinterpret_cast<const BYTE*>(module);

        HCRYPTPROV hProv = 0;
        if (!CryptAcquireContext(&hProv, nullptr, nullptr, PROV_RSA_AES, CRYPT_VERIFYCONTEXT))
            return {};

        HCRYPTHASH hHash = 0;
        if (!CryptCreateHash(hProv, CALG_SHA_256, 0, 0, &hHash)) {
            CryptReleaseContext(hProv, 0);
            return {};
        }

        if (!CryptHashData(hHash, base, static_cast<DWORD>(imageSize), 0)) {
            CryptDestroyHash(hHash);
            CryptReleaseContext(hProv, 0);
            return {};
        }

        DWORD hashSize = 0, sizeLen = sizeof(hashSize);
        if (!CryptGetHashParam(hHash, HP_HASHSIZE, reinterpret_cast<BYTE*>(&hashSize), &sizeLen, 0)) {
            CryptDestroyHash(hHash);
            CryptReleaseContext(hProv, 0);
            return {};
        }

        std::vector<BYTE> hash(hashSize);
        if (!CryptGetHashParam(hHash, HP_HASHVAL, hash.data(), &hashSize, 0)) {
            CryptDestroyHash(hHash);
            CryptReleaseContext(hProv, 0);
            return {};
        }

        DWORD b64Len = 0;
        if (!CryptBinaryToStringA(hash.data(), hashSize,
            CRYPT_STRING_BASE64 | CRYPT_STRING_NOCRLF,
            nullptr, &b64Len)) {
            CryptDestroyHash(hHash);
            CryptReleaseContext(hProv, 0);
            return {};
        }

        std::string out(b64Len, '\0');
        if (!CryptBinaryToStringA(hash.data(), hashSize,
            CRYPT_STRING_BASE64 | CRYPT_STRING_NOCRLF,
            out.data(), &b64Len)) {
            CryptDestroyHash(hHash);
            CryptReleaseContext(hProv, 0);
            return {};
        }

        CryptDestroyHash(hHash);
        CryptReleaseContext(hProv, 0);
        return out;
    }

}