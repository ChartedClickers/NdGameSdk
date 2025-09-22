#pragma once

#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/components/SdkComponent.hpp"

#include <NdGameSdk/shared/src/corelib/memory/memory.hpp>
#include <NdGameSdk/shared/src/corelib/memory/allocator-heap.hpp>
#include <NdGameSdk/shared/src/ndlib/debug/nd-dmenu.hpp>

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/ndlib/io/FileSystem.hpp>
#elif defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/ndlib/io/FileSystem.hpp>
#endif

#include "file-system-fios2.hpp"

namespace NdGameSdk::ndlib { class EngineComponents; }

using namespace NdGameSdk::corelib::memory;
using namespace NdGameSdk::gamelib::debug;
using namespace NdGameSdk::ndlib;
using namespace NdGameSdk::ndlib::debug;

namespace NdGameSdk::ndlib::io {

	/* Extern classes */
	class NdGameSdk_API FileSystemWin : public ISdkRegenny<regenny::shared::ndlib::io::FileSystem> {
	public:
	#if defined(T2R)
		using Priority = regenny::shared::ndlib::io::FileSystem::Priority;

		class Overlay : public ISdkRegenny<regenny::shared::ndlib::io::FileSystem::FileSystemOverlay> {
		public:
			bool GetDisplayOverlay() const;
			void SetDisplayOverlay(bool value);
		};

		class ReadOnlyFileHandle : public ISdkRegenny<regenny::shared::ndlib::io::FileSystem::ReadOnlyFileHandle> {
		public:
			uint32_t GetIoHandle() const;
			uint64_t GetOffset() const;
			uint64_t GetSize() const;
			bool IsArchive() const;
		};

		class ReadOperation : public ISdkRegenny<regenny::shared::ndlib::io::FileSystem::ReadOperation> {
		public:
			HANDLE* GetEventHandle() const;
			FsResult& GetFsResult();
		};

		class BatchResolveItem : public ISdkRegenny<regenny::shared::ndlib::io::FileSystem::BatchResolveItem> {};
		class BatchReadItem : public ISdkRegenny<regenny::shared::ndlib::io::FileSystem::BatchReadItem> {};
	#endif
		class ArchiveMount : public ISdkRegenny<regenny::shared::ndlib::io::FileSystem::ArchiveMount> {
		public:
		#if defined(T1X)
			using ArchiveMountFlags = regenny::shared::ndlib::io::FileSystem::ArchiveMount::ArchiveMountFlags;
		#endif

			ArchiveMount() = default;

			uint64_t GetId() const;
			uint64_t GetSize() const;
	#if defined(T1X)
			ArchiveMountFlags GetFlags() const;
	#elif defined(T2R)
			const char* GetMountPath() const;
			const char* GetArchivePath() const;

		private:
			regenny::shared::ndlib::io::FileSystem::ArchiveMount::Buffer* GetBuffer() const;
	#endif
		};

	#if defined(T2R)
		Overlay& GetOverlay();
		bool IsInitialized() const;
		HeapAllocatorWithOverflow& GetAllocator();
	#endif
	};

#if defined(T2R)

	#define FileSystemInternal FileSystemWin

	class NdGameSdk_API FileSystem : public ISdkComponent {
	public:
		FileSystem();
		SDK_DEPENDENCIES(EngineComponents, Memory);

		FileSystemData* GetFileSystemData();

		bool OpenSync(FsResult& outResult, const char* path, FileSystemInternal::ReadOnlyFileHandle* pFileHandle, FileSystemInternal::Priority prio = FileSystemInternal::Priority::None);
		bool CloseSync(FsResult& outResult, FileSystemInternal::ReadOnlyFileHandle& pFileHandle);
		bool GetSizeSync(FsResult& outResult, FileSystemInternal::ReadOnlyFileHandle& pFileHandle, int64_t* outSize);
		bool PreadSync(FsResult& outResult, FileSystemInternal::ReadOnlyFileHandle* pFileHandle, void* dst, uint64_t fileRelativeOffset,
			uint64_t requestedBytes, uint64_t* ioBytesDoneCell, FileSystemInternal::Priority prio = FileSystemInternal::Priority::None);

		bool OpenSyncImp(FsResult& outResult, const char* path, uint32_t* outFh, FhOpenFlags openFlags, bool resolveMode);
		bool CloseSyncImp(FsResult& outResult, uint32_t fh, bool flush);

		bool WriteSync(FsResult& outResult, uint32_t fh, const void* src, int64_t length, int64_t* outBytesWritten, uint8_t opFlags);

