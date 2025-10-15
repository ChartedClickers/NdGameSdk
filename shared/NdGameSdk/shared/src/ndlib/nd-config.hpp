#pragma once

#include <cstdint>
#include <Utility/assertion/assert.hpp>

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/ndlib/NdConfig.hpp>
#elif defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/ndlib/NdConfig.hpp>
#endif

#include "debug/nd-dmenu.hpp"

namespace NdGameSdk::ndlib {
	class NdConfig {
	public:
		using Config = ::regenny::shared::ndlib::NdConfig::Config;

		NdGameSdk_API ndlib::debug::DMENU& GetDmenu();
		NdGameSdk_API ndlib::debug::DMENU::MenuGroup& GetNdDevMenu();

		template <typename TConfig>
		NdGameSdk_API TConfig* GetConfig(Config index) {
			always_assert(g_ndConfig == nullptr, "g_ndConfig was not set!");
			return (TConfig*)(g_ndConfig[index]);
		}

	private:
		friend class EngineComponents;
		// g_ndConfig+0xConfig*8
		uintptr_t** g_ndConfig{};
	};
}