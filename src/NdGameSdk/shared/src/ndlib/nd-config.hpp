#pragma once

#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/components/SdkComponent.hpp"

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/ndlib/NdConfig.hpp>
#elif defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/ndlib/NdConfig.hpp>
#endif

#include <cstdint>
#include <Utility/assertion/assert.hpp>

#include "debug/nd-dmenu.hpp"

namespace NdGameSdk::gamelib::level {
	class LevelDefCollectionInternal;
	class LoadRegistryInternal;
}

namespace NdGameSdk::ndlib {

	class NdGameSdk_API NdConfig : ISdkRegenny<regenny::shared::ndlib::NdConfig> {
	public:
		NdConfig() = default;
		NdConfig(const NdConfig&) = delete;
		NdConfig& operator=(const NdConfig&) = delete;
		NdConfig(NdConfig&&) = delete;
		NdConfig& operator=(NdConfig&&) = delete;

		ndlib::debug::DMENU& GetDmenu();
		ndlib::debug::DMENU::MenuGroup& GetNdDevMenu();

	#if defined(T2R)
		gamelib::level::LevelDefCollectionInternal& GetLevelDefCollection();
		gamelib::level::LoadRegistryInternal& GetLoadRegistry();
	#endif

	};

	class NdConfigComponent : public ISdkComponent {
	public:
		NdConfigComponent();
		NdGameSdk_API ndlib::NdConfig& GetNdConfig();

		/*Extern variables*/
		static NdConfig* g_ndConfig;
	private:
		void Initialize() override;
	};

}
