#include "data-loading.hpp"
#include "./NdGameSdk/shared/sharedpatterns.hpp"

#include "level-def-collection.hpp"
#include "load-registry.hpp"
#include "level-util.hpp"

namespace NdGameSdk::gamelib::level {
#if defined(T2R)

	DataLoading::DataLoading() : ISdkComponent(TOSTRING(DataLoading)) {}

	void DataLoading::Awake() {
		auto SharedComponents = ISdkComponent::GetSharedComponents();
		NdConfigComponent* NdConfigComp = GetDependencyComponent<NdConfigComponent>(SharedComponents);

		AddSubComponent<LevelDefCollection>(*NdConfigComp);
		AddSubComponent<LoadRegistry>(*NdConfigComp);
	}

	void DataLoading::Initialize() {
		static std::once_flag Initialized;

		std::call_once(Initialized, [this] {
			spdlog::info("Initializing {} patterns...", GetName());

			Patterns::SdkPattern findpattern{};
			auto module = Utility::memory::get_executable();

			findpattern = Patterns::DataLoading_Initialize;
			auto DataLoadingInitialize = (void*)Utility::FindAndPrintPattern(module
				, findpattern.pattern, wstr(Patterns::DataLoading_Initialize), findpattern.offset);

			if (!DataLoadingInitialize) {
				throw SdkComponentEx { std::format("Failed to find addresses!"), SdkComponentEx::ErrorCode::PatternFailed };
			}

			findpattern = Patterns::DataLoading_LevelUtil_LoadActorByName;
			LevelUtil::DataLoading_LevelUtil_LoadActorByName = (LevelUtil::DataLoading_LevelUtil_LoadActorByName_ptr)Utility::FindAndPrintPattern(module
				, findpattern.pattern, wstr(Patterns::DataLoading_LevelUtil_LoadActorByName), findpattern.offset);

			findpattern = Patterns::DataLoading_LevelUtil_UnloadActor;
			LevelUtil::DataLoading_LevelUtil_UnloadActor = (LevelUtil::DataLoading_LevelUtil_UnloadActor_ptr)Utility::FindAndPrintPattern(module
				, findpattern.pattern, wstr(Patterns::DataLoading_LevelUtil_UnloadActor), findpattern.offset);

			findpattern = Patterns::DataLoading_LevelUtil_ReloadLevel;
			LevelUtil::DataLoading_LevelUtil_ReloadLevel = (LevelUtil::DataLoading_LevelUtil_ReloadLevel_ptr)Utility::FindAndPrintPattern(module
				, findpattern.pattern, wstr(Patterns::DataLoading_LevelUtil_ReloadLevel), findpattern.offset);

			findpattern = Patterns::DataLoading_LevelUtil_CacheFilenames;
			LevelUtil::DataLoading_LevelUtil_CacheFilenames = (LevelUtil::DataLoading_LevelUtil_CacheFilenames_ptr)Utility::FindAndPrintPattern(module
				, findpattern.pattern, wstr(Patterns::DataLoading_LevelUtil_CacheFilenames), findpattern.offset);

			findpattern = Patterns::DataLoading_LevelUtil_LoadLevelSet;
			LevelUtil::DataLoading_LevelUtil_LoadLevelSet = (LevelUtil::DataLoading_LevelUtil_LoadLevelSet_ptr)Utility::FindAndPrintPattern(module
				, findpattern.pattern, wstr(Patterns::DataLoading_LevelUtil_LoadLevelSet), findpattern.offset);

			if (!LevelUtil::DataLoading_LevelUtil_LoadActorByName ||
				!LevelUtil::DataLoading_LevelUtil_UnloadActor ||
				!LevelUtil::DataLoading_LevelUtil_ReloadLevel ||
				!LevelUtil::DataLoading_LevelUtil_CacheFilenames ||
				!LevelUtil::DataLoading_LevelUtil_LoadLevelSet) {
				throw SdkComponentEx{ "Failed to find LevelUtil:: game functions!", SdkComponentEx::ErrorCode::PatternFailed};
			}

			m_DataLoadingInitializeHook = Utility::MakeSafetyHookInline(DataLoadingInitialize, DataLoading::InitializeInternal,
				wstr(Patterns::DataLoading_Initialize), wstr(DataLoading::InitializeInternal));

			if (!m_DataLoadingInitializeHook) {
				throw SdkComponentEx{ std::format("Failed to create hooks!"), SdkComponentEx::ErrorCode::PatchFailed };
			}

		});
	}

	void __cdecl DataLoading::InitializeInternal(DataLoading::Config& pConfig) {
		auto pDataLoading = Instance<DataLoading>();
		pDataLoading->m_DataLoadingInitializeHook.thiscall<void>(&pConfig);
		return;
	}

#endif
}
