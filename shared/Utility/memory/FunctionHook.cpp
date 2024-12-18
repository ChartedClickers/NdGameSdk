#include "FunctionHook.hpp"

#include <stdexcept>
#include <spdlog/spdlog.h>

namespace Utility::memory
{
	ProtectionOverride::ProtectionOverride(void* address, size_t size, uint32_t protection) :
		m_address{ address },
		m_size{ size }
	{
		if (!VirtualProtect(address, size, protection, (DWORD*)&m_old)) {
			SPDLOG_ERROR("PointerHook: VirtualProtect failed ({:x})", (uintptr_t)address);
			throw std::runtime_error("VirtualProtect failed");
		}
	}

	ProtectionOverride::~ProtectionOverride()
	{
		VirtualProtect(m_address, m_size, m_old, (DWORD*)&m_old);
	}


	FunctionHook::FunctionHook(Address target, HookFn destination_fn, wstring name)
		: m_target{ target }, m_destination{ (uintptr_t)destination_fn }, m_name{ name }
	{
		SPDLOG_INFO("Attempting to hook {:p}->{:p}", target.get(), destination_fn);
	}

	FunctionHook::~FunctionHook() {}

	bool FunctionHook::create()
	{
		std::unique_lock _{ m_initialization_mutex };

		if (m_target == 0 || m_destination == 0) {
			SPDLOG_ERROR("FunctionHook not initialized");
			return false;
		}

		if (is_valid_unsafe()) {
			return true; // already hooked
		}

        try {
            m_inline_hook = InlineHook::create(m_target, m_destination);
            if (!m_inline_hook) {
                std::string error = "";
                switch (m_inline_hook.error().type) {
                case safetyhook::InlineHook::Error::BAD_ALLOCATION:
                case safetyhook::InlineHook::Error::FAILED_TO_DECODE_INSTRUCTION:
                case safetyhook::InlineHook::Error::SHORT_JUMP_IN_TRAMPOLINE:
                case safetyhook::InlineHook::Error::IP_RELATIVE_INSTRUCTION_OUT_OF_RANGE:
                case safetyhook::InlineHook::Error::UNSUPPORTED_INSTRUCTION_IN_TRAMPOLINE:
                case safetyhook::InlineHook::Error::FAILED_TO_UNPROTECT:
                case safetyhook::InlineHook::Error::NOT_ENOUGH_SPACE:
                    error = InlineHookError[m_inline_hook.error().type];
                    break;
                default:
                    error = format("unknown error {}", (int32_t)m_inline_hook.error().type);
                    break;
                };

                SPDLOG_ERROR("Failed to hook {:x}: {}", m_target, error);
                return false;
            }
        }
        catch (const std::exception& e) {
            SPDLOG_ERROR("Failed to hook {:x}: {}", m_target, e.what());
            return false;
        }
        catch (...) {
            SPDLOG_ERROR("Failed to hook {:x}: unknown exception", m_target);
            return false;
        }

        if (m_inline_hook) {
            SPDLOG_INFO("Hooked {:x}->{:x}", m_target, m_destination);
        }
        else {
            SPDLOG_ERROR("Failed to hook {:x}", m_target);
            return false;
        }

        return true;
	}
}