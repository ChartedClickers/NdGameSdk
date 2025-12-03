#pragma once
#include <Utility/assertion/assert.hpp>

#include "thread-win.hpp"

namespace NdGameSdk::corelib::system::platform {

	class alignas(16) Thread : public ISdkRegenny<regenny::shared::corelib::system::platform::ndsys::Thread> {
	public:
		Thread() = default;

		HANDLE* GetNativeThread() const {
			return reinterpret_cast<HANDLE*>(this->Get()->m_nativeThread);
		}

		uint32_t GetId() const {
			return this->Get()->m_id;
		}

		bool IsJoinable() const {
			return this->Get()->m_joinable != 0;
		}

		void SetJoinable(bool joinable) {
			this->Get()->m_joinable = joinable ? 1 : 0;
		}

		void Join() {
		#if defined(T2R) || defined(T1X)
			always_assert(NdSystem_Thread_Join == nullptr, "Function pointer was not set!");
			NdSystem_Thread_Join(this);
		#else
			if (IsJoinable()) {
				std::thread(reinterpret_cast<void(*)(void*)>(GetNativeThread()), nullptr).join();
			}
		#endif
		}
	};

	class ThreadDesc : public ISdkRegenny<regenny::shared::corelib::system::platform::ndsys::ThreadDesc> {
	public:
		ThreadDesc(uint64_t stackSize, uint32_t priority, uint32_t affinity, uint32_t flags, const char* name) {
			auto self = this->Get();
			self->m_stackSize = stackSize;
			self->m_priority = priority;
			self->m_affinity = affinity;
			self->m_flags = flags;
			std::strncpy(self->m_name, name, sizeof(self->m_name) - 1);
			self->m_name[sizeof(self->m_name) - 1] = '\0'; // Ensure null-termination
		}

		uint64_t GetStackSize() const {
			return this->Get()->m_stackSize;
		}

		uint32_t GetPriority() const {
			return this->Get()->m_priority;
		}

		uint32_t GetAffinity() const {
			return this->Get()->m_affinity;
		}

		uint32_t GetFlags() const {
			return this->Get()->m_flags;
		}

		const char* GetName() const {
			return this->Get()->m_name;
		}
	};

	static_assert(sizeof(Thread) == 0x10, "Size of Thread is not correct.");
	static_assert(sizeof(ThreadDesc) == 0x120, "Size of ThreadDesc is not correct.");
}