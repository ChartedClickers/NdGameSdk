#pragma once
#include "NdGameSdk/components/SdkRegenny.hpp"

#if defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/ndlib/NdFrameState.hpp>
#endif

namespace NdGameSdk::ndlib {

#if defined(T1X)
	class NdFrameState : public ISdkRegenny<regenny::shared::ndlib::NdFrameState> {};
	static_assert(sizeof(NdFrameState) == 0x288a0, "Size of NdFrameState is not correct.");
#endif
}