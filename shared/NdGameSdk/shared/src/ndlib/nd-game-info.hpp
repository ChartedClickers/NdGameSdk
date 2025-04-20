#pragma once
#include "NdGameSdk/components/SdkRegenny.hpp"

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/ndlib/NdGameInfo.hpp>
#elif defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/ndlib/NdGameInfo.hpp>
#endif

namespace NdGameSdk::ndlib {

	class NdGameInfo : public ISdkRegenny<regenny::shared::ndlib::NdGameInfo> {};

#if defined(T1X)
	static_assert(sizeof(NdGameInfo) == 0x45c0, "Size of NdGameInfo is not correct.");
#elif defined(T2R)
	static_assert(sizeof(NdGameInfo) == 0x4660, "Size of NdGameInfo is not correct.");
#endif
}