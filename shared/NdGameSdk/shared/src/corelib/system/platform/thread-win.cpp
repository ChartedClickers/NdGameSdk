#include "thread-win.hpp"

namespace NdGameSdk::corelib::system::platform {
	INIT_FUNCTION_PTR(NdSystem_CreateThread);
	INIT_FUNCTION_PTR(NdSystem_ReleaseThreadHandle);
	INIT_FUNCTION_PTR(NdSystem_Thread_Join);
}
