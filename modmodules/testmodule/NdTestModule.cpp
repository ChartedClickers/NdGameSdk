#include "NdTestModule.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include <NdGameSdk/sdk.hpp>
#include <NdGameSdk/shared/src/ndlib/engine-components.hpp>
#include <NdGameSdk/shared/src/common/common-game-init.hpp>

using namespace std;

std::unique_ptr<NdTestModule> g_ndtestmodule{};

NdTestModule::NdTestModule(HMODULE ndgame_module) :
	m_ndgame_module { ndgame_module },
	ISdkModule(PROJECT_NAME) {

	auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

	(*console_sink.get()).set_color_mode(spdlog::color_mode::always);

	spdlog::sinks_init_list sink_list = { console_sink };

	m_logger = std::make_shared<spdlog::logger>(PROJECT_NAME, begin(sink_list), end(sink_list));
	spdlog::register_logger(m_logger);
	spdlog::set_default_logger(m_logger);
	spdlog::flush_on(spdlog::level::info);

};

NdTestModule::~NdTestModule() {

}

void NdTestModule::OnModuleRegistered() {

}
