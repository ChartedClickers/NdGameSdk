#pragma once

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/corelib/system/platform/ndsys.hpp>
#elif defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/corelib/system/platform/ndsys.hpp>
#endif

#include <Utility/helper.hpp>
#include <Utility/function_ptr.hpp>

namespace NdGameSdk::corelib::system::platform {

	class Thread;
	class ThreadDesc;

	TYPEDEF_EXTERN_FUNCTION_PTR(void, NdSystem_CreateThread, Thread* pThread, ThreadDesc* pThreadDesc, void* Function, ...);
	TYPEDEF_EXTERN_FUNCTION_PTR(bool, NdSystem_ReleaseThreadHandle, Thread* pThread);
	TYPEDEF_EXTERN_FUNCTION_PTR(uint32_t, NdSystem_Thread_Join, Thread* pThread);
}