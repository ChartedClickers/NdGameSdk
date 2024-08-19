#include "shared.hpp"

#include "src/corelib/memory/memory.hpp"
#include "src/ndlib/engine-components.hpp"
#include "src/ndlib/render/util/prim.hpp"
#include "src/common/common-game-init.hpp"
#include "src/gamelib/debug/nd-dev-menu.hpp"
#include "src/gamelib/render/particle/particle.hpp"

namespace NdGameSdk {

	void InitSharedComponents(SdkConfig& cfg)
	{
		auto SharedComponents = ISdkComponent::GetSharedComponents();
		auto MemoryComponent = 
			SharedComponents->AddComponent<corelib::memory::Memory>(cfg.Memory);

		SharedComponents->AddComponent<ndlib::EngineComponents>();
#if defined(T1X)
		SharedComponents->AddComponent<ndlib::render::util::PrimServerComponent>(cfg.PrimServer);
		SharedComponents->AddComponent<gamelib::render::particle::ParticleManager>();
#endif
		SharedComponents->AddComponent<common::CommonGame>();
		SharedComponents->AddComponent<gamelib::debug::NdDevMenu>(cfg.NdDevMenu);

		SharedComponents->InitializeSdkComponents();

#if defined(T1X)
		if (MemoryComponent->IsDebugMemoryAvailable()) {
			auto MissingDependencies = ISdkComponent::CheckSdkComponents
				<gamelib::debug::NdDevMenu, gamelib::render::particle::ParticleManager>({
					SharedComponents->GetComponent<gamelib::debug::NdDevMenu>().get(),
					SharedComponents->GetComponent<gamelib::render::particle::ParticleManager>().get() });

			if (MissingDependencies.has_value()) {
				throw SdkComponentEx
				{ std::format("Necessary dependencies for DebugMemory is missing: {:s}", MissingDependencies.value()),
					SdkComponentEx::ErrorCode::DependenciesFailed, true };
			}
		}
#endif

	}
}
