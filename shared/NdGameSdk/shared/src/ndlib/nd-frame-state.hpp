#pragma once
#include "NdGameSdk/components/SdkRegenny.hpp"

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/ndlib/NdFrameState.hpp>
#elif defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/ndlib/NdFrameState.hpp>
#endif

namespace NdGameSdk::ndlib {


	class NdFrameState : public ISdkRegenny<regenny::shared::ndlib::NdFrameState> {};

#if defined(T2R)
	static_assert(sizeof(NdFrameState) == 0x29518, "Size of NdFrameState is not correct.");
#elif defined(T1X)
	static_assert(sizeof(NdFrameState) == 0x288a0, "Size of NdFrameState is not correct.");
#endif

}