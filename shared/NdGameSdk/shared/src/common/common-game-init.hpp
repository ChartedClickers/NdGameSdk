#pragma once

#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/sdkconfig.hpp"
#include "NdGameSdk/components/SdkComponent.hpp"

#if defined(T2R)
#include <NdGameSdk/shared/src/common/win/nxapp-hooks.hpp>
using namespace NdGameSdk::common::win;
#elif defined(T1X)
#include <NdGameSdk/shared/src/ndlib/render/util/prim.hpp>
using namespace NdGameSdk::ndlib::render::util;
#endif

#include <NdGameSdk/shared/src/ndlib/engine-components.hpp>
#include <NdGameSdk/shared/src/corelib/memory/memory.hpp>
#include "common-allocator.hpp"

using namespace NdGameSdk::corelib::memory;
using namespace NdGameSdk::ndlib;

namespace NdGameSdk::common {

	class CommonGame : public ISdkComponent
	{
	public:
		CommonGame();

		SdkEvent<bool> e_GameInitialized{true};

		NdGameSdk_API uint32_t GetGameVersion();
		NdGameSdk_API bool IsGameInitialized();
	private:
		void Awake() override;
		void Initialize() override;

		uint32_t m_GameVersion;
		bool m_GameInitialized;

		MidHook m_GameInitHook{};
		MidHook m_GameInitReturnHook{};

		shared_ptr<Memory> m_Memory;
		shared_ptr<EngineComponents> m_EngineComponents;
		optional<IAllocator> m_IAllocator;
#if defined(T2R)
		NxAppHooks m_NxAppHooks{};
#elif defined(T1X)
		MidHook m_PrimServer_CreateHook{};
		shared_ptr<PrimServerComponent> m_PrimServer;
#endif
	};
}