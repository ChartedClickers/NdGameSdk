#pragma once



#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/components/SdkComponent.hpp"

#include <NdGameSdk/shared/src/corelib/memory/memory.hpp>
#include <NdGameSdk/shared/src/ndlib/debug/nd-dmenu.hpp>

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/ndlib/io/PackageMgr.hpp>
#include <NdGameSdk/regenny/t2r/shared/ndlib/io/PackageProcessingInfo.hpp>
#endif

#include "package.hpp"

namespace NdGameSdk::ndlib { class EngineComponents; }

using namespace NdGameSdk::corelib::memory;
using namespace NdGameSdk::gamelib::debug;
using namespace NdGameSdk::ndlib::debug;

namespace NdGameSdk::ndlib::io {

#if defined(T2R)
	/* Extern classes */
	class NdGameSdk_API PackageProcessingInfo : public ISdkRegenny<regenny::shared::ndlib::io::PackageProcessingInfo> 
	{
	public:
		using LoadingStatus = regenny::shared::ndlib::io::PackageProcessingInfo::LoadingStatus;
	};

	class NdGameSdk_API PackageMgr : public ISdkRegenny<regenny::shared::ndlib::io::PackageMgr> {
	public:

		class Configuration : public ISdkRegenny<regenny::shared::ndlib::io::PackageMgr::Configuration> 
		{
		public:
			int GetFreePackageSlots() const;
			int GetAllocationRingBufferSize() const;

			void SetFreePackageSlots(int slots);
			void SetAllocationRingBufferSize(int size);
		};

		int GetFreePackageSlots() const;
		int GetAllocationRingBufferSize() const;
		int GetProcessingCount() const;
		uint64_t GetNumAwaitingUnload() const;
		Memory::Context& GetMemoryContext() const;

		Package* PackageHead();
		const Package* PackageHead() const;
		PackageProcessingInfo** GetProcessingArray() const;


		struct PackageIterator {
			Package* base;
			std::size_t idx;

			Package* operator*() const {
				auto bytep = reinterpret_cast<char*>(base);
				return reinterpret_cast<Package*>(bytep + idx * sizeof(Package));
			}

			PackageIterator& operator++() { ++idx; return *this; }
			bool operator!=(PackageIterator const& o) const { return idx != o.idx; }
		};

		struct PackageRange {
			PackageIterator begin_it, end_it;
			PackageIterator begin() const { return begin_it; }
			PackageIterator end()   const { return end_it; }
			std::size_t     size()  const { return end_it.idx; }
		};
		
		struct ProcIt {
			PackageProcessingInfo** ptr;
			PackageProcessingInfo* operator*() const { return *ptr; }
			ProcIt& operator++() { ++ptr; return *this; }
			bool operator!=(ProcIt const& o) const { return ptr != o.ptr; }
		};

		struct ProcRange {
			ProcIt begin_it, end_it;
			ProcIt begin() const { return begin_it; }
			ProcIt end()   const { return end_it; }
			std::size_t size() const { return end_it.ptr - begin_it.ptr; }
		};

		PackageRange Packages() {
			auto* head = PackageHead();
			auto  count = static_cast<std::size_t>(GetFreePackageSlots());
			return { { head, 0 }, { head, count } };
		}

		PackageRange Packages() const {
			auto* head = const_cast<PackageMgr*>(this)->PackageHead();
			auto  count = static_cast<std::size_t>(GetFreePackageSlots());
			return { { head, 0 }, { head, count } };
		}

		ProcRange PackageProcessingQueue() const {
			auto** base = GetProcessingArray();
			auto   cnt = static_cast<std::size_t>(GetProcessingCount());
			return { { base }, { base + cnt } };
		};

		ProcRange PackageProcessing() const {
			auto** base = GetProcessingArray();
			auto   cnt = static_cast<std::size_t>(GetFreePackageSlots());
			return { { base }, { base + cnt } };
		};

	};


	class NdGameSdk_API PackageManager : public ISdkComponent {
	public:

		PackageManager();

		SdkEvent<PackageManager*> e_PackageManagerInitialized{true};

		SDK_DEPENDENCIES(ndlib::EngineComponents);

		/*Extern variables*/
		inline static constexpr uint32_t kMaxNumPackagesAwaitingUnload = 0x800;
	private:
		void Initialize() override;
		void Awake() override;

		static bool TestFunct(DMENU::ItemFunction& pFunction, DMENU::Message pMessage);

		/*Extern Functs*/
		static void Init(PackageMgr* pPackageMgr, PackageMgr::Configuration* pConfiguration);
		static void PackageManagerInitialized(SafetyHookContext& ctx);

		static DMENU::ItemSubmenu* CreatePackageManagerMenu(NdDevMenu* pdmenu, DMENU::Menu* pMenu);


		ndlib::EngineComponents* m_EngineComponents;

		InlineHook m_PackageMgrInitHook{};
		MidHook m_PackageMgrInitReturnHook{};

		friend class NdDevMenu;
	};

	static_assert(sizeof(PackageMgr) == 0x4f70, "PackageMgr size mismatch! Please check the SDK version and the game version.");
	static_assert(sizeof(PackageMgr::Configuration) == 0x50, "PackageMgr::Configuration size mismatch! Please check the SDK version and the game version.");
	static_assert(sizeof(PackageProcessingInfo) == 0xad0, "PackageProcessingInfo size mismatch! Please check the SDK version and the game version.");

#endif
}