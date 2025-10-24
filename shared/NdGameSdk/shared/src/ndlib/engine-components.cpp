#include "engine-components.hpp"
#include "./NdGameSdk/shared/sharedpatterns.hpp"

#include "nd-game-info.hpp"
#include "nd-frame-state.hpp"
#include "io/file-system-win-fios2.hpp"
#include "io/package-mgr.hpp"
#include "io/prefetch.hpp"

#include <Utility/helper.hpp>
#include <Utility/global_resolver.hpp>

namespace NdGameSdk::ndlib {

	EngineComponents::EngineComponents() : ISdkComponent(TOSTRING(EngineComponents)) {}

	void EngineComponents::Initialize() {
		static std::once_flag Initialized;

		std::call_once(Initialized, [this] {

			spdlog::info("Initializing {} patterns...", GetName());

			Patterns::SdkPattern findpattern{};

			findpattern = Patterns::EngineComponents_s_table;
			s_table = Utility::GlobalResolver::RipSlotOrNull<EngineComponentsTable>(Utility::memory::get_executable(),
				findpattern.pattern, wstr(Patterns::EngineComponents_s_table), findpattern.offset, 3, 7);

			if (!s_table) {
				throw SdkComponentEx { std::format("Failed to find components"), SdkComponentEx::ErrorCode::PatternFailed };
			}

		});
	}

	ndlib::NdGameInfo& EngineComponents::GetNdGameInfo() {
		return *GetEngineComponent<ndlib::NdGameInfo>(EngineComponent::NdGameInfo);
	}

	ndlib::NdFrameState& EngineComponents::GetNdFrameState() {
		return *GetEngineComponent<ndlib::NdFrameState>(EngineComponent::NdFrameState);
	}
	
	ndlib::io::FileSystemWin& EngineComponents::GetFileSystem() {
		return *GetEngineComponent<ndlib::io::FileSystemWin>(EngineComponent::FileSystem);
	}

	ndlib::io::PackageMgr& EngineComponents::GetPackageMgr() {
		return *GetEngineComponent<ndlib::io::PackageMgr>(EngineComponent::PackageMgr);
	}

	ndlib::io::PrefetchMgr& EngineComponents::GetPrefetchMgr() {
		return *GetEngineComponent<ndlib::io::PrefetchMgr>(EngineComponent::PrefetchMgr);
	}
}
