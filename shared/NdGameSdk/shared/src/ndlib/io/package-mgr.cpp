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

			findpattern = Patterns::PackageManager_Init;
			auto PackageMgrInit = (void*)Utility::FindAndPrintPattern(module
				, findpattern.pattern, wstr(Patterns::PackageManager_Init), findpattern.offset);

			findpattern = Patterns::PackageManager_InitReturn;
			auto PackageMgrInitReturn = (void*)Utility::FindAndPrintPattern(module
				, findpattern.pattern, wstr(Patterns::PackageManager_InitReturn), findpattern.offset);

			if (!PackageMgrInit || 
				!PackageMgrInitReturn) {
				throw SdkComponentEx{ std::format("Failed to find PackageMgr patterns!"),
					SdkComponentEx::ErrorCode::PatternFailed };
			}

			m_PackageMgrInitHook = Utility::MakeSafetyHookInline(PackageMgrInit, Init,
				wstr(Patterns::PackageManager_Init), wstr(PackageManager::Init));

			m_PackageMgrInitReturnHook = Utility::MakeMidHook(PackageMgrInitReturn, PackageManagerInitialized,
				wstr(Patterns::PackageManager_InitReturn), wstr(PackageManager::PackageManagerInitialized));

			if (!m_PackageMgrInitHook ||
				!m_PackageMgrInitReturnHook) {
				throw SdkComponentEx{ "Failed to create hooks!", SdkComponentEx::ErrorCode::PatchFailed };
			}

		});
	}

	bool PackageManager::TestFunct(DMENU::ItemFunction& pFunction, DMENU::Message pMessage) {
		if (pMessage == DMENU::Message::OnExecute) {
			auto PackageMgrSdkComponent = reinterpret_cast<PackageManager*>(pFunction.Data());
			if (PackageMgrSdkComponent) {
				spdlog::info("TestFunct called!");
				auto PackageMgr = &PackageMgrSdkComponent->m_EngineComponents->GetPackageMgr();

				return true;
			}
		}
		return true;
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
		return this->Get()->m_PackageWantedCount;
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

#endif
}


