#include "file-system-archive.hpp"
#include "file-system-fios2.hpp"
#include "psarc/psarc_reader.hpp"
#include "psarc/psarc_dsar.hpp"
#include "psarc/psarc_parser.hpp"

#include <Windows.h>
#include <format>
#include <cstring>
#include <memory>
#include <spdlog/spdlog.h>

#include <NdGameSdk/shared/src/ndlib/engine-components.hpp>

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

    uint32_t ArchiveSystem::Archive::GetIoHandle() const {
        return this->Get()->m_ioHandle;
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

    const  PSARC::PSARCHeaderBE& ArchiveSystem::Archive::GetPSARCHeader() const {
        return this->Get()->m_psarcHeader;
    }

    std::vector<std::string> ArchiveSystem::Archive::ListPsarcFiles() {
        std::vector<std::string> result;
        
        FileSystemData* fsd = ArchiveSystem::s_FileSystem->GetFileSystemData();
        StorageCore* sc = fsd->GetStorageCore();
		always_assert(sc == nullptr, "StorageCore is null");

        const uint32_t ioHandle = this->GetIoHandle();
        auto* fr = sc->LookupByIoHandle(ioHandle);
        if (!fr) {
            spdlog::warn("{}: LookupByIoHandle({}) returned null", __func__, ioHandle);
            return result;
        }

        std::unique_ptr<PSARC::iReader> baseReader;
        switch (fr->GetHandleType()) {
        case FileRecord::HandleObjType::kHandleWin32:
            baseReader = std::make_unique<PSARC::Win32Reader>(fr->GetHandleObject<HANDLE>());
			break;
		case FileRecord::HandleObjType::kHandleDSFile:
			baseReader = std::make_unique<PSARC::DSReader>(sc, fr->GetHandleObject<IDStorageFile*>());
            break;
        default:
			spdlog::warn("{}: Unsupported file handle type {}", __func__, static_cast<uint32_t>(fr->GetHandleType()));
            return result;
        }

        auto readerWrapped = PSARC::AsPsarcReader(std::move(baseReader));
        if (!readerWrapped) {
            spdlog::warn("{}: Unsupported or unreadable archive header", __func__);
            return result;
        }

        std::vector<std::string> names;
        const auto& beHeader = this->GetPSARCHeader();
        const auto normHeader = PSARC::ToHeaderNormalized(beHeader);

        bool ok = PSARC::ListFilenames(*readerWrapped, normHeader, names);
        if (!ok) {
            spdlog::warn("{}: Failed to parse PSARC filenames", __func__);
            return result;
        }
        return names;
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

    ArchiveSystem::Archive* ArchiveSystem::FindMountedArchive(uint64_t archiveId) {
        if (archiveId == 0) return nullptr;
        for (auto* a : this->GetMountedArchives()) {
            if (a && a->GetId() == archiveId) return a;
        }
        return nullptr;
    }

    std::vector<std::string> ArchiveSystem::ListPsarcFiles(uint64_t archiveId) {
        if (archiveId == 0) return {};
        auto* archive = FindMountedArchive(archiveId);
        return archive->ListPsarcFiles();
    }

    INIT_FUNCTION_PTR(ArchiveSystem::FileSystem_ArchiveSystem_Add);
    INIT_FUNCTION_PTR(ArchiveSystem::FileSystem_ArchiveSystem_Remove);
    INIT_FUNCTION_PTR(ArchiveSystem::FileSystem_ArchiveSystem_Resolve);

	FileSystem* ArchiveSystem::s_FileSystem = nullptr;

#endif
}
