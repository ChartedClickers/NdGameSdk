#pragma once

#include <filesystem>
#include <windows.h>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/ansicolor_sink.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/basic_file_sink.h>

#include <NdGameSdk/sdk.hpp>
#include <NdGameSdk/components/SdkModule.hpp>

#include "config.hpp"

using namespace NdGameSdk;

class NdTestModule : public ISdkModule {

public:
	NdTestModule(HMODULE ndgame_module);

	virtual ~NdTestModule();

private:

	void OnModuleRegistered() override;

	HMODULE m_ndgame_module{};

};

extern std::unique_ptr<NdTestModule> g_ndtestmodule;