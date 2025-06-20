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

		Package* GetPackage() const;
		LoadingStatus GetStatus() const;
		Package::PakHeader& GetPakHeader();
	};

	class NdGameSdk_API PackageMgr : public ISdkRegenny<regenny::shared::ndlib::io::PackageMgr> {
	public:

		class Configuration : public ISdkRegenny<regenny::shared::ndlib::io::PackageMgr::Configuration>  {
		public:
			int GetFreePackageSlots() const;
			int GetAllocationRingBufferSize() const;

			void SetFreePackageSlots(int slots);
			void SetAllocationRingBufferSize(int size);
		};

		class PackageRequest : public ISdkRegenny<regenny::shared::ndlib::io::PackageMgr::PackageRequest> {
		public:
			PackageRequest() = default;

			PackageRequest(
				uint64_t requestType, 
				StringId64 packId, 
				const char* name,
				uint64_t level
			) {
				auto self = this->Get();
				self->m_RequestType = requestType;
				self->m_packid = packId;
				std::strncpy(self->m_name, name, sizeof(self->m_name) - 1);
				self->m_Level = level;
			}

			uint64_t GetRequestType() const;
			StringId64 GetPackId() const;
		};

		class PackageRequestInfo : public ISdkRegenny<regenny::shared::ndlib::io::PackageMgr::PackageRequestInfo> {
		public:
			uint32_t GetTotalRequests() const;
			uint32_t GetOverAllRequests() const;
			uint32_t GetNumRequests() const;
			uint32_t GetLimitRequests() const;
			PackageRequest* GetRequests();
		};

		int GetFreePackageSlots() const;
		int GetAllocationRingBufferSize() const;
		int GetProcessingCount() const;
		uint64_t GetNumAwaitingLogout() const;
		uint64_t GetNumAwaitingUpdate() const;
		uint64_t GetNumAwaitingUnload() const;
		Memory::Context& GetMemoryContext() const;

		Package* PackageHead();
		const Package* PackageHead() const;
		PackageProcessingInfo** GetProcessingArray() const;

		PackageRequestInfo& GetPackageRequestInfo();

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

		inline static constexpr uint32_t kMaxNumPackagesAwaitingUnload = 0x800;
	};


	class NdGameSdk_API PackageManager : public ISdkComponent {
	public:

		PackageManager();

		SdkEvent<PackageManager*> e_PackageManagerInitialized{true};

		SDK_DEPENDENCIES(ndlib::EngineComponents);
		
		Package* GetPackageById(StringId64 PackId);
		bool ArePackageQueuesIdle() const;
		bool RequestLoadPackage(const char* pPackageName);
		bool RequestLogoutPackage(StringId64 pPackId);
		bool RequestReloadPackage(StringId64 pPackId);

	private:
		void Initialize() override;
		void Awake() override;

		static bool TestFunct(DMENU::ItemFunction& pFunction, DMENU::Message pMessage);

		PackageMgr* GetPackageMgr() const;
		bool AddPackageRequest(PackageMgr::PackageRequest* pPackageRequest);

		static DMENU::ItemSubmenu* CreatePackageManagerMenu(NdDevMenu* pdmenu, DMENU::Menu* pMenu);

		/*Extern Functs*/
		static void Init(PackageMgr* pPackageMgr, PackageMgr::Configuration* pConfiguration);
		static void PackageManagerInitialized(SafetyHookContext& ctx);

		ndlib::EngineComponents* m_EngineComponents;

		InlineHook m_PackageMgrInitHook{};
		MidHook m_PackageMgrInitReturnHook{};

		MEMBER_FUNCTION_PTR(Package*, PackageMgr_GetPackageById, PackageMgr* pPackageMgr, StringId64 PackId);
		MEMBER_FUNCTION_PTR(Package::Status, PackageMgr_GetPackageStatusById, PackageMgr* pPackageMgr, StringId64 PackId);
		MEMBER_FUNCTION_PTR(Package*, PackageMgr_GetPackageByIndex, PackageMgr* pPackageMgr, uint32_t index, bool MustBeLoaded);
		
		MEMBER_FUNCTION_PTR(void, PackageMgr_UpdatePackageStatus, PackageProcessingInfo* pPackageInfo, PackageProcessingInfo::LoadingStatus status);
		MEMBER_FUNCTION_PTR(void, PackageMgr_SetPackageStatus, PackageProcessingInfo* pPackageInfo);

		MEMBER_FUNCTION_PTR(PackageProcessingInfo*, PackageMgr_PreparePackageForLoading, PackageMgr* pPackageMgr, const char* pPackageName, uint32_t arg3);
		MEMBER_FUNCTION_PTR(uint32_t, PackageMgr_LogoutPackage, PackageMgr* pPackageMgr, PackageProcessingInfo* pPackageInfo);
		MEMBER_FUNCTION_PTR(bool, PackageMgr_PackageLoginResItem, PackageMgr* pPackageMgr, Package* pPackage, Package::ResItem* pResItem);

		MEMBER_FUNCTION_PTR(bool, PackageMgr_PackageQueuesIdle, PackageMgr* pPackageMgr);
		MEMBER_FUNCTION_PTR(void, PackageMgr_RequestLoadPackage, PackageMgr* pPackageMgr, const char* pPackageName, uint64_t pLevel, uint32_t arg4, uint32_t arg5);
		MEMBER_FUNCTION_PTR(void, PackageMgr_RequestLogoutPackage, PackageMgr* pPackageMgr, StringId64 pPackId);
		MEMBER_FUNCTION_PTR(void, PackageMgr_RequestReloadPackage, PackageMgr* pPackageMgr, StringId64 pPackId);
		MEMBER_FUNCTION_PTR(void, PackageMgr_AddRequest, PackageMgr::PackageRequestInfo* pRequestInfo, PackageMgr::PackageRequest* pPackageRequest);

		friend class NdDevMenu;
	};

	TYPEDEF_EXTERN_FUNCTION_PTR(const char*, PackageMgr_PackageProcessingInfo_GetStatusString, PackageProcessingInfo::LoadingStatus status);

	static_assert(sizeof(PackageMgr) == 0x4f70, "PackageMgr size mismatch! Please check the SDK version and the game version.");
	static_assert(sizeof(PackageMgr::Configuration) == 0x50, "PackageMgr::Configuration size mismatch! Please check the SDK version and the game version.");
	static_assert(sizeof(PackageProcessingInfo) == 0xad0, "PackageProcessingInfo size mismatch! Please check the SDK version and the game version.");

#endif
}