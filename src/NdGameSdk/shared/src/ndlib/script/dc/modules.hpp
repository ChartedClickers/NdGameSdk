#pragma once
#include "data-compilation.hpp"

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/ndlib/script/DC/modules/modules.hpp>
#elif defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/ndlib/script/DC/modules/modules.hpp>
#endif

namespace NdGameSdk::ndlib::script::dc {

	namespace DC {

		using modules_raw = ::regenny::shared::ndlib::script::DC::modules::modules;
		using ModuleUnkCollectionRaw = ::regenny::shared::ndlib::script::DC::modules::modules::ModuleUnkCollection;
		using ModuleCollectionRaw = ::regenny::shared::ndlib::script::DC::modules::modules::ModuleCollection;
		using ModuleInfoRaw = ::regenny::shared::ndlib::script::DC::modules::modules::ModuleInfo;
		using ModuleInfoArrayRaw = ::regenny::shared::ndlib::script::DC::modules::modules::ModuleInfoArray;

        struct NdGameSdk_API ModuleUnkCollection : public ISdkRegenny<ModuleUnkCollectionRaw> {
            std::size_t size() const { return this->Get()->m_num; }
            StringId64* data() { return this->Get()->m_pArray; }
            const StringId64* data() const { return this->Get()->m_pArray; }
            StringId64 operator[](std::size_t i) const { return data()[i]; }
        };

        struct NdGameSdk_API ModuleCollection : public ISdkRegenny<ModuleCollectionRaw> {
            std::size_t size() const { return this->Get()->m_num; }
            StringId64* data() { return this->Get()->m_modules; }
            const StringId64* data() const { return this->Get()->m_modules; }
            StringId64 operator[](std::size_t i) const { return data()[i]; }
        };

        struct NdGameSdk_API ModuleInfo : public ISdkRegenny<ModuleInfoRaw> {
            const char* name() const { return this->Get()->m_name; }
            StringId64 hash() const { return this->Get()->m_hash; }
            std::uint64_t sizeBytes() const { return this->Get()->m_size; }

            ModuleCollection* modules() { return reinterpret_cast<ModuleCollection*>(this->Get()->m_pCollection); }
            const ModuleCollection* modules() const { return reinterpret_cast<const ModuleCollection*>(this->Get()->m_pCollection); }

            ModuleUnkCollection* unknowns() { return reinterpret_cast<ModuleUnkCollection*>(this->Get()->m_unkCollection); }
            const ModuleUnkCollection* unknowns() const { return reinterpret_cast<const ModuleUnkCollection*>(this->Get()->m_unkCollection); }
        };

        struct NdGameSdk_API ModuleInfoArray : public ISdkRegenny<ModuleInfoArrayRaw> {
            std::size_t  size() const { return this->Get()->m_numModules; }

            DC::Array<ModuleInfo>* array() {
                return reinterpret_cast<DC::Array<ModuleInfo>*>(&this->Get()->m_modules);
            }
            const DC::Array<ModuleInfo>* array() const {
                return reinterpret_cast<const DC::Array<ModuleInfo>*>(&this->Get()->m_modules);
            }

            // STL‑style accessors
            ModuleInfo* data() { return reinterpret_cast<ModuleInfo*>(this->Get()->m_modules); }
            const ModuleInfo* data() const { return reinterpret_cast<const ModuleInfo*>(this->Get()->m_modules); }

            ModuleInfo& operator[](std::size_t i) { return data()[i]; }
            const ModuleInfo& operator[](std::size_t i) const { return data()[i]; }

            ModuleInfo* begin() { return data(); }
            ModuleInfo* end() { return data() + size(); }
            const ModuleInfo* begin() const { return data(); }
            const ModuleInfo* end()   const { return data() + size(); }
        };

        inline ModuleInfoArray* GetModuleInfoArray(Header& hdr) {
            for (RawEntry& e : Entries(hdr)) {
                if (e.GetTypeId() == DC::kModuleInfoArray)
                    return reinterpret_cast<ModuleInfoArray*>(e.GetEntryPtr());
            }
            return nullptr;
        }
	}

	static_assert(sizeof(DC::ModuleUnkCollection) == 0x10, "Size of ModuleUnkCollection is not correct.");
	static_assert(sizeof(DC::ModuleCollection) == 0x10, "Size of ModuleCollection is not correct.");
	static_assert(sizeof(DC::ModuleInfo) == 0x28, "Size of ModuleInfo is not correct.");
	static_assert(sizeof(DC::ModuleInfoArray) == 0x10, "Size of ModuleInfoArray is not correct.");

}