#include "file-system-fios2.hpp"
#include "file-system-win-fios2.hpp"

#include <NdGameSdk/shared/src/ndlib/engine-components.hpp>

namespace NdGameSdk::ndlib::io {
#if defined(T2R)

	FileSystemData* FileSystem::GetFileSystemData() {
		always_assert(g_FileSystemDataSlot == nullptr, "g_FileSystemData was not set!");
		return *reinterpret_cast<FileSystemData* volatile*>(g_FileSystemDataSlot);
	}

	StorageCore* FileSystemData::GetStorageCore() const {
		return reinterpret_cast<StorageCore*>(this->Get()->m_storageCore);
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

	bool StorageCore::IsUsingDirectStorage() {
		return this->Get()->m_useDirectStorage;
	}

	FileSystemData* FileSystem::g_FileSystemDataSlot = nullptr;

#endif
}