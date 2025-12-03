#include "game-loading.hpp"
#include "./NdGameSdk/shared/sharedpatterns.hpp"

#include <NdGameSdk/shared/src/gamelib/debug/nd-dev-menu.hpp>

#include <Utility/helper.hpp>
#include <Utility/global_resolver.hpp>
#include <cstddef>

namespace NdGameSdk::gamelib::level {

	GameLoading::GameLoading() : ISdkComponent(TOSTRING(GameLoading)) {}

	void GameLoading::Awake() {
		auto SharedComponents = ISdkComponent::GetSharedComponents();
		m_NdJob = GetDependencyComponent<NdJob>(SharedComponents);
	}

	void GameLoading::Initialize() {
		static std::once_flag Initialized;
		std::call_once(Initialized, [this] {
			spdlog::info("Initializing {} patterns...", GetName());
			
			Patterns::SdkPattern findpattern{};
			auto module = Utility::memory::get_executable();

			findpattern = Patterns::GameLoading_Initialize;
			auto GameLoading_Initialize = (void*)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::GameLoading_Initialize), findpattern.offset);

			if (!GameLoading_Initialize) {
				throw SdkComponentEx{ std::format("Failed to find {} addresses!", GetName()),
					SdkComponentEx::ErrorCode::PatternFailed };
			}

	#if defined(T2R)

			findpattern = Patterns::GameLoading_g_GameLoadingData;
			Utility::GlobalResolver::RipLea32Anchor anchor{ findpattern.pattern, findpattern.offset, 3, 7, wstr(Patterns::GameLoading_g_GameLoadingData) };
			
			auto* GameLoadingDataBase = Utility::GlobalResolver::ResolveBase(module, anchor);
			if (!GameLoadingDataBase) {
				throw SdkComponentEx{ "Failed to resolve GameLoadingDataBase!", SdkComponentEx::ErrorCode::PatternFailed };
			}

			constexpr ptrdiff_t NumCoreArchives_Offset = 0x000;
			constexpr ptrdiff_t CoreArchives_Offset = 0x010;
			constexpr ptrdiff_t WorldNameCurrent_Offset = 0x6d8;
			constexpr ptrdiff_t SpMpModeDesired_Offset = 0x6f0;
			constexpr ptrdiff_t WorldNameTarget_Offset = 0x708;
			constexpr ptrdiff_t WorldCompanionNameTarget_Offset = 0x710;
			constexpr ptrdiff_t WorldNamePrevious_Offset = 0x718;
			constexpr ptrdiff_t SpMpModeCurrent_Offset = 0x720;
			constexpr ptrdiff_t GameLoadingState_Offset = 0x988;
			constexpr ptrdiff_t StepCounter_Offset = 0x9d0;

			g_NumCoreArchives = Utility::GlobalResolver::SlotAt<uint64_t>(GameLoadingDataBase, NumCoreArchives_Offset, L"g_NumCoreArchives");
			g_CoreArchives = Utility::GlobalResolver::SlotAt<FileSystemWin::ArchiveMount>(GameLoadingDataBase, CoreArchives_Offset, L"g_CoreArchives");
			g_SpMpModeCurrent = Utility::GlobalResolver::SlotAt<SpMpMode>(GameLoadingDataBase, SpMpModeCurrent_Offset, L"g_SpMpModeCurrent");
			g_SpMpModeDesired = Utility::GlobalResolver::SlotAt<SpMpMode>(GameLoadingDataBase, SpMpModeDesired_Offset, L"g_SpMpModeDesired");

			// ptr slots
			g_WorldNameCurrent = Utility::GlobalResolver::PtrSlotAt<const char>(GameLoadingDataBase, WorldNameCurrent_Offset, L"g_WorldNameCurrent");
			g_WorldNameTarget = Utility::GlobalResolver::PtrSlotAt<const char>(GameLoadingDataBase, WorldNameTarget_Offset, L"g_WorldNameTarget");
			g_WorldCompanionNameTarget = Utility::GlobalResolver::PtrSlotAt<const char>(GameLoadingDataBase, WorldCompanionNameTarget_Offset, L"g_WorldCompanionNameTarget");
			g_WorldNamePrevious = Utility::GlobalResolver::PtrSlotAt<const char>(GameLoadingDataBase, WorldNamePrevious_Offset, L"g_WorldNamePrevious");

			g_pGameLoadingState = Utility::GlobalResolver::PtrSlotAt<CounterHandle>(GameLoadingDataBase, GameLoadingState_Offset, L"g_pGameLoadingState");
			g_pStepCounter = Utility::GlobalResolver::PtrSlotAt<CounterHandle>(GameLoadingDataBase, StepCounter_Offset, L"g_pStepCounter");

	#elif defined(T1X)

			findpattern = Patterns::GameLoading_g_NumCoreArchives;
			g_NumCoreArchives = Utility::GlobalResolver::RipSlotOrNull<uint64_t>(
				module, findpattern.pattern, wstr(Patterns::GameLoading_g_NumCoreArchives), findpattern.offset, 3, 7);

			findpattern = Patterns::GameLoading_g_SpMpModeDesired;
			g_SpMpModeDesired = Utility::GlobalResolver::RipSlotOrNull<SpMpMode>(
				module, findpattern.pattern, wstr(Patterns::GameLoading_g_SpMpModeDesired), findpattern.offset, 2, 6);

			findpattern = Patterns::GameLoading_g_SpMpModeCurrent;
			g_SpMpModeCurrent = Utility::GlobalResolver::RipSlotOrNull<SpMpMode>(
				module, findpattern.pattern, wstr(Patterns::GameLoading_g_SpMpModeCurrent), findpattern.offset, 2, 6);

			// pointer-slots (address-of-storage);
			findpattern = Patterns::GameLoading_g_WorldNameCurrent;
			g_WorldNameCurrent = Utility::GlobalResolver::RipPtrSlotOrNull<const char>(
				module, findpattern.pattern, wstr(Patterns::GameLoading_g_WorldNameCurrent), findpattern.offset, 3, 7);

			findpattern = Patterns::GameLoading_g_WorldNameTarget;
			g_WorldNameTarget = Utility::GlobalResolver::RipPtrSlotOrNull<const char>(
				module, findpattern.pattern, wstr(Patterns::GameLoading_g_WorldNameTarget), findpattern.offset, 3, 7);

			findpattern = Patterns::GameLoading_g_WorldCompanionNameTarget;
			g_WorldCompanionNameTarget = Utility::GlobalResolver::RipPtrSlotOrNull<const char>(
				module, findpattern.pattern, wstr(Patterns::GameLoading_g_WorldCompanionNameTarget), findpattern.offset, 3, 7);

			findpattern = Patterns::GameLoading_g_WorldNamePrevious;
			g_WorldNamePrevious = Utility::GlobalResolver::RipPtrSlotOrNull<const char>(
				module, findpattern.pattern, wstr(Patterns::GameLoading_g_WorldNamePrevious), findpattern.offset, 3, 7);

			findpattern = Patterns::GameLoading_g_pGameLoadingState;
			g_pGameLoadingState = Utility::GlobalResolver::RipPtrSlotOrNull<CounterHandle>(
				module, findpattern.pattern, wstr(Patterns::GameLoading_g_pGameLoadingState), findpattern.offset, 3, 7);

			findpattern = Patterns::GameLoading_g_pStepCounter;
			g_pStepCounter = Utility::GlobalResolver::RipPtrSlotOrNull<CounterHandle>(
				module, findpattern.pattern, wstr(Patterns::GameLoading_g_pStepCounter), findpattern.offset, 3, 7);

			if (!g_NumCoreArchives ||
				!g_SpMpModeCurrent ||
				!g_SpMpModeDesired ||
				!g_WorldNameCurrent ||
				!g_WorldNameTarget ||
				!g_WorldCompanionNameTarget ||
				!g_WorldNamePrevious ||
				!g_pGameLoadingState ||
				!g_pStepCounter) {
				throw SdkComponentEx{ "Failed to resolve GameLoading static variables!", SdkComponentEx::ErrorCode::PatternFailed };
			}

			g_CoreArchives = Utility::GlobalResolver::Derive<FileSystemWin::ArchiveMount>(
				static_cast<void*>(g_NumCoreArchives), 0x8, L"g_CoreArchives(base)");
	#endif

			m_GameLoadingInitializeHook = Utility::MakeSafetyHookInline(GameLoading_Initialize, InitializeInternal,
				wstr(Patterns::GameLoading_Initialize), wstr(GameLoading::InitializeInternal));

			if (!m_GameLoadingInitializeHook) {
				throw SdkComponentEx{ "Failed to create hooks!", SdkComponentEx::ErrorCode::PatchFailed };
			}

			findpattern = Patterns::GameLoading_SwitchToSPLevel;
			GameLoading_SwitchToSPLevel = (GameLoading_SwitchToSPLevel_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::GameLoading_SwitchToSPLevel), findpattern.offset);

