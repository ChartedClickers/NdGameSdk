#include "engine-components.hpp"
#include "./NdGameSdk/shared/sharedpatterns.hpp"

#include <Utility/helper.hpp>

namespace NdGameSdk::ndlib {

	EngineComponents::EngineComponents() : ISdkComponent(TOSTRING(EngineComponents)) {}

	void EngineComponents::Initialize()
	{
		static std::once_flag Initialized;

		std::call_once(Initialized, [this] {

			spdlog::info("Initializing {} patterns...", GetName());

			Patterns::SdkPattern findpattern{};

			findpattern = Patterns::EngineComponents_s_table;
			const auto s_table = (uintptr_t**)Utility::ReadLEA32(Utility::memory::get_executable(),
				findpattern.pattern, wstr(Patterns::EngineComponents_s_table), findpattern.offset, 3, 7);

			findpattern = Patterns::EngineComponents_s_ndConfig;
			const auto s_ndConfig = (uintptr_t**)Utility::ReadLEA32(Utility::memory::get_executable(),
				findpattern.pattern, wstr(Patterns::EngineComponents_s_ndConfig), findpattern.offset, 3, 7);

			if (!s_table && !s_ndConfig) {
				throw SdkComponentEx { std::format("Failed to find components"), SdkComponentEx::ErrorCode::PatternFailed };
			}

			m_ptrs = s_table;
			m_ndConfig.g_ndConfig = s_ndConfig;

		});
	}

	ndlib::NdGameInfo& EngineComponents::GetNdGameInfo() {
		return *GetEngineComponent<ndlib::NdGameInfo>(EngineComponent::NdGameInfo);
	}

	ndlib::NdFrameState& EngineComponents::GetNdFrameState() {
		return *GetEngineComponent<ndlib::NdFrameState>(EngineComponent::NdFrameState);
	}
	
#if defined(T2R)
	ndlib::io::FileSystemWin& EngineComponents::GetFileSystem() {
		return *GetEngineComponent<ndlib::io::FileSystemWin>(EngineComponent::FileSystem);
	}

	ndlib::io::PackageMgr& EngineComponents::GetPackageMgr() {
		return *GetEngineComponent<ndlib::io::PackageMgr>(EngineComponent::PackageMgr);
	}
#endif
}
