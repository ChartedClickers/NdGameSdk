#include "package-util.hpp"

namespace NdGameSdk::ndlib::io {
#if defined(T2R)

	Package::PakPageEntry* GetPakHdrPageEntry(Package::PakHeader* pPakHdr, uint32_t* arg2, uint32_t index) {
		always_assert(PackageMgr_GetPakHdrPageEntry == nullptr, "Function pointer was not set!");
		return PackageMgr_GetPakHdrPageEntry(pPakHdr, arg2, index);
	}

	Package::ResPage* ResolvePakPage(PackageMgr* pPackageMgr, Package* pPackage, uint32_t LoginTableIdx) {
		always_assert(PackageMgr_ResolvePakPagePtr == nullptr, "Function pointer was not set!");
		return PackageMgr_ResolvePakPagePtr(pPackageMgr, pPackage, LoginTableIdx);
	}

	INIT_FUNCTION_PTR(PackageMgr_GetPakHdrPageEntry);
	INIT_FUNCTION_PTR(PackageMgr_ResolvePakPagePtr);

#endif
}