#pragma once

#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/sdkconfig.hpp"
#include "NdGameSdk/components/SdkComponent.hpp"

#if defined(T2R)
#include <NdGameSdk/shared/src/common/win/nxapp-hooks.hpp>
using namespace NdGameSdk::common::win;
#elif defined(T1X)
#endif

#include <NdGameSdk/shared/src/ndlib/engine-components.hpp>
#include <NdGameSdk/shared/src/corelib/memory/memory.hpp>
#include <NdGameSdk/shared/src/gamelib/debug/nd-dev-menu.hpp>

#include "common-allocator.hpp"
#include "common-game-loop.hpp"

using namespace NdGameSdk::corelib::memory;
using namespace NdGameSdk::gamelib::debug;
using namespace NdGameSdk::ndlib;

namespace NdGameSdk::common {

class CommonGameLoop;

class CommonGame : public ISdkComponent
{
public:
	CommonGame();

	SDK_DEPENDENCIES(Memory, EngineComponents);

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

	IAllocator* m_IAllocator;
	CommonGameLoop* m_CommonGameLoop;

	Memory* m_Memory;
	EngineComponents* m_EngineComponents;

#if defined(T2R)
	NxAppHooks m_NxAppHooks{};
#elif defined(T1X)
	MidHook m_PrimServer_CreateHook{};
#endif

	friend class IAllocator;
};
}