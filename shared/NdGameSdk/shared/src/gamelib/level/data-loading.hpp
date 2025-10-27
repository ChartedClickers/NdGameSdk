#pragma once

#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/components/SdkComponent.hpp"
#include "NdGameSdk/components/SdkSubComponent.hpp"

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/gamelib/level/DataLoading.hpp>
#endif

#include <NdGameSdk/shared/src/ndlib/nd-config.hpp>

using namespace NdGameSdk::ndlib;

namespace NdGameSdk::gamelib::level {

#if defined(T2R)

	class NdGameSdk_API DataLoading final : public ISdkComponent {
	public:
		using Config = regenny::shared::gamelib::level::DataLoading::Config;

		DataLoading();
		SDK_DEPENDENCIES(NdConfigComponent);

	private:
		void Awake() override;
		void Initialize() override;

		/*Extern Functs*/
		// void __cdecl DataLoading::Initialize(const class DataLoading::Config &)
		static void __cdecl InitializeInternal(DataLoading::Config& pConfig);

		InlineHook m_DataLoadingInitializeHook{};
	};

#endif

}

