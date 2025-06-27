#include "package-mgr.hpp"
#include "./NdGameSdk/shared/sharedpatterns.hpp"


#include <NdGameSdk/shared/src/ndlib/engine-components.hpp>
#include <NdGameSdk/shared/src/gamelib/debug/nd-dev-menu.hpp>

namespace NdGameSdk::ndlib::io {

#if defined(T2R)
	PackageManager::PackageManager() : ISdkComponent(TOSTRING(PackageManager)) {}

	void PackageManager::Awake() {
		auto SharedComponents = ISdkComponent::GetSharedComponents();
		m_EngineComponents = GetDependencyComponent<ndlib::EngineComponents>(SharedComponents);
	}

	void PackageManager::Initialize() {
		static std::once_flag Initialized;
		std::call_once(Initialized, [this] {
			spdlog::info("Initializing {} patterns...", GetName());

			Patterns::SdkPattern findpattern{};
			auto module = Utility::memory::get_executable();

			findpattern = Patterns::PackageMgr_Init;
			auto PackageMgrInit = (void*)Utility::FindAndPrintPattern(module
				, findpattern.pattern, wstr(Patterns::PackageMgr_Init), findpattern.offset);

			findpattern = Patterns::PackageMgr_InitReturn;
			auto PackageMgrInitReturn = (void*)Utility::FindAndPrintPattern(module
				, findpattern.pattern, wstr(Patterns::PackageMgr_InitReturn), findpattern.offset);

			if (!PackageMgrInit || 
				!PackageMgrInitReturn) {
				throw SdkComponentEx{ std::format("Failed to find PackageMgr patterns!"),
					SdkComponentEx::ErrorCode::PatternFailed };
			}

            findpattern = Patterns::PackageMgr_GetPackageById;
            PackageMgr_GetPackageById = (PackageMgr_GetPackageById_ptr)Utility::FindAndPrintPattern(module,
                findpattern.pattern, wstr(Patterns::PackageMgr_GetPackageById), findpattern.offset);

            findpattern = Patterns::PackageMgr_GetPackageStatusById;
            PackageMgr_GetPackageStatusById = (PackageMgr_GetPackageStatusById_ptr)Utility::FindAndPrintPattern(module,
                findpattern.pattern, wstr(Patterns::PackageMgr_GetPackageStatusById), findpattern.offset);

            findpattern = Patterns::PackageMgr_GetPackageByIndex;
            PackageMgr_GetPackageByIndex = (PackageMgr_GetPackageByIndex_ptr)Utility::FindAndPrintPattern(module,
                findpattern.pattern, wstr(Patterns::PackageMgr_GetPackageByIndex), findpattern.offset);

            findpattern = Patterns::PackageMgr_UpdatePackageStatus;
            PackageMgr_UpdatePackageStatus = (PackageMgr_UpdatePackageStatus_ptr)Utility::FindAndPrintPattern(module,
                findpattern.pattern, wstr(Patterns::PackageMgr_UpdatePackageStatus), findpattern.offset);

            findpattern = Patterns::PackageMgr_SetPackageStatus;
            PackageMgr_SetPackageStatus = (PackageMgr_SetPackageStatus_ptr)Utility::FindAndPrintPattern(module,
                findpattern.pattern, wstr(Patterns::PackageMgr_SetPackageStatus), findpattern.offset);

            findpattern = Patterns::PackageMgr_PreparePackageForLoading;
            PackageMgr_PreparePackageForLoading = (PackageMgr_PreparePackageForLoading_ptr)Utility::FindAndPrintPattern(module,
                findpattern.pattern, wstr(Patterns::PackageMgr_PreparePackageForLoading), findpattern.offset);

            findpattern = Patterns::PackageMgr_LogoutPackage;
            PackageMgr_LogoutPackage = (PackageMgr_LogoutPackage_ptr)Utility::FindAndPrintPattern(module,
                findpattern.pattern, wstr(Patterns::PackageMgr_LogoutPackage), findpattern.offset);

            findpattern = Patterns::PackageMgr_PackageQueuesIdle;
            PackageMgr_PackageQueuesIdle = (PackageMgr_PackageQueuesIdle_ptr)Utility::FindAndPrintPattern(module,
                findpattern.pattern, wstr(Patterns::PackageMgr_PackageQueuesIdle), findpattern.offset);

            findpattern = Patterns::PackageMgr_RequestLoadPackage;
            PackageMgr_RequestLoadPackage = (PackageMgr_RequestLoadPackage_ptr)Utility::FindAndPrintPattern(module,
                findpattern.pattern, wstr(Patterns::PackageMgr_RequestLoadPackage), findpattern.offset);

            findpattern = Patterns::PackageMgr_RequestLogoutPackage;
            PackageMgr_RequestLogoutPackage = (PackageMgr_RequestLogoutPackage_ptr)Utility::FindAndPrintPattern(module,
                findpattern.pattern, wstr(Patterns::PackageMgr_RequestLogoutPackage), findpattern.offset);

            findpattern = Patterns::PackageMgr_RequestReloadPackage;
            PackageMgr_RequestReloadPackage = (PackageMgr_RequestReloadPackage_ptr)Utility::FindAndPrintPattern(module,
                findpattern.pattern, wstr(Patterns::PackageMgr_RequestReloadPackage), findpattern.offset);

            findpattern = Patterns::PackageMgr_AddRequest;
            PackageMgr_AddRequest = (PackageMgr_AddRequest_ptr)Utility::FindAndPrintPattern(module,
                findpattern.pattern, wstr(Patterns::PackageMgr_AddRequest), findpattern.offset);

			findpattern = Patterns::PackageMgr_PackageProcessingInfo_GetStatusString;
			PackageMgr_PackageProcessingInfo_GetStatusString = (PackageMgr_PackageProcessingInfo_GetStatusString_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::PackageMgr_PackageProcessingInfo_GetStatusString), findpattern.offset);

			findpattern = Patterns::PackageMgr_Package_ResolvePakItem;
			PackageMgr_Package_ResolvePakItem = (PackageMgr_Package_ResolvePakItem_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::PackageMgr_Package_ResolvePakItem), findpattern.offset);

			findpattern = Patterns::PackageMgr_Package_GetStatusString;
			PackageMgr_Package_GetStatusString = (PackageMgr_Package_GetStatusString_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::PackageMgr_Package_GetStatusString), findpattern.offset);

