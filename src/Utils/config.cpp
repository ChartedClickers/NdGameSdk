#include "config.hpp"
#include "logger.hpp"

#include <Utility/assertion/assert.hpp>
#include <string>

// Global INI Variables
#if NDEBUG
bool g_bShowDebugConsole{false};
#else
bool g_bShowDebugConsole{true};
#endif
	
namespace Utils {

	Config::Config(const std::string& config_path) : m_configpath { config_path }  {
		m_ini.SetUnicode();
		SI_Error rc = m_ini.LoadFile(config_path.c_str());
		m_isloaded = rc >= SI_OK;
	}

	bool Config::InitDefaultConfig() {
		CSimpleIniA ini{};
		ini.SetUnicode();
		auto config_path = PROJECT_INI_PATH;
		SI_Error rc = ini.LoadFile(config_path);

		if (rc < SI_OK)
		{
			g_bShowDebugConsole = true;
			Utils::Logger::InitConsole();

			if (rc > SI_FILE) {
				spdlog::error("Failed to load config {}", config_path);
				return false;
			}

			// no ini, lets generate one.
			SetDefaultValues(ini);

			rc = ini.SaveFile(config_path);
			if (rc < SI_OK)
			{
				spdlog::error("Failed to Created default config {}", config_path);
				return false;
			}

			spdlog::info("Created default config {}", config_path);
		}
		else {
			g_bShowDebugConsole = ini.GetBoolValue(PROJECT_NAME, "bShowDebugConsole", g_bShowDebugConsole);
		}

		return true; 
	}

	void Config::SetDefaultValues(CSimpleIniA& Ini)
	{
		Ini.SetBoolValue(PROJECT_NAME, "bShowDebugConsole", g_bShowDebugConsole);

		Ini.SetBoolValue(PROJECT_SDK, "btest", true);
	}

	void Config::LogConfigParse()
	{
		std::ostringstream oss{};
		CSimpleIniA::TNamesDepend sections;

		m_ini.GetAllSections(sections);
		for (auto& section : sections) {
			CSimpleIniA::TNamesDepend keys;
			oss << std::format("[{}]\n", section.pItem);

			m_ini.GetAllKeys(section.pItem, keys);
			for (auto& key : keys) {
				oss << std::format("{}: {}\n", key.pItem,
					m_ini.GetValue(section.pItem, key.pItem));
			}

			oss << "\n";
		}

		spdlog::info("Config: \n{}", oss.str());
	}

	bool Config::Save() {
		return m_ini.SaveFile(m_configpath.c_str()) >= SI_OK;
	}

	bool Config::IsLoaded() {
		return m_isloaded;
	}

	bool Config::IsSectionExists(const std::string& section) {
		return m_ini.SectionExists(section.c_str());
	}
}
