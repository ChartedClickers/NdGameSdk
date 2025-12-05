#pragma once
#include "NdGameSdk/sdk.hpp"
#include "package.hpp"

#include <helper.hpp>
#include <function_ptr.hpp>

namespace NdGameSdk::ndlib::io {
#if defined(T2R)

	class PackageMgrInternal;

	Package::PakPageEntry* GetPakHdrPageEntry(Package::PakHeader* pPakHdr, uint32_t* arg2, uint32_t index);
	Package::ResPage* ResolvePakPage(PackageMgrInternal* pPackageMgr, Package* pPackage, uint32_t LoginTableIdx);

	TYPEDEF_EXTERN_FUNCTION_PTR(Package::PakPageEntry*, PackageMgr_GetPakHdrPageEntry, Package::PakHeader* pPakHdr, uint32_t* arg2, uint32_t index);
	TYPEDEF_EXTERN_FUNCTION_PTR(Package::ResPage*, PackageMgr_ResolvePakPagePtr, PackageMgrInternal* pPackageMgr, Package* pPackage, uint32_t LoginTableIdx);
#endif
}