		bool PreadAsync(FsResult& outResult, FileSystemInternal::ReadOnlyFileHandle& pFileHandle,
			FileSystemInternal::ReadOperation* pReadOperation, void* dst, int64_t fileRelativeOffset,
			int64_t requestedBytes, uint64_t* ioBytesDoneCell, FileSystemInternal::Priority prio = FileSystemInternal::Priority::None,
			bool allowShortRead = false);
		DWORD PollReadOp(FileSystemInternal::ReadOperation* pReadOperation, FsResult* pFsResult);
		bool Wait(FsResult& outResult, FileSystemInternal::ReadOperation* pReadOperation);
		bool Wait(FsResult& outResult, int32_t opId);

		bool DeleteSync(FsResult& outResult, const char* path);
		bool RenameSync(FsResult& outResult, const char* oldPath, const char* newPath);
		int64_t ResolvePath(const char* originalPath, char* resolvedPath, uint64_t resolvedPathSize, bool skipAssetView);

		bool IsFileExists(const char* Path);
		bool IsDirectoryExsist(const char* Path);

		bool MountArchiveSync(FsResult& outResult, const char* archivePath, const char* mountPath, FileSystemInternal::ArchiveMount* pArchiveMount, bool appendToEnd = false);
		bool UnmountArchiveSync(FsResult& outResult, FileSystemInternal::ArchiveMount* pArchiveMount);

		static const char* FsStrError(FsResult& pFsResult);
	private:
		void Initialize() override;
		void Awake() override;

		FileSystemInternal* GetFileSystem() const;

		static DMENU::ItemSubmenu* CreateFileSystemMenu(NdDevMenu* pdmenu, DMENU::Menu* pMenu);

		/*Extern Functs*/
		static void Init(FileSystemInternal* pFileSys);

		EngineComponents* m_EngineComponents;
		Memory* m_Memory;

		InlineHook m_FileSystemInitHook{};

		/*Extern variables*/
		static FileSystemData* g_FileSystemDataSlot;

		MEMBER_FUNCTION_PTR(int32_t*, FileSystem_PreadSync, FileSystemInternal* pFileSys, FsResult* pOutResult, FileSystemInternal::ReadOnlyFileHandle* pFileHandle,
			void* dst, uint64_t pfileRelativeOffset, uint64_t pRequestedBytes, uint64_t* pIoBytesDoneCell, FileSystemInternal::Priority prio);
		MEMBER_FUNCTION_PTR(int32_t*, FileSystem_PreadAsync, FileSystemInternal* pFileSys, FsResult* pOutResult, FileSystemInternal::ReadOnlyFileHandle& pFileHandle,
			FileSystemInternal::ReadOperation* pReadOperation, void* dst, int64_t pfileRelativeOffset, int64_t pRequestedBytes,
			uint64_t* pIoBytesDoneCell, FileSystemInternal::Priority prio, bool allowShortRead);
		MEMBER_FUNCTION_PTR(int32_t*, FileSystem_OpenSync, FileSystemInternal* pFileSys, FsResult* pOutResult, const char* path,
			FileSystemInternal::ReadOnlyFileHandle* pFileHandle, FileSystemInternal::Priority prio);
		MEMBER_FUNCTION_PTR(int32_t*, FileSystem_CloseSync, FileSystemInternal* pFileSys, FsResult* pOutResult, FileSystemInternal::ReadOnlyFileHandle* pFileHandle);
        MEMBER_FUNCTION_PTR(int32_t*, FileSystem_OpenSyncImp, FileSystemInternal* pFileSys, FsResult* pOutResult, const char* path, 
            uint32_t* pFh, FhOpenFlags openFlags, bool resolveMode);
        MEMBER_FUNCTION_PTR(int32_t*, FileSystem_CloseSyncImp, FileSystemInternal* pFileSys, FsResult* pOutResult, uint32_t fh, bool flush);
        MEMBER_FUNCTION_PTR(int32_t*, FileSystem_WriteSync, FileSystemInternal* pFileSys, FsResult* pFsResult, int32_t fh, const void* src,
			int64_t length, int64_t* numWritten, uint8_t opFlags);
		MEMBER_FUNCTION_PTR(int32_t*, FileSystem_WriteAsync, FileSystemInternal* pFileSys, FsResult* pFsResult, int32_t fh, const void* src,
			int64_t length, int64_t* FiosOpId, bool flush);
		MEMBER_FUNCTION_PTR(int32_t*, FileSystem_WaitReadOperation, FileSystemInternal* pFileSys, FsResult* pOut, FileSystemInternal::ReadOperation* pReadOperation);
		MEMBER_FUNCTION_PTR(int32_t*, FileSystem_WaitFIOSOpId, FileSystemInternal* pFileSys, FsResult* pOut, int32_t opId);
		MEMBER_FUNCTION_PTR(DWORD, FileSystem_PollReadOp, FileSystemInternal* pFileSys, FileSystemInternal::ReadOperation* pReadOperation, FsResult* pFsResult);
		MEMBER_FUNCTION_PTR(void, FileSystem_ReleaseOp, FileSystemInternal* pFileSys, int32_t opId);
		MEMBER_FUNCTION_PTR(int32_t*, FileSystem_ReadSync, FileSystemInternal* pFileSys, FsResult* pOutResult, int32_t fh, void* dst, int64_t length, 
			uint64_t* outBytesRead, uint8_t flags);
        MEMBER_FUNCTION_PTR(int32_t*, FileSystem_ReadAsync, FileSystemInternal* pFileSys, FsResult* outErr, int32_t fh, const void* buffer, uint64_t length, 
            uint64_t* bytesThisSubmit, int32_t* outOpId, uint8_t submitFlag);

		MEMBER_FUNCTION_PTR(bool, FileSystem_IsFileExists, FileSystemInternal* pFileSys, char* Path);
		MEMBER_FUNCTION_PTR(int64_t, FileSystem_IsDirectoryExsist, FileSystemInternal* pFileSys, char* path);
		MEMBER_FUNCTION_PTR(int32_t*, FileSystem_GetSizeSync, FileSystemInternal* FileSys, FsResult* pFsResult, 
			FileSystemInternal::ReadOnlyFileHandle* pFileHandle, int64_t* outSize);
		MEMBER_FUNCTION_PTR(int32_t*, FileSystem_GetFileSizeSync, FileSystemInternal* pFileSys, FsResult* pOutResult,
			char* Path, uint64_t* outSize);
		MEMBER_FUNCTION_PTR(bool, FileSystem_IsDoneOpId, FileSystemInternal* pFileSys, int32_t opId, FsResult* pOutResult,
			uint64_t* bytesTransferredOut);
		MEMBER_FUNCTION_PTR(int32_t*, FileSystem_IsDoneBatchKey, FileSystemInternal* pFileSys, FsResult* pOutResult,
			int32_t BatchKey);

		MEMBER_FUNCTION_PTR(uint64_t, FileSystem_AddOverlay, FileSystemInternal* pFileSys, const char* toPath, const char* fromPath, bool appendToEnd);
		MEMBER_FUNCTION_PTR(int64_t, FileSystem_RemoveOverlayById, FileSystemInternal* pFileSys, int32_t overlayId);

		MEMBER_FUNCTION_PTR(int32_t*, FileSystem_DeleteSync, FileSystemInternal* pFileSys, FsResult* pOutResult, const char* path);
		MEMBER_FUNCTION_PTR(int32_t*, FileSystem_RenameSync, FileSystemInternal* pFileSys, FsResult* pOutResult, const char* oldPath, const char* newPath);
		MEMBER_FUNCTION_PTR(int64_t, FileSystem_ResolvePath, char* pOriginalPath, char* pResolvedPath, uint64_t resolvedPathSize, bool skipAssetView);

		MEMBER_FUNCTION_PTR(int32_t*, FileSystem_BatchResolve, FileSystemInternal* FileSys, FsResult* pOutResult, FileSystemInternal::BatchResolveItem* items, 
			int32_t count, int32_t* outBatchKey, char* source_function, char* source_file, uint32_t source_line);
		MEMBER_FUNCTION_PTR(int32_t*, FileSystem_BatchRelease, FileSystemInternal* pFileSys, FsResult* pOutResult, const int32_t* fhs, int32_t count, 
			int32_t* outBatchKey, char* source_function, char* source_file, uint32_t source_line);
		MEMBER_FUNCTION_PTR(int32_t*, FileSystem_BatchRead, FileSystemInternal* FileSys, FsResult* pOutResult, FileSystemInternal::BatchReadItem* items, 
			int32_t count, int32_t* outBatchKey, char* source_function, char* source_file, uint32_t source_line);

		MEMBER_FUNCTION_PTR(int32_t*, FileSystem_MountArchiveSync, FileSystemInternal* pFileSys, FsResult* pOutResult, const char* indexPath, const char* mountPrefix, 
			FileSystemInternal::ArchiveMount* ArchiveMount, bool preferForeground);
        MEMBER_FUNCTION_PTR(int32_t*, FileSystem_UnmountArchiveSync, FileSystemInternal* FileSys, FsResult* outRes, FileSystemInternal::ArchiveMount* pArchiveMount);

        friend class NdDevMenu;
    };

#endif

	#if defined(T2R)
		static_assert(sizeof(FileSystemWin) == 0x220, "Invalid FileSystemWin size");
		static_assert(sizeof(FileSystemWin::Overlay) == 0x60, "Invalid Overlay size");
		static_assert(sizeof(FileSystemWin::ReadOnlyFileHandle) == 0x20, "Invalid ReadOnlyFileHandle size");
		static_assert(sizeof(FileSystemWin::ReadOperation) == 0x18, "Invalid ReadOperation size");
		static_assert(sizeof(FileSystemWin::ArchiveMount) == 0x10, "Invalid ArchiveMount size");
	#elif defined(T1X)
	static_assert(sizeof(FileSystemWin::ArchiveMount) == 0x18, "Invalid ArchiveMount size");
	#endif

}
