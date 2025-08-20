#pragma once
#include <Utility/assertion/assert.hpp>

#include "mutex-win.hpp"

namespace NdGameSdk::corelib::system::platform {

	class MutexDesc : public ISdkRegenny<regenny::shared::corelib::system::platform::ndsys::MutexDesc> {
	public:
		using MutexType = regenny::shared::corelib::system::platform::ndsys::Mutex::Type;

		MutexDesc() {
			auto self = this->Get();
			self->m_type = MutexType(0);
			std::memset(self->m_name, 0, sizeof(self->m_name));
		}

		explicit MutexDesc(const char* name) {
			auto self = this->Get();
			self->m_type = MutexType(0);

			if (!name) {
				std::memset(self->m_name, 0, sizeof(self->m_name));
			}
			else {
				size_t len = 0;
				while (name[len] != '\0') ++len;
				size_t n = (len < 0x20) ? len : size_t(0x1F);

				std::memcpy(self->m_name, name, n);
				self->m_name[n] = '\0';
			}
		}

		MutexType GetType() const {
			return this->Get()->m_type;
		}

		const char* GetName() const {
			return this->Get()->m_name;
		}

		void SetType(MutexType type) {
			this->Get()->m_type = type;
		}
	};

	class Mutex : public ISdkRegenny<regenny::shared::corelib::system::platform::ndsys::Mutex> {
	public:
		using MutexType = regenny::shared::corelib::system::platform::ndsys::Mutex::Type;

		bool IsInitialized() const {
			return this->Get()->m_initialized;
		}

		bool Lock(int32_t timeoutMs = KInfiniteTimeoutMs) {
			always_assert(NdSystem_Mutex_Lock == nullptr, "Function pointer was not set!");
			return NdSystem_Mutex_Lock(this, timeoutMs);
		};

		bool TryLock() {
			always_assert(NdSystem_Mutex_TryLock == nullptr, "Function pointer was not set!");
			return NdSystem_Mutex_TryLock(this);
		};

		void Unlock() {
			always_assert(NdSystem_Mutex_Unlock == nullptr, "Function pointer was not set!");
			NdSystem_Mutex_Unlock(this);
		}

		inline static constexpr int32_t KInfiniteTimeoutMs = 0xffffffff;
	};

	struct ScopedLock {
		Mutex* m{}; bool locked{ false };
		explicit ScopedLock(Mutex* mu, int32_t timeoutMs = Mutex::KInfiniteTimeoutMs) : m(mu) { if (m && m->IsInitialized()) locked = m->Lock(); }
		~ScopedLock() { if (locked && m) m->Unlock(); }
	};

	static_assert(sizeof(Mutex) == 0x40, "Size of Mutex is not correct.");
}