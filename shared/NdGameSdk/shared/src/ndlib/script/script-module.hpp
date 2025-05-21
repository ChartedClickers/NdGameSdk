#pragma once
#include "NdGameSdk/components/SdkRegenny.hpp"

#include <NdGameSdk/shared/src/corelib/memory/memory-map.hpp>

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/ndlib/script/ScriptModule.hpp>
#include <NdGameSdk/regenny/t2r/shared/ndlib/script/ModuleRequest.hpp>
#elif defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/ndlib/script/ScriptModule.hpp>
#include <NdGameSdk/regenny/t1x/shared/ndlib/script/ModuleRequest.hpp>
#endif

#include "dc/data-compilation.hpp"

#include <Utility/helper.hpp>
#include <Utility/function_ptr.hpp>

namespace NdGameSdk::ndlib::script {

    class ModuleInfo;

    class NdGameSdk_API ScriptModule : public ISdkRegenny<regenny::shared::ndlib::script::ScriptModule> 
    {
    public:

        std::string GetModuleName() const;
		StringId64 GetModuleId() const;
        uint32_t GetNumEntries() const;
        double GetLoadTimeSec() const;

        ScriptModule* NextScriptModule() const;
        ScriptModule* PrevScriptModule() const;

		ModuleInfo* GetModuleInfo() const;
		MemoryContextType GetMemoryContext() const;

        // Return the embedded DC header as the strongly-typed wrapper.
        dc::Header* DcHeader();

        // Get the i-th DC entry as Entry<Data>. Returns nullptr if OOB / no hdr.
        template<class Data = void>
        dc::Entry<Data>* DcEntry(std::size_t i = 0) {
            auto* h = DcHeader();
            return h ? h->GetEntry<Data>(i) : nullptr;
        }

        // Directly fetch the i-th payload pointer, already cast to Data*.
        template<class Data = void>
        Data* DcPayload(std::size_t i = 0) {
            auto* e = DcEntry<>(i);
            return e ? reinterpret_cast<Data*>(e->GetEntryPtr()) : nullptr;
        }

        // Range-for support over all DC entries in this module.
        dc::EntryRange DcEntries();

        ScriptModule* GetNextModule(std::size_t index = 0);
    };

    class NdGameSdk_API ModuleRequest : public ISdkRegenny<regenny::shared::ndlib::script::ModuleRequest> 
    {
    public:
        ModuleRequest* NextModuleRequest() const;
        ModuleRequest* PrevModuleRequest() const;

		StringId64 GetModuleRequestId() const;
        size_t GetSize() const;
		MemoryContextType GetMemoryContext() const;

        struct ModuleRequestRange {
            struct iterator {
                ModuleRequest* cur;
                iterator(ModuleRequest* c) : cur(c) {}
                bool operator!=(iterator const& o) const { return cur != o.cur; }
                ModuleRequest* operator*() const { return cur; }
                iterator& operator++() {
                    cur = cur ? cur->NextModuleRequest() : nullptr;
                    return *this;
                }
            };
            ModuleRequest* head;
            size_t size() const {
                size_t count = 0;
                for (auto* cur = head; cur; cur = cur->NextModuleRequest()) {
                    ++count;
                }
                return count;
            }
            iterator begin() const { return { head }; }
            iterator end() const { return { nullptr }; }
        };

        ModuleRequestRange GetNextModuleRequestsRange() const {
            return { this->NextModuleRequest() };
        }

    };

    TYPEDEF_EXTERN_FUNCTION_PTR(void*, ScriptModule_FetchScriptModuleEntry, ScriptModule* scriptmodule, StringId64 scriptid);
    
    /*
    * TYPEDEF_EXTERN_FUNCTION_PTR(bool, ScriptModule_Login, struct ScriptManager::ScriptModule* module);
    */

    static_assert(sizeof(ScriptModule) == 0x70, "Size of ScriptModule is not correct.");
    static_assert(sizeof(ModuleRequest) == 0x40, "Size of ModuleRequest is not correct.");

}