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

	bool PackageManager::ArePackageQueuesIdle() const {
	#if defined(T2R) || defined(T1X)
		always_assert(PackageMgr_PackageQueuesIdle == nullptr, "Function pointer was not set!");
		return PackageMgr_PackageQueuesIdle(GetPackageMgr());
	#elif
		auto PackageMgr = GetPackageMgr();
		return PackageMgr->GetPackageRequestInfo().GetNumRequests() <= 0 &&
			PackageMgr->GetProcessingCount() <= 0 &&
			PackageMgr->GetNumAwaitingLoad() <= 0 &&
			PackageMgr->GetNumAwaitingUpdate() <= 0 &&
			PackageMgr->GetNumAwaitingUnload() <= 0;
	#endif
	}

	bool PackageManager::RequestLoadPackage(const char* pPackageName) {
	#if defined(T2R) || defined(T1X)
		always_assert(PackageMgr_RequestLoadPackage == nullptr, "Function pointer was not set!");
		PackageMgr_RequestLoadPackage(GetPackageMgr(), pPackageName, 0x0, 0x0, 0x0);
		return true;
	#else
		PackageMgr::PackageRequest packageRequest {
			0,
			SID(pPackageName),
			pPackageName,
			0x0
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
				0x1,
				pPackage->GetPackId(),
				pPackage->GetName(),
				0x0
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
				0x1,
				pPackage->GetPackId(),
				pPackage->GetName(),
				0x0
			};

			AddPackageRequest(&packageRequest);

			PackageMgr::PackageRequest packageRequest{
				0x0,
				pPackage->GetPackId(),
				pPackage->GetName(),
				(uint64_t)pPackage->Get()->m_Level
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
			auto PackageMgrSdkComponent = reinterpret_cast<PackageManager*>(pFunction.Data());
			if (PackageMgrSdkComponent) {
				spdlog::info("TestFunct called!");
				auto PackageMgr = PackageMgrSdkComponent->GetPackageMgr();

				return true;
			}
		}
		return true;
	}

	Package* PackageManager::GetPackageById(StringId64 PackId) {
		always_assert(PackageMgr_GetPackageById == nullptr, "Function pointer was not set!");
		return PackageMgr_GetPackageById(GetPackageMgr(), PackId);
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

	int PackageMgr::GetProcessingCount() const {
		return this->Get()->m_LoadQueue;
	}

	uint64_t PackageMgr::GetNumAwaitingLoad() const {
		return this->Get()->m_numPackagesAwaitingLoad;
	}

	uint64_t PackageMgr::GetNumAwaitingUpdate() const {
		return this->Get()->m_numPackagesAwaitingUpdate;
	}

	uint64_t PackageMgr::GetNumAwaitingUnload() const {
		return this->Get()->m_numPackagesAwaitingUnload;
	}

	Memory::Context& PackageMgr::GetMemoryContext() const {
		return this->Get()->m_memcontext;
	}

	Package* PackageMgr::PackageHead() {
		return reinterpret_cast<Package*>(this->Get()->m_packages);
	}

	const Package* PackageMgr::PackageHead()  const  {
		return reinterpret_cast<const Package*>(this->Get()->m_packages);
	}

	PackageProcessingInfo** PackageMgr::GetProcessingArray() const {
		return reinterpret_cast<PackageProcessingInfo**>(this->Get()->m_packageinfos);
	}

	PackageMgr::PackageRequestInfo& PackageMgr::GetPackageRequestInfo() {
		return reinterpret_cast<PackageRequestInfo&>(this->Get()->m_RequestInfo);
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

	Package* PackageProcessingInfo::GetPackage() const {
		return reinterpret_cast<Package*>(this->Get()->m_package);
	}

	PackageProcessingInfo::LoadingStatus PackageProcessingInfo::GetStatus() const {
		return this->Get()->m_status;
	}

	Package::PakHeader& PackageProcessingInfo::GetPakHeader() {
		return reinterpret_cast<Package::PakHeader&>(this->Get()->m_pakHdr);
	}

	uint64_t PackageMgr::PackageRequest::GetRequestType() const {
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

	INIT_FUNCTION_PTR(PackageMgr_PackageProcessingInfo_GetStatusString);

#endif
}


