#pragma once

#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/components/SdkComponent.hpp"

#include <NdGameSdk/shared/src/corelib/system/NdSystem.hpp>
#include <NdGameSdk/shared/src/corelib/memory/memory.hpp>
#include <NdGameSdk/shared/src/corelib/job/job-system.hpp>
#include <NdGameSdk/shared/src/ndlib/frame-params.hpp>
#include <NdGameSdk/shared/src/ndlib/debug/nd-dmenu.hpp>

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/ndlib/io/PackageMgr.hpp>
#include <NdGameSdk/regenny/t2r/shared/ndlib/io/PackageProcessingInfo.hpp>
#endif

#include <future>
#include <boost/function.hpp>

#include "package.hpp"
#include "package-util.hpp"

namespace NdGameSdk::ndlib { class EngineComponents; }

using namespace NdGameSdk::corelib::system::platform;
using namespace NdGameSdk::corelib::memory;
using namespace NdGameSdk::corelib::job;
using namespace NdGameSdk::gamelib::debug;
using namespace NdGameSdk::gamelib::level;
using namespace NdGameSdk::ndlib;
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
		std::string GetStatusString() const;
		Package::PakHeader& GetPakHeader();

		static std::string GetStatusString(LoadingStatus status);
	};

	class NdGameSdk_API PackageMgr : public ISdkRegenny<regenny::shared::ndlib::io::PackageMgr> {
	public:
		using PackageCategory = regenny::shared::ndlib::io::PackageMgr::PackageCategory;

		class Configuration : public ISdkRegenny<regenny::shared::ndlib::io::PackageMgr::Configuration>  {
		public:
			int GetFreePackageSlots() const;
			int GetAllocationRingBufferSize() const;

			void SetFreePackageSlots(int slots);
			void SetAllocationRingBufferSize(int size);
		};

		class PackageRequest : public ISdkRegenny<regenny::shared::ndlib::io::PackageMgr::PackageRequest> {
		public:
			using RequestType = regenny::shared::ndlib::io::PackageMgr::PackageRequest::RequestType;

			PackageRequest() = default;

			PackageRequest(
				RequestType requestType,
				StringId64 packId, 
				const char* name,
				Level* level = nullptr,
				PackageCategory category = PackageCategory::Initial
			) {
				auto self = this->Get();
				self->m_RequestType = requestType;
				self->m_packid = packId;
				std::strncpy(self->m_name, name, sizeof(self->m_name) - 1);
				self->m_Level = reinterpret_cast<regenny::shared::gamelib::level::Level*>(level);
				self->m_category = category;
			}

			RequestType GetRequestType() const;
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

		class ProcessingRingBuffer : public ISdkRegenny<regenny::shared::ndlib::io::PackageMgr::ProcessingRingBuffer> {
		public:
			int GetProcessingCount() const;
			PackageProcessingInfo** GetSlotArray() const;
			uint32_t Capacity()	const;
			uint32_t Head()	const;

			struct Iterator {
				const ProcessingRingBuffer* ring;
				uint32_t offset;

				PackageProcessingInfo* operator*() const {
					const uint32_t idx = (ring->Head() + offset) % ring->Capacity();
					return ring->GetSlotArray()[idx];
				}

				Iterator& operator++() { ++offset; return *this; }
				friend bool operator==(const Iterator& a, const Iterator& b) { return a.ring == b.ring && a.offset == b.offset; }
				friend bool operator!=(const Iterator& a, const Iterator& b) { return !(a == b); }
			};

			Iterator begin() const { return { this,0u }; }
			Iterator end() const { return { this,static_cast<uint32_t>(GetProcessingCount()) }; }
			std::size_t size() const { return static_cast<std::size_t>(GetProcessingCount()); }
		};

		int GetFreePackageSlots() const;
		int GetAllocationRingBufferSize() const;
		Memory::Context& GetRingBufferContext() const;
		Memory::Context& GetMemoryContext() const;

		Package* PackageHead();
		const Package* PackageHead() const;
		PackageProcessingInfo* PackageHeadProcessingInfo();
		const PackageProcessingInfo* PackageHeadProcessingInfo() const;

		PackageRequestInfo& GetPackageRequestInfo();

		ProcessingRingBuffer& GetProcessingLoadQueue() const;
		ProcessingRingBuffer& GetProcessingUpdateQueue() const;
		ProcessingRingBuffer& GetProcessingUnloadQueue() const;

		Mutex* GetLoadingLock() const;
		Mutex* GetLoginLock() const;

		int GetPackageReleaseVramCount();
		PackageProcessingInfo** GetPendingPackageVramRelease();

		/*Virtual Funcs*/
		bool PackageLoginResItem(Package* pPackage, Package::ResItem* pResItem);
		void ReleaseLoadedVramPages();

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

		struct PackageProcessingIterator {
			PackageProcessingInfo* base;
			std::size_t idx;

			PackageProcessingInfo* operator*() const {
				auto p = reinterpret_cast<char*>(base);
				return reinterpret_cast<PackageProcessingInfo*>(p + idx * sizeof(PackageProcessingInfo));
			}

			PackageProcessingIterator& operator++() { ++idx; return *this; }
			bool operator!=(const PackageProcessingIterator& o) const { return idx != o.idx; }
		};

		struct PackageProcessingRange {
			PackageProcessingIterator begin_it, end_it;

			PackageProcessingIterator begin() const { return begin_it; }
			PackageProcessingIterator end()   const { return end_it; }
			std::size_t               size()  const { return end_it.idx; }
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

		PackageProcessingRange ProcessingInfos() {
			auto* head = PackageHeadProcessingInfo();
			auto  count = static_cast<std::size_t>(GetFreePackageSlots());
			return { { head,0 }, { head,count } };
		}

		PackageProcessingRange ProcessingInfos() const {
			auto* head = const_cast<PackageMgr*>(this)->PackageHeadProcessingInfo();
			auto  count = static_cast<std::size_t>(GetFreePackageSlots());
			return { { head,0 }, { head,count } };
		}

		inline static constexpr uint32_t kMaxNumPackagesAwaitingUnload = 0x800;
	};

	class NdGameSdk_API PackageManager : public ISdkComponent {
	public:
		using PackageLoginResItemCallback = boost::function<bool(PackageMgr*, Package*, Package::ResItem*)>;

		PackageManager();
		SdkEvent<PackageManager*> e_PackageManagerInitialized{true};
		SDK_DEPENDENCIES(EngineComponents, Memory, RenderFrameParams, NdJob);
		
		struct DumpHandle {
			CounterHandle* counter{ nullptr };
			uint32_t totalPackages{ 0 };
		};

		Package* GetPackageById(StringId64 PackId);
		PackageProcessingInfo* FetchPackageProcessingInfo(Package* pPackage);

		int GetNumUsedPackageSlots() const;
		int GetNumFreePackageSlots() const;
		bool HasFreePackageSlot() const;
		bool ArePackageQueuesIdle() const;

		bool RequestLoadPackage(const char* pPackageName, Level* pLevel = nullptr,
			PackageMgr::PackageCategory pCategory = PackageMgr::PackageCategory::Initial);
		bool RequestLogoutPackage(StringId64 pPackId);
		bool RequestReloadPackage(StringId64 pPackId);

	private:
		void Initialize() override;
		void Awake() override;

		PackageMgr* GetPackageMgr() const;
		bool ProcessLoginQueue(float budgetSec = 0x3f800000);
		bool AddPackageRequest(PackageMgr::PackageRequest* pPackageRequest);

		std::expected<std::vector<Package::ResItem*>, std::string> ParseResources(PackageProcessingInfo* ppi);
		DumpHandle DumpPackageResourcesAsync(
			std::span<const std::string> packages, PackageLoginResItemCallback onResItem,
			uint32_t maxConcurrentLogins = 10, bool wait = false);

		struct Dumper {
			struct Ctx {
				PackageLoginResItemCallback cb{};
				uint32_t count{ 0 };
				char* namesRaw{};
				char** names{};
				StringId64* ids{};
				StringId64* batchIds{};
				uint32_t maxConcurrent{ 8 };
				bool selfFree{ true };
			};

			struct ResWork {
				Package* pkg{};
				Package::ResItem* res{};
				PackageLoginResItemCallback cb{};
			};

			static void __cdecl Coordinator(Ctx* ctx);
			static void __cdecl ResEntry(uint64_t arg);
			static void FreeCtx(Ctx* c);

			static Mutex s_DumperMutex;
		};


		static bool TestDumpPackages(DMENU::ItemFunction& pFunction, DMENU::Message pMessage);
		static bool TestLoginPackage(DMENU::ItemFunction& pFunction, DMENU::Message pMessage);
		static bool TestParseResources(DMENU::ItemFunction& pFunction, DMENU::Message pMessage);

		static DMENU::ItemSubmenu* CreatePackageManagerMenu(NdDevMenu* pdmenu, DMENU::Menu* pMenu);

		/*Extern Functs*/
		static void Init(PackageMgr* pPackageMgr, PackageMgr::Configuration* pConfiguration);
		static void PackageManagerInitialized(SafetyHookContext& ctx);

		EngineComponents* m_EngineComponents;
		RenderFrameParams* m_RenderFrameParams;
		Memory* m_Memory;
		NdJob* m_JobSystem;

		InlineHook m_PackageMgrInitHook{};
		MidHook m_PackageMgrInitReturnHook{};

		MEMBER_FUNCTION_PTR(Package*, PackageMgr_GetPackageById, PackageMgr* pPackageMgr, StringId64 PackId);
		MEMBER_FUNCTION_PTR(PackageProcessingInfo*, PackageMgr_GetProcessingInfoFromPackage, PackageMgr* pPackageMgr, Package* pPackage);
		MEMBER_FUNCTION_PTR(Package::Status, PackageMgr_GetPackageStatusById, PackageMgr* pPackageMgr, StringId64 PackId);
		MEMBER_FUNCTION_PTR(Package*, PackageMgr_GetPackageByIndex, PackageMgr* pPackageMgr, uint32_t index, bool MustBeLoaded);
		
		MEMBER_FUNCTION_PTR(void, PackageMgr_UpdatePackageStatus, PackageProcessingInfo* pPackageInfo, PackageProcessingInfo::LoadingStatus status);
		MEMBER_FUNCTION_PTR(void, PackageMgr_SetPackageStatus, PackageProcessingInfo* pPackageInfo);

		MEMBER_FUNCTION_PTR(bool, PackageMgr_ProcessLoginQueue, PackageMgr* pPackageMgr, float budgetSec);
		MEMBER_FUNCTION_PTR(PackageProcessingInfo*, PackageMgr_PreparePackageForLoading, PackageMgr* pPackageMgr, const char* pPackageName, uint32_t arg3);
		MEMBER_FUNCTION_PTR(uint32_t, PackageMgr_LogoutPackage, PackageMgr* pPackageMgr, PackageProcessingInfo* pPackageInfo);

		MEMBER_FUNCTION_PTR(bool, PackageMgr_PackageQueuesIdle, PackageMgr* pPackageMgr);
		MEMBER_FUNCTION_PTR(void, PackageMgr_RequestLoadPackage, PackageMgr* pPackageMgr, const char* pPackageName, Level* pLevel, uint32_t isNumberedPart, PackageMgr::PackageCategory pCategory);
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