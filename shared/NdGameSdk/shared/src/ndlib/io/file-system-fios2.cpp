#include "file-system-fios2.hpp"
#include "file-system-win-fios2.hpp"

#include <NdGameSdk/shared/src/ndlib/engine-components.hpp>

namespace NdGameSdk::ndlib::io {
#if defined(T2R)

	FileSystemData* FileSystem::GetFileSystemData() {
		always_assert(g_FileSystemDataSlot == nullptr, "g_FileSystemData was not set!");
		return *reinterpret_cast<FileSystemData* volatile*>(g_FileSystemDataSlot);
	}

	bool FileSystem::OpenSync(FsResult& outResult, const char* path, 
		FileSystemInternal::ReadOnlyFileHandle* pFileHandle, FileSystemInternal::Priority prio) {
		always_assert(FileSystem_OpenSync == nullptr, "FileSystem_OpenSync was not set!");

		int32_t* ret = FileSystem_OpenSync(
			this->GetFileSystem(),
			&outResult,
			path,
			pFileHandle,
			prio
		);

		const int32_t code = ret ? *ret : 0;
		return code <= 0;
	}

	bool FileSystem::CloseSync(FsResult& outResult, FileSystemInternal::ReadOnlyFileHandle& pFileHandle) {
		always_assert(FileSystem_CloseSync == nullptr, "FileSystem_CloseSync was not set!");
		int32_t* ret = FileSystem_CloseSync(
			this->GetFileSystem(),
			&outResult,
			&pFileHandle
		);

		const int32_t code = ret ? *ret : 0;
		return code <= 0;
	}

	bool FileSystem::GetSizeSync(FsResult& outResult, FileSystemInternal::ReadOnlyFileHandle& pFileHandle, int64_t* outSize) {
		always_assert(FileSystem_GetSizeSync == nullptr, "FileSystem_GetSizeSync was not set!");

		int32_t* ret = FileSystem_GetSizeSync(
			this->GetFileSystem(),
			&outResult,
			&pFileHandle,
			outSize
		);

		const int32_t code = ret ? *ret : 0;
		return code <= 0;
	}

	bool FileSystem::PreadSync(FsResult& outResult, FileSystemInternal::ReadOnlyFileHandle* pFileHandle, void* dst, 
		uint64_t fileRelativeOffset, uint64_t requestedBytes, uint64_t* ioBytesDoneCell, FileSystemInternal::Priority prio) {
		always_assert(FileSystem_PreadSync == nullptr, "FileSystem_PreadSync was not set!");
		int32_t* ret = FileSystem_PreadSync(
			this->GetFileSystem(),
			&outResult,
			pFileHandle,
			dst,
			fileRelativeOffset,
			requestedBytes,
			ioBytesDoneCell,
			prio
		);

		const int32_t code = ret ? *ret : 0;
		return code <= 0;
	}

	bool FileSystem::MountArchiveSync(FsResult& outResult, const char* archivePath, const char* mountPath,
		FileSystemInternal::ArchiveMount* pArchiveMount, bool appendToEnd) {
		always_assert(FileSystem_MountArchiveSync == nullptr, "FileSystem_MountArchiveSync was not set!");
		
		spdlog::info("Mounting archive '{}' at mount point '{}'...", archivePath, mountPath);
		int32_t* ret = FileSystem_MountArchiveSync(
			this->GetFileSystem(),
			&outResult,
			archivePath,
			mountPath,
			pArchiveMount,
			appendToEnd
		);

		const int32_t code = ret ? *ret : 0;
		return code <= 0;
	}

	bool FileSystem::UnmountArchiveSync(FsResult& outResult, FileSystemInternal::ArchiveMount* pArchiveMount) {
		always_assert(FileSystem_UnmountArchiveSync == nullptr, "FileSystem_UnmountArchiveSync was not set!");

		spdlog::info("Unmounting archive at mount point '{}'...", pArchiveMount ? pArchiveMount->GetMountPath() : "(null)");
		int32_t* ret = FileSystem_UnmountArchiveSync(
			this->GetFileSystem(),
			&outResult,
			pArchiveMount
		);

		const int32_t code = ret ? *ret : 0;
		return code <= 0;
	}

	const char* FileSystem::FsStrError(FsResult& pFsResult) {
		always_assert(FileSystem_StrError == nullptr, "FileSystem_FsStrError was not set!");
		return FileSystem_StrError(&pFsResult);
	}

	StorageCore* FileSystemData::GetStorageCore() const {
		return reinterpret_cast<StorageCore*>(this->Get()->m_storageCore);
	}

	ArchiveSystem* FileSystemData::GetArchiveSystem() const {
		return reinterpret_cast<ArchiveSystem*>(this->Get()->m_archive);
	}

	inline const wchar_t* FileRecord::GetPath() const {
		const auto* self = this->Get();
		const auto& ps = self->m_pathStr;

		// SSO: inline buffer starts at the m_pathPtr field itself
		return (ps.m_pathCap < 0x8)
			? reinterpret_cast<const wchar_t*>(&ps.m_pathPtr)
			: ps.m_pathPtr;
	}

	inline uint64_t FileRecord::GetPathLen() const {
		return this->Get()->m_pathStr.m_pathLen;
	}