			findpattern = Patterns::GameLoading_MountArchiveIfNotMounted;
			GameLoading_MountArchiveIfNotMounted = (GameLoading_MountArchiveIfNotMounted_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::GameLoading_MountArchiveIfNotMounted), findpattern.offset);

			findpattern = Patterns::GameLoading_UnmountArchive;
			GameLoading_UnmountArchive = (GameLoading_UnmountArchive_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::GameLoading_UnmountArchive), findpattern.offset);

			findpattern = Patterns::GameLoading_StageStepDown;
			GameLoading_StageStepDown = (GameLoading_StageStepDown_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::GameLoading_StageStepDown), findpattern.offset);

			findpattern = Patterns::GameLoading_RequestLoadPackageWithDictionary;
			GameLoading_RequestLoadPackageWithDictionary = (GameLoading_RequestLoadPackageWithDictionary_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::GameLoading_RequestLoadPackageWithDictionary), findpattern.offset);

	#if defined(T1X)
			findpattern = Patterns::GameLoading_SetModeSP;
			GameLoading_SetModeSP = (GameLoading_SetModeSP_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::GameLoading_SetModeSP), findpattern.offset);

			findpattern = Patterns::GameLoading_SetModeMP;
			GameLoading_SetModeMP = (GameLoading_SetModeMP_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::GameLoading_SetModeMP), findpattern.offset);
	#else
			findpattern = Patterns::GameLoading_SetModeAndScheduleSwitch;
			GameLoading_SetModeAndScheduleSwitch = (GameLoading_SetModeAndScheduleSwitch_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::GameLoading_SetModeAndScheduleSwitch), findpattern.offset);
	#endif

			if (
				!GameLoading_SwitchToSPLevel ||
				!GameLoading_MountArchiveIfNotMounted ||
				!GameLoading_UnmountArchive ||
				!GameLoading_StageStepDown ||
				!GameLoading_RequestLoadPackageWithDictionary
				#if defined(T1X)
				|| !GameLoading_SetModeSP
				|| !GameLoading_SetModeMP
				#else
				|| !GameLoading_SetModeAndScheduleSwitch
				#endif
				) { throw SdkComponentEx{ std::format("Failed to find {}:: game functions!", GetName()), SdkComponentEx::ErrorCode::PatternFailed }; }

		});
	}

	void GameLoading::InitializeInternal() {
		GameLoading* pGameLoading = Instance<GameLoading>();
		pGameLoading->m_GameLoadingInitializeHook.thiscall<void>();
	}

	void GameLoading::SwitchToSPLevel(const char* pWorldLevel, const char* companionName, bool requireSecondaryCopyPhaseGate) {
		always_assert(GameLoading_SwitchToSPLevel == nullptr, "GameLoading::SwitchToSPLevel is null!");
		GameLoading_SwitchToSPLevel(pWorldLevel, companionName, requireSecondaryCopyPhaseGate);
	}

	void GameLoading::MountArchiveIfNotMounted(const char* pArchiveName, FileSystemWin::ArchiveMount* pArchiveMountSlot) {
		always_assert(GameLoading_MountArchiveIfNotMounted == nullptr, "GameLoading::MountArchiveIfNotMounted is null!");
		GameLoading_MountArchiveIfNotMounted(pArchiveName, pArchiveMountSlot);
	}

	void GameLoading::UnmountArchive(FileSystemWin::ArchiveMount* pArchiveMountSlot) {
		always_assert(GameLoading_UnmountArchive == nullptr, "GameLoading::UnmountArchive is null!");
		GameLoading_UnmountArchive(pArchiveMountSlot);
	}

	uint64_t GameLoading::StageStepDown(CounterHandle* pGameLoadingState) {
		always_assert(GameLoading_StageStepDown == nullptr, "GameLoading::StageStepDown is null!");
		return GameLoading_StageStepDown(pGameLoadingState);
	}

	void GameLoading::RequestLoadPackageWithDictionary(const char* pBasePackageName) {
		always_assert(GameLoading_RequestLoadPackageWithDictionary == nullptr, "GameLoading::RequestLoadPackageWithDictionary is null!");
		GameLoading_RequestLoadPackageWithDictionary(pBasePackageName);
	}

	bool GameLoading::SetModeAndScheduleSwitch(SpMpMode newMode) {
	#if defined (T1X)
		switch (newMode) {
		case SpMpMode::kModeSP:
			always_assert(GameLoading_SetModeSP == nullptr, "GameLoading::SetModeSP is null!");
			GameLoading_SetModeSP();
			return true;
		case SpMpMode::kModeMP:
			always_assert(GameLoading_SetModeMP == nullptr, "GameLoading::SetModeMP is null!");
			GameLoading_SetModeMP();
			return true;
		default:
			spdlog::warn("GameLoading::SetModeAndScheduleSwitch: Unsupported mode {}", (int)newMode);
			return false;
		}
	#else
		always_assert(GameLoading_SetModeAndScheduleSwitch == nullptr, "GameLoading::SetModeAndScheduleSwitch is null!");
		GameLoading_SetModeAndScheduleSwitch(newMode);
		return true;
	#endif

	}

	void GameLoading::WaitForSteadyState() {
		auto* loadingState = GetGameLoadingState();
		always_assert(loadingState == nullptr, "g_pGameLoadingState == nullptr");
		RequireInstance<GameLoading>().m_NdJob->WaitForCounter(&loadingState, TransitionStatus::kSteady);
	}

	void GameLoading::WaitForSPCommonAvailability() {
		auto* loadingState = GetGameLoadingState();
		always_assert(loadingState == nullptr, "g_pGameLoadingState == nullptr");
		RequireInstance<GameLoading>().m_NdJob->WaitForCounter(&loadingState, TransitionStatus::kMountingSPCommon - 1);
	}

	void GameLoading::WaitForFirstWorldAvailability() {
		auto* loadingState = GetGameLoadingState();
		always_assert(loadingState == nullptr, "g_pGameLoadingState == nullptr");
		RequireInstance<GameLoading>().m_NdJob->WaitForCounter(&loadingState, TransitionStatus::kMountingFirstWorld - 1);
	}

	void GameLoading::WaitForCoreAvailability() {
		auto* loadingState = GetGameLoadingState();
		always_assert(loadingState == nullptr, "g_pGameLoadingState == nullptr");
		RequireInstance<GameLoading>().m_NdJob->WaitForCounter(&loadingState, TransitionStatus::kMountingCore - 1);
	}

	void GameLoading::WaitForCommonAvailability() {
		auto* loadingState = GetGameLoadingState();
		always_assert(loadingState == nullptr, "g_pGameLoadingState == nullptr");
		RequireInstance<GameLoading>().m_NdJob->WaitForCounter(&loadingState, TransitionStatus::kMountingCommon - 1);
	}

	void GameLoading::WaitForBinAvailability() {
		auto* loadingState = GetGameLoadingState();
		always_assert(loadingState == nullptr, "g_pGameLoadingState == nullptr");
		RequireInstance<GameLoading>().m_NdJob->WaitForCounter(&loadingState, TransitionStatus::kMountingBin - 1);
	}

	DMENU::ItemSubmenu* GameLoading::CreateGameLoadingMenu(NdDevMenu* pdmenu, DMENU::Menu* pMenu) {
		auto pGameLoading = Instance<GameLoading>();
		if (pGameLoading) {
			uint64_t GameLoadingAddr = reinterpret_cast<uint64_t>(static_cast<void*>(pGameLoading));
			DMENU::Menu* GameLoadingMenu = pdmenu->Create_DMENU_Menu(pGameLoading->GetName().data(), HeapArena_Source);
			if (GameLoadingMenu) {
			#if SDK_DEBUG

				pdmenu->Create_DMENU_ItemFunction("Test function", GameLoadingMenu,
					+[](DMENU::ItemFunction& pFunction, DMENU::Message pMessage)->bool {
						if (pMessage == DMENU::Message::OnExecute) {
							auto* gameloading = reinterpret_cast<GameLoading*>(pFunction.Data());
							

							spdlog::info("NumCoreArchives: {}", g_NumCoreArchives ? *g_NumCoreArchives : 0ull);
							spdlog::info("SpMpMode cur/desired: {}/{}",
								g_SpMpModeCurrent ? (int)*g_SpMpModeCurrent : -1,
								g_SpMpModeDesired ? (int)*g_SpMpModeDesired : -1);

							// pointer slots
							auto* loadingState = (g_pGameLoadingState && *g_pGameLoadingState) ? *g_pGameLoadingState : nullptr;
							spdlog::info("g_pGameLoadingState slot={} value={}",
								fmt::ptr(g_pGameLoadingState), fmt::ptr(loadingState));

							const char* curWorld = (g_WorldNameCurrent && *g_WorldNameCurrent) ? *g_WorldNameCurrent : nullptr;
							spdlog::info("WorldNameCurrent slot={} ptr={} text={}",
								fmt::ptr(g_WorldNameCurrent),
								fmt::ptr(curWorld),
								curWorld ? curWorld : "nullptr");

							if (g_CoreArchives) {
								const auto count = g_NumCoreArchives ? *g_NumCoreArchives : 0ull;
								spdlog::info("CoreArchives base={} count={}", fmt::ptr(g_CoreArchives), count);

								if (count > 0) {
									auto& m0 = g_CoreArchives[0];
									spdlog::info("core[0] addr={} archiveId={} sizeBytes={}", fmt::ptr(&m0), m0.GetId(), m0.GetSize());
								}
							}
							
						}
						return true;
					},
					GameLoadingAddr, false, HeapArena_Source);

			#endif
				return pdmenu->Create_DMENU_ItemSubmenu(GameLoadingMenu->Name(), pMenu,
					GameLoadingMenu, NULL, NULL, nullptr, HeapArena_Source);
			}
		}
		return nullptr;
	}

	CounterHandle* GameLoading::GetGameLoadingState() {
		return (g_pGameLoadingState && *g_pGameLoadingState) ? *g_pGameLoadingState : nullptr;
	}

	uint64_t* GameLoading::g_NumCoreArchives = nullptr;
	GameLoading::SpMpMode* GameLoading::g_SpMpModeCurrent = nullptr;
	GameLoading::SpMpMode* GameLoading::g_SpMpModeDesired = nullptr;
	CounterHandle** GameLoading::g_pGameLoadingState = nullptr;
	CounterHandle** GameLoading::g_pStepCounter = nullptr;
	const char** GameLoading::g_WorldNameTarget = nullptr;
	const char** GameLoading::g_WorldCompanionNameTarget = nullptr;
	const char** GameLoading::g_WorldNamePrevious = nullptr;
	const char** GameLoading::g_WorldNameCurrent = nullptr;
	FileSystemWin::ArchiveMount* GameLoading::g_CoreArchives = nullptr;

	INIT_FUNCTION_PTR(GameLoading::GameLoading_SwitchToSPLevel);
	INIT_FUNCTION_PTR(GameLoading::GameLoading_MountArchiveIfNotMounted);
	INIT_FUNCTION_PTR(GameLoading::GameLoading_UnmountArchive);
	INIT_FUNCTION_PTR(GameLoading::GameLoading_StageStepDown);
	INIT_FUNCTION_PTR(GameLoading::GameLoading_RequestLoadPackageWithDictionary);
#if defined(T1X)
	INIT_FUNCTION_PTR(GameLoading::GameLoading_SetModeSP);
	INIT_FUNCTION_PTR(GameLoading::GameLoading_SetModeMP);
#else
	INIT_FUNCTION_PTR(GameLoading::GameLoading_SetModeAndScheduleSwitch);
#endif

}
