#include "SdkModule.hpp"

namespace NdGameSdk {

	class ISdkModule;

	uint32_t ISdkModule::BuildInfo::toUInt() const noexcept {
		return (uint32_t(major) << 24)
			| (uint32_t(minor) << 16)
			| (uint32_t(patch) << 8);
	}

	std::string ISdkModule::BuildInfo::versionString() const {
		return std::to_string(major) + "."
			+ std::to_string(minor) + "."
			+ std::to_string(patch);
	}

	std::string ISdkModule::BuildInfo::toString() const {
		std::ostringstream ss;
		ss << versionString();

		if (gitBranch != "main" && !gitBranch.empty()) {
			ss << " @" << gitBranch;
		}

		ss << " [" << buildMode << "]" << " (" << buildStamp << ")";
		return ss.str();
	}

	ISdkModule::ISdkModule(std::string name, BuildInfo buildinfo, HMODULE module) : m_name{ name }, m_build{ buildinfo }, m_module { module } {}

	ISdkModule::~ISdkModule() {
		e_OnUnregister.Invoke(this);
	}

	std::string ISdkModule::GetModuleName() {
		return m_name;
	}

	std::string ISdkModule::GetBuildInfoString() const {
		std::ostringstream oss;
		oss << m_name << " " << m_build.toString();
		return oss.str();
	}

	HMODULE ISdkModule::GetModule() {
		return m_module;
	}

	bool ISdkModule::IsRegistered() {
		return m_registered;
	}

	ISdkModule* ISdkModule::GetRegisteredModule(HMODULE ActionModule) {
		if (ActionModule != g_SdkModuleHandle) {
			auto SdkModules = GetSdkModules();
			auto SdkModule = SdkModules->find(ActionModule);
			if (SdkModule != SdkModules->end()) {
				return SdkModule->second;
			}

                        throw SdkModuleException("Module " + get_module_name(ActionModule).value_or("UNKNOWN") + "is not registered in SDK!",
                                SdkModuleException::ErrorCode::NotRegistered);
		}

		return nullptr;
	}

	std::unordered_map<HMODULE, ISdkModule*>* ISdkModule::GetSdkModules() {
		return &s_SdkModules;
	}

	std::unordered_map<HMODULE, ISdkModule*> ISdkModule::s_SdkModules{};
}