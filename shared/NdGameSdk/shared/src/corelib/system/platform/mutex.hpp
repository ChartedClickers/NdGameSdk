#pragma once
#include <Utility/assertion/assert.hpp>

#include "mutex-win.hpp"

namespace NdGameSdk::corelib::system::platform {

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

	static_assert(sizeof(Mutex) == 0x40, "Size of Mutex is not correct.");
}