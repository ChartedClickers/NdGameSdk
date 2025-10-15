#pragma once
#include "NdGameSdk/components/SdkRegenny.hpp"

#include <NdGameSdk/shared/src/corelib/memory/memory-map.hpp>

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/ndlib/script/ModuleInfo.hpp>
#elif defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/ndlib/script/ModuleInfo.hpp>
#endif

#include <Utility/helper.hpp>
#include <Utility/function_ptr.hpp>

#include "script-module.hpp"

namespace NdGameSdk::ndlib::script {

	class LookupDcEntry;

	class NdGameSdk_API ModuleInfo : public ISdkRegenny<regenny::shared::ndlib::script::ModuleInfo> 
	{
	public:
		ModuleInfo(char* moduleName) {
			auto* self = Get();
			self->m_name = moduleName;
			self->m_hash = ToStringId64(moduleName);
		}

		std::string GetModuleName() const;
		StringId64 GetModuleId() const;
		size_t GetModuleSize() const;
		bool IsDebugModule() const;
		bool IsLocal() const;
		bool IsLoaded() const;
		ScriptModule* GetScriptModule() const;

		bool FetchModule(MemoryContextType pContext) const;

		ModuleInfo* NextModule() { return reinterpret_cast<ModuleInfo*>(this->Get()->m_NextModule); }
		const ModuleInfo* NextModule() const { return reinterpret_cast<const ModuleInfo*>(this->Get()->m_NextModule); }

		ModuleInfo* PrevModule() { return reinterpret_cast<ModuleInfo*>(this->Get()->m_PrevModule); }
		const ModuleInfo* PrevModule() const { return reinterpret_cast<const ModuleInfo*>(this->Get()->m_PrevModule); }

		static bool FetchModule(StringId64 pModuleId, MemoryContextType pContext);
		static ModuleInfo* LookupModuleByDcEntry(StringId64 pTypeid, StringId64 pScriptId);
	};

	// If module exist in the FileSystem
#if defined(T1X)
	TYPEDEF_EXTERN_FUNCTION_PTR(bool, ModuleInfo_FetchModule, StringId64 pModuleId, MemoryContextType pContext, uint64_t arg3, MemoryContextType arg4);
#else
	TYPEDEF_EXTERN_FUNCTION_PTR(bool, ModuleInfo_FetchModule, StringId64 pModuleId);
#endif
	TYPEDEF_EXTERN_FUNCTION_PTR(ModuleInfo*, ModuleInfo_LookupModuleByDcEntry, StringId64 pTypeid, StringId64 pScriptId);

#if defined(T2R)
	static_assert(sizeof(ModuleInfo) == 0x70, "Size of ModuleInfo is not correct.");
#elif defined(T1X)
	static_assert(sizeof(ModuleInfo) == 0x60, "Size of ModuleInfo is not correct.");
#endif

}