			findpattern = Patterns::PackageMgr_GetPakHdrPageEntry;
			PackageMgr_GetPakHdrPageEntry = (PackageMgr_GetPakHdrPageEntry_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::PackageMgr_GetPakHdrPageEntry), findpattern.offset);

			findpattern = Patterns::PackageMgr_ResolvePakPagePtr;
			PackageMgr_ResolvePakPagePtr = (PackageMgr_ResolvePakPagePtr_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::PackageMgr_ResolvePakPagePtr), findpattern.offset);

			if(!PackageMgr_GetPackageById ||
				!PackageMgr_GetPackageStatusById ||
				!PackageMgr_GetPackageByIndex ||
				!PackageMgr_UpdatePackageStatus ||
				!PackageMgr_SetPackageStatus ||
				!PackageMgr_PreparePackageForLoading ||
				!PackageMgr_LogoutPackage ||
				!PackageMgr_PackageQueuesIdle ||
				!PackageMgr_RequestLoadPackage ||
				!PackageMgr_RequestLogoutPackage ||
				!PackageMgr_RequestReloadPackage ||
				!PackageMgr_AddRequest ||
				!PackageMgr_PackageProcessingInfo_GetStatusString ||
				!PackageMgr_Package_ResolvePakItem ||
				!PackageMgr_Package_GetStatusString ||
				!PackageMgr_GetPakHdrPageEntry ||
				!PackageMgr_ResolvePakPagePtr
			) {
				throw SdkComponentEx{ std::format("Failed to find {}:: game functions!", GetName()), SdkComponentEx::ErrorCode::PatternFailed };
			}

			m_PackageMgrInitHook = Utility::MakeSafetyHookInline(PackageMgrInit, Init,
				wstr(Patterns::PackageMgr_Init), wstr(PackageManager::Init));

			m_PackageMgrInitReturnHook = Utility::MakeMidHook(PackageMgrInitReturn, PackageManagerInitialized,
				wstr(Patterns::PackageMgr_InitReturn), wstr(PackageManager::PackageManagerInitialized));

			if (!m_PackageMgrInitHook ||
				!m_PackageMgrInitReturnHook) {
				throw SdkComponentEx{ "Failed to create hooks!", SdkComponentEx::ErrorCode::PatchFailed };
			}

		});
	}

	PackageMgr* PackageManager::GetPackageMgr() const {
		return &m_EngineComponents->GetPackageMgr();
	}

	bool PackageManager::AddPackageRequest(PackageMgr::PackageRequest* pPackageRequest) {
		always_assert(PackageMgr_AddRequest == nullptr, "Function pointer was not set!");
		PackageMgr_AddRequest(&GetPackageMgr()->GetPackageRequestInfo(), pPackageRequest);
		return true;
	}

	std::expected<std::vector<Package::ResItem*>, std::string> 
		PackageManager::ParseResources(PackageProcessingInfo* ppi) {

		PackageMgr* mgr = GetPackageMgr();
		Package* pkg = ppi->GetPackage();

		always_assert(pkg == nullptr, "PackageProcessingInfo did not have a package set!");

		using LoadingStatus = PackageProcessingInfo::LoadingStatus;
		static constexpr std::array<LoadingStatus, 3> allowedStatuses = {
			LoadingStatus::LoadingPackageStatusLoaded,
			LoadingStatus::LoadingPackageStatusDoingLogin,
			LoadingStatus::LoadingPackageStatusFinalizing
		};

		if (std::none_of(allowedStatuses.begin(), allowedStatuses.end(),
			[status = ppi->GetStatus()](LoadingStatus s) { return s == status; })) {
			return std::unexpected{ "Login package did not have a proper status" };
		}

		const Package::PakHeader& hdr = ppi->GetPakHeader();
		Package::ResPage* pResPage = ResolvePakPage(mgr, pkg, hdr->m_pakLoginTableIdx);

		if (!pResPage) {
			return std::unexpected{ "failed to resolve login-table page" };
		}

		PakLoginTableEntry* pPakLoginTable =
			reinterpret_cast<PakLoginTableEntry*>(reinterpret_cast<std::byte*>(pResPage) + hdr->m_pakLoginTableOffset);

		if (pPakLoginTable->GetResourceType() != Package::ItemId::PAK_LOGIN_TABLE) {
			return std::unexpected{ "pakLoginTable resource type was not PAK_LOGIN_TABLE" };
		}

		std::vector<Package::ResItem*> ResOut;
		const uint32_t maxResources = pPakLoginTable->GetMaxResources();
		PakLoginTableEntry::ResourcePair* pPairs = pPakLoginTable->GetPairs();

		for (uint32_t i = 0; i < maxResources; ++i)
		{
			uint32_t pageIdx = pPairs[i].GetPageIdx();
			uint32_t itemOfs = pPairs[i].GetItemOfs();

			uint32_t flags = pkg->Get()->m_LoginTableFlags[pageIdx];

			if ((flags & 0x3) == 0x3
				|| (flags & 0xC) == 0xC
				|| (flags & 0xFFF0) == 0xFFF0
				|| (flags & 0xFF0000) == 0x800000)
				continue;

			Package::ResPage* pageBase = ResolvePakPage(mgr, pkg, pageIdx);

			if (!pageBase) continue;

			Package::ResItem* res = reinterpret_cast<Package::ResItem*>(
				reinterpret_cast<std::byte*>(pageBase) + itemOfs);

			ResOut.push_back(res);
		}

		return ResOut;
	}

	bool PackageManager::ArePackageQueuesIdle() const {
	#if defined(T2R) || defined(T1X)
		always_assert(PackageMgr_PackageQueuesIdle == nullptr, "Function pointer was not set!");
		return PackageMgr_PackageQueuesIdle(GetPackageMgr());
	#else
		auto PackageMgr = GetPackageMgr();
		return PackageMgr->GetPackageRequestInfo().GetNumRequests() <= 0 &&
			PackageMgr->GetProcessingLoadQueue().GetProcessingCount() <= 0 &&
			PackageMgr->GetProcessingUpdateQueue().GetProcessingCount() <= 0 &&
			PackageMgr->GetProcessingUnloadQueue().GetProcessingCount() <= 0 &&
			PackageMgr->GetPackageReleaseVramCount() <= 0;
	#endif
	}

	bool PackageManager::RequestLoadPackage(const char* pPackageName, Level* pLevel, PackageMgr::PackageCategory pCategory) {
	#if defined(T2R) || defined(T1X)
		always_assert(PackageMgr_RequestLoadPackage == nullptr, "Function pointer was not set!");
		PackageMgr_RequestLoadPackage(GetPackageMgr(), pPackageName, pLevel, 0x0, pCategory);
		return true;
	#else
		PackageMgr::PackageRequest packageRequest {
			PackageMgr::PackageRequest::RequestType::Login,
			SID(pPackageName),
			pPackageName,
			pLevel,
			pCategory
		};

		return AddPackageRequest(&packageRequest);
	#endif
	}

	bool PackageManager::RequestLogoutPackage(StringId64 pPackId) {
	#if defined(T2R) || defined(T1X)
		always_assert(PackageMgr_RequestLogoutPackage == nullptr, "Function pointer was not set!");
		PackageMgr_RequestLogoutPackage(GetPackageMgr(), pPackId);
		return true;
	#else
		auto pPackage = GetPackageById(pPackId);
		if (pPackage) {
			PackageMgr::PackageRequest packageRequest{
				PackageMgr::PackageRequest::RequestType::Logout,
				pPackage->GetPackId(),
				pPackage->GetName(),
				nullptr
			};
			return AddPackageRequest(&packageRequest);
		}
		return false;
	#endif
	}

	bool PackageManager::RequestReloadPackage(StringId64 pPackId) {
#if defined(T2R) || defined(T1X)
		always_assert(PackageMgr_RequestReloadPackage == nullptr, "Function pointer was not set!");
		PackageMgr_RequestReloadPackage(GetPackageMgr(), pPackId);
		return true;
#else
		auto pPackage = GetPackageById(pPackId);
		if (pPackage) {
			PackageMgr::PackageRequest packageRequest{
				PackageMgr::PackageRequest::RequestType::Logout,
				pPackage->GetPackId(),
				pPackage->GetName(),
				nullptr
			};

			AddPackageRequest(&packageRequest);

			PackageMgr::PackageRequest packageRequest{
				PackageMgr::PackageRequest::RequestType::Login,
				pPackage->GetPackId(),
				pPackage->GetName(),
				pPackage->GetLevel()
			};

			AddPackageRequest(&packageRequest);

			// TODO : Add a way to wait for the package to be reloaded or check if it was reloaded successfully.

			return true;
		}
		return false;
#endif
	}

	bool PackageManager::TestFunct(DMENU::ItemFunction& pFunction, DMENU::Message pMessage) {
		if (pMessage == DMENU::Message::OnExecute) {
			auto PackageMgr = reinterpret_cast<PackageManager*>(pFunction.Data());
			if (PackageMgr) {
				spdlog::info("TestFunct called!");

				const char* packageName = "world-patrol-jackson-ingame";

				if (!PackageMgr->GetPackageById(SID(packageName))) {
					spdlog::info("Package '{}' not found, requesting load...", packageName);
					if (PackageMgr->RequestLoadPackage(packageName, nullptr, PackageMgr::PackageCategory::LevelPak)) {
						spdlog::info("Load request for package '{}' sent successfully.", packageName);
					}
					else {
						spdlog::error("Failed to send load request for package '{}'.", packageName);
					}
				}
				else {
					spdlog::info("Package '{}' is already loaded.", packageName);
					PackageMgr->RequestLogoutPackage(SID(packageName));
					spdlog::info("Logout request for package '{}' sent successfully.", packageName);
				}

				return true;
			}
		}
		return true;
	}

	bool PackageManager::TestFunct2(DMENU::ItemFunction& pFunction, DMENU::Message pMessage) {
		if (pMessage == DMENU::Message::OnExecute) {
			auto PackageMgr = reinterpret_cast<PackageManager*>(pFunction.Data());
			if (PackageMgr) {
				spdlog::info("TestFunct2 called!");

				const char* packageName = "world-patrol-jackson-ingame";

				auto pPackage = PackageMgr->GetPackageById(SID(packageName));

				if (pPackage) {
					spdlog::info("Package '{}' found, fetching processing info...", packageName);
					auto pProcessingInfo = PackageMgr->FetchPackageProcessingInfo(pPackage);
					if (pProcessingInfo) {
						spdlog::info("Processing info for package '{}': Status = {}", packageName, pProcessingInfo->GetStatusString());

						if (pProcessingInfo->GetStatus() == PackageProcessingInfo::LoadingStatus::LoadingPackageStatusLoaded) {
							auto res = PackageMgr->ParseResources(pProcessingInfo);
							for (Package::ResItem* item : res.value_or({})) {
								if (item) {
									spdlog::info("Resource Item: Type = {}, Name = {}, Size = {} bytes",
										item->GetResourceTypeId(), item->GetResourceName(), item->GetPageSize());
								}
								else {
									spdlog::warn("Found a null resource item in package '{}'.", packageName);
								}
							}
						}
					}
					else {
						spdlog::error("Failed to fetch processing info for package '{}'.", packageName);
					}
				}
				else {
					spdlog::error("Package '{}' not found.", packageName);
				}

				return true;
			}
		}
		return true;
	}

	Package* PackageManager::GetPackageById(StringId64 PackId) {
		always_assert(PackageMgr_GetPackageById == nullptr, "Function pointer was not set!");
		return PackageMgr_GetPackageById(GetPackageMgr(), PackId);
	}

	PackageProcessingInfo* PackageManager::FetchPackageProcessingInfo(Package* pPackage) {
		if (!pPackage) return nullptr;

		auto* mgr = GetPackageMgr();
		auto range = mgr->ProcessingInfos();

		for (auto* info : range)
			if (info && info->GetPackage() == pPackage)
				return info;

		return nullptr;
	}

	void PackageManager::Init(PackageMgr* pPackageMgr, PackageMgr::Configuration* pConfiguration) {
		auto pPackageManager = Instance<PackageManager>();
		pPackageManager->m_PackageMgrInitHook.thiscall<void>(pPackageMgr, pConfiguration);
	}

	void PackageManager::PackageManagerInitialized(SafetyHookContext& ctx) {
		auto PackageMgrComponent = Instance<PackageManager>();
		PackageMgr* PackageMgr = reinterpret_cast<io::PackageMgr*>(ctx.rbx);
		PackageMgrComponent->InvokeSdkEvent(PackageMgrComponent->e_PackageManagerInitialized, PackageMgrComponent);
		return;
	}
		
	DMENU::ItemSubmenu* PackageManager::CreatePackageManagerMenu(NdDevMenu* pdmenu, DMENU::Menu* pMenu) {
		auto pPackageManager = Instance<PackageManager>();
		if (pPackageManager) {
			uint64_t PackageManagerAddr = reinterpret_cast<uint64_t>(static_cast<void*>(pPackageManager));
			DMENU::Menu* PackageManagerMenu = pdmenu->Create_DMENU_Menu(pPackageManager->GetName().data(), HeapArena_Source);
			if (PackageManagerMenu) {
			#if SDK_DEBUG
                pdmenu->Create_DMENU_ItemFunction("Test funct", PackageManagerMenu, &TestFunct, PackageManagerAddr, false, HeapArena_Source);
				pdmenu->Create_DMENU_ItemFunction("Test funct2", PackageManagerMenu, &TestFunct2, PackageManagerAddr, false, HeapArena_Source);

            #endif
				return pdmenu->Create_DMENU_ItemSubmenu(PackageManagerMenu->Name(),
					pMenu, PackageManagerMenu, NULL, NULL, nullptr, HeapArena_Source);
			}
		}
		return nullptr;
	}

	int PackageMgr::GetFreePackageSlots() const {
		return this->Get()->m_freepackageslots;
	}

	int PackageMgr::GetAllocationRingBufferSize() const {
		return this->Get()->m_allocationRingBufferSize;
	}

	Memory::Context& PackageMgr::GetMemoryContext() const {
		return this->Get()->m_memcontext;
	}

	Package* PackageMgr::PackageHead() {
		return reinterpret_cast<Package*>(this->Get()->m_packages);
	}

	const Package* PackageMgr::PackageHead() const {
		return reinterpret_cast<const Package*>(this->Get()->m_packages);
	}

	PackageProcessingInfo* PackageMgr::PackageHeadProcessingInfo() {
		return reinterpret_cast<PackageProcessingInfo*>(this->Get()->m_packageinfos);
	}

	const PackageProcessingInfo* PackageMgr::PackageHeadProcessingInfo() const {
		return reinterpret_cast<const PackageProcessingInfo*>(this->Get()->m_packageinfos);
	}

	PackageMgr::PackageRequestInfo& PackageMgr::GetPackageRequestInfo() {
		return reinterpret_cast<PackageRequestInfo&>(this->Get()->m_RequestInfo);
	}

	PackageMgr::ProcessingRingBuffer& PackageMgr::GetProcessingLoadQueue() const {
		return reinterpret_cast<ProcessingRingBuffer&>(this->Get()->m_processingLoadQueue);
	}

	PackageMgr::ProcessingRingBuffer& PackageMgr::GetProcessingUpdateQueue() const {
		return reinterpret_cast<ProcessingRingBuffer&>(this->Get()->m_processingUpdateQueue);
	}

	PackageMgr::ProcessingRingBuffer& PackageMgr::GetProcessingUnloadQueue() const {
		return reinterpret_cast<ProcessingRingBuffer&>(this->Get()->m_processingUnloadQueue);
	}

	int PackageMgr::Configuration::GetFreePackageSlots() const {
		return this->Get()->m_freepackageslots;
	}

	int PackageMgr::Configuration::GetAllocationRingBufferSize() const {
		return this->Get()->m_allocationRingBufferSize;
	}

	void PackageMgr::Configuration::SetFreePackageSlots(int slots) {
		this->Get()->m_freepackageslots = slots;
	}

	void PackageMgr::Configuration::SetAllocationRingBufferSize(int size) {
		this->Get()->m_allocationRingBufferSize = size;
	}

	int PackageMgr::GetPackageReleaseVramCount() {
		return this->Get()->m_PendingPackageVramReleaseCount;
	}

	PackageProcessingInfo** PackageMgr::GetPendingPackageVramRelease() {
		return reinterpret_cast<PackageProcessingInfo**>(this->Get()->m_PendingPackageVramRelease);
	}

	bool PackageMgr::PackageLoginResItem(Package* pPackage, Package::ResItem* pResItem) {
		return this->Get()->m_PackageLoginResFuncs->PackageLoginResItem(
			reinterpret_cast<regenny::shared::ndlib::io::Package*>(pPackage),
			reinterpret_cast<regenny::shared::ndlib::io::Package::ResItem*>(pResItem));
	}

	Package* PackageProcessingInfo::GetPackage() const {
		return reinterpret_cast<Package*>(this->Get()->m_package);
	}

	PackageProcessingInfo::LoadingStatus PackageProcessingInfo::GetStatus() const {
		return this->Get()->m_status;
	}

	std::string PackageProcessingInfo::GetStatusString() const {
		return GetStatusString(this->GetStatus());
	}

	Package::PakHeader& PackageProcessingInfo::GetPakHeader() {
		return reinterpret_cast<Package::PakHeader&>(this->Get()->m_pakHdr);
	}

	std::string PackageProcessingInfo::GetStatusString(LoadingStatus status) {
	#if defined(T2R) || defined(T1X)
		always_assert(PackageMgr_PackageProcessingInfo_GetStatusString == nullptr, "Function pointer was not set!");
		return PackageMgr_PackageProcessingInfo_GetStatusString(status);
	#else
		switch (status) {
		case LoadingStatus::LoadingPackageStatusUnused:
			return "Unused";
		case LoadingStatus::LoadingPackageStatusError:
			return "Error";
		case LoadingStatus::LoadingPackageStatusInvalid:
			return "Invalid";
		case LoadingStatus::LoadingPackageStatusWanted:
			return "Wanted";
		case LoadingStatus::LoadingPackageStatusOpenFile:
			return "OpenFile";
		case LoadingStatus::LoadingPackageStatusLoadingPakHeader:
			return "LoadingPakHeader";
		case LoadingStatus::LoadingPackageStatusLoadingHeader:
			return "LoadingHeader";
		case LoadingStatus::LoadingPackageStatusLoadingPages:
			return "LoadingPages";
		case LoadingStatus::LoadingPackageStatusLoadingVram:
			return "LoadingVram";
		case LoadingStatus::LoadingPackageStatusWaitingForVramPages:
			return "WaitingForVramPages";
		case LoadingStatus::LoadingPackageStatusDataIsLoaded:
			return "DataIsLoaded";
		case LoadingStatus::LoadingPackageStatusWaitingForVramProcessing:
			return "WaitingForVramProcessing";
		case LoadingStatus::LoadingPackageStatusDoingLogin:
			return "DoingLogin";
		case LoadingStatus::LoadingPackageStatusFinalizing:
			return "Finalizing";
		case LoadingStatus::LoadingPackageStatusLoaded:
			return "Loaded";
		case LoadingStatus::LoadingPackageStatusWaitingForLogout:
			return "WaitingForLogout";
		case LoadingStatus::LoadingPackageStatusDoingLogout:
			return "DoingLogout";
		case LoadingStatus::LoadingPackageStatusWaitingForUnload:
			return "WaitingForUnload";
		case LoadingStatus::LoadingPackageStatusFailedOptionalFile:
			return "FailedOptionalFile";
		default:
			return "Unknown";
		}
	#endif
	}

	PackageMgr::PackageRequest::RequestType PackageMgr::PackageRequest::GetRequestType() const {
		return this->Get()->m_RequestType;
	}

	StringId64 PackageMgr::PackageRequest::GetPackId() const {
		return this->Get()->m_packid;
	}

	uint32_t PackageMgr::PackageRequestInfo::GetTotalRequests() const {
		return this->Get()->m_totalrequested;
	}

	uint32_t PackageMgr::PackageRequestInfo::GetOverAllRequests() const {
		return this->Get()->m_overallrequested;
	}

	uint32_t PackageMgr::PackageRequestInfo::GetNumRequests() const {
		return this->Get()->m_numPackagesRequested;
	}

	uint32_t PackageMgr::PackageRequestInfo::GetLimitRequests() const {
		return this->Get()->m_maxrequestlimit;
	}

	PackageMgr::PackageRequest* PackageMgr::PackageRequestInfo::GetRequests() {
		return reinterpret_cast<PackageMgr::PackageRequest*>(this->Get()->m_PackagesRequested);
	}

	int PackageMgr::ProcessingRingBuffer::GetProcessingCount() const {
		return this->Get()->m_numQueued;
	}

	PackageProcessingInfo** PackageMgr::ProcessingRingBuffer::GetSlotArray() const {
		return reinterpret_cast<PackageProcessingInfo**>(this->Get()->m_slots);
	}

	uint32_t PackageMgr::ProcessingRingBuffer::Capacity() const {
		return this->Get()->m_capacity;
	}

	uint32_t PackageMgr::ProcessingRingBuffer::Head() const {
		return this->Get()->m_head;
	}

	INIT_FUNCTION_PTR(PackageMgr_PackageProcessingInfo_GetStatusString);

#endif
}


