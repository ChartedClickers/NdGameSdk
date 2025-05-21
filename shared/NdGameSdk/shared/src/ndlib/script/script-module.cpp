#include "script-module.hpp"
#include "module-info.hpp"

namespace NdGameSdk::ndlib::script {

	std::string ScriptModule::GetModuleName() const {
		return this->Get()->m_ModuleName;
	}

	StringId64 ScriptModule::GetModuleId() const {
		return this->Get()->m_modulehash;
	}

	ScriptModule* ScriptModule::NextScriptModule() const {
		return reinterpret_cast<ScriptModule*>(this->Get()->m_NextModule);
	}

	ScriptModule* ScriptModule::PrevScriptModule() const {
		return reinterpret_cast<ScriptModule*>(this->Get()->m_PrevModule);
	}

	ModuleInfo* ScriptModule::GetModuleInfo() const {
		return reinterpret_cast<ModuleInfo*>(this->Get()->m_ModuleInfo);
	}

	MemoryContextType ScriptModule::GetMemoryContext() const {
		return this->Get()->m_moduleMemContext;
	}

	uint32_t ScriptModule::GetNumEntries() const {
		return this->Get()->m_numEntries;
	}

	double ScriptModule::GetLoadTimeSec() const {
		return *reinterpret_cast<const double*>(&this->Get()->m_loadtime);
	}

	dc::Header* ScriptModule::DcHeader() {
		return reinterpret_cast<dc::Header*>(this->Get()->m_header);
	}

	dc::EntryRange ScriptModule::DcEntries() {
		return dc::EntryRange(DcHeader());
	}

	ScriptModule* ScriptModule::GetNextModule(std::size_t index) {
		auto* cur = this->NextScriptModule();
		for (std::size_t i = 0; cur && i < index; ++i) {
			cur = cur->NextScriptModule();
		}
		return cur;
	}

	ModuleRequest* ModuleRequest::NextModuleRequest() const {
		return reinterpret_cast<ModuleRequest*>(this->Get()->m_NextModuleRequest);
	}

	ModuleRequest* ModuleRequest::PrevModuleRequest() const {
		return reinterpret_cast<ModuleRequest*>(this->Get()->m_PrevModuleRequest);
	}

	StringId64 ModuleRequest::GetModuleRequestId() const {
		return this->Get()->m_hash;
	}

	size_t ModuleRequest::GetSize() const {
		return this->Get()->m_size;
	}

	MemoryContextType ModuleRequest::GetMemoryContext() const {
		return this->Get()->m_MemContext;
	}

	INIT_FUNCTION_PTR(ScriptModule_FetchScriptModuleEntry);
}