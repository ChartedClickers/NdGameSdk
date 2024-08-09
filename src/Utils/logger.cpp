#include "logger.hpp"
#include "config.hpp"

namespace Utils {

	bool Logger::InitConsole()
	{
		if (g_bShowDebugConsole && AllocConsole()) {
			SetConsoleTitleA(ND_GAME_NAME " - Debug Console");
			freopen_s(reinterpret_cast<FILE**>(stdin), "conin$", "r", stdin);
			freopen_s(reinterpret_cast<FILE**>(stdout), "conout$", "w", stdout);
			freopen_s(reinterpret_cast<FILE**>(stderr), "conout$", "w", stderr);
			::ShowWindow(GetConsoleWindow(), SW_SHOW);

			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			DWORD dwMode = 0;
			GetConsoleMode(hConsole, &dwMode);
			printf_s("dwMode: 0x08%x\n", dwMode);

			// enable ansi color formatting
			dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
			printf_s("dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING: 0x08%x\n", dwMode);
			SetConsoleMode(hConsole, dwMode);
			printf_s("The console has been successfully initialized\n");
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
