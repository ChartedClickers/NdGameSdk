#pragma once
#include "NdGameSdk/components/SdkRegenny.hpp"

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/ndlib/script/DC/Header.hpp>
#include <NdGameSdk/regenny/t2r/shared/ndlib/script/DC/Entry.hpp>
#elif defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/ndlib/script/DC/Header.hpp>
#include <NdGameSdk/regenny/t1x/shared/ndlib/script/DC/Entry.hpp>
#endif

namespace NdGameSdk::ndlib::script::dc {
	
	template<class Data = void>
	struct NdGameSdk_API Entry : public ISdkRegenny<regenny::shared::ndlib::script::DC::Entry>
	{
		using DataType = Data;

        StringId64 GetScriptId() const { return this->Get()->m_scriptId; }
        StringId64 GetTypeId() const { return this->Get()->m_typeId; }

		Data* GetEntryPtr() const {
			return reinterpret_cast<Data*>(this->Get()->m_entryPtr);
		}
	};

	using RawEntry = Entry<void>;

	struct NdGameSdk_API Header : public ISdkRegenny<regenny::shared::ndlib::script::DC::Header>
	{
        uint32_t GetNumEntries() const {
            return this->Get()->m_numEntries;
        };

		size_t GetSize() const {
			return this->Get()->m_textSize;
		};

		template<class Data = void>
		Entry<Data>* GetEntry(std::size_t index) const {
			if (index >= GetNumEntries()) return nullptr;
			auto base = reinterpret_cast<RawEntry*>(this->Get()->m_pStartOfData);
			return reinterpret_cast<Entry<Data>*>(base + index);
		}
	};

    class EntryRange {
    public:
        struct iterator {
            using value_type = RawEntry;
            using difference_type = std::ptrdiff_t;
            using pointer = RawEntry*;
            using reference = RawEntry&;
            using iterator_category = std::forward_iterator_tag;

            explicit iterator(pointer p) : cur(p) {}
            reference operator*()  const { return *cur; }
            pointer   operator->() const { return  cur; }
            iterator& operator++() { ++cur; return *this; }
            iterator  operator++(int) { auto tmp = *this; ++(*this); return tmp; }
            bool operator!=(const iterator& o) const { return cur != o.cur; }
        private:
            pointer cur{};
        };

        explicit EntryRange(Header* h)
        {
            if (h && h->Get()) {
                beginPtr_ = reinterpret_cast<RawEntry*>(h->Get()->m_pStartOfData);
                endPtr_ = beginPtr_ + h->GetNumEntries();
            }
        }

        iterator begin() const { return iterator(beginPtr_); }
        iterator end()   const { return iterator(endPtr_); }
        std::size_t size() const { return static_cast<std::size_t>(endPtr_ - beginPtr_); }
        bool empty() const { return beginPtr_ == endPtr_; }

    private:
        RawEntry* beginPtr_{};
        RawEntry* endPtr_{};
    };

    inline EntryRange Entries(Header& h) { return EntryRange(&h); }

    namespace DC {

        enum ScriptId : StringId64 {
            Modules = SID("*modules*"),
            PersistentCommandList = SID("*persistent-command-list*"),
            MouseDefaultSettings = SID("*mouse-default-settings*"),
            AnalogStickIconPaths = SID("*analog-stick-icon-paths*"),
            MeleeOverrideIds = SID("*melee-override-ids*"),
            WeaponCrossPressReleaseBlacklist = SID("*weapon-cross-press-release-blacklist*"),
            JoypadAdditionalPresets = SID("*joypad-additional-presets*"),
            ActionMap = SID("*action-map*")
        };

        enum Type : StringId64 {
            kArray = SID("array"),
            k_Array = SID("array*"),
            kMap = SID("map"),
            kFloat = SID("float"),
            kSymbol = SID("symbol"),
            kString = SID("string"),
            kSymbolArray = SID("symbol-array"),
            kModuleInfoArray = SID("module-info-array"),
            kActionScheme = SID("action-scheme"),
            kJoypadPersistentCommandList = SID("joypad-persistent-command-list"),
            kMouseDefaultSettings = SID("mouse-default-settings"),
            kActionCollection = SID("action-collection"),
        };

        // @ kArray
        template<class T> struct Array { 
            T* m_value{ nullptr }; 
        };

		// @ kArray || k_Array
        template<class T> struct FixedSizeArray {
            std::uint32_t m_fixedSize{ 0 };
            T* m_value{ nullptr };
        };

		// @ kMap
        template<class K, class V> struct map {
            std::uint64_t m_size{ 0 };
            K* m_key{ nullptr };
            V* m_val{ nullptr };
        };

    }

	static_assert(sizeof(Header) == 0x20, "DC Header size mismatch");
	static_assert(sizeof(Entry<void>) == 0x18, "DC Entry<void> size mismatch");

	static_assert(sizeof(DC::map<void, void>) == 0x18, "DC::map<void, void> size mismatch");
	static_assert(sizeof(DC::Array<void>) == 0x8, "DC::Array<void> size mismatch");
	static_assert(sizeof(DC::FixedSizeArray<void>) == 0x10, "DC::FixedSizeArray<void> size mismatch");
	static_assert(sizeof(DC::map<void, void>) == 0x18, "DC::map<StringId64, StringId64> size mismatch");
}