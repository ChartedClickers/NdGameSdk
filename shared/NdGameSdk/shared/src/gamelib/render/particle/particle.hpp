#pragma once

#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/components/SdkComponent.hpp"

#if defined(T1X)

#include <NdGameSdk/shared/src/corelib/memory/memory.hpp>
#include <NdGameSdk/shared/src/gamelib/debug/nd-dev-menu.hpp>

#include <Utility/assertion/assert.hpp>
#include <Utility/helper.hpp>

#include "particle-debug.hpp"

using namespace NdGameSdk::corelib::memory;
using namespace NdGameSdk::ndlib;

namespace NdGameSdk::gamelib::render::particle {

	class ParticleManager : public ISdkComponent {
	public:
		ParticleManager();
		ParticleInternal::ParticleDebug m_ParticleDebug{};
	private:
		void Awake() override;
		void Initialize() override;

		Patch::Ptr m_ParticleDebug_RenderUpdatePatch{};
		FunctionHook::Ptr m_ParticleDebug_OnExecuteRootDataSelectorHook{};
		MidHook m_ParticleDebug_InitHook{};
		shared_ptr<Memory> m_Memory;
	};

}
#endif