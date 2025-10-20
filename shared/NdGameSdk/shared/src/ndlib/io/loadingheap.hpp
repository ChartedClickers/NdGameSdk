#pragma once
#include "NdGameSdk/sdk.hpp"

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/ndlib/io/LoadingHeap.hpp>
#elif defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/ndlib/io/LoadingHeap.hpp>
#endif


namespace NdGameSdk::ndlib::io {

	class LoadingHeap : public ISdkRegenny<regenny::shared::ndlib::io::LoadingHeap> {};

}