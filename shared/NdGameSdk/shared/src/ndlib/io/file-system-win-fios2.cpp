#include "file-system-win-fios2.hpp"
#include "./NdGameSdk/shared/sharedpatterns.hpp"

#include <NdGameSdk/shared/src/ndlib/engine-components.hpp>
#include <NdGameSdk/shared/src/gamelib/debug/nd-dev-menu.hpp>

namespace NdGameSdk::ndlib::io {

#if defined(T2R)

	FileSystem::FileSystem() : ISdkComponent(TOSTRING(FileSystem)) {}

	void FileSystem::Awake() {
		auto SharedComponents = ISdkComponent::GetSharedComponents();
		m_EngineComponents = GetDependencyComponent<EngineComponents>(SharedComponents);
	}

	void FileSystem::Initialize() {
		static std::once_flag Initialized;
		std::call_once(Initialized, [this] {
			spdlog::info("Initializing {} patterns...", GetName());

			Patterns::SdkPattern findpattern{};
			auto module = Utility::memory::get_executable();

			findpattern = Patterns::FileSystem_Init;
			auto FileSystemInit = (void*)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::FileSystem_Init), findpattern.offset);

			findpattern = Patterns::FileSystem_g_FileSystemData;
			g_FileSystemDataSlot = (FileSystemData*)Utility::ReadLEA32(module,
				findpattern.pattern, wstr(Patterns::FileSystem_g_FileSystemData), findpattern.offset, 3, 7);

			if (!FileSystemInit || !g_FileSystemDataSlot) {
				throw SdkComponentEx{ std::format("Failed to find {} addresses!", GetName()),
					SdkComponentEx::ErrorCode::PatternFailed };
			}

			m_FileSystemInitHook = Utility::MakeSafetyHookInline(FileSystemInit, Init,
				wstr(Patterns::FileSystem_Init), wstr(FileSystem::Init));

			if (!m_FileSystemInitHook) {
				throw SdkComponentEx{ "Failed to create hooks!", SdkComponentEx::ErrorCode::PatchFailed };
			}

		});
	}

	FileSystemInternal* FileSystem::GetFileSystem() const {
		return &m_EngineComponents->GetFileSystem();
	}

	DMENU::ItemSubmenu* FileSystem::CreateFileSystemMenu(NdDevMenu* pdmenu, DMENU::Menu* pMenu) {
		auto pFileSystem = Instance<FileSystem>();
		if (pFileSystem) {
			uint64_t FileSystemAddr = reinterpret_cast<uint64_t>(static_cast<void*>(pFileSystem));
			DMENU::Menu* pFileSystemMenu = pdmenu->Create_DMENU_Menu(pFileSystem->GetName().data(), HeapArena_Source);
			if (pFileSystemMenu) {
			#if SDK_DEBUG
				pdmenu->Create_DMENU_ItemFunction("Test function", pFileSystemMenu,
					+[](DMENU::ItemFunction& pFunction, DMENU::Message pMessage)->bool {
						if (pMessage == DMENU::Message::OnExecute) {
							auto* fs = reinterpret_cast<FileSystem*>(pFunction.Data());
							StorageCore* storage = fs->GetFileSystemData()->GetStorageCore();

							for (auto* fr : storage->OpenFiles()) {
								const auto path = fr->GetPathView();
								spdlog::info(L"OpenFile: {}  Path: {}", static_cast<const void*>(fr), path);

								BY_HANDLE_FILE_INFORMATION info{};
								if (fr->TryGetByHandleInfo(info)) {
									const uint64_t size =
										(uint64_t(info.nFileSizeHigh) << 32) | uint64_t(info.nFileSizeLow);

									spdlog::info(
										L"  Info: Attr=0x{:X} Links={} Size={} Index={:08X}{:08X}",
										info.dwFileAttributes,
										info.nNumberOfLinks,
										size,
										info.nFileIndexHigh, info.nFileIndexLow
									);
								}
								else {
									// Fall back
									spdlog::info(
										L"  Info: <unavailable>  Type={}  StoredSize={}",
										static_cast<uint32_t>(fr->GetHandleType()),
										fr->GetFileSize()
									);
								}

								if (fr->IsWin32Handle()) {
									auto h = reinterpret_cast<HANDLE>(fr->Get()->m_handleObj.m_obj);
									spdlog::info(L"  Win32 Handle: {}", static_cast<const void*>(h));
								}
								else if (fr->IsDirectStorageFile()) {
									auto ds = reinterpret_cast<IDStorageFile*>(fr->Get()->m_handleObj.m_obj);
									spdlog::info(L"  DS File*:   {}", static_cast<const void*>(ds));
								}
							}
						}
						return true;
					},
					FileSystemAddr, false, HeapArena_Source);
			#endif
				return pdmenu->Create_DMENU_ItemSubmenu(pFileSystemMenu->Name(),
					pMenu, pFileSystemMenu, NULL, NULL, nullptr, HeapArena_Source);
			}
		}
		return nullptr;
	}

	void FileSystem::Init(FileSystemInternal* pFileSys) {
		FileSystem* pFileSystem = Instance<FileSystem>();
		pFileSystem->m_FileSystemInitHook.thiscall<void>(pFileSys);
	}

    FileSystemWin::Overlay& FileSystemWin::GetOverlay() {  
       return *reinterpret_cast<FileSystemWin::Overlay*>(&this->Get()->m_SystemOverlay);  
    }

	bool FileSystemWin::IsInitialized() const {
		return this->Get()->m_initialized;
	}

	Memory::Allocator& FileSystemWin::GetAllocator() {
		return *reinterpret_cast<Memory::Allocator*>(&this->Get()->m_allocator);
	}

	bool FileSystemWin::Overlay::GetDisplayOverlay() const {
		return this->Get()->m_DisplayDataLoadingStatistics && this->Get()->m_showFiosOpsDump;
	}

	void FileSystemWin::Overlay::SetDisplayOverlay(bool value) {
		this->Get()->m_DisplayDataLoadingStatistics = value;
		this->Get()->m_showFiosOpsDump = value;
	}

	uint32_t FileSystemWin::ReadOnlyFileHandle::GetIoHandle() const {
		return this->Get()->m_ioHandle;
	}

	uint64_t FileSystemWin::ReadOnlyFileHandle::GetOffset() const {
		return this->Get()->m_offset;
	}

	uint64_t FileSystemWin::ReadOnlyFileHandle::GetSize() const {
		return this->Get()->m_size;
	}

	bool FileSystemWin::ReadOnlyFileHandle::IsArchive() const {
		return this->Get()->m_isArchive;
	}

	HANDLE* FileSystemWin::ReadOperation::GetEventHandle() const {
		return reinterpret_cast<HANDLE*>(this->Get()->m_hEvent);
	}

	FsResult& FileSystemWin::ReadOperation::GetFsResult() {
		return this->Get()->m_FsResult;
	}

	uint64_t FileSystemWin::ArchiveMount::GetId() const {
		if (auto* buffer = this->GetBuffer())
			return buffer->m_archiveId;
		else 
			return 0;
	}

	uint64_t FileSystemWin::ArchiveMount::GetSize() const {
		return this->Get()->m_sizeBytes;
	}

	const char* FileSystemWin::ArchiveMount::GetMountPath() const {
		if (auto* buffer = this->GetBuffer())
			return buffer->m_mountPrefix;
		else
			return nullptr;
	}

	const char* FileSystemWin::ArchiveMount::GetArchivePath() const {
		if (auto* buffer = this->GetBuffer())
			return buffer->m_indexPath;
		else
			return nullptr;
	}

	regenny::shared::ndlib::io::FileSystem::ArchiveMount::Buffer* 
		FileSystemWin::ArchiveMount::GetBuffer() const {
		return this->Get()->m_pMountBuffer;
	}

#endif

}
