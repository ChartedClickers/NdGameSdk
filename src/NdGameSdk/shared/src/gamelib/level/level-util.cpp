#include "level-util.hpp"

namespace NdGameSdk::gamelib::level {
#if defined(T2R)

	namespace LevelUtil {

		bool LoadActorByName(char const* pActorName, ndlib::io::AssetType pAssetType, bool sync) {
			always_assert(DataLoading_LevelUtil_LoadActorByName == nullptr, "LevelUtil::LoadActorByName missing function pointer");
			// return LevelMgr::IsLevelLoaded
			return DataLoading_LevelUtil_LoadActorByName(pActorName, pAssetType, sync);
		}

		void UnloadActor(char const* pActorName) {
			always_assert(DataLoading_LevelUtil_UnloadActor == nullptr, "LevelUtil::UnloadActor missing function pointer");
			DataLoading_LevelUtil_UnloadActor(pActorName);
		}

		void ReloadLevel(char const* pLevelName) {
			always_assert(DataLoading_LevelUtil_ReloadLevel == nullptr, "LevelUtil::ReloadLevel missing function pointer");
			DataLoading_LevelUtil_ReloadLevel(pLevelName);
		}

		void CacheFilenames(char const* pFileName) {
			always_assert(DataLoading_LevelUtil_CacheFilenames == nullptr, "LevelUtil::CacheFilenames missing function pointer");
			// lookup in NdGameInfo->m_GameDataPath
			DataLoading_LevelUtil_CacheFilenames(pFileName);
		}

		void LoadLevelSet(char const* levelSetName) {
			always_assert(DataLoading_LevelUtil_LoadLevelSet == nullptr, "LevelUtil::LoadLevelSet missing function pointer");
			DataLoading_LevelUtil_LoadLevelSet(levelSetName);
		}

		INIT_FUNCTION_PTR(DataLoading_LevelUtil_LoadActorByName);
		INIT_FUNCTION_PTR(DataLoading_LevelUtil_UnloadActor);
		INIT_FUNCTION_PTR(DataLoading_LevelUtil_ReloadLevel);
		INIT_FUNCTION_PTR(DataLoading_LevelUtil_CacheFilenames);
		INIT_FUNCTION_PTR(DataLoading_LevelUtil_LoadLevelSet);

	}

#endif
}