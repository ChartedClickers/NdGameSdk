#pragma once
#include "NdGameSdk/components/SdkRegenny.hpp"

#if defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/ndlib/NdGameInfo.hpp>
#endif

namespace NdGameSdk::ndlib {

	class NdGameInfo : public ISdkRegenny<regenny::shared::ndlib::NdGameInfo> {};
	static_assert(sizeof(NdGameInfo) == 0x45c0, "Size of NdGameInfo is not correct.");
}