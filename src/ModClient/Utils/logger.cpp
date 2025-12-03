#include "logger.hpp"
#include "config.hpp"

namespace Utils {

	bool Logger::InitConsole()
	{
		if (g_bShowDebugConsole && Utility::sys::AllocConsole()) {
			SetConsoleTitleA(ND_GAME_NAME " - Debug Console");
			::ShowWindow(GetConsoleWindow(), SW_SHOW);
			return true;
		}

		return false;
	}

	void Logger::InitSpdLogConsoleSink(stdout_color_sink_mt& wincolor)
	{
		#if NDEBUG
		auto log_level = level::info;
		#else
		auto log_level = level::debug;
		#endif

		wincolor.set_color_mode(spdlog::color_mode::always);
		wincolor.set_level(log_level);
		//wincolor.set_color(level::level_enum::info, FOREGROUND_BLUE);
	}

	void Logger::InitSpdLogFileSink(basic_file_sink_mt& filesink)
	{
		#if NDEBUG
		auto log_level = level::info;
		#else
		auto log_level = level::debug;
		#endif

		filesink.set_level(log_level);
	}
}
