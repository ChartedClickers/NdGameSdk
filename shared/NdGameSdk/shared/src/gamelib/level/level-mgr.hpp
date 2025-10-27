#pragma once

#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/components/SdkComponent.hpp"

#if defined(T2R)
#ifdef interface
#pragma push_macro("interface")
#undef interface
#define NDGSDK_LEVELMGR_RESTORE_INTERFACE 1
#endif
#include <NdGameSdk/regenny/t2r/shared/gamelib/level/LevelMgr.hpp>
#ifdef NDGSDK_LEVELMGR_RESTORE_INTERFACE
#pragma pop_macro("interface")
#undef NDGSDK_LEVELMGR_RESTORE_INTERFACE
#endif
#endif

#include "level.hpp"
#include "want-load.hpp"

namespace NdGameSdk::gamelib::level {
#if defined (T2R)

	class LevelMgr : public ISdkRegenny<regenny::shared::gamelib::level::LevelMgr> {
	public:
		using LevelLoadedCallback = NdGameSdk::gamelib::level::LevelLoadedCallback;
	};


#endif
}
