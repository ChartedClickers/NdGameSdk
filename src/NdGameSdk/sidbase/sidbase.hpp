/******************************************************************************/
/*
  Author  - icemesh
*/
/******************************************************************************/
#pragma once

#include "../sdk.hpp"
#include "../sdkstringid.hpp"

#include <cinttypes>
#include <spdlog/spdlog.h>

namespace NdGameSdk::Sidbase {

#if defined(Big4R)
	typedef StringId32 StringId;
#else
	typedef StringId64 StringId;
#endif

	extern bool g_bSidbaseAvailable;

	bool InitSidbase(const char* sid_path = "sidbase.bin");
	void ShutdownSidbase();
	NdGameSdk_API std::string StringIdToStringInternal(StringId sid);
}
