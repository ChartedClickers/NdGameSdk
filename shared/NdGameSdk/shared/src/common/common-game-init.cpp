#include "common-game-init.hpp"
#include "./NdGameSdk/shared/sharedpatterns.hpp"

#include <NdGameSdk/shared/src/ndlib/render/dev/debugdraw-common.hpp>
#include <NdGameSdk/shared/src/ndlib/profiling/profile-ctrl.hpp>

namespace NdGameSdk::common {

	CommonGame::CommonGame() : ISdkComponent(TOSTRING(CommonGame)) {}

	uint32_t CommonGame::GetGameVersion() {
		return m_GameVersion;
	}

	bool CommonGame::IsGameInitialized() {
		return m_GameInitialized;
	}

	void CommonGame::Awake() {
		auto SharedComponents = ISdkComponent::GetSharedComponents();
		m_EngineComponents = GetDependencyComponent<EngineComponents>(SharedComponents);

		const auto manualInit = ISdkComponent::SubComponentInitPolicy::Manual;
		#if defined(T2R)
		m_NxAppHooks = AddSubComponentWithPolicy<NxAppHooks>(manualInit);
		#endif
        m_IAllocator = AddSubComponentWithPolicy<IAllocator>(manualInit);
        m_CommonGameLoop = AddSubComponentWithPolicy<CommonGameLoop>(manualInit);
        m_CommonMainWin = AddSubComponentWithPolicy<CommonMainWin>(manualInit);

	}

