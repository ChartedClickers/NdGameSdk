#pragma once

#include <filesystem>
#include <windows.h>

#include <NdGameSdk/sdk.hpp>
#include <NdGameSdk/components/SdkModule.hpp>

#include <NdGameSdk/shared/src/common/common-game-init.hpp>
#include <NdGameSdk/shared/src/ndlib/engine-components.hpp>

#if defined(T1X)
#include <NdGameSdk/shared/src/corelib/memory/memory.hpp>
#endif

#include "Utils/config.hpp"
#include "Utils/logger.hpp"

#include "NdModClientException.hpp"
#include "NdMods.hpp"

using namespace NdGameSdk;

class NdMods;

class NdModClient : public ISdkModule {

public:
	NdModClient(HMODULE ndgame_module);
	virtual ~NdModClient();

	bool Initialize();
	bool is_ready() const { return m_initialized && m_ndmods_initialized; }
	const auto& GetNdMods() const { return m_ndmods; }
private:

	void OnModuleRegistered() override;
	void OnGameInitialized(bool status) override;
	#if defined(T1X)
	void OnMemoryMapped(corelib::memory::Memory* Memory) override;
	void OnAppendSdkDevMenu(gamelib::debug::NdDevMenu* NdDevMenu, gamelib::debug::NdDevMenu::AppendSdkSubMenusCallback AppendSdkDevMenu) override;
	#endif

	bool m_initialized{false};
	std::atomic<bool> m_ndmods_initialized{ false };

	ndlib::EngineComponents* m_EngineComponents;
	common::CommonGame* m_CommonGame;

	std::unique_ptr<NdMods> m_ndmods;
	std::recursive_mutex m_startup_mutex{};

	HMODULE m_ndgame_module{};
};

extern std::unique_ptr<NdModClient> g_ndmodclient;