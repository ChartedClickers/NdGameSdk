#include "package-mgr.hpp"
#include "./NdGameSdk/shared/sharedpatterns.hpp"


#include <NdGameSdk/shared/src/ndlib/engine-components.hpp>
#include <NdGameSdk/shared/src/gamelib/debug/nd-dev-menu.hpp>

namespace NdGameSdk::ndlib::io {

#if defined(T2R)
	PackageManager::PackageManager() : ISdkComponent(TOSTRING(PackageManager)) {}

	void PackageManager::Awake() {
		auto SharedComponents = ISdkComponent::GetSharedComponents();
		m_EngineComponents = GetDependencyComponent<EngineComponents>(SharedComponents);
		m_Memory = GetDependencyComponent<Memory>(SharedComponents);
		m_RenderFrameParams = GetDependencyComponent<RenderFrameParams>(SharedComponents);
		m_JobSystem = GetDependencyComponent<NdJob>(SharedComponents);
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

			findpattern = Patterns::PackageMgr_GetProcessingInfoFromPackage;
			PackageMgr_GetProcessingInfoFromPackage = (PackageMgr_GetProcessingInfoFromPackage_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::PackageMgr_GetProcessingInfoFromPackage), findpattern.offset);

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

			findpattern = Patterns::PackageMgr_ProcessLoginQueue;
			PackageMgr_ProcessLoginQueue = (PackageMgr_ProcessLoginQueue_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::PackageMgr_ProcessLoginQueue), findpattern.offset);

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
				!PackageMgr_GetProcessingInfoFromPackage ||
				!PackageMgr_GetPackageStatusById ||
				!PackageMgr_GetPackageByIndex ||
				!PackageMgr_UpdatePackageStatus ||
				!PackageMgr_SetPackageStatus ||
				!PackageMgr_ProcessLoginQueue ||
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

	bool PackageManager::ProcessLoginQueue(float budgetSec) {
		always_assert(PackageMgr_ProcessLoginQueue == nullptr, "Function pointer was not set!");
		return PackageMgr_ProcessLoginQueue(GetPackageMgr(), budgetSec);
	}

	bool PackageManager::AddPackageRequest(PackageMgr::PackageRequest* pPackageRequest) {
		always_assert(PackageMgr_AddRequest == nullptr, "Function pointer was not set!");
		PackageMgr_AddRequest(&GetPackageMgr()->GetPackageRequestInfo(), pPackageRequest);
		return true;
	}

	std::expected<std::vector<Package::ResItem*>, std::string> 
		PackageManager::ParseResources(PackageProcessingInfo* ppi) {

		PackageMgr* InternalMgr = GetPackageMgr();
		Package* pkg = ppi->GetPackage();

		always_assert(pkg == nullptr, "PackageProcessingInfo did not have a package set!");

		using LoadingStatus = PackageProcessingInfo::LoadingStatus;
		static constexpr std::array<LoadingStatus, 4> allowedStatuses = {
			LoadingStatus::LoadingPackageStatusDoingLogin,
			LoadingStatus::LoadingPackageStatusFinalizing,
			LoadingStatus::LoadingPackageStatusLoaded,
			LoadingStatus::LoadingPackageStatusWaitingForLogout
		};

		if (std::none_of(allowedStatuses.begin(), allowedStatuses.end(),
			[status = ppi->GetStatus()](LoadingStatus s) { return s == status; })) {
			return std::unexpected{ std::format("Login package did not have a proper status: {}", ppi->GetStatusString()) };
		}

		const Package::PakHeader& hdr = ppi->GetPakHeader();
		Package::ResPage* pResPage = ResolvePakPage(InternalMgr, pkg, hdr->m_pakLoginTableIdx);

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

		for (uint32_t i = 0; i < maxResources; ++i) {
			uint32_t pageIdx = pPairs[i].GetPageIdx();
			uint32_t itemOfs = pPairs[i].GetItemOfs();

			uint32_t flags = pkg->Get()->m_LoginTableFlags[pageIdx];

			if ((flags & 0x3) == 0x3
				|| (flags & 0xC) == 0xC
				|| (flags & 0xFFF0) == 0xFFF0
				|| (flags & 0xFF0000) == 0x800000)
				continue;

			Package::ResPage* pageBase = ResolvePakPage(InternalMgr, pkg, pageIdx);

			if (pageBase) {
				Package::ResItem* res = reinterpret_cast<Package::ResItem*>(
					reinterpret_cast<std::byte*>(pageBase) + itemOfs);
				ResOut.push_back(res);
			}

		}

		return ResOut;
	}

	PackageManager::DumpHandle PackageManager::DumpPackageResourcesAsync(
	std::span<const std::string> packages, PackageLoginResItemCallback onResItem,
	uint32_t maxConcurrentLogins, bool wait) {
		DumpHandle out{};
		if (packages.empty()) 
			return out;

		PackageMgr* InternalMgr = GetPackageMgr();

		auto* ctx = m_Memory->AllocateAtContext<Dumper::Ctx>(sizeof(Dumper::Ctx), 0x10, InternalMgr->GetMemoryContext());
		if (!ctx) return out;
		std::memset(ctx, 0, sizeof(*ctx));

		ctx->cb = onResItem;
		ctx->count = packages.size();
		ctx->maxConcurrent = std::max<uint32_t>(1, maxConcurrentLogins);
		ctx->selfFree = !wait;

		const size_t namesBytes = size_t(ctx->count) * Package::kMaxNameLength;
		ctx->namesRaw = m_Memory->AllocateAtContext<char>(namesBytes, 0x10, InternalMgr->GetMemoryContext());
		ctx->names = m_Memory->AllocateAtContext<char*>(sizeof(char*) * ctx->count, 0x10, InternalMgr->GetMemoryContext());
		ctx->ids = m_Memory->AllocateAtContext<StringId64>(sizeof(StringId64) * ctx->count, 0x10, InternalMgr->GetMemoryContext());
		ctx->batchIds = m_Memory->AllocateAtContext<StringId64>(sizeof(StringId64) * ctx->count, 0x10, InternalMgr->GetMemoryContext());

		for (uint32_t i = 0; i < ctx->count; ++i) {
			char* slot = ctx->namesRaw + size_t(i) * Package::kMaxNameLength;
			std::memset(slot, 0, Package::kMaxNameLength);
			std::strncpy(slot, packages[i].c_str(), Package::kMaxNameLength - 1);
			ctx->names[i] = slot;
			ctx->ids[i] = SID(slot);
		}

		CounterHandle* ctr = nullptr;
		m_JobSystem->SubmitJobArray(reinterpret_cast<void*>(Dumper::Coordinator),
			ctx, 1, NdJob::Priority::KNormal, HeapArena_Source, &ctr, NdJob::JobFlag::ArrayRoot);

		out.counter = ctr;
		out.totalPackages = ctx->count;

		if (wait && out.counter) {
			m_JobSystem->WaitForCounterAndFree(&out.counter, 0);
			Dumper::FreeCtx(ctx);
		}

		return out;
	}

	bool PackageManager::ArePackageQueuesIdle() const {
	#if defined(T2R) || defined(T1X)
		always_assert(PackageMgr_PackageQueuesIdle == nullptr, "Function pointer was not set!");
		return PackageMgr_PackageQueuesIdle(GetPackageMgr());
	#else
		auto InternalMgr = GetPackageMgr();
		return InternalMgr->GetPackageRequestInfo().GetNumRequests() <= 0 &&
			InternalMgr->GetProcessingLoadQueue().GetProcessingCount() <= 0 &&
			InternalMgr->GetProcessingUpdateQueue().GetProcessingCount() <= 0 &&
			InternalMgr->GetProcessingUnloadQueue().GetProcessingCount() <= 0 &&
			InternalMgr->GetPackageReleaseVramCount() <= 0;
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

	bool PackageManager::TestDumpPackages(DMENU::ItemFunction& pFunction, DMENU::Message pMessage) {
		if (pMessage == DMENU::Message::OnExecute) {
			auto pm = reinterpret_cast<PackageManager*>(pFunction.Data());
			if (pm) {


				spdlog::info("TestDumpPackages : launching DumpPackageResources (NdJobWorkerThread async)");

				static const std::vector<std::string> kPackages = {
					"t2r-anim-ratking",
					"t2r-anim-ellie-workbench",
					"t2r-anim-nor-sewers"
				};

				auto cb = [](PackageMgr*,
					Package* pkg,
					Package::ResItem* ri) -> bool
					{
						//const auto t = ri->GetResourceType();
						//if (t != Package::ItemId::ANIM && t != Package::ItemId::ANIM_STREAM) {
						//	return true;
						//}

						std::string_view name = ri->GetResourceName();
						spdlog::info("[Dump]  {:<28} {}", pkg->GetName(), name);
						return true;
					};

				auto handle = pm->DumpPackageResourcesAsync(kPackages, cb, 1, false);

				if (!handle.counter) {
					spdlog::error("Dump dispatch failed (no counter).");
					return true;
				}

				std::thread watcher([pm, ctr = handle.counter]() mutable {
					while (ctr->GetCountJobArrays() != 0) {
						spdlog::debug("[Dump] coordinator running remaining arrays={}", ctr->GetCountJobArrays());
						std::this_thread::sleep_for(std::chrono::milliseconds{ 500 });
					}
					pm->m_JobSystem->FreeCounter(&ctr);
					spdlog::info("Dump completed.");
					});
				watcher.detach();

				return true;
			}
		}
		return true;
	}

	bool PackageManager::TestLoginPackage(DMENU::ItemFunction& pFunction, DMENU::Message pMessage) {
		if (pMessage == DMENU::Message::OnExecute) {
			auto pm = reinterpret_cast<PackageManager*>(pFunction.Data());
			if (pm) {

				const char* packageName = "t2r-anim-ratking";

				if (!pm->GetPackageById(SID(packageName))) {
					spdlog::info("Package '{}' not found, requesting load...", packageName);
					if (pm->RequestLoadPackage(packageName, nullptr, PackageMgr::PackageCategory::GlobalPak)) {
						spdlog::info("Load request for package '{}' sent successfully.", packageName);
						pFunction.SetActive(true);
					}
					else {
						spdlog::error("Failed to send load request for package '{}'.", packageName);
					}
				}
				else {
					spdlog::info("Package '{}' is already loaded.", packageName);
					pm->RequestLogoutPackage(SID(packageName));
					pFunction.SetActive(false);
					spdlog::info("Logout request for package '{}' sent successfully.", packageName);
				}

				return true;
			}
		}

		if (pMessage == DMENU::Message::OnOpen) {
			auto pm = reinterpret_cast<PackageManager*>(pFunction.Data());
			if (pm) {
				const char* packageName = "t2r-anim-ratking";
				auto pPackage = pm->GetPackageById(SID(packageName));
				if (pPackage) {
					pFunction.SetActive(true);
				}
				else {
					pFunction.SetActive(false);
				}
			}
		}

		return true;
	}

	bool PackageManager::TestParseResources(DMENU::ItemFunction& pFunction, DMENU::Message pMessage) {
		if (pMessage == DMENU::Message::OnExecute) {
			auto PackageMgr = reinterpret_cast<PackageManager*>(pFunction.Data());
			if (PackageMgr) {
				spdlog::info("TestParseResources called!");

				const char* packageName = "t2r-anim-ratking";

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
		auto* InternalMgr = GetPackageMgr();

	#if defined(T2R) || defined(T1X)
		always_assert(PackageMgr_GetProcessingInfoFromPackage == nullptr, "Function pointer was not set!");
		return PackageMgr_GetProcessingInfoFromPackage(InternalMgr, pPackage);
	#else
		auto range = InternalMgr->ProcessingInfos();

		for (auto* info : range)
			if (info && info->GetPackage() == pPackage)
				return info;

		return nullptr;
	#endif
	}

	int PackageManager::GetNumUsedPackageSlots() const {
		auto* InternalMgr = GetPackageMgr();

		const int capacity = InternalMgr->GetFreePackageSlots();
		const Package* cur = InternalMgr->PackageHead();

		int used = 0;
		for (int i = 0; i < capacity; ++i, ++cur)
			if (cur->GetStatus() != Package::Status::PackageStatusUnused)
				++used;

		return used;
	}

	int PackageManager::GetNumFreePackageSlots() const {
		auto* InternalMgr = GetPackageMgr();
		return InternalMgr->GetFreePackageSlots() - GetNumUsedPackageSlots();
	}

	bool PackageManager::HasFreePackageSlot() const {
		return GetNumFreePackageSlots() > 0;
	}

	void PackageManager::Init(PackageMgr* pPackageMgr, PackageMgr::Configuration* pConfiguration) {
		auto pPackageManager = Instance<PackageManager>();
		pPackageManager->m_PackageMgrInitHook.thiscall<void>(pPackageMgr, pConfiguration);

		NdSystem* pSystem = GetSharedComponents()->GetComponent<NdSystem>();
		if (pSystem) {
			platform::MutexDesc pDesc{ "PkgMgr SdkDumperLock" };
			pDesc.SetType(Mutex::MutexType::MUTEX_RECURSIVE);
			pSystem->CreateMutex(&pDesc, &Dumper::s_DumperMutex);
		}
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
                pdmenu->Create_DMENU_ItemFunction("Test Dump Packages (NdJobWorkerThread)", PackageManagerMenu, &TestDumpPackages, PackageManagerAddr, false, HeapArena_Source);
				pdmenu->Create_DMENU_ItemFunction("Test Login Package", PackageManagerMenu, &TestLoginPackage, PackageManagerAddr, false, HeapArena_Source);
				pdmenu->Create_DMENU_ItemFunction("Test Parse Resources", PackageManagerMenu, &TestParseResources, PackageManagerAddr, false, HeapArena_Source);

            #endif
				return pdmenu->Create_DMENU_ItemSubmenu(PackageManagerMenu->Name(),
					pMenu, PackageManagerMenu, NULL, NULL, nullptr, HeapArena_Source);
			}
		}
		return nullptr;
	}

	void __cdecl PackageManager::Dumper::ResEntry(uint64_t arg) {
		PackageManager* pm = Instance<PackageManager>();
		auto* w = reinterpret_cast<ResWork*>(arg);
		if (!w || !w->cb) return;
		w->cb(pm->GetPackageMgr(), w->pkg, w->res);
	}

	void __cdecl PackageManager::Dumper::Coordinator(Ctx* ctx) {
		if (!ctx) return;

		PackageManager* pm = Instance<PackageManager>();
		NdJob* js = pm->m_JobSystem;
		Memory* mem = pm->m_Memory;
		PackageMgr* mgr = pm->GetPackageMgr();

		auto wait_frames = [pm, js](uint64_t baseline, uint32_t frames, uint32_t msTimeout)->bool {
			const uint64_t t0 = GetTickCount64();
			for (;;) {
				FrameParams* fp = pm->m_RenderFrameParams->GetRenderFrameParams();
				if (fp) {
					const uint64_t fn = fp->GetFrameNumber();
					if (fn >= baseline + frames) {
						// ensure the (fn-1) frame is fully completed
						if (fn > 0 && pm->m_RenderFrameParams->IsFrameReady(fn - 1))
							return true;
					}
				}
				if ((GetTickCount64() - t0) > msTimeout) return false;
				js->JobYield();
			}
		};

		auto wait_queues_idle = [pm, js](const char* what, uint32_t msTimeout)->bool {
			const uint64_t t0 = GetTickCount64();
			for (;;) {
				FrameParams* fp = pm->m_RenderFrameParams->GetRenderFrameParams();
				if (fp) {
					const uint64_t fn = fp->GetFrameNumber();
					if (fn > 0 && pm->m_RenderFrameParams->IsFrameReady(fn - 1)) {
						if (!fp->Get()->m_ArePackageQueuesBusy)
							return true;
					}
				}
				else {
					if (pm->ArePackageQueuesIdle())
						return true;
				}

				if ((GetTickCount64() - t0) > msTimeout) {
					spdlog::error("[PkgDump] timeout (queues) while waiting for {}", what);
					return false;
				}
				js->JobYield();
			}
		};

		auto wait_slot_available = [pm, js](uint32_t msTimeout)->bool {
			const uint64_t t0 = GetTickCount64();
			while (pm->GetNumFreePackageSlots() == 0) {
				if ((GetTickCount64() - t0) > msTimeout) {
					return false;
				}
				js->JobYield();
			}
			return true;
		};

		constexpr uint32_t kTimeoutMs = 25'000;
		constexpr size_t kResChunk = 256;

		mem->PushAllocator(mgr->GetMemoryContext(), HeapArena_Source);
		mgr->Get()->m_forceReleaseVirtualMemory = true;

		try {

			size_t cursor = 0;

			while (cursor < ctx->count) {

				ScopedLock ql(&s_DumperMutex, kTimeoutMs);

				const size_t freeNow = static_cast<size_t>(pm->GetNumFreePackageSlots());
				auto& reqInfo = mgr->GetPackageRequestInfo();
				const uint32_t inFlight = reqInfo.GetNumRequests();
				const uint32_t limit = reqInfo.GetLimitRequests();
				const size_t reqRemaining = (limit > inFlight) ? (limit - inFlight) : 0;

				const size_t slots = freeNow; 
				const size_t toReq = reqRemaining > 0 ? size_t(reqRemaining) : 0;
				const size_t remaining = (cursor >= size_t(ctx->count)) ? 0 : size_t(ctx->count) - cursor;
				
				size_t cap = size_t(ctx->maxConcurrent);
				if (cap == 0) cap = SIZE_MAX;

				const size_t batch = (std::min)({ slots, toReq, cap, remaining });
				
				if (batch == 0) {

					// budget exhausted: inFlight >= limit
					if (toReq == 0) {
						if (!wait_queues_idle("login budget", kTimeoutMs)) {
							spdlog::warn("[PkgDump] login budget stuck; breaking");
							break;
						}
						continue;
					}

					// no free package slots
					if (slots == 0) {
						if (!wait_slot_available(kTimeoutMs)) {
							spdlog::error("[PkgDump] timeout waiting for free slot");
							break;
						}
						continue;
					}

					js->JobYield();
					continue;
				}

				// login
				for (size_t i = 0; i < batch; ++i) {
					const char* name = ctx->names[cursor + i];
					pm->RequestLoadPackage(name, nullptr, PackageMgr::PackageCategory::GlobalPak);
					ctx->batchIds[i] = ctx->ids[cursor + i];
					spdlog::info("[PkgDump] login '{}'", name);
				}

				const uint64_t baseFn = pm->m_RenderFrameParams->GetCurrentFrameNumber();
				if (!wait_frames(baseFn, 1, kTimeoutMs)) {
					spdlog::error("[PkgDump] frame fence timeout after queuing loads");
					break;
				}

				const bool login_ok = wait_queues_idle("login queue", kTimeoutMs);
				if (!login_ok) {
					spdlog::error("[PkgDump] login queue did not fully drain in time (continuing)");
					break;
				}

				if (login_ok) {
					for (size_t i = 0; i < batch; ++i) {
						const StringId64 pid = ctx->batchIds[i];

						Package* pkg = pm->GetPackageById(pid);
						if (!pkg) {
							const char* wantedName = ctx->names[cursor + i];
							spdlog::error("[PkgDump] missing pkg post-login '{}' (id=0x{:016x})", wantedName, (uint64_t)pid);
							continue;
						}

						PackageProcessingInfo* ppi = pm->FetchPackageProcessingInfo(pkg);
						if (!ppi) {
							throw std::runtime_error{ std::format("PackageProcessingInfo for package '{}' was null after login.", pkg->GetName()) };
						}

						if (ppi->GetStatus() == PackageProcessingInfo::LoadingStatus::LoadingPackageStatusError) {
							spdlog::error("[PkgDump] load error '{}': {}", pkg->GetName(), ppi->GetStatusString());
							continue;
						}

						if (pkg->GetNumRequests() > 1) {
							spdlog::warn("[PkgDump] package '{}' has multiple requests ({})", pkg->GetName(), pkg->GetNumRequests());
						}

						auto resItems = [&]() -> decltype(pm->ParseResources(ppi)) {
							ScopedLock lk(mgr->GetLoadingLock());
							return pm->ParseResources(ppi);
						}();

						if (!resItems.has_value()) {
							spdlog::error("[PkgDump] parse failed '{}': {}", pkg->GetName(), resItems.error());
							continue;
						}

						const size_t n = resItems->size();
						size_t rk = 0;
						while (rk < n) {

							const size_t chunk = std::min<size_t>(kResChunk, n - rk);
							ResWork* work = mem->Allocate<ResWork>(sizeof(ResWork) * chunk, 0x10, HeapArena_Source);
							ResWork** items = mem->Allocate<ResWork*>(sizeof(ResWork*) * chunk, 0x10, HeapArena_Source);

							if (!work || !items) {
								spdlog::error("[PkgDump] work alloc failed '{}'", pkg->GetName());
								if (work) mem->Free(work, HeapArena_Source);
								if (items) mem->Free(items, HeapArena_Source);
								break;
							}

							for (size_t j = 0; j < chunk; ++j) {
								work[j] = ResWork{ pkg, (*resItems)[rk + j], ctx->cb };
								items[j] = &work[j];
							}

							CounterHandle* ctr = nullptr;
							js->SubmitJobArray(
								reinterpret_cast<void*>(ResEntry),
								reinterpret_cast<void**>(items),
								chunk,
								NdJob::Priority::KLow,
								HeapArena_Source,
								&ctr);

							spdlog::info("[PkgDump] submitted {} resources for package '{}'", chunk, pkg->GetName());
							if (ctr) {
								js->WaitForCounterAndFree(&ctr, 0);
							}

							mem->Free(work, HeapArena_Source);
							mem->Free(items, HeapArena_Source);
							rk += chunk;
						}
					}
				}

				for (size_t i = 0; i < batch; ++i) {
					const auto pid = ctx->batchIds[i];
					if (pm->GetPackageById(pid)) {
						pm->RequestLogoutPackage(pid);
					}
				}

				const bool logout_ok = wait_queues_idle("logout queue", kTimeoutMs);
				if (logout_ok) {
					mgr->ReleaseLoadedVramPages();
				}

				cursor += batch;
			}

		} catch (const std::exception& e) {
			spdlog::error("[PkgDump] Error during dump: {}", e.what());
		} 

		if (ctx->selfFree) {
			FreeCtx(ctx);
		}

		mgr->Get()->m_forceReleaseVirtualMemory = false;
		mem->PopAllocator();
	}

	void PackageManager::Dumper::FreeCtx(Ctx* ctx) {
		auto* pm = Instance<PackageManager>();
		always_assert(pm == nullptr, "PackageManager instance missing in FreeCtx");

		Memory* mem = pm->m_Memory;
		mem->Free(ctx->namesRaw, HeapArena_Source);
		mem->Free(ctx->names, HeapArena_Source);
		mem->Free(ctx->ids, HeapArena_Source);
		mem->Free(ctx->batchIds, HeapArena_Source);
		mem->Free(ctx, HeapArena_Source);
	}

	int PackageMgr::GetFreePackageSlots() const {
		return this->Get()->m_freepackageslots;
	}

	int PackageMgr::GetAllocationRingBufferSize() const {
		return this->Get()->m_allocationRingBufferSize;
	}

	Memory::Context& PackageMgr::GetRingBufferContext() const {
		return this->Get()->m_RingBufferContext;
	}

	Memory::Context& PackageMgr::GetMemoryContext() const {
		return this->Get()->m_memoryContext;
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

	Mutex* PackageMgr::GetLoadingLock() const {
		return reinterpret_cast<Mutex*>(&this->Get()->m_LoadingLock);
	}

	Mutex* PackageMgr::GetLoginLock() const {
		return reinterpret_cast<Mutex*>(&this->Get()->m_LoginLock);
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
		return this->Get()->m_PackageLoginResFuncs->PackageLoginResItem(pPackage->Get(), pResItem->Get());
	}

	void PackageMgr::ReleaseLoadedVramPages() {
		this->Get()->m_PackageLoginResFuncs->ReleaseLoadedVramPages();
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

	Mutex PackageManager::Dumper::s_DumperMutex{};

	INIT_FUNCTION_PTR(PackageMgr_PackageProcessingInfo_GetStatusString);

#endif

}


