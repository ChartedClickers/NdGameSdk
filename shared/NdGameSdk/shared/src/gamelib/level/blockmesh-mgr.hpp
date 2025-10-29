#pragma once

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/gamelib/level/BlockMeshMgr.hpp>
#endif

namespace NdGameSdk::gamelib::level {
#if defined(T2R)
	class BlockMeshMgr : public ISdkRegenny<regenny::shared::gamelib::level::BlockmeshMgr> {};

#endif
}