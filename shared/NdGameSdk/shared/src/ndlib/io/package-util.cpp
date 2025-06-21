#include "package-util.hpp"

namespace NdGameSdk::ndlib::io {
#if defined(T2R)

	INIT_FUNCTION_PTR(PackageMgr_GetPakHdrPageEntry);
	INIT_FUNCTION_PTR(PackageMgr_ResolvePagePtr);

#endif
}