#include "SdkModule.hpp"

namespace NdGameSdk {

	class ISdkModule;

	ISdkModule::ISdkModule(std::string name) 
		: m_name{ name }, m_module{ Utility::memory::get_this_dll_handle() } {}

	ISdkModule::~ISdkModule() {
		e_OnUnregister.Invoke(this);
	}

	std::string ISdkModule::GetModuleName() {
		return m_name;
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

			throw SdkModuleException("Module " + get_module_name(ActionModule).value_or("UNKNOW") + "is not registered in SDK!",
				SdkModuleException::ErrorCode::NotRegistered);
		}

		return nullptr;
	}

	std::unordered_map<HMODULE, ISdkModule*>* ISdkModule::GetSdkModules() {
		return &s_SdkModules;
	}

	std::unordered_map<HMODULE, ISdkModule*> ISdkModule::s_SdkModules{};
}