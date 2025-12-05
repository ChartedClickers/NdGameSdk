#pragma once

#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/components/SdkComponent.hpp"

#include <cstdint>
#include <string>
#include <format>
#include <spdlog/spdlog.h>
#include <assertion/assert.hpp>

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/ndlib/EngineComponents.hpp>
#elif defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/ndlib/EngineComponents.hpp>
#endif

namespace NdGameSdk::gamelib::level {
	class LevelMgrInternal;
}

namespace NdGameSdk::ndlib {

	class NdGameInfo;
	class NdFrameState;

	namespace io {
		class FileSystemWin;
		class PackageMgrInternal;
		class PrefetchMgr;
	}

	using EngineComponent = ::regenny::shared::ndlib::EngineComponents::Component;
	using LevelMgr = ::NdGameSdk::gamelib::level::LevelMgrInternal;
	using FileSystem = io::FileSystemWin;
	using PackageMgr = io::PackageMgrInternal;
	using io::PrefetchMgr;

	class EngineComponentsTable : public ISdkRegenny<regenny::shared::ndlib::EngineComponents> {};

    class EngineComponents : public ISdkComponent {
	public:
		EngineComponents();

		NdGameSdk_API NdGameInfo& GetNdGameInfo();
		NdGameSdk_API NdFrameState& GetNdFrameState();
		NdGameSdk_API FileSystem& GetFileSystem();
		NdGameSdk_API PrefetchMgr& GetPrefetchMgr();
		NdGameSdk_API PackageMgr& GetPackageMgr();
		NdGameSdk_API LevelMgr& GetLevelMgr();

		template <typename TComponent>
		NdGameSdk_API TComponent* GetEngineComponent(EngineComponent type) {
			always_assert(s_table == nullptr, "s_table was not set!");
			return (TComponent*)((*s_table)->m_ptrs[type]);
		}

		NdGameSdk_API uint32_t GetEngineComponentSize(EngineComponent type) {
			always_assert(s_table == nullptr, "s_table was not set!");
			return (*s_table)->m_sizes[type];
		}

	private:
		void Initialize() override;

		// s_table.m_ptrs+0xEngineComponent*8
		inline static EngineComponentsTable* s_table{ nullptr };
	};

}
