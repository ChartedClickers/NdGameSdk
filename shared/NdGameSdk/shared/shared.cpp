#include "shared.hpp"

#include "src/corelib/memory/memory.hpp"
#include "src/ndlib/engine-components.hpp"
#include "src/ndlib/script/script-manager.hpp"
#include "src/ndlib/render/util/prim.hpp"
#include "src/common/common-game-init.hpp"
#include "src/gamelib/debug/nd-dev-menu.hpp"
#include "src/gamelib/render/particle/particle.hpp"

namespace NdGameSdk {

	void InitSharedComponents(SdkConfig& cfg)
	{
		auto SharedComponents = ISdkComponent::GetSharedComponents();
#if defined(T1X)
		auto MemComponent = SharedComponents->AddComponent<corelib::memory::Memory>(cfg.Memory);
#endif
		SharedComponents->AddComponent<ndlib::EngineComponents>();

#if defined(T1X)
		SharedComponents->AddComponent<ndlib::script::ScriptManager>();
		SharedComponents->AddComponent<ndlib::render::util::PrimServerComponent>(cfg.PrimServer);
		auto ParticleMgr = SharedComponents->AddComponent<gamelib::render::particle::ParticleManager>();
#endif
		SharedComponents->AddComponent<common::CommonGame>();
#if defined(T1X)
		auto DmenuComponent = SharedComponents->AddComponent<gamelib::debug::NdDevMenu>(cfg.NdDevMenu);
#endif
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
