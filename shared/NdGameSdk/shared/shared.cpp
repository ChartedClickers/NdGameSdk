#include "shared.hpp"

#include "src/corelib/system/NdSystem.hpp"
#include "src/corelib/memory/memory.hpp"
#include "src/corelib/job/job-system.hpp"
#include "src/ndlib/engine-components.hpp"
#include "src/ndlib/frame-params.hpp"
#include "src/ndlib/render/ndgi/win/ndgi-win-device.hpp"
#include "src/ndlib/io/file-system-win-fios2.hpp"
#include "src/ndlib/io/package-mgr.hpp"
#include "src/ndlib/script/script-manager.hpp"
#include "src/ndlib/render/dev/debugdraw-common.hpp"
#include "src/ndlib/profiling/profile-ctrl.hpp"
#include "src/ndlib/settings/settings.hpp"
#include "src/common/common-game-init.hpp"
#include "src/gamelib/debug/nd-dev-menu.hpp"
#include "src/gamelib/render/particle/particle.hpp"
#include "src/gamelib/level/game-loading.hpp"

namespace NdGameSdk {

	void InitSharedComponents()
	{
		auto SharedComponents = ISdkComponent::GetSharedComponents();

		SharedComponents->AddComponent<corelib::system::NdSystem>();
		auto MemComponent = SharedComponents->AddComponent<corelib::memory::Memory>();
		SharedComponents->AddComponent<ndlib::EngineComponents>();
		SharedComponents->AddComponent<ndlib::RenderFrameParams>();
		SharedComponents->AddComponent<ndlib::render::ndgi::win::NDGI>();
		SharedComponents->AddComponent<corelib::job::NdJob>();
		SharedComponents->AddComponent<ndlib::render::dev::DebugDrawCommon>();
		SharedComponents->AddComponent<ndlib::script::ScriptManager>();
		SharedComponents->AddComponent<ndlib::settings::SettingsControl>();

#if defined(T1X)
		auto ParticleMgr = SharedComponents->AddComponent<gamelib::render::particle::ParticleManager>();
#elif defined(T2R)
		SharedComponents->AddComponent<ndlib::io::FileSystem>();
		SharedComponents->AddComponent<ndlib::io::PackageManager>();
	#if SDK_DEBUG
		SharedComponents->AddComponent<ndlib::profiling::ProfileController>();
	#endif
#endif

		SharedComponents->AddComponent<common::CommonGame>();
		SharedComponents->AddComponent<gamelib::level::GameLoading>();
		auto DmenuComponent = SharedComponents->AddComponent<gamelib::debug::NdDevMenu>();

		SharedComponents->InitializeSdkComponents();

#if defined(T1X)
		if (MemComponent->IsDebugMemoryAvailable()) {
			auto MissingDependencies = ISdkComponent::CheckSdkComponents
				<gamelib::debug::NdDevMenu, gamelib::render::particle::ParticleManager>({
					ParticleMgr, DmenuComponent });

			if (MissingDependencies.has_value()) {
				throw SdkComponentEx
				{ std::format("Necessary dependencies for DebugMemory is missing: {:s}", MissingDependencies.value()),
					SdkComponentEx::ErrorCode::DependenciesFailed, true };
			}
		}
#endif

	}
}
