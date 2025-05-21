#pragma once
#include "NdGameSdk/components/SdkRegenny.hpp"

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/ndlib/script/ModuleInfo.hpp>
#include <NdGameSdk/regenny/t2r/shared/ndlib/script/LookupDcEntry.hpp>
#elif defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/ndlib/script/ModuleInfo.hpp>
#include <NdGameSdk/regenny/t1x/shared/ndlib/script/LookupDcEntry.hpp>
#endif

#include <Utility/helper.hpp>
#include <Utility/function_ptr.hpp>

#include "script-module.hpp"

namespace NdGameSdk::ndlib::script {

	class NdGameSdk_API ModuleInfo : public ISdkRegenny<regenny::shared::ndlib::script::ModuleInfo> 
	{
	public:
		std::string GetModuleName() const;
		StringId64 GetModuleId()   const;
		size_t GetModuleSize() const;
		bool IsDebugModule() const;
		ScriptModule* GetScriptModule() const;

		ModuleInfo* NextModule() { return reinterpret_cast<ModuleInfo*>(this->Get()->m_NextModule); }
		const ModuleInfo* NextModule() const { return reinterpret_cast<const ModuleInfo*>(this->Get()->m_NextModule); }

		ModuleInfo* PrevModule() { return reinterpret_cast<ModuleInfo*>(this->Get()->m_PrevModule); }
		const ModuleInfo* PrevModule() const { return reinterpret_cast<const ModuleInfo*>(this->Get()->m_PrevModule); }

	};

	class NdGameSdk_API LookupDcEntry : public ISdkRegenny<regenny::shared::ndlib::script::LookupDcEntry> {
	public:
		LookupDcEntry() = default;

		template<typename T>
		T* GetEntry() {
			auto DcEntryPtr = this->Get()->m_entryPtr;
			return reinterpret_cast<T*>(DcEntryPtr);
		}

		ModuleInfo* GetModule() const;
		StringId64 GetScriptId() const;
		StringId64 GetTypeId() const;
	};

	TYPEDEF_EXTERN_FUNCTION_PTR(ModuleInfo*, ModuleInfo_LookupModuleByDcEntry, StringId64 ptypeid, StringId64 pscriptId);
	TYPEDEF_EXTERN_FUNCTION_PTR(LookupDcEntry*, ModuleInfo_LookupDcEntry, LookupDcEntry* pLookupDcEntry, StringId64 pscriptId, StringId64 ptypeid);

	static_assert(sizeof(ModuleInfo) == 0x60, "Size of ModuleInfo is not correct.");
	static_assert(sizeof(LookupDcEntry) == 0x28, "Size of LookupDcEntry is not correct.");

}