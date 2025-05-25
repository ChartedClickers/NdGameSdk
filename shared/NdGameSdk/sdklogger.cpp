#include "sdklogger.hpp"
#include "sdkconst.hpp"

namespace NdGameSdk {

	SdkLogger::SdkLogger(const std::string& name, const std::string& log_path, level::level_enum log_level) {
		auto console_sink = std::make_shared<sinks::stdout_color_sink_mt>();
		auto file_sink = std::make_shared<sinks::basic_file_sink_mt>(log_path, true);
		s_sinks = { console_sink, file_sink };

		sinks_init_list sink_list{ console_sink, file_sink };
		m_logger = std::make_shared<logger>(name, sink_list);
		register_logger(m_logger);

		m_logger->set_level(log_level);
		m_logger->flush_on(log_level);
	}

	std::shared_ptr<logger> SdkLogger::GetLogger()
	{
		static SdkLogger sdklogger{ SDK_NAME, SDK_LOG_PATH,  
		#if !SDK_DEBUG
		level::info
		#else
		level::debug
		#endif
		};

		return sdklogger.m_logger;
	}

	std::shared_ptr<logger> SdkLogger::GetNdGameLogger()
	{
		auto def = GetLogger();

		if (!s_ndgameLogger) {
			s_ndgameLogger = std::make_shared<logger>(
				ND_GAME_NAME,
				s_sinks.begin(),
				s_sinks.end()
			);
			s_ndgameLogger->set_level(def->level());
			s_ndgameLogger->flush_on(def->flush_level());
			register_logger(s_ndgameLogger);
		}

		return s_ndgameLogger;
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

	std::vector<sink_ptr> SdkLogger::s_sinks;
	std::shared_ptr<logger> SdkLogger::s_ndgameLogger = nullptr;
}