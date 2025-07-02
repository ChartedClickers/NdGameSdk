#include "NdSystem.hpp"
#include "./NdGameSdk/shared/sharedpatterns.hpp"

#include <Utility/helper.hpp>

namespace NdGameSdk::corelib::system {

	NdSystem::NdSystem() : ISdkComponent(TOSTRING(NdSystem)) {}

	void NdSystem::Initialize() {
		static std::once_flag Initialized;

		std::call_once(Initialized, [this] {

			spdlog::info("Initializing {} patterns...", GetName());

			Patterns::SdkPattern findpattern{};

			findpattern = Patterns::NdSystem_CreateThread;
			platform::NdSystem_CreateThread = (platform::NdSystem_CreateThread_ptr)Utility::FindAndPrintPattern(
				Utility::memory::get_executable(), findpattern.pattern, wstr(Patterns::NdSystem_CreateThread), findpattern.offset);

			findpattern = Patterns::NdSystem_ReleaseThreadHandle;
			platform::NdSystem_ReleaseThreadHandle = (platform::NdSystem_ReleaseThreadHandle_ptr)Utility::FindAndPrintPattern(
				Utility::memory::get_executable(), findpattern.pattern, wstr(Patterns::NdSystem_ReleaseThreadHandle), findpattern.offset);

			findpattern = Patterns::NdSystem_Thread_Join;
			platform::NdSystem_Thread_Join = (platform::NdSystem_Thread_Join_ptr)Utility::FindAndPrintPattern(
				Utility::memory::get_executable(), findpattern.pattern, wstr(Patterns::NdSystem_Thread_Join), findpattern.offset);

			findpattern = Patterns::NdSystem_Mutex_Lock;
			platform::NdSystem_Mutex_Lock = (platform::NdSystem_Mutex_Lock_ptr)Utility::FindAndPrintPattern(
				Utility::memory::get_executable(), findpattern.pattern, wstr(Patterns::NdSystem_Mutex_Lock), findpattern.offset);

			findpattern = Patterns::NdSystem_Mutex_TryLock;
			platform::NdSystem_Mutex_TryLock = (platform::NdSystem_Mutex_TryLock_ptr)Utility::FindAndPrintPattern(
				Utility::memory::get_executable(), findpattern.pattern, wstr(Patterns::NdSystem_Mutex_TryLock), findpattern.offset);

			findpattern = Patterns::NdSystem_Mutex_Unlock;
			platform::NdSystem_Mutex_Unlock = (platform::NdSystem_Mutex_Unlock_ptr)Utility::FindAndPrintPattern(
				Utility::memory::get_executable(), findpattern.pattern, wstr(Patterns::NdSystem_Mutex_Unlock), findpattern.offset);

			if (!platform::NdSystem_CreateThread ||
				!platform::NdSystem_ReleaseThreadHandle ||
				!platform::NdSystem_Thread_Join ||
				!platform::NdSystem_Mutex_Lock ||
				!platform::NdSystem_Mutex_TryLock ||
				!platform::NdSystem_Mutex_Unlock) {
				throw SdkComponentEx{ std::format("Failed to find {}:: NdSys functions!", GetName()), SdkComponentEx::ErrorCode::PatternFailed };
			}

		});
	}

	bool NdSystem::ReleaseThreadHandle(platform::Thread* pThread) {
		always_assert(platform::NdSystem_ReleaseThreadHandle == nullptr, "Function pointer was not set!");
		return platform::NdSystem_ReleaseThreadHandle(pThread);
	}


}