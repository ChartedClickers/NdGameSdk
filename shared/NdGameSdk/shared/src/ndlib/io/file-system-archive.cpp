#include "file-system-archive.hpp"

namespace NdGameSdk::ndlib::io {
#if defined(T2R)

    uint64_t ArchiveSystem::Archive::GetId() const {
        return this->Get()->m_id;
    }

    const char* ArchiveSystem::Archive::GetMountPrefix() const {
        return this->Get()->m_mountPrefix;
    }

    uint32_t ArchiveSystem::Archive::GetMountPrefixLen() const {
        return this->Get()->m_mountPrefixLen;
    }

    uint32_t ArchiveSystem::Archive::GetSize() const {
		return this->GetPSARCHeader().m_tocLength;
    }

    uint64_t ArchiveSystem::Archive::GetSizeUncompressed() const {
		return this->GetPSARCHeader().m_tocUncompressedLen;
    }

    std::string_view ArchiveSystem::Archive::GetMountPrefixView() const {
        const char* s = GetMountPrefix();
        return s ? std::string_view{ s, GetMountPrefixLen() } : std::string_view{};
    }

    ArchiveSystem::PriorityGroup ArchiveSystem::Archive::GetPriority() const {
		return this->Get()->m_priority;
    }

    const PSARCHeaderBE& ArchiveSystem::Archive::GetPSARCHeader() const {
        return this->Get()->m_psarcHeader;
    }

    uint32_t ArchiveSystem::File::GetIoHandle() const {
        return this->Get()->m_ioHandle;
    }

    uint64_t ArchiveSystem::File::GetOffset() const {
        return this->Get()->m_offset;
    }

    uint64_t ArchiveSystem::File::GetSize() const {
        return this->Get()->m_size;
    }

    uint32_t ArchiveSystem::GetCount() const {
        return this->Get()->m_count;
    }

    uint32_t ArchiveSystem::GetCapacity() const {
        return this->Get()->m_capacity;
    }

    ArchiveSystem::Archive* ArchiveSystem::GetTable() const {
        return reinterpret_cast<Archive*>(this->Get()->m_table);
    }

    uint32_t ArchiveSystem::GetPtrCount() const {
        return this->Get()->m_ptrCount;
    }

    uint32_t ArchiveSystem::GetPtrCapacity() const {
        return this->Get()->m_ptrCap;
    }

    ArchiveSystem::Archive** ArchiveSystem::GetPtrs() const {
        return reinterpret_cast<Archive**>(this->Get()->m_ptrs);
    }

    StorageCore* ArchiveSystem::GetStorageCore() const {
        return reinterpret_cast<StorageCore*>(this->Get()->m_storageCore);
    }

    uint64_t ArchiveSystem::GetNextId() const {
        return this->Get()->m_nextId;
    }

    uint64_t ArchiveSystem::Add(const char* indexPath, const char* mountPrefix, PriorityGroup prio) {
        always_assert(FileSystem_ArchiveSystem_Add == nullptr, "FileSystem_ArchiveSystem_Add was not initialized!");
        return FileSystem_ArchiveSystem_Add(this, indexPath, mountPrefix, prio);
    }

    bool ArchiveSystem::Remove(uint64_t archiveId) {
        always_assert(FileSystem_ArchiveSystem_Remove == nullptr, "FileSystem_ArchiveSystem_Remove was not initialized!");
        return FileSystem_ArchiveSystem_Remove(this, archiveId);
    }

    ArchiveSystem::File* ArchiveSystem::Resolve(File* pFile, char* Path) {
        always_assert(FileSystem_ArchiveSystem_Resolve == nullptr, "FileSystem_ArchiveSystem_Resolve was not initialized!");
        return FileSystem_ArchiveSystem_Resolve(this, pFile, Path);
    }

    INIT_FUNCTION_PTR(ArchiveSystem::FileSystem_ArchiveSystem_Add);
	INIT_FUNCTION_PTR(ArchiveSystem::FileSystem_ArchiveSystem_Remove);
	INIT_FUNCTION_PTR(ArchiveSystem::FileSystem_ArchiveSystem_Resolve);

#endif
}
