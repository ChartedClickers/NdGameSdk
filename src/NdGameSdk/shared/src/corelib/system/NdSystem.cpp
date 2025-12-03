#include "NdSystem.hpp"
#include "./NdGameSdk/shared/sharedpatterns.hpp"

#include "../util/error.hpp"

#include <Utility/helper.hpp>

namespace NdGameSdk::corelib::system {

	NdSystem::NdSystem() : ISdkComponent(TOSTRING(NdSystem)) {}

	void NdSystem::Initialize() {
		static std::once_flag Initialized;

		std::call_once(Initialized, [this] {

			spdlog::info("Initializing {} patterns...", GetName());

			Patterns::SdkPattern findpattern{};

			auto module = Utility::memory::get_executable();

			findpattern = Patterns::NdSystem_CreateThread;
			platform::NdSystem_CreateThread = (platform::NdSystem_CreateThread_ptr)Utility::FindAndPrintPattern(module, 
				findpattern.pattern, wstr(Patterns::NdSystem_CreateThread), findpattern.offset);

			findpattern = Patterns::NdSystem_ReleaseThreadHandle;
			platform::NdSystem_ReleaseThreadHandle = (platform::NdSystem_ReleaseThreadHandle_ptr)Utility::FindAndPrintPattern(module, 
				findpattern.pattern, wstr(Patterns::NdSystem_ReleaseThreadHandle), findpattern.offset);

			findpattern = Patterns::NdSystem_Thread_Join;
			platform::NdSystem_Thread_Join = (platform::NdSystem_Thread_Join_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::NdSystem_Thread_Join), findpattern.offset);

			findpattern = Patterns::NdSystem_CreateMutex;
			platform::NdSystem_CreateMutex = (platform::NdSystem_CreateMutex_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::NdSystem_CreateMutex), findpattern.offset);

			findpattern = Patterns::NdSystem_Mutex_Lock;
			platform::NdSystem_Mutex_Lock = (platform::NdSystem_Mutex_Lock_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::NdSystem_Mutex_Lock), findpattern.offset);

			findpattern = Patterns::NdSystem_Mutex_TryLock;
			platform::NdSystem_Mutex_TryLock = (platform::NdSystem_Mutex_TryLock_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::NdSystem_Mutex_TryLock), findpattern.offset);

			findpattern = Patterns::NdSystem_Mutex_Unlock;
			platform::NdSystem_Mutex_Unlock = (platform::NdSystem_Mutex_Unlock_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::NdSystem_Mutex_Unlock), findpattern.offset);

			findpattern = Patterns::NdSystem_Err_Describe;
			util::Err::NdSystem_Err_Describe = (util::Err::NdSystem_Err_Describe_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::NdSystem_Err_Describe), findpattern.offset);

			if (!platform::NdSystem_CreateThread ||
				!platform::NdSystem_ReleaseThreadHandle ||
				!platform::NdSystem_Thread_Join ||
				!platform::NdSystem_CreateMutex ||
				!platform::NdSystem_Mutex_Lock ||
				!platform::NdSystem_Mutex_TryLock ||
				!platform::NdSystem_Mutex_Unlock ||
				!util::Err::NdSystem_Err_Describe) {
				throw SdkComponentEx{ std::format("Failed to find {}:: NdSys functions!", GetName()), SdkComponentEx::ErrorCode::PatternFailed };
			}


		});
	}

	void NdSystem::CreateMutex(platform::MutexDesc* pMutexDesc, platform::Mutex* pMutexData) {
		always_assert(platform::NdSystem_CreateMutex == nullptr, "Function pointer was not set!");
		platform::NdSystem_CreateMutex(pMutexDesc, pMutexData);
		spdlog::debug("Created mutex: {}", pMutexDesc->GetName());
	}

	bool NdSystem::ReleaseThreadHandle(platform::Thread* pThread) {
		always_assert(platform::NdSystem_ReleaseThreadHandle == nullptr, "Function pointer was not set!");
		return platform::NdSystem_ReleaseThreadHandle(pThread);
	}


}