#include "sdklogger.hpp"
#include "sdkconst.hpp"

namespace NdGameSdk {

	SdkLogger::SdkLogger(std::string name, std::string log_path, spdlog::level::level_enum log_level)
	{
		auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
		auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(log_path, true);

		spdlog::sinks_init_list sink_list = { console_sink, file_sink };

		m_logger = std::make_shared<logger>(name, sink_list);
		register_logger(m_logger);
		flush_on(log_level);
		set_level(log_level);
	}

	std::shared_ptr<logger> SdkLogger::GetLogger()
	{
		static SdkLogger sdklogger{ SDK_NAME, SDK_LOG_PATH,  
		#if NDEBUG
		level::info
		#else
		level::debug
		#endif
		};

		return sdklogger.m_logger;
	}

	std::shared_ptr<sinks::basic_file_sink_mt> SdkLogger::LinkFileSink(logger& plogger)
	{
		auto sdklogger = SdkLogger::GetLogger();

		auto sinks = plogger.sinks();
		auto filesink = std::find_if(sinks.begin(), sinks.end(), 
			[](const spdlog::sink_ptr& sink)
			{
				auto file_sink =
					std::dynamic_pointer_cast<spdlog::sinks::basic_file_sink_mt>(sink);
				return static_cast<bool>(file_sink);
			});

		if (filesink != sinks.end()) {
			sdklogger->sinks().push_back(*filesink);
			return std::dynamic_pointer_cast<spdlog::sinks::basic_file_sink_mt>(*filesink);
		}

		return nullptr;
	}

	bool SdkLogger::UnlinkFileSink(logger& plogger)
	{
		auto sdklogger = SdkLogger::GetLogger();

		auto sinks = plogger.sinks();
		auto filesink = std::find_if(sinks.begin(), sinks.end(),
			[](const spdlog::sink_ptr& sink)
			{
				auto file_sink =
					std::dynamic_pointer_cast<spdlog::sinks::basic_file_sink_mt>(sink);
				return static_cast<bool>(file_sink);
			});

		if (filesink != sinks.end()) {
			return std::erase_if(sdklogger->sinks(),
				[filesink](const spdlog::sink_ptr& sink)
				{
					return sink == *filesink;
				}) > 0;
		}

		return false;
	}
}