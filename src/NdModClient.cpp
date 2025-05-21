#include <NdGameSdk/sdk.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include <NdGameSdk/shared/src/ndlib/engine-components.hpp>
#include <NdGameSdk/shared/src/common/common-game-init.hpp>

#include "NdModClient.hpp"

using namespace std;
using namespace Utils;

std::unique_ptr<NdModClient> g_ndmodclient{};

NdModClient::NdModClient(HMODULE ndgame_module) :
	m_ndgame_module{ ndgame_module }, ISdkModule(PROJECT_NAME, BuildInfo { BUILD_VERSION, BUILD_STAMP, "main", BUILD_MODE }, get_this_dll_handle()) {

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
	m_EngineComponents = GetSharedSdkComponent<ndlib::EngineComponents>();
	m_CommonGame = GetSharedSdkComponent<common::CommonGame>();
	m_DebugDraw = GetSharedSdkComponent<ndlib::render::dev::DebugDrawCommon>();
}

void NdModClient::OnGameInitialized(bool status) {
	spdlog::info("GAME initialized!");

	auto& gameconfig = m_EngineComponents->GetNdGameInfo();
	spdlog::info("BUILD: {}", gameconfig->m_BranchName);

}

void NdModClient::OnMemoryMapped(corelib::memory::Memory* Memory) {
	spdlog::info("MemoryMapped!");
}

void NdModClient::DebugDraw(FrameParams* frame) {
	/*
	WindowContext ctx{};
	WindowContext::GetWindowContext(&ctx, WindowContext::ContextType::Context4, frame->m_DynamicRenderContext);
	char print_text[256]{};
	_snprintf_s(print_text, sizeof(print_text), PROJECT_NAME);
	m_DebugDraw->TextPrintV(&ctx, { 50., 180., 0.8, 0.8 }, print_text);
	m_DebugDraw->PrimTextPrint({ 0.0f, 2.0f, 0.0f, 0.0f },Color(BasicColors::White), 1.0f, PROJECT_NAME);
	*/
}
