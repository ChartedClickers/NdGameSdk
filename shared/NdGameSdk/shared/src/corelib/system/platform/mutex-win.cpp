#include "mutex-win.hpp"

namespace NdGameSdk::corelib::system::platform {
	INIT_FUNCTION_PTR(NdSystem_Mutex_Lock);
	INIT_FUNCTION_PTR(NdSystem_Mutex_TryLock);
	INIT_FUNCTION_PTR(NdSystem_Mutex_Unlock);
}