	void CommonGame::Initialize() {
		static std::once_flag Initialized;

		std::call_once(Initialized, [this] {
			
			spdlog::info("Initializing {} patterns...", GetName());

			auto module = Utility::memory::get_executable();

			Patterns::SdkPattern findpattern{};

#if defined(T2R)
			constexpr size_t GameInitReturnHook_Offset = 0x13;
#elif defined(T1X)
			constexpr size_t GameInitReturnHook_Offset = 0x4c;
#endif

			findpattern = Patterns::CommonGame_GameInit;
			auto GameInitJMP = (void*)Utility::FindAndPrintPattern(module
				, findpattern.pattern, wstr(Patterns::CommonGame_GameInit), findpattern.offset);
			auto GameInitReturnJMP = (void*)Utility::FindAndPrintPattern(module
				, findpattern.pattern, wstr(Patterns::CommonGame_GameInit), findpattern.offset + GameInitReturnHook_Offset);

			if (!GameInitJMP ||
				!GameInitReturnJMP) {
				throw SdkComponentEx
				{ std::format("Failed to find addresses!"),
					SdkComponentEx::ErrorCode::PatternFailed, true };
			}

			m_GameInitHook = Utility::MakeMidHook(GameInitJMP,
				[](SafetyHookContext& ctx)
				{
					//Reconfiguring the NdGame
					auto pCommonGame = GetSharedComponents()->GetComponent<CommonGame>();

					if (pCommonGame->m_EngineComponents) {
						auto& ndgameinfo = pCommonGame->m_EngineComponents->GetNdGameInfo();
					#if defined(T2R)
						// Rollback original cfg path to game path (Like it was in T1X)
						strcpy(ndgameinfo->m_CfgPath, ndgameinfo->m_GamePath);
					#endif
						ndgameinfo->m_DevMode = g_SdkConfig.NdDevMenu.GameDebugMenu;
						ndgameinfo->m_DevConfig = true;
					}

				}, wstr(Patterns::CommonGame_GameInit), wstr(GameInitJMP));


			m_GameInitReturnHook = Utility::MakeMidHook(GameInitReturnJMP,
				[](SafetyHookContext& ctx)
				{
					auto pCommonGame = GetSharedComponents()->GetComponent<CommonGame>();
					bool successful = !((*(uint32_t*)ctx.rax) > 0);
					pCommonGame->m_GameInitialized = successful;

					if (pCommonGame->m_EngineComponents) {
						auto& ndgameinfo = pCommonGame->m_EngineComponents->GetNdGameInfo();
						strcpy(ndgameinfo->m_DiscUser, SDK_NAME);
						strcpy(ndgameinfo->m_StatsBuild, SDK_NAME);
					}

					pCommonGame->InvokeSdkEvent(pCommonGame->e_GameInitialized, successful);

				}, wstr(Patterns::CommonGame_GameInit), wstr(GameInitReturnJMP));
			
			m_Memory = GetSharedComponents()->GetComponent<Memory>();

			if (m_Memory) {

				this->InitSubComponent<IAllocator>();

	#if defined(T2R)
			if (m_Memory->IsDebugMemoryAvailable()) {
				auto ProfileCtrl = GetSharedComponents()->GetComponent<ndlib::profiling::ProfileController>();

				findpattern = Patterns::CommonGame_ProfileCtrl_Initialize;
				auto ProfileCtrlInitJMP = (void*)Utility::FindAndPrintPattern(module
					, findpattern.pattern, wstr(Patterns::CommonGame_ProfileCtrl_Initialize), findpattern.offset);

				if (ProfileCtrl && ProfileCtrlInitJMP) {
					auto static ProfileCtrlInitHook = Utility::MakeMidHook(ProfileCtrlInitJMP,
						[](SafetyHookContext& ctx)
						{
							auto profileCtrl = GetSharedComponents()->GetComponent<ndlib::profiling::ProfileController>();
							profileCtrl->InternalInitialize();

						}, wstr(Patterns::CommonGame_ProfileCtrl_Initialize), wstr(ProfileCtrlInitJMP));

					if (!ProfileCtrlInitHook) {
						throw SdkComponentEx{ std::format("Failed to create hook {:s} in {:s}!", TOSTRING(ProfileCtrlInitHook), GetName()),
							SdkComponentEx::ErrorCode::PatchFailed, false };
					}
				}
			}

	#elif defined(T1X)
			if (m_Memory->IsDebugMemoryAvailable()) {

				auto DebugDraw = GetSharedComponents()->GetComponent<ndlib::render::dev::DebugDrawCommon>();

				findpattern = Patterns::CommonGame_PrimServer_Create;
				auto PrimServerCreateJMP = (void*)Utility::FindAndPrintPattern(module
					, findpattern.pattern, wstr(Patterns::CommonGame_PrimServer_Create), findpattern.offset);

				if (DebugDraw && PrimServerCreateJMP) {

					m_PrimServer_CreateHook = Utility::MakeMidHook(PrimServerCreateJMP,
						[](SafetyHookContext& ctx)
						{
							auto gameinit = GetSharedComponents()->GetComponent<CommonGame>();
							auto pPrimServer = GetSharedComponents()->GetComponent<ndlib::render::dev::DebugDrawCommon>()
								->GetSubComponent<PrimServerManager>();

							if (pPrimServer) {
								MemoryMapEntry* DebugDrawing = gameinit->m_Memory->GetMemoryMapEntry(MemoryMapId::ALLOCATION_DEBUG_DRAWING);
								PrimServer::InitParams pParams{ DebugDrawing->Size() };
								pPrimServer->Create(&pParams);
							}

						}, wstr(Patterns::CommonGame_PrimServer_Create), wstr(PrimServerCreateJMP));

					if (!m_PrimServer_CreateHook) {
						throw SdkComponentEx{ std::format("Failed to create hook {:s} in {:s}!", TOSTRING(m_PrimServer_CreateHook),GetName()),
							SdkComponentEx::ErrorCode::PatchFailed, true };
					}
				}
			}
	#endif
			}

			if (!m_GameInitHook ||
				!m_GameInitReturnHook) {
				throw SdkComponentEx{ "Failed to hook CommonGame functions!",
					SdkComponentEx::ErrorCode::PatchFailed, true };
			}

         #if defined(T2R)
            this->InitSubComponent<NxAppHooks>();
		#endif
			this->InitSubComponent<CommonGameLoop>();
            this->InitSubComponent<CommonMainWin>();

			const char* game_ver_text = "BUILD_NUMBER=";
			uintptr_t version_number = (uintptr_t)Utility::memory::char_Scan(module, game_ver_text);

			if (version_number) {
				m_GameVersion = strtol((const char*)version_number + strlen(game_ver_text), nullptr, 10);
				spdlog::info("Game version: {:d}", m_GameVersion);
			}

		});
	}
}
