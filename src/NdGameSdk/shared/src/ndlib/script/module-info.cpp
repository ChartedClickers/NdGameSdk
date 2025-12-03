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

	bool ModuleInfo::IsLocal() const {
		return this->Get()->m_IsLocal;
	}

	bool ModuleInfo::IsLoaded() const {
		return this->Get()->m_isLoaded;
	}

	ScriptModule* ModuleInfo::GetScriptModule() const {
		return reinterpret_cast<ScriptModule*>(this->Get()->m_ScriptModule);
	}

	bool ModuleInfo::FetchModule(MemoryContextType pContext) const {
		return FetchModule(this->GetModuleId(), pContext);
	}

	bool ModuleInfo::FetchModule(StringId64 pModuleId, MemoryContextType pContext) {
		always_assert(ModuleInfo_FetchModule == nullptr, "Function pointer was not set!");
	#if defined(T1X)
		return ModuleInfo_FetchModule(pModuleId, pContext, 0, pContext);
	#else
		return ModuleInfo_FetchModule(pModuleId);
	#endif
	}

	ModuleInfo* ModuleInfo::LookupModuleByDcEntry(StringId64 pTypeid, StringId64 pScriptId) {
		always_assert(ModuleInfo_LookupModuleByDcEntry == nullptr, "Function pointer was not set!");
		return ModuleInfo_LookupModuleByDcEntry(pTypeid, pScriptId);
	}

	INIT_FUNCTION_PTR(ModuleInfo_FetchModule);
	INIT_FUNCTION_PTR(ModuleInfo_LookupModuleByDcEntry);
}