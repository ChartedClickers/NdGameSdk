#pragma once

#include <cstddef>
#include <cstdint>
#include <Windows.h>
#include <type_traits>
#include "helper.hpp"

namespace Utility::GlobalResolver {

    struct RipLea32Anchor {
        const wchar_t* pattern;
        size_t pattern_offset{ 0 };
        size_t disp_offset{ 3 }; // where the disp32 starts
        size_t instr_size{ 7 }; // e.g., 48 8D 0D ?? ?? ?? ?? / 48 8B 05 ?? ?? ?? ??
        const wchar_t* name{ L"" };
    };

    inline uint8_t* ResolveBase(HMODULE module, const RipLea32Anchor& a) {
        auto* base = reinterpret_cast<uint8_t*>(
            Utility::ReadLEA32(module, a.pattern, a.name, a.pattern_offset, a.disp_offset, a.instr_size));
        LOG_DEBUG(L"[GlobalResolver] ResolveBase name='%ls' module=0x%016llx base=0x%016llx pattern_offset=%zu disp_offset=%zu instr_size=%zu",
            a.name ? a.name : L"(null)",
            static_cast<unsigned long long>(reinterpret_cast<uintptr_t>(module)),
            static_cast<unsigned long long>(reinterpret_cast<uintptr_t>(base)),
            a.pattern_offset, a.disp_offset, a.instr_size);
        return base;
    }

    // RIP-rel helpers (nullptr on failure)
    template<typename T>
    inline T* RipSlotOrNull(HMODULE module, const wchar_t* pattern, const wchar_t* name,
        size_t pattern_offset = 0, size_t disp_off = 3, size_t instr_sz = 7) {
        auto addr = Utility::ReadLEA32(module, pattern, name, pattern_offset, disp_off, instr_sz);
        if (!addr) {
            LOG_ERROR(L"[GlobalResolver] RipSlot FAILED name='%ls'", name ? name : L"(null)");
            return nullptr;
        }
        auto* p = reinterpret_cast<T*>(addr);
        LOG_DEBUG(L"[GlobalResolver] RipSlot name='%ls' -> slot=0x%016llx sizeof(T)=%zu",
            name ? name : L"",
            static_cast<unsigned long long>(reinterpret_cast<uintptr_t>(p)),
            sizeof(T));
        return p;
    }

    template<typename T>
    inline T** RipPtrSlotOrNull(HMODULE module, const wchar_t* pattern, const wchar_t* name,
        size_t pattern_offset = 0, size_t disp_off = 3, size_t instr_sz = 7) {
        auto addr = Utility::ReadLEA32(module, pattern, name, pattern_offset, disp_off, instr_sz);
        if (!addr) {
            LOG_ERROR(L"[GlobalResolver] RipPtrSlot FAILED name='%ls'", name ? name : L"(null)");
            return nullptr;
        }
        auto** pp = reinterpret_cast<T**>(addr);
        LOG_DEBUG(L"[GlobalResolver] RipPtrSlot name='%ls' -> slot=0x%016llx sizeof(T*)=%zu",
            name ? name : L"",
            static_cast<unsigned long long>(reinterpret_cast<uintptr_t>(pp)),
            sizeof(T*));
        return pp;
    }

    // direct base+off helpers
    template<typename T>
    inline T* SlotAt(uint8_t* base, std::ptrdiff_t off = 0x0, const wchar_t* name = L"") {
        auto* addr = reinterpret_cast<T*>(base + off);
        LOG_DEBUG(L"[GlobalResolver] SlotAt name='%ls' base=0x%016llx off=0x%llx -> addr=0x%016llx sizeof(T)=%zu",
            name ? name : L"",
            static_cast<unsigned long long>(reinterpret_cast<uintptr_t>(base)),
            static_cast<unsigned long long>(static_cast<uintptr_t>(off)),
            static_cast<unsigned long long>(reinterpret_cast<uintptr_t>(addr)), sizeof(T));
        return addr;
    }

    template<typename T>
    inline T** PtrSlotAt(uint8_t* base, std::ptrdiff_t off = 0x0, const wchar_t* name = L"") {
        auto** slot = reinterpret_cast<T**>(base + off);
        LOG_DEBUG(L"[GlobalResolver] PtrSlotAt name='%ls' base=0x%016llx off=0x%llx -> slot=0x%016llx sizeof(T*)=%zu",
            name ? name : L"",
            static_cast<unsigned long long>(reinterpret_cast<uintptr_t>(base)),
            static_cast<unsigned long long>(static_cast<uintptr_t>(off)),
            static_cast<unsigned long long>(reinterpret_cast<uintptr_t>(slot)), sizeof(T*));
        return slot;
    }

    // derive from a known neighbor
    template<typename T>
    inline T* Derive(void* basePtr, std::ptrdiff_t off = 0x0, const wchar_t* name = L"") {
        auto* addr = reinterpret_cast<T*>(reinterpret_cast<uint8_t*>(basePtr) + off);
        LOG_DEBUG(L"[GlobalResolver] Derive name='%ls' basePtr=0x%016llx off=0x%llx -> addr=0x%016llx sizeof(T)=%zu",
            name ? name : L"",
            static_cast<unsigned long long>(reinterpret_cast<uintptr_t>(basePtr)),
            static_cast<unsigned long long>(static_cast<uintptr_t>(off)),
            static_cast<unsigned long long>(reinterpret_cast<uintptr_t>(addr)), sizeof(T));
        return addr;
    }

    template<typename T>
    inline T** DerivePtr(void* basePtr, std::ptrdiff_t off = 0x0, const wchar_t* name = L"") {
        auto** slot = reinterpret_cast<T**>(reinterpret_cast<uint8_t*>(basePtr) + off);
        LOG_DEBUG(L"[GlobalResolver] DerivePtr name='%ls' basePtr=0x%016llx off=0x%llx -> slot=0x%016llx sizeof(T*)=%zu",
            name ? name : L"",
            static_cast<unsigned long long>(reinterpret_cast<uintptr_t>(basePtr)),
            static_cast<unsigned long long>(static_cast<uintptr_t>(off)),
            static_cast<unsigned long long>(reinterpret_cast<uintptr_t>(slot)), sizeof(T*));
        return slot;
    }
}
