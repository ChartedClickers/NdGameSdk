#pragma once

#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/components/SdkComponent.hpp"

#include "platform/thread.hpp"
#include "platform/mutex.hpp"

namespace NdGameSdk::corelib::system {

	class NdSystem : public ISdkComponent {
	public:
		NdSystem();
		
		template <typename T = void*>
		void CreateThread(
			platform::Thread* pThread,
			platform::ThreadDesc* pThreadDesc,
			void* pUserParam,
			unsigned(__stdcall* pEntryPoint)(T*)) {
			always_assert(platform::NdSystem_CreateThread == nullptr, "Function pointer was not set!");
			platform::NdSystem_CreateThread(pThread, pThreadDesc, pEntryPoint, pUserParam);
		}

		void CreateMutex(platform::MutexDesc* pMutexDesc, platform::Mutex* pMutexData);

		bool ReleaseThreadHandle(platform::Thread* pThread);
	private:
		void Initialize() override;
	};

}