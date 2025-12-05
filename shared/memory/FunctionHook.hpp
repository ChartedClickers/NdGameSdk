#pragma once

#include <memory>
#include <vector>
#include <optional>
#include <string>
#include <array>
#include <Windows.h>
#include <shared_mutex>

#include <safetyhook.hpp>
#include <safetyhook/inline_hook.hpp>

#include "Address.hpp"

using namespace std;
using namespace safetyhook;

namespace Utility::memory
{
	using HookFn = void*;
	static const char* InlineHookError[] =  { 
		"bad allocation",
		"failed to decode instruction",
		"short jump in trampoline",
		"IP relative instruction out of range",
		"unsupported instruction in trampoline",
		"failed to unprotect memory",
		"not enough space"
	};

	struct ProtectionOverride {
		ProtectionOverride(void* address, size_t size, uint32_t protection);
		virtual ~ProtectionOverride();

		void* m_address{};
		size_t m_size{};
		uint32_t m_old{};
	};

	class FunctionHook {

	public:
		using Ptr = unique_ptr<FunctionHook>;
		FunctionHook() = delete;
		FunctionHook(const FunctionHook& other) = delete;
		FunctionHook(FunctionHook&& other) = delete;
		FunctionHook(Address target, HookFn destination_fn, wstring name);
		virtual ~FunctionHook();

		FunctionHook& operator=(const FunctionHook& other) = delete;
		FunctionHook& operator=(FunctionHook&& other) = delete;

		virtual bool create();

		wstring GetName() const noexcept { return m_name; }
		uint8_t* GetTarget() const noexcept { return (uint8_t*)m_target; }
		uint8_t* GetDestination() const noexcept { return (uint8_t*)m_destination; }

		auto get_original() const {
			std::shared_lock _{ m_initialization_mutex };
			return m_inline_hook->trampoline().address();
		}

		template <typename T>
		T* get_original() const {
			std::shared_lock _{ m_initialization_mutex };
			return m_inline_hook->original<T*>();
		}

		auto is_valid() const {
			std::shared_lock _{ m_initialization_mutex };
			return is_valid_unsafe();
		}

	protected:
		bool is_valid_unsafe() const {
			return m_inline_hook && m_inline_hook->operator bool();
		}

		mutable shared_mutex m_initialization_mutex{};
		expected<InlineHook, InlineHook::Error> m_inline_hook;

		wstring m_name{};
		uintptr_t m_target{};
		uintptr_t m_destination{};
	};
}
