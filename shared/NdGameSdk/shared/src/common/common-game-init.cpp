#include "common-game-init.hpp"
#include "./NdGameSdk/shared/sharedpatterns.hpp"

#include <NdGameSdk/shared/src/ndlib/render/dev/debugdraw-common.hpp>

namespace NdGameSdk::common {

	CommonGame::CommonGame() : ISdkComponent("CommonGameInit") {}

	uint32_t CommonGame::GetGameVersion() {
		return m_GameVersion;
	}

	bool CommonGame::IsGameInitialized() {
		return m_GameInitialized;
	}

	void CommonGame::Awake() {
		auto SharedComponents = ISdkComponent::GetSharedComponents();
		m_Memory = SharedComponents->GetComponent<Memory>();
		m_EngineComponents = SharedComponents->GetComponent<ndlib::EngineComponents>();
		m_PrimServer = SharedComponents->GetComponent<ndlib::render::dev::DebugDrawCommon>()->GetSubComponent<PrimServerManager>();
		m_IAllocator = AddSubComponent<IAllocator>();
	}

	void CommonGame::Initialize() {
		static std::once_flag Initialized;

		std::call_once(Initialized, [this] {
			
			spdlog::info("Initializing {} patterns...", GetName());

			auto MissingDependencies = CheckSdkComponents
				<Memory>({ m_Memory.get() });

			if (MissingDependencies.has_value()) {
				throw SdkComponentEx
				{ std::format("Missing necessary dependencies: {:s}", MissingDependencies.value()),
					SdkComponentEx::ErrorCode::DependenciesFailed, true };
			}

			auto module = Utility::memory::get_executable();

			Patterns::SdkPattern findpattern{};

#if defined(T2R)
			constexpr size_t GameInitReturnHook_Offset = 0x13;
#elif defined(T1X)
			constexpr size_t GameInitReturnHook_Offset = 0x4c;
#endif

			findpattern = Patterns::GameInit;
			auto GameInitJMP = (void*)Utility::FindAndPrintPattern(module
				, findpattern.pattern, wstr(Patterns::GameInit), findpattern.offset);
			auto GameInitReturnJMP = (void*)Utility::FindAndPrintPattern(module
				, findpattern.pattern, wstr(Patterns::GameInit), findpattern.offset + GameInitReturnHook_Offset);

			if (!GameInitJMP ||
				!GameInitReturnJMP) {
				throw SdkComponentEx
				{ std::format("Failed to find addresses!"),
					SdkComponentEx::ErrorCode::PatternFailed };
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
						ndgameinfo->m_DevConfig = true;
					}

				}, wstr(Patterns::GameInit), wstr(GameInitJMP));


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

				}, wstr(Patterns::GameInit), wstr(GameInitReturnJMP));

	#if defined(T2R)
			findpattern = Patterns::NIXXES_StdHandle;
			m_NxAppHooks.m_StdHandleHook = Utility::WritePatchPattern_Hook(module, findpattern.pattern, wstr(Patterns::NIXXES_StdHandle),
				findpattern.offset, (void*)NxAppHooks_StdHandle_CC);

			if (!m_NxAppHooks.m_StdHandleHook) {
				spdlog::warn("Failed to patch {:s}! Logs may not work!", TOSTRING(Patterns::NIXXES_StdHandle));
			}

			m_IAllocator->Init();

	#elif defined(T1X)
			if (m_Memory->IsDebugMemoryAvailable()) {
				if (m_PrimServer.get() && m_PrimServer->IsInitialized()) {

					findpattern = Patterns::GameInit_PrimServer_Create;
					auto PrimServerCreateJMP = (void*)Utility::FindAndPrintPattern(module
						, findpattern.pattern, wstr(Patterns::GameInit_PrimServer_Create), findpattern.offset);

					m_PrimServer_CreateHook = Utility::MakeMidHook(PrimServerCreateJMP,
						[](SafetyHookContext& ctx)
						{
							auto gameinit = GetSharedComponents()->GetComponent<CommonGame>();
							MemoryMapEntry* DebugDrawing = gameinit->m_Memory->GetMemoryMapEntry(MemoryMapId::ALLOCATION_DEBUG_DRAWING);
							PrimServer::InitParams pParams{ DebugDrawing->Size() };
							gameinit->m_PrimServer->Create(&pParams);

						}, wstr(Patterns::GameInit_PrimServer_Create), wstr(PrimServerCreateJMP));

					if (!m_PrimServer_CreateHook) {
						throw SdkComponentEx{ std::format("Failed to create hook {:s} in {:s}!", TOSTRING(m_PrimServer_CreateHook),GetName()),
							SdkComponentEx::ErrorCode::PatchFailed };
					}
				}
			}
	#endif

			if (!m_GameInitHook ||
				!m_GameInitReturnHook) {
				throw SdkComponentEx{ "Failed to hook CommonGame functions!",
					SdkComponentEx::ErrorCode::PatchFailed };
			}

			const char* game_ver_text = "BUILD_NUMBER=";
			uintptr_t version_number = (uintptr_t)Utility::memory::char_Scan(module, game_ver_text);

			if (version_number) {
				m_GameVersion = strtol((const char*)version_number + strlen(game_ver_text), nullptr, 10);
				spdlog::info("Game version: {:d}", m_GameVersion);
			}

		});
	}
}