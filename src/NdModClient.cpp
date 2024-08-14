#include "NdModClient.hpp"

#include <NdGameSdk/sdk.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include <NdGameSdk/shared/src/ndlib/engine-components.hpp>
#include <NdGameSdk/shared/src/common/common-game-init.hpp>

using namespace std;
using namespace Utils;

std::unique_ptr<NdModClient> g_ndmodclient{};

NdModClient::NdModClient(HMODULE ndgame_module) :
	m_ndgame_module{ ndgame_module }, ISdkModule(PROJECT_NAME, get_this_dll_handle()) {

	auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
	auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(PROJECT_LOG_PATH, false);

	Logger::InitSpdLogConsoleSink(*console_sink.get());
	Logger::InitSpdLogFileSink(*file_sink.get());

	spdlog::sinks_init_list sink_list = { console_sink, file_sink };

	m_logger = std::make_shared<spdlog::logger>(GetModuleName(), sink_list);
	spdlog::register_logger(m_logger);
	spdlog::set_default_logger(m_logger);
	spdlog::flush_on(level::debug);
};

NdModClient::~NdModClient() {
	spdlog::info("{:s} shutting down...", GetModuleName());
}

bool NdModClient::Initialize() {
	if (m_initialized) {
		return true;
	}

	std::thread init_thread([this]() {
		std::scoped_lock _{ this->m_startup_mutex };

		try {
			m_ndmods = std::make_unique<NdMods>();
			m_ndmods->InitializeNdMods();
		}
		catch (const std::exception ex) {
			spdlog::error("Initialization of mods failed. Reason: {}", ex.what());
		}
		catch (...) {
			spdlog::error("Unknow exception occurred during NdMods initialization");
		}

		m_ndmods_initialized = true;
		});

	init_thread.detach();

	return m_initialized = true;
}

void NdModClient::OnModuleRegistered() {
	m_EngineComponents = GetSharedSdkComponent<ndlib::EngineComponents>().get();
	m_CommonGame = GetSharedSdkComponent<common::CommonGame>().get();
}

void NdModClient::OnMemoryMapped(corelib::memory::Memory* Memory) {
	spdlog::info("MemoryMapped!");
}

void NdModClient::OnGameInitialized(bool status) {
	spdlog::info("GAME initialized!");
	spdlog::info("BUILD: {}", m_EngineComponents->GetGameInfo()->BranchName);

	auto user = m_EngineComponents->GetGameInfo()->DiscUser;
	strcpy(user, "ALEXA DESPACITO");
}

void NdModClient::OnAppendSdkDevMenu(gamelib::debug::NdDevMenu* NdDevMenu, 
	gamelib::debug::NdDevMenu::AppendSdkDevMenuCallback AppendSdkDevMenu) {

	// We can create our menus here and also will broadcast this event to our NdMods.
	spdlog::info("OnAppendSdkDevMenu by {}!", NdDevMenu->GetName());

	// it's Invokes a private method from the NdDevMenu component that will create ItemSubmenu for our menus!
	AppendSdkDevMenu(nullptr);
}
