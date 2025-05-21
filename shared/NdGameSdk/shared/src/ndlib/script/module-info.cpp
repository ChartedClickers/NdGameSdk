#include "module-info.hpp"

namespace NdGameSdk::ndlib::script {

	std::string ModuleInfo::GetModuleName() const {
		return this->Get()->m_name;
	}

	StringId64 ModuleInfo::GetModuleId() const {
		return this->Get()->m_hash;
	}

	size_t ModuleInfo::GetModuleSize() const {
		return this->Get()->m_size;
	}

	bool ModuleInfo::IsDebugModule() const {
		return this->Get()->m_DebugModule;
	}

	ScriptModule* ModuleInfo::GetScriptModule() const {
		return reinterpret_cast<ScriptModule*>(this->Get()->m_ScriptModule);
	}

	ModuleInfo* LookupDcEntry::GetModule() const {
		return reinterpret_cast<ModuleInfo*>(this->Get()->m_module);
	}

	StringId64 LookupDcEntry::GetScriptId() const {
		return this->Get()->m_scriptId;
	}

	StringId64 LookupDcEntry::GetTypeId() const{
		return this->Get()->m_typeId;
	}

	INIT_FUNCTION_PTR(ModuleInfo_LookupModuleByDcEntry);
	INIT_FUNCTION_PTR(ModuleInfo_LookupDcEntry);
}