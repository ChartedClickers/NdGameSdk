#pragma once
#include "NdGameSdk/sdkderived.hpp"
#include "NdGameSdk/components/SdkRegenny.hpp"

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/ndlib/io/ArchiveSystem.hpp>
#endif

#include <string_view>
#include <Utility/function_ptr.hpp>

namespace NdGameSdk::ndlib::io {
#if defined(T2R)

    class FileSystem;
	class StorageCore;

    using PSARCHeaderBE = regenny::shared::ndlib::io::PSARCHeaderBE;

    class NdGameSdk_API ArchiveSystem : public ISdkRegenny<regenny::shared::ndlib::io::ArchiveSystem> {
    public:
        using PriorityGroup = regenny::shared::ndlib::io::ArchiveSystem::PriorityGroup;

        class Archive : public ISdkRegenny<regenny::shared::ndlib::io::ArchiveSystem::Archive> {
        public:

            const char* GetMountPrefix() const;

            uint64_t GetId() const;
            uint32_t GetMountPrefixLen() const;

            uint32_t GetSize() const;
			uint64_t GetSizeUncompressed() const;

            std::string_view GetMountPrefixView() const;

            PriorityGroup GetPriority() const;

            const PSARCHeaderBE& GetPSARCHeader() const;
        };

        class File : public ISdkRegenny<regenny::shared::ndlib::io::ArchiveSystem::File> {
        public:
            uint32_t GetIoHandle() const;
            uint64_t GetOffset() const;
            uint64_t GetSize() const;
        };

        uint32_t GetCount() const;
        uint32_t GetCapacity() const;
        uint32_t GetPtrCount() const;
        uint32_t GetPtrCapacity() const;
        uint64_t GetNextId() const;

        Archive* GetTable() const;
        Archive** GetPtrs() const;

        StorageCore* GetStorageCore() const;

        uint64_t Add(const char* indexPath, const char* mountPrefix, PriorityGroup prio = PriorityGroup::Low);
		bool Remove(uint64_t archiveId);
		File* Resolve(File* pFile, char* Path);

        struct PtrIterator {
            Archive** it{};
            Archive* operator*() const { return *it; }
            PtrIterator& operator++() { ++it; return *this; }
            bool operator!=(const PtrIterator& o) const { return it != o.it; }
        };

        struct PtrRange {
            Archive** first{};
            Archive** last{};
            PtrIterator begin() const { return { first }; }
            PtrIterator end()   const { return { last }; }
            std::size_t size() const { return static_cast<std::size_t>(last - first); }
            bool empty() const { return first == last; }
        };

        struct TableIterator {
            Archive* cur{};
            Archive* operator*() const { return cur; }
            TableIterator& operator++() { ++cur; return *this; }
            bool operator!=(const TableIterator& o) const { return cur != o.cur; }
        };

        struct TableRange {
            Archive* first{};
            Archive* last{};
            TableIterator begin() const { return { first }; }
            TableIterator end()   const { return { last }; }
            std::size_t size() const { return static_cast<std::size_t>(last - first); }
            bool empty() const { return first == last; }
        };

        PtrRange Ptrs() const {
            auto** begin = GetPtrs();
            auto** end = begin ? (begin + GetPtrCount()) : begin;
            return { begin, end };
        }

        TableRange GetMountedArchives() const {
            auto* first = GetTable();
            auto* last = first ? (first + GetCount()) : first;
            return { first, last };
        }

    private:
        TYPEDEF_FUNCTION_PTR(uint64_t, FileSystem_ArchiveSystem_Add, ArchiveSystem* pArchiveSystem, const char* indexPath, const char* mountPrefix, PriorityGroup prio);
        TYPEDEF_FUNCTION_PTR(bool, FileSystem_ArchiveSystem_Remove, ArchiveSystem* pArchiveSystem, uint64_t archiveId);
        TYPEDEF_FUNCTION_PTR(File*, FileSystem_ArchiveSystem_Resolve, ArchiveSystem* pArchiveSystem, File* pFile, char* Path);
        friend class FileSystem;
    };

    static_assert(sizeof(ArchiveSystem) == 0x50, "Invalid ArchiveSystem size");
    static_assert(sizeof(ArchiveSystem::Archive) == 0x468, "Invalid Archive size");
    static_assert(sizeof(ArchiveSystem::File) == 0x18, "Invalid Archive::File size");

#endif
}
