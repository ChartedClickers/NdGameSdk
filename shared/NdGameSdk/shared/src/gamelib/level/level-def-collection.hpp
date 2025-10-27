#pragma once

#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/components/SdkSubComponent.hpp"
#include "NdGameSdk/sdkregenny.hpp"

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/gamelib/level/LevelDefCollection.hpp>
#endif

#include <NdGameSdk/shared/src/ndlib/nd-config.hpp>
#include <NdGameSdk/shared/src/corelib/containers/robinhood-hash-table.hpp>
#include <NdGameSdk/shared/src/corelib/util/fixed-array.hpp>
#include <NdGameSdk/shared/src/corelib/memory/allocator-pool.hpp>

#include <boost/function.hpp>

#include "level-def.hpp"
#include "level-def-loader.hpp"

namespace NdGameSdk::gamelib::level {

#if defined(T2R)

	class LevelDefCollectionInternal : public ISdkRegenny<regenny::shared::gamelib::level::LevelDefCollection> {
	public:
		using RawPendingQueue = regenny::shared::gamelib::level::LevelDefCollection::FixedArray_corelib_util_level___LevelDef_ptr___3000;
		using PendingQueue = NdGameSdk::corelib::util::FixedArray<LevelDef*, 3000, RawPendingQueue>;
		using LevelDefTable = NdGameSdk::corelib::containers::RobinHoodHashTable<StringId64, const LevelDef*>;

		bool IsUseLevelDefAsyncLoad() const;

		PendingQueue& GetPendingQueue();
		const PendingQueue& GetPendingQueue() const;

		LevelDefTable& GetLevelDefTable();
		const LevelDefTable& GetLevelDefTable() const;

		corelib::memory::PoolAllocator* GetLoaderAllocator();
		const corelib::memory::PoolAllocator* GetLoaderAllocator() const;

		LevelDefLoader* GetLevelDefLoader();
		const LevelDefLoader* GetLevelDefLoader() const;
	};

	class LevelDefCollection final : public ISdkSubComponent {
	public:
		explicit LevelDefCollection(ndlib::NdConfigComponent& ndConfig);

		LevelDefLoader* GetLevelDefLoader() const;

		/*Extern Functs*/
		LevelDef* GetLevelDef(char* levelName, StringId64 levelId = 0x0, bool disablePartPackages = false);
		LevelDef* AllocateLevelDef(char* levelName, StringId64 levelId = 0x0, bool disablePartPackages = false);
		LevelDef* AsyncLoad(LevelDef* pLevelDef);

	private:
		void Init() override;

		inline LevelDefCollectionInternal& GetLevelDefCollectionInternal() const;

		ndlib::NdConfigComponent* m_NdConfigComp{ nullptr };

		MEMBER_FUNCTION_PTR(LevelDef*, LevelDefCollection_GetLevelDef, LevelDefCollectionInternal* pLevelDefCollection, 
			char* levelName, StringId64 levelId, bool disablePartPackages);
		MEMBER_FUNCTION_PTR(LevelDef*, LevelDefCollection_AllocateLevelDef, LevelDefCollectionInternal* pLevelDefCollection,
			char* levelName, StringId64 levelId, bool disablePartPackages);
		MEMBER_FUNCTION_PTR(LevelDef*, LevelDefCollection_AsyncLoad, LevelDefCollectionInternal* pLevelDefCollection, LevelDef* pLevelDef);
	};

#endif

}
