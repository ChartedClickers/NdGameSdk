#include "level-def-collection.hpp"
#include "level-def.hpp"
#include "./NdGameSdk/shared/sharedpatterns.hpp"


namespace NdGameSdk::gamelib::level {

#if defined(T2R)

	LevelDefCollection::LevelDefCollection(NdGameSdk::ndlib::NdConfigComponent& ndConfig) 
		: ISdkSubComponent(TOSTRING(LevelDefCollection), InitPolicy::Manual), m_NdConfigComp{ &ndConfig } {}

	void LevelDefCollection::Init() {
		static std::once_flag Initialized;
		std::call_once(Initialized, [this] {

			spdlog::info("Initializing {} patterns...", GetName());

			Patterns::SdkPattern findpattern{};
			auto module = Utility::memory::get_executable();

			findpattern = Patterns::LevelDefCollection_GetLevelDef;
			LevelDefCollection_GetLevelDef = (LevelDefCollection_GetLevelDef_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::LevelDefCollection_GetLevelDef), findpattern.offset);

			findpattern = Patterns::LevelDefCollection_AllocateLevelDef;
			LevelDefCollection_AllocateLevelDef = (LevelDefCollection_AllocateLevelDef_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::LevelDefCollection_AllocateLevelDef), findpattern.offset);

			findpattern = Patterns::LevelDefCollection_AsyncLoad;
			LevelDefCollection_AsyncLoad = (LevelDefCollection_AsyncLoad_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::LevelDefCollection_AsyncLoad), findpattern.offset);

			findpattern = Patterns::LevelDefCollection_LevelDef_Update;
			LevelDef::LevelDefCollection_LevelDef_Update = (LevelDef::LevelDefCollection_LevelDef_Update_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::LevelDefCollection_LevelDef_Update), findpattern.offset);

			if (!LevelDefCollection_GetLevelDef ||
				!LevelDefCollection_AllocateLevelDef ||
				!LevelDefCollection_AsyncLoad || 
				!LevelDef::LevelDefCollection_LevelDef_Update				
				) {
				throw SdkComponentEx{ std::format("Failed to find {}:: game functions!", GetName()), SdkComponentEx::ErrorCode::PatternFailed };
			}

		});
	}

	inline LevelDefCollectionInternal& LevelDefCollection::GetLevelDefCollectionInternal() const {
		always_assert(m_NdConfigComp == nullptr, "LevelDefCollection::GetLevelDefCollectionInternal missing NdConfigComponent");
		return m_NdConfigComp->GetNdConfig().GetLevelDefCollection();
	}

	LevelDefLoader* LevelDefCollection::GetLevelDefLoader() const {
		return GetLevelDefCollectionInternal().GetLevelDefLoader();
	}

	LevelDef* LevelDefCollection::GetLevelDef(char* levelName, StringId64 levelId, bool disablePartPackages) {
		always_assert(LevelDefCollection_GetLevelDef == nullptr, "Function pointer was not set!");
		return LevelDefCollection_GetLevelDef(&GetLevelDefCollectionInternal(), levelName, levelId, disablePartPackages);
	}

	LevelDef* LevelDefCollection::AllocateLevelDef(char* levelName, StringId64 levelId, bool disablePartPackages) {
		always_assert(LevelDefCollection_AllocateLevelDef == nullptr, "Function pointer was not set!");
		return LevelDefCollection_AllocateLevelDef(&GetLevelDefCollectionInternal(), levelName, levelId, disablePartPackages);
	}

	LevelDef* LevelDefCollection::AsyncLoad(LevelDef* pLevelDef) {
		always_assert(LevelDefCollection_AsyncLoad == nullptr, "Function pointer was not set!");
		return LevelDefCollection_AsyncLoad(&GetLevelDefCollectionInternal(), pLevelDef);
	}

	bool LevelDefCollectionInternal::IsUseLevelDefAsyncLoad() const {
		return this->Get()->m_UseLevelDefAsyncLoad;
	}

	LevelDefCollectionInternal::PendingQueue& LevelDefCollectionInternal::GetPendingQueue() {
		return reinterpret_cast<PendingQueue&>(this->Get()->m_pendingQueue);
	}

	const LevelDefCollectionInternal::PendingQueue& LevelDefCollectionInternal::GetPendingQueue() const {
		return reinterpret_cast<const PendingQueue&>(this->Get()->m_pendingQueue);
	}

	LevelDefCollectionInternal::LevelDefTable& LevelDefCollectionInternal::GetLevelDefTable() {
		return reinterpret_cast<LevelDefTable&>(this->Get()->m_table);
	}

	const LevelDefCollectionInternal::LevelDefTable& LevelDefCollectionInternal::GetLevelDefTable() const {
		return reinterpret_cast<const LevelDefTable&>(this->Get()->m_table);
	}

	NdGameSdk::corelib::memory::PoolAllocator* LevelDefCollectionInternal::GetLoaderAllocator() {
		return reinterpret_cast<NdGameSdk::corelib::memory::PoolAllocator*>(&this->Get()->m_allocator);
	}

	const NdGameSdk::corelib::memory::PoolAllocator* LevelDefCollectionInternal::GetLoaderAllocator() const {
		return reinterpret_cast<const NdGameSdk::corelib::memory::PoolAllocator*>(&this->Get()->m_allocator);
	}

	LevelDefLoader* LevelDefCollectionInternal::GetLevelDefLoader() {
		return reinterpret_cast<LevelDefLoader*>(&this->Get()->m_DefLoader);
	}

	const LevelDefLoader* LevelDefCollectionInternal::GetLevelDefLoader() const {
		return reinterpret_cast<const LevelDefLoader*>(&this->Get()->m_DefLoader);
	}

#endif

}
