#pragma once
#include "NdGameSdk/components/SdkRegenny.hpp"

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/ndlib/io/PrefetchMgr.hpp>
#elif defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/ndlib/io/PrefetchMgr.hpp>
#endif

namespace NdGameSdk::ndlib::io {

	class PrefetchMgr : public ISdkRegenny<regenny::shared::ndlib::io::PrefetchMgr> {};

#if defined(T2R) || defined(T1X)
	static_assert(sizeof(PrefetchMgr) == 0x9e0, "Size of PrefetchMgr is not correct.");
#endif
}