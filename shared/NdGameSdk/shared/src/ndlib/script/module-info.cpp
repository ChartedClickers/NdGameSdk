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

	LookupDcEntry* ModuleInfo::LookupDcEntry(script::LookupDcEntry* pLookupDcEntry, StringId64 pScriptId, StringId64 pTypeid) {
		always_assert(ModuleInfo_LookupDcEntry == nullptr, "Function pointer was not set!");
		return ModuleInfo_LookupDcEntry(pLookupDcEntry, pScriptId, pTypeid);
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

	INIT_FUNCTION_PTR(ModuleInfo_FetchModule);
	INIT_FUNCTION_PTR(ModuleInfo_LookupModuleByDcEntry);
	INIT_FUNCTION_PTR(ModuleInfo_LookupDcEntry);
}