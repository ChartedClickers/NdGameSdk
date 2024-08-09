#pragma once

#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/components/SdkComponent.hpp"
#include "NdGameSdk/config/DevModeCfg.hpp"

#include <NdGameSdk/shared/src/corelib/memory/memory.hpp>
#include <NdGameSdk/shared/src/ndlib/engine-components.hpp>
#include <NdGameSdk/shared/src/ndlib/debug/nd-dmenu.hpp>

#include <Utility/helper.hpp>

using namespace NdGameSdk::corelib::memory;
using namespace NdGameSdk::ndlib;
using namespace NdGameSdk::ndlib::debug;

namespace NdGameSdk::gamelib::debug {

	class NdDevMenu : public ISdkComponent {
	public:
		NdDevMenu(NdDevMenuCfg& cfg);
		NdGameSdk_API bool IsGameDebugMenu();
		NdGameSdk_API bool IsExtendedDebugMenu();
	private:
		void Awake() override;
		void Initialize() override;

		NdDevMenuCfg m_cfg{};
		DMENU* m_dmenu;

#if defined(T1X)
		Patch::Ptr m_GameConfig_DevModePatch{};

		Patch::Ptr m_Assert_UpdateSelectRegionByNameMenuPatch{};
		Patch::Ptr m_Assert_UpdateSelectIgcByNameMenuPatch{};
		Patch::Ptr m_Assert_UpdateSelectSpawnerByNameMenuPatch{};
#endif

		shared_ptr<EngineComponents> m_EngineComponents;
		shared_ptr<Memory> m_Memory;
	};

}