	inline std::wstring_view FileRecord::GetPathView() const {
		return { GetPath(), static_cast<size_t>(GetPathLen()) };
	}

	std::wstring FileRecord::GetFileName() const {
		auto v = GetFileNameView();
		return std::wstring(v.begin(), v.end());
	}

	std::wstring FileRecord::GetExtension() const {
		auto v = GetExtensionView();
		return std::wstring(v.begin(), v.end());
	}

	std::wstring FileRecord::GetFileNameWithoutExtension() const {
		auto v = GetFileNameWithoutExtensionView();
		return std::wstring(v.begin(), v.end());
	}

	bool FileRecord::IsWin32Handle() const {
		return GetHandleType() == HandleObjType::kHandleWin32;
	}

	bool FileRecord::IsDirectStorageFile() const {
		return GetHandleType() == HandleObjType::kHandleDSFile;
	}

	bool FileRecord::HasValidHandle() const {
		switch (GetHandleType()) {
		case HandleObjType::kHandleWin32:
			return reinterpret_cast<HANDLE>(this->Get()->m_handleObj.m_obj) != INVALID_HANDLE_VALUE;
		case HandleObjType::kHandleDSFile:
			return this->Get()->m_handleObj.m_obj != nullptr;
		default:
			return false;
		}
	}

	bool FileRecord::TryGetByHandleInfo(BY_HANDLE_FILE_INFORMATION& out) const {
		ZeroMemory(&out, sizeof(out));

		const auto* self = this->Get();
		switch (self->m_handleObj.m_type) {
		case HandleObjType::kHandleWin32: {
			const HANDLE h = reinterpret_cast<HANDLE>(self->m_handleObj.m_obj);
			if (!h || h == INVALID_HANDLE_VALUE) return false;
			return ::GetFileInformationByHandle(h, &out) != FALSE;
		}
		case HandleObjType::kHandleDSFile: {
			auto* ds = reinterpret_cast<IDStorageFile*>(self->m_handleObj.m_obj);
			if (!ds) return false;
			const HRESULT hr = ds->GetFileInformation(&out);
			return SUCCEEDED(hr);
		}
		default:
			return false;
		}
	}

	uint64_t FileRecord::GetFileSize() const {
		return this->Get()->m_fileSize;
	}

	uint32_t FileRecord::GetRefCount() const {
		return this->Get()->m_refCount;
	}

	uint32_t FileRecord::GetOpenIndex() const {
		return this->Get()->m_openIndex;
	}

	FileRecord::HandleObjType FileRecord::GetHandleType() const {
		return this->Get()->m_handleObj.m_type;
	}

	FileRecord::FileState FileRecord::GetFileState() const {
		return this->Get()->m_state;
	}

	inline std::wstring_view FileRecord::GetFileNameView() const {
		auto p = GetPathView();

		while (!p.empty() && (p.back() == L'\\' || p.back() == L'/'))
			p.remove_suffix(1);

		const auto pos = p.find_last_of(L"/\\");
		return (pos == std::wstring_view::npos) ? p : p.substr(pos + 1);
	}

	inline std::wstring_view FileRecord::GetExtensionView() const {
		const auto fn = GetFileNameView();
		if (fn.empty()) return {};

		const auto dot = fn.find_last_of(L'.');
		if (dot == std::wstring_view::npos || dot == 0) return {}; 
		return fn.substr(dot);
	}

	inline std::wstring_view FileRecord::GetFileNameWithoutExtensionView() const {
		const auto fn = GetFileNameView();
		if (fn.empty()) return {};

		const auto dot = fn.find_last_of(L'.');
		if (dot == std::wstring_view::npos || dot == 0) return fn;
		return fn.substr(0, dot);
	}

	uint64_t StorageCore::GetCountFileRecords() {
		return this->Get()->m_mapCount;
	}

	CRITICAL_SECTION* StorageCore::GetCriticalSection() {
		return reinterpret_cast<CRITICAL_SECTION*>(&this->Get()->m_cs);
	}

	IDStorageFactory* StorageCore::GetDirectStorageFactory() const {
		return reinterpret_cast<IDStorageFactory*>(this->Get()->m_dsFactory);
	}

	IDStorageQueue* StorageCore::GetDirectStorageQueue() const {
		return reinterpret_cast<IDStorageQueue*>(this->Get()->m_dsQueue);
	}

	FileRecord* StorageCore::LookupByIoHandle(uint32_t ioHandle) const {
		if (ioHandle == 0) return nullptr;

		const auto* self = this->Get();

		auto** begin = reinterpret_cast<FileRecord**>(self->m_openBegin);
		auto** end = reinterpret_cast<FileRecord**>(self->m_openEnd);
		const size_t count = static_cast<size_t>(end - begin);

		const size_t idx = static_cast<size_t>(ioHandle - 1); // 1-based -> 0-based
		if (idx >= count) return nullptr;

		FileRecord* fr = begin[idx];
		if (!fr || fr->Get()->m_openIndex != idx) 
			return nullptr;

		return fr;
	}

	bool StorageCore::IsUsingDirectStorage() {
		return this->Get()->m_useDirectStorage;
	}

	FileSystemData* FileSystem::g_FileSystemDataSlot = nullptr;

	INIT_FUNCTION_PTR(FileSystem_StrError);

#endif
}