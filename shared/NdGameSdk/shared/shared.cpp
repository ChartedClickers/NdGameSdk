#include "shared.hpp"

#include "src/corelib/memory/memory.hpp"
#include "src/ndlib/engine-components.hpp"
#include "src/ndlib/script/script-manager.hpp"
#include "src/ndlib/render/dev/debugdraw-common.hpp"
#include "src/common/common-game-init.hpp"
#include "src/gamelib/debug/nd-dev-menu.hpp"
#include "src/gamelib/render/particle/particle.hpp"

namespace NdGameSdk {

	void InitSharedComponents(SdkConfig& cfg)
	{
		auto SharedComponents = ISdkComponent::GetSharedComponents();

		auto MemComponent = SharedComponents->AddComponent<corelib::memory::Memory>(cfg.Memory);

		SharedComponents->AddComponent<ndlib::EngineComponents>();
		SharedComponents->AddComponent<ndlib::render::dev::DebugDrawCommon>();

#if defined (T2R)
#elif defined(T1X)
		SharedComponents->AddComponent<ndlib::script::ScriptManager>();
		auto ParticleMgr = SharedComponents->AddComponent<gamelib::render::particle::ParticleManager>();
#endif
		SharedComponents->AddComponent<common::CommonGame>();
		auto DmenuComponent = SharedComponents->AddComponent<gamelib::debug::NdDevMenu>(cfg.NdDevMenu);

		SharedComponents->InitializeSdkComponents();

#if defined(T1X)
		if (MemComponent->IsDebugMemoryAvailable()) {
			auto MissingDependencies = ISdkComponent::CheckSdkComponents
				<gamelib::debug::NdDevMenu, gamelib::render::particle::ParticleManager>({
					ParticleMgr.get(), DmenuComponent.get() });

			if (MissingDependencies.has_value()) {
				throw SdkComponentEx
				{ std::format("Necessary dependencies for DebugMemory is missing: {:s}", MissingDependencies.value()),
					SdkComponentEx::ErrorCode::DependenciesFailed, true };
			}
		}
#endif

	}
}
