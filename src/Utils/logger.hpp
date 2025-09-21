#include <filesystem>

#include <spdlog/spdlog.h>
#include <spdlog/common.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/ansicolor_sink.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/basic_file_sink.h>

#include <Utility/system/console.hpp>

namespace Utils {

	using namespace spdlog;
	using namespace spdlog::sinks;

	static class Logger {
	public:
		static bool InitConsole();
		static void InitSpdLogConsoleSink(stdout_color_sink_mt& wincolor);
		static void InitSpdLogFileSink(basic_file_sink_mt& filesink);
	};

}