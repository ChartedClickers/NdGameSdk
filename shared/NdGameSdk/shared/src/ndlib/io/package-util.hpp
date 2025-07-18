#pragma once
#include "NdGameSdk/sdk.hpp"
#include "package.hpp"

#include <Utility/helper.hpp>
#include <Utility/function_ptr.hpp>

namespace NdGameSdk::ndlib::io {
#if defined(T2R)

	class PackageMgr;

	Package::PakPageEntry* GetPakHdrPageEntry(Package::PakHeader* pPakHdr, uint32_t* arg2, uint32_t index);
	Package::ResPage* ResolvePakPage(PackageMgr* pPackageMgr, Package* pPackage, uint32_t LoginTableIdx);

	TYPEDEF_EXTERN_FUNCTION_PTR(Package::PakPageEntry*, PackageMgr_GetPakHdrPageEntry, Package::PakHeader* pPakHdr, uint32_t* arg2, uint32_t index);
	TYPEDEF_EXTERN_FUNCTION_PTR(Package::ResPage*, PackageMgr_ResolvePakPagePtr, PackageMgr* pPackageMgr, Package* pPackage, uint32_t LoginTableIdx);
#endif
}