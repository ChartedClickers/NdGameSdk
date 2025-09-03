#pragma once

#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/components/SdkComponent.hpp"

#include <NdGameSdk/shared/src/corelib/memory/memory.hpp>
#include <NdGameSdk/shared/src/ndlib/debug/nd-dmenu.hpp>

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/ndlib/io/FileSystem.hpp>
#include <NdGameSdk/regenny/t2r/shared/ndlib/io/FsResult.hpp>
#endif

#include "file-system-fios2.hpp"

namespace NdGameSdk::ndlib { class EngineComponents; }

using namespace NdGameSdk::corelib::memory;
using namespace NdGameSdk::gamelib::debug;
using namespace NdGameSdk::ndlib;
using namespace NdGameSdk::ndlib::debug;

namespace NdGameSdk::ndlib::io {

#if defined(T2R)

	/* Extern classes */
	class FileSystemWin;
	using FsResult = regenny::shared::ndlib::io::FsResult;
	#define FileSystemInternal FileSystemWin

	class NdGameSdk_API FileSystem : public ISdkComponent {
	public:
		FileSystem();
		SDK_DEPENDENCIES(EngineComponents);

		FileSystemData* GetFileSystemData();

	private:
		void Initialize() override;
		void Awake() override;

		FileSystemInternal* GetFileSystem() const;

		static DMENU::ItemSubmenu* CreateFileSystemMenu(NdDevMenu* pdmenu, DMENU::Menu* pMenu);

		/*Extern Functs*/
		static void Init(FileSystemInternal* pFileSys);

		EngineComponents* m_EngineComponents;

		InlineHook m_FileSystemInitHook{};

		/*Extern variables*/
		static FileSystemData* g_FileSystemDataSlot;

		friend class NdDevMenu;
	};

	class NdGameSdk_API FileSystemWin : public ISdkRegenny<regenny::shared::ndlib::io::FileSystem> {
	public:
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

		class ArchiveMount : public ISdkRegenny<regenny::shared::ndlib::io::FileSystem::ArchiveMount> {
		public:
			uint64_t GetId() const;
			uint64_t GetSize() const;

			const char* GetMountPath() const;
			const char* GetArchivePath() const;

		private:
			regenny::shared::ndlib::io::FileSystem::ArchiveMount::Buffer* GetBuffer() const;
		};

		Overlay& GetOverlay();
		bool IsInitialized() const;
		Memory::Allocator& GetAllocator();
	};

	static_assert(sizeof(FileSystemWin) == 0x220, "Invalid FileSystemWin size");
	static_assert(sizeof(FileSystemWin::Overlay) == 0x60, "Invalid Overlay size");
	static_assert(sizeof(FileSystemWin::ReadOnlyFileHandle) == 0x20, "Invalid ReadOnlyFileHandle size");
	static_assert(sizeof(FileSystemWin::ReadOperation) == 0x18, "Invalid ReadOperation size");
	static_assert(sizeof(FileSystemWin::ArchiveMount) == 0x10, "Invalid ArchiveMount size");

#endif

}