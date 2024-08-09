#include <memory>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/ansicolor_sink.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/basic_file_sink.h>

using namespace spdlog;

namespace NdGameSdk {
    class SdkLogger {
    public:
        static std::shared_ptr<logger> GetLogger();
        static std::shared_ptr<sinks::basic_file_sink_mt> LinkFileSink(logger& plogger);
        static bool UnlinkFileSink(logger& plogger);
    private:
        SdkLogger(std::string name, std::string log_path, level::level_enum log_level = spdlog::level::info);
        std::shared_ptr<logger> m_logger{};
    };
}