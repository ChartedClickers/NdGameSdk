#pragma once

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/corelib/system/platform/ndsys.hpp>
#elif defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/corelib/system/platform/ndsys.hpp>
#endif

#include <Utility/helper.hpp>
#include <Utility/function_ptr.hpp>

namespace NdGameSdk::corelib::system::platform {

	class Mutex;

	TYPEDEF_EXTERN_FUNCTION_PTR(bool, NdSystem_Mutex_Lock, Mutex* pMutexData, int32_t timeoutMs);
	TYPEDEF_EXTERN_FUNCTION_PTR(bool, NdSystem_Mutex_TryLock, Mutex* pMutexData);
	TYPEDEF_EXTERN_FUNCTION_PTR(void, NdSystem_Mutex_Unlock, Mutex* pMutexData);

}