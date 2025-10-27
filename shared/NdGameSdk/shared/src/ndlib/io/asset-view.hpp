#pragma once 

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/ndlib/io/AssetType.hpp>
#elif defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/ndlib/io/AssetType.hpp>
#endif

namespace NdGameSdk::ndlib::io {

	using AssetType = regenny::shared::ndlib::io::AssetType;

}