#pragma once
#include <SimpleIni.h>

#define wstr(s) L#s
#define wxstr(s) wstr(s)

#define PROJECT_NAME ND_GAME_NAME ".ModClient"
#define PROJECT_SDK ND_GAME_NAME "SDK"
#define PROJECT_LOG_PATH PROJECT_NAME ".log"
#define PROJECT_INI_PATH PROJECT_NAME ".ini"
#define BUILD_STAMP "Built: " __DATE__ " @ " __TIME__
#define BUILD_TIME PROJECT_NAME " " BUILD_STAMP

#if defined(T1X)
#define GAME_MODULE_NAME "tlou-i.exe"
#elif defined(T2R)
#define GAME_MODULE_NAME "tlou-ii.exe"
#endif

namespace Utils {
	class Config {
	public:
		Config(const std::string& config_path = PROJECT_INI_PATH);
		static bool InitDefaultConfig();
		static void SetDefaultValues(CSimpleIniA& Ini);
		void LogConfigParse();
		template<typename T = std::string>
		std::optional<T> get(const std::string& section, const std::string& key, T default_value = {}) const {
			if constexpr (std::is_same_v<T, bool>) {
				return m_ini.GetBoolValue(section.c_str(), key.c_str(), default_value);
			}
			else if (std::is_same_v<T, double>) {
				return m_ini.GetDoubleValue(section.c_str(), key.c_str(), default_value);
			}
			else if (std::is_same_v<T, long>) {
				return m_ini.GetLongValue(section.c_str(), key.c_str(), default_value);
			}
			else {
				return m_ini.GetValue(section.c_str(), key.c_str(), default_value);
			}
		};
		template<typename T = std::string>
		bool set(const std::string& section, const std::string& key, std::optional<T> value) {

			if (!value.has_value()) {
				return m_ini.Delete(section.c_str(), key.c_str(), true);
			}

			SI_Error rc{};

			if constexpr (std::is_same_v<T, bool>) {
				rc = m_ini.SetBoolValue(section.c_str(), key.c_str(), value.value());
			}
			else if (std::is_same_v<T, double>) {
				rc = m_ini.SetDoubleValue(section.c_str(), key.c_str(), value.value());
			}
			else if (std::is_same_v<T, long>) {
				rc = m_ini.SetLongValue(section.c_str(), key.c_str(), value.value());
			}
			else {
				rc = m_ini.SetValue(section.c_str(), key.c_str(), value.value());
			}

			return rc >= SI_OK;
		};
		bool Save();
		bool IsLoaded();
		bool IsSectionExists(const std::string& section);
	private:
		CSimpleIniA m_ini{};
		std::string m_configpath;
		bool m_isloaded{};
	};
}

extern bool g_bShowDebugConsole;
