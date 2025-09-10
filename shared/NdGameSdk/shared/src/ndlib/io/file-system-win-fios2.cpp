#include "file-system-win-fios2.hpp"
#include "file-system-archive.hpp"
#include "./NdGameSdk/shared/sharedpatterns.hpp"

#include <NdGameSdk/shared/src/ndlib/engine-components.hpp>
#include <NdGameSdk/shared/src/gamelib/debug/nd-dev-menu.hpp>

namespace NdGameSdk::ndlib::io {

#if defined(T2R)

	FileSystem::FileSystem() : ISdkComponent(TOSTRING(FileSystem)) {
		ArchiveSystem::s_FileSystem = this;
	}

	void FileSystem::Awake() {
		auto SharedComponents = ISdkComponent::GetSharedComponents();
		m_EngineComponents = GetDependencyComponent<EngineComponents>(SharedComponents);
		m_Memory = GetDependencyComponent<Memory>(SharedComponents);
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

			// FileSystem game function pointers
			findpattern = Patterns::FileSystem_PreadSync;
			FileSystem_PreadSync = (FileSystem_PreadSync_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::FileSystem_PreadSync), findpattern.offset);

			findpattern = Patterns::FileSystem_PreadAsync;
			FileSystem_PreadAsync = (FileSystem_PreadAsync_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::FileSystem_PreadAsync), findpattern.offset);

			findpattern = Patterns::FileSystem_PwriteSync;
			FileSystem_PwriteSync = (FileSystem_PwriteSync_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::FileSystem_PwriteSync), findpattern.offset);

			findpattern = Patterns::FileSystem_OpenSync;
			FileSystem_OpenSync = (FileSystem_OpenSync_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::FileSystem_OpenSync), findpattern.offset);

			findpattern = Patterns::FileSystem_CloseSync;
			FileSystem_CloseSync = (FileSystem_CloseSync_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::FileSystem_CloseSync), findpattern.offset);

			findpattern = Patterns::FileSystem_OpenSyncImp;
			FileSystem_OpenSyncImp = (FileSystem_OpenSyncImp_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::FileSystem_OpenSyncImp), findpattern.offset);

			findpattern = Patterns::FileSystem_CloseSyncImp;
			FileSystem_CloseSyncImp = (FileSystem_CloseSyncImp_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::FileSystem_CloseSyncImp), findpattern.offset);

			findpattern = Patterns::FileSystem_WriteSync;
			FileSystem_WriteSync = (FileSystem_WriteSync_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::FileSystem_WriteSync), findpattern.offset);

			findpattern = Patterns::FileSystem_WriteAsync;
			FileSystem_WriteAsync = (FileSystem_WriteAsync_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::FileSystem_WriteAsync), findpattern.offset);

			findpattern = Patterns::FileSystem_WaitOSHandle;
			FileSystem_WaitOSHandle = (FileSystem_WaitOSHandle_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::FileSystem_WaitOSHandle), findpattern.offset);

			findpattern = Patterns::FileSystem_WaitFIOSOpId;
			FileSystem_WaitFIOSOpId = (FileSystem_WaitFIOSOpId_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::FileSystem_WaitFIOSOpId), findpattern.offset);

			findpattern = Patterns::FileSystem_PollReadOp;
			FileSystem_PollReadOp = (FileSystem_PollReadOp_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::FileSystem_PollReadOp), findpattern.offset);

			findpattern = Patterns::FileSystem_ReleaseOp;
			FileSystem_ReleaseOp = (FileSystem_ReleaseOp_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::FileSystem_ReleaseOp), findpattern.offset);

			findpattern = Patterns::FileSystem_ReadSync;
			FileSystem_ReadSync = (FileSystem_ReadSync_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::FileSystem_ReadSync), findpattern.offset);

			findpattern = Patterns::FileSystem_ReadAsync;
			FileSystem_ReadAsync = (FileSystem_ReadAsync_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::FileSystem_ReadAsync), findpattern.offset);

			findpattern = Patterns::FileSystem_IsFileExists;
			FileSystem_IsFileExists = (FileSystem_IsFileExists_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::FileSystem_IsFileExists), findpattern.offset);

			findpattern = Patterns::FileSystem_IsDirectoryExsist;
			FileSystem_IsDirectoryExsist = (FileSystem_IsDirectoryExsist_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::FileSystem_IsDirectoryExsist), findpattern.offset);

			findpattern = Patterns::FileSystem_GetSizeSync;
			FileSystem_GetSizeSync = (FileSystem_GetSizeSync_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::FileSystem_GetSizeSync), findpattern.offset);

			findpattern = Patterns::FileSystem_GetFileSizeSync;
			FileSystem_GetFileSizeSync = (FileSystem_GetFileSizeSync_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::FileSystem_GetFileSizeSync), findpattern.offset);

			findpattern = Patterns::FileSystem_IsDoneOpId;
			FileSystem_IsDoneOpId = (FileSystem_IsDoneOpId_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::FileSystem_IsDoneOpId), findpattern.offset);

			findpattern = Patterns::FileSystem_IsDoneBatchKey;
			FileSystem_IsDoneBatchKey = (FileSystem_IsDoneBatchKey_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::FileSystem_IsDoneBatchKey), findpattern.offset);

			findpattern = Patterns::FileSystem_AddOverlay;
			FileSystem_AddOverlay = (FileSystem_AddOverlay_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::FileSystem_AddOverlay), findpattern.offset);

			findpattern = Patterns::FileSystem_RemoveOverlayById;
			FileSystem_RemoveOverlayById = (FileSystem_RemoveOverlayById_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::FileSystem_RemoveOverlayById), findpattern.offset);

			findpattern = Patterns::FileSystem_DeleteSync;
			FileSystem_DeleteSync = (FileSystem_DeleteSync_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::FileSystem_DeleteSync), findpattern.offset);

			findpattern = Patterns::FileSystem_RenameSync;
			FileSystem_RenameSync = (FileSystem_RenameSync_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::FileSystem_RenameSync), findpattern.offset);

			findpattern = Patterns::FileSystem_ResolvePath;
			FileSystem_ResolvePath = (FileSystem_ResolvePath_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::FileSystem_ResolvePath), findpattern.offset);

			findpattern = Patterns::FileSystem_BatchResolve;
			FileSystem_BatchResolve = (FileSystem_BatchResolve_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::FileSystem_BatchResolve), findpattern.offset);

			findpattern = Patterns::FileSystem_BatchRelease;
			FileSystem_BatchRelease = (FileSystem_BatchRelease_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::FileSystem_BatchRelease), findpattern.offset);

			findpattern = Patterns::FileSystem_BatchRead;
			FileSystem_BatchRead = (FileSystem_BatchRead_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::FileSystem_BatchRead), findpattern.offset);

			findpattern = Patterns::FileSystem_MountArchiveSync;
			FileSystem_MountArchiveSync = (FileSystem_MountArchiveSync_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::FileSystem_MountArchiveSync), findpattern.offset);

			findpattern = Patterns::FileSystem_UnmountArchiveSync;
			FileSystem_UnmountArchiveSync = (FileSystem_UnmountArchiveSync_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::FileSystem_UnmountArchiveSync), findpattern.offset);

			// ArchiveSystem helpers
			findpattern = Patterns::FileSystem_ArchiveSystem_Add;
			ArchiveSystem::FileSystem_ArchiveSystem_Add = (ArchiveSystem::FileSystem_ArchiveSystem_Add_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::FileSystem_ArchiveSystem_Add), findpattern.offset);

			findpattern = Patterns::FileSystem_ArchiveSystem_Remove;
			ArchiveSystem::FileSystem_ArchiveSystem_Remove = (ArchiveSystem::FileSystem_ArchiveSystem_Remove_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::FileSystem_ArchiveSystem_Remove), findpattern.offset);

			findpattern = Patterns::FileSystem_ArchiveSystem_Resolve;
			ArchiveSystem::FileSystem_ArchiveSystem_Resolve = (ArchiveSystem::FileSystem_ArchiveSystem_Resolve_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::FileSystem_ArchiveSystem_Resolve), findpattern.offset);

			// extern functions
			findpattern = Patterns::FileSystem_StrError;
			FileSystem_StrError = (FileSystem_StrError_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::FileSystem_StrError), findpattern.offset);

			m_FileSystemInitHook = Utility::MakeSafetyHookInline(FileSystemInit, Init,
				wstr(Patterns::FileSystem_Init), wstr(FileSystem::Init));

			if (!m_FileSystemInitHook) {
				throw SdkComponentEx{ "Failed to create hooks!", SdkComponentEx::ErrorCode::PatchFailed };
			}

			if (!FileSystem_PreadSync ||
				!FileSystem_PreadAsync ||
				!FileSystem_PwriteSync ||
				!FileSystem_OpenSync ||
				!FileSystem_CloseSync ||
				!FileSystem_OpenSyncImp ||
				!FileSystem_CloseSyncImp ||
				!FileSystem_WriteSync ||
				!FileSystem_WriteAsync ||
				!FileSystem_WaitOSHandle ||
				!FileSystem_WaitFIOSOpId ||
				!FileSystem_PollReadOp ||
				!FileSystem_ReleaseOp ||
				!FileSystem_ReadSync ||
				!FileSystem_ReadAsync ||
				!FileSystem_IsFileExists ||
				!FileSystem_IsDirectoryExsist ||
				!FileSystem_GetSizeSync ||
				!FileSystem_GetFileSizeSync ||
				!FileSystem_IsDoneOpId ||
				!FileSystem_IsDoneBatchKey ||
				!FileSystem_AddOverlay ||
				!FileSystem_RemoveOverlayById ||
				!FileSystem_DeleteSync ||
				!FileSystem_RenameSync ||
				!FileSystem_ResolvePath ||
				!FileSystem_BatchResolve ||
				!FileSystem_BatchRelease ||
				!FileSystem_BatchRead ||
				!FileSystem_MountArchiveSync ||
				!FileSystem_UnmountArchiveSync ||
				!FileSystem_StrError ||
				!ArchiveSystem::FileSystem_ArchiveSystem_Add ||
				!ArchiveSystem::FileSystem_ArchiveSystem_Remove ||
				!ArchiveSystem::FileSystem_ArchiveSystem_Resolve) {
				throw SdkComponentEx{ std::format("Failed to find {}:: game functions!", GetName()), SdkComponentEx::ErrorCode::PatternFailed };
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

								if (!fr->HasValidHandle()) {
									spdlog::warn("  File : <unavailable>, StoredSize={}", fr->GetFileSize());
									continue;
								}

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

				pdmenu->Create_DMENU_ItemFunction("Dump archives", pFileSystemMenu,
					+[](DMENU::ItemFunction& pFunction, DMENU::Message pMessage)->bool {
						if (pMessage == DMENU::Message::OnExecute) {
							auto* fs = reinterpret_cast<FileSystem*>(pFunction.Data());
							auto* fsa = fs->GetFileSystemData()->GetArchiveSystem();
							spdlog::info("Mounted Archives:");
							for (const auto& archive : fsa->GetMountedArchives()) {
								spdlog::info("ID={} Size={} MountedAt='{}'",
									archive->GetId(),
									archive->GetSize(),
									archive->GetMountPrefixView()
								);
							}
						}
						return true;
					},
					FileSystemAddr, false, HeapArena_Source);

				static FileSystemInternal::ArchiveMount pTestMount{};

				pdmenu->Create_DMENU_ItemFunction("Mount/Unmount Archive", pFileSystemMenu,
					+[](DMENU::ItemFunction& pFunction, DMENU::Message pMessage)->bool {
						if (pMessage == DMENU::Message::OnExecute) {
							auto* fs = reinterpret_cast<FileSystem*>(pFunction.Data());
							NdGameInfo& NdGameInfo = fs->m_EngineComponents->GetNdGameInfo();

							if (!pTestMount.GetId()) {
								const std::string archivePathStr = std::format("{}/pack_src.psarc", NdGameInfo.Get()->m_GamePath);
								const std::string mountPrefixStr = std::format("{}/pack_src", NdGameInfo.Get()->m_GamePath);

								FsResult outResult{};

								if (!fs->MountArchiveSync(outResult, archivePathStr.c_str(), mountPrefixStr.c_str(), &pTestMount, true)) {
									spdlog::error("MountArchiveSync failed for '{}': {}", archivePathStr, FileSystem::FsStrError(outResult));
									return false;
								}

								pFunction.SetActive(true);
							}
							else {
								FsResult outResult{};
								if (!fs->UnmountArchiveSync(outResult, &pTestMount)) {
									spdlog::error("UnmountArchiveSync failed for '{}': {}", pTestMount.GetMountPath(), FileSystem::FsStrError(outResult));
									return false;
								}

								pFunction.SetActive(false);
							}

						}
						return true;
					},
					FileSystemAddr, false, HeapArena_Source);

				pdmenu->Create_DMENU_ItemFunction("Read testfile.txt", pFileSystemMenu,
					+[](DMENU::ItemFunction& pFunction, DMENU::Message pMessage)->bool {
						if (pMessage == DMENU::Message::OnExecute) {
							auto* fs = reinterpret_cast<FileSystem*>(pFunction.Data());
							NdGameInfo& NdGameInfo = fs->m_EngineComponents->GetNdGameInfo();

							const std::string filePath = std::format("{}/pack_src/testfile.txt", NdGameInfo.Get()->m_GamePath);

							FsResult fsRes{};
							FileSystemInternal::ReadOnlyFileHandle fh{};

							if (!fs->OpenSync(fsRes, filePath.c_str(), &fh)) {
								spdlog::error("OpenSync failed for '{}': {}", filePath, FileSystem::FsStrError(fsRes));
								return false;
							}

							int64_t size = 0;
							if (!fs->GetSizeSync(fsRes, fh, &size)) {
								spdlog::error("GetSizeSync failed for '{}': {}", filePath, FileSystem::FsStrError(fsRes));
								fs->CloseSync(fsRes, fh);
								return false;
							}

							if (size <= 0) {
								spdlog::warn("File '{}' is empty ({} bytes)", filePath, size);
								fs->CloseSync(fsRes, fh);
								return true;
							}
							const uint64_t bytesToRead = static_cast<uint64_t>(size);
							char* buffer = fs->m_Memory->AllocateAtContext<char>(bytesToRead + 1, 0x10, Memory::Context::kAllocAppCpu);
							if (!buffer) {
								spdlog::error("AllocateAtContext failed for {} bytes", bytesToRead + 1);
								fs->CloseSync(fsRes, fh);
								return false;
							}

							uint64_t bytesDone = 0;
							const bool ok = fs->PreadSync(fsRes, &fh, buffer, /*offset*/0, bytesToRead, &bytesDone);
							const uint64_t termIndex = (bytesDone < bytesToRead) ? bytesDone : bytesToRead;
							buffer[termIndex] = '\0';

							if (!ok) {
								spdlog::error("PreadSync failed for '{}': {}", filePath, FileSystem::FsStrError(fsRes));
								fs->m_Memory->Free(buffer, HeapArena_Source);
								fs->CloseSync(fsRes, fh);
								return false;
							}

							spdlog::info("File '{}' opened successfully: Handle={} Offset={} Size={} IsArchive={}",
								filePath,
								fh.GetIoHandle(),
								fh.GetOffset(),
								fh.GetSize(),
								fh.IsArchive() ? "true" : "false"
							);

							spdlog::info("Contents of '{}':\n{}", filePath, buffer);

							fs->m_Memory->Free(buffer, HeapArena_Source);
							fs->CloseSync(fsRes, fh);
						}
						return true;
					},
					FileSystemAddr, false, HeapArena_Source);

				pdmenu->Create_DMENU_ItemFunction("List archive files", pFileSystemMenu,
					+[](DMENU::ItemFunction& pFunction, DMENU::Message pMessage)->bool {
						if (pMessage == DMENU::Message::OnExecute) {
							auto* fs = reinterpret_cast<FileSystem*>(pFunction.Data());
							NdGameInfo& NdGameInfo = fs->m_EngineComponents->GetNdGameInfo();
							ArchiveSystem* fsa = fs->GetFileSystemData()->GetArchiveSystem();

							if (auto ArchiveId = pTestMount.GetId()) {
								auto list = fsa->ListPsarcFiles(ArchiveId);
								spdlog::info("Entries in {} ({}):", pTestMount.GetMountPath(), list.size());
								for (auto& s : list) {
									spdlog::info("  {}", s);
								}
							}
							else {
								spdlog::warn("No test archive mounted at '{}'", NdGameInfo.Get()->m_GamePath);
							}

							/*
							auto archive0 = fsa->GetMountedArchives().begin().cur[0];

							auto list = archive0.ListPsarcFiles();
							if (!list.empty()) {

								auto archive0File = fsa->GetStorageCore()->LookupByIoHandle(archive0.GetIoHandle());

								if (archive0File != nullptr) {
								    const auto wname = archive0File->GetFileName();
								    const std::string name(wname.begin(), wname.end());
								    spdlog::info("Entries in {} ({}):", name, list.size());
								} else {
								    spdlog::info("Entries in IOHandle={} ({}):", archive0.GetIoHandle(), list.size());
								}

								for (auto& s : list) {
									spdlog::info("  {}", s);
								}

							} else {
								spdlog::warn("Failed to list files in archive ID={}", archive0.GetId());
							}
							*/

							return true;
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
