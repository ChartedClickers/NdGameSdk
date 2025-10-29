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

#include <NdGameSdk/shared/src/ndlib/engine-components.hpp>
#include <NdGameSdk/shared/src/corelib/containers/fixedsizeheap.hpp>
#include <NdGameSdk/shared/src/corelib/containers/fixed-size-hashtable.hpp>
#include <NdGameSdk/shared/src/corelib/containers/list-array.hpp>
#include <NdGameSdk/shared/src/corelib/containers/bit-array.hpp>

#include "level.hpp"
#include "want-load.hpp"
#include "blockmesh-mgr.hpp"

namespace NdGameSdk::gamelib::level {
#if defined (T2R)

	using namespace ndlib;
	using namespace corelib::containers;

	class LevelLoadObserver : public ISdkRegenny<regenny::shared::gamelib::level::LevelLoadObserver> {};

	class LevelMgrInternal : public ISdkRegenny<regenny::shared::gamelib::level::LevelMgr> {
	public:
	#if defined(T2R)
		class Configuration : public ISdkRegenny<regenny::shared::gamelib::level::LevelMgr::Configuration> {};

		class LevelLookupNode : public ISdkRegenny<regenny::shared::gamelib::level::LevelMgr::LevelLookupNode, FixedSizeHashTable<LevelLookupNode>::ListHead> {
		public:
			StringId64 GetLevelId();
			StringId64 GetLevelId() const;
			Level* GetLevelPtr();
			const Level* GetLevelPtr() const;
		};

		class Request : public ISdkRegenny<regenny::shared::gamelib::level::LevelMgr::Request> {
		public:
			using LoadingType = regenny::shared::gamelib::level::LevelMgr::Request::LoadingType;
			Level* GetLevel();
			WantLoadInfo* GetWantLoadInfo();
			LoadingType GetLoadingType();
			bool IsProcessed() const;
		};

		class SoundBankInfos : public ISdkRegenny<regenny::shared::gamelib::level::LevelMgr::SoundBankInfos> {};
		class MiniSoundBankInfos : public ISdkRegenny<regenny::shared::gamelib::level::LevelMgr::MiniSoundBankInfos> {};


		FixedSizeHeap* GetLevelPool();
		ListArray<Request>& GetRequests();

		FixedSizeHashTable<LevelLookupNode>& GetActiveLevelsTable();
		FixedSizeHashTable<LevelLookupNode>& GetPendingLevelsTable();

		ListArray<Level>& GetLoadedLevels();
		ListArray<Level>& GetPendingLevels();
		ListArray<Level>& GetDisplayReadyLevels();
		ListArray<Level>& GetEntitySpawnerLevels();
		ListArray<StringId64>& GetCriticalLoadIds();

		BitArray<4096>& GetSoundBankInfoBits();
		BitArray<2048>& GetMiniSoundBankInfoBits();
		BitArray<160>& GetBackgroundInUseBits();

		BlockMeshMgr* GetBlockMeshMgr();
		LevelLoadObserver* GetLevelLoadObserver();

	#endif
	};

	class NdGameSdk_API LevelMgr : public ISdkComponent {
	public:
		using Configuration = LevelMgrInternal::Configuration;
		using LevelLookupNode = LevelMgrInternal::LevelLookupNode;
		using Request = LevelMgrInternal::Request;

		LevelMgr();
		SDK_DEPENDENCIES(EngineComponents, Memory);

		void Sync(bool runStreamingOnly);
		Level* GetLevelSafe(StringId64 levelId);
		int GetNumCriticalLoads();
		bool IsLevelLoaded(StringId64 levelId) const;
		bool ShouldPauseForCriticalLoads();
		void AddCriticalLoadLevel(StringId64 levelId);

	private:
		void Awake() override;
		void Initialize() override;

		LevelMgrInternal* GetLevelMgrInternal() const;

		/*Extern Functs*/
		// void __cdecl LevelMgr::Init(const class LevelMgr::Configuration &)
		static void __cdecl InitInternal(LevelMgrInternal* pLevelMgrInternal, LevelMgr::Configuration& pConfig);

		EngineComponents* m_EngineComponents;

		InlineHook m_LevelMgrInitHook{};

		MEMBER_FUNCTION_PTR(void, LevelMgr_Sync, LevelMgrInternal* pLevelMgr, bool runStreamingOnly);
		MEMBER_FUNCTION_PTR(Level*, LevelMgr_GetLevelSafe, LevelMgrInternal* pLevelMgr, StringId64 levelId);
		MEMBER_FUNCTION_PTR(uint32_t, LevelMgr_GetNumCriticalLoads, LevelMgrInternal* pLevelMgr);
		MEMBER_FUNCTION_PTR(void, LevelMgr_AddCriticalLoadLevel, LevelMgrInternal* pLevelMgr, StringId64 levelId);
		MEMBER_FUNCTION_PTR(bool, LevelMgr_ShouldPauseForCriticalLoads, LevelMgrInternal* pLevelMgr);

	};


	static_assert(sizeof(LevelMgrInternal) == 0x481f20, "LevelMgr size mismatch");
	static_assert(sizeof(LevelMgrInternal::Configuration) == 0x10, "LevelMgr::Configuration size mismatch");
	static_assert(sizeof(LevelMgrInternal::LevelLookupNode) - sizeof(FixedSizeHashTable<LevelMgrInternal::LevelLookupNode>::ListHead) == 0x10, "LevelMgr::LevelLookupNode size mismatch");
	static_assert(sizeof(LevelMgrInternal::Request) == 0x18, "LevelMgr::Request size mismatch");
	static_assert(sizeof(LevelMgrInternal::SoundBankInfos) == 0x410, "LevelMgr::SoundBankInfos size mismatch");
	static_assert(sizeof(LevelMgrInternal::MiniSoundBankInfos) == 0x50, "LevelMgr::MiniSoundBankInfos size mismatch");

#endif
}
