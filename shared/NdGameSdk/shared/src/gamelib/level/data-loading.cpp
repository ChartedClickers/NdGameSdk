#include "data-loading.hpp"
#include "./NdGameSdk/shared/sharedpatterns.hpp"

#include "level-def-collection.hpp"
#include "load-registry.hpp"

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
