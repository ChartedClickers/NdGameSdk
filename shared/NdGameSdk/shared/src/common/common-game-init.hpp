#pragma once

#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/sdkconfig.hpp"
#include "NdGameSdk/components/SdkComponent.hpp"

#include <NdGameSdk/shared/src/corelib/memory/memory.hpp>
#include <NdGameSdk/shared/src/ndlib/render/util/prim.hpp>

using namespace NdGameSdk::corelib::memory;
using namespace NdGameSdk::ndlib::render::util;

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
		shared_ptr<Memory> m_Memory;

#if defined(T1X)
		MidHook m_PrimServer_CreateHook{};
		shared_ptr<PrimServerComponent> m_PrimServer;
#endif
	};
}