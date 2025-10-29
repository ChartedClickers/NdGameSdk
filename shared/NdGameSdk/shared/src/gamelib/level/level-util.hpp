#pragma once

#include "NdGameSdk/sdk.hpp"

#include <NdGameSdk/shared/src/ndlib/io/asset-view.hpp>

#include <Utility/function_ptr.hpp>
#include <Utility/assertion/assert.hpp>

namespace NdGameSdk::gamelib::level {
#if defined(T2R)

	namespace LevelUtil {

		bool LoadActorByName(char const* pActorName, ndlib::io::AssetType pAssetType, bool sync);
		void UnloadActor(char const* pActorName);
		void ReloadLevel(char const* pLevelName);
		void CacheFilenames(char const* pFileName);
		void LoadLevelSet(char const* levelSetName);

		TYPEDEF_EXTERN_FUNCTION_PTR(bool, DataLoading_LevelUtil_LoadActorByName, char const* pActorName, ndlib::io::AssetType pAssetType, bool sync);
		TYPEDEF_EXTERN_FUNCTION_PTR(void, DataLoading_LevelUtil_UnloadActor, char const* pActorName);
		TYPEDEF_EXTERN_FUNCTION_PTR(void, DataLoading_LevelUtil_ReloadLevel, char const* pLevelName);
		TYPEDEF_EXTERN_FUNCTION_PTR(void, DataLoading_LevelUtil_CacheFilenames, char const* pFileName);
		TYPEDEF_EXTERN_FUNCTION_PTR(void, DataLoading_LevelUtil_LoadLevelSet, char const* levelSetName);
	}

#endif
}