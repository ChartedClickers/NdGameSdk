#pragma once

#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/components/SdkComponent.hpp"

#include <cstdint>
#include <string>
#include <format>
#include <spdlog/spdlog.h>
#include <Utility/assertion/assert.hpp>

#if defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/ndlib/EngineComponents.hpp>
#elif defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/ndlib/EngineComponents.hpp>
#endif

#include "nd-game-info.hpp"
#include "nd-frame-state.hpp"
#include "io/file-system-win-fios2.hpp"
#include "io/package-mgr.hpp"
#include "nd-config.hpp"

using EngineComponent = ::regenny::shared::ndlib::EngineComponents::Component;

namespace NdGameSdk::ndlib {

    class EngineComponents : public ISdkComponent {
	public:
		EngineComponents();

		NdGameSdk_API ndlib::NdGameInfo& GetNdGameInfo();
		NdGameSdk_API ndlib::NdFrameState& GetNdFrameState();

#if defined(T2R)
		NdGameSdk_API ndlib::io::FileSystemWin& GetFileSystem();
		NdGameSdk_API ndlib::io::PackageMgr& GetPackageMgr();
#endif

		template <typename TComponent>
		NdGameSdk_API TComponent* GetEngineComponent(EngineComponent index) {
			always_assert(m_ptrs == nullptr, "m_ptrs was not set!");
			return (TComponent*)(m_ptrs[index]);
		}

		NdConfig m_ndConfig{};
	private:
		void Initialize() override;

		// m_ptrs+0xEngineComponent*8
		uintptr_t** m_ptrs{};
	};

}