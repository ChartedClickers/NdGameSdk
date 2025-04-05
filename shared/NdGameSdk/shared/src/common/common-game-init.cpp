#include "common-game-init.hpp"
#include "./NdGameSdk/shared/sharedpatterns.hpp"

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
	#if defined(T1X)
		m_Memory = SharedComponents->GetComponent<Memory>();
	#endif
	}

	void CommonGame::Initialize() {
		static std::once_flag Initialized;

		std::call_once(Initialized, [this] {
			
			spdlog::info("Initializing {} patterns...", GetName());

			#if defined(T1X)
			auto MissingDependencies = CheckSdkComponents
				<Memory>({ m_Memory.get() });

			if (MissingDependencies.has_value()) {
				throw SdkComponentEx
				{ std::format("Missing necessary dependencies: {:s}", MissingDependencies.value()),
					SdkComponentEx::ErrorCode::DependenciesFailed, true };
			}
			#endif

			auto module = Utility::memory::get_executable();

			Patterns::SdkPattern findpattern{};

			findpattern = Patterns::GameInit_ReturnHook;
			auto GameInitJMP = (void*)Utility::FindAndPrintPattern(module
				, findpattern.pattern, wstr(Patterns::GameInit_ReturnHook), findpattern.offset);

			if (!GameInitJMP) {
				throw SdkComponentEx
				{ std::format("Failed to find addresses!"),
					SdkComponentEx::ErrorCode::PatternFailed };
			}

			m_GameInitHook = Utility::MakeMidHook(GameInitJMP,
				[](SafetyHookContext& ctx)
				{
					auto gameinit = GetSharedComponents()->GetComponent<CommonGame>();
					bool successful = !((*(uint32_t*)ctx.rax) > 0);
					gameinit->m_GameInitialized = successful;
					gameinit->InvokeSdkEvent(gameinit->e_GameInitialized, successful);

				}, wstr(Patterns::GameInit_ReturnHook), wstr(GameInitJMP));

	#if defined(T2R)
			findpattern = Patterns::NIXXES_StdHandle;
			m_NxAppHooks.m_StdHandleHook = Utility::WritePatchPattern_Hook(module, findpattern.pattern, wstr(Patterns::NIXXES_StdHandle),
				findpattern.offset, (void*)NxAppHooks_StdHandle_CC);

			if (!m_NxAppHooks.m_StdHandleHook) {
				spdlog::warn("Failed to patch {:s}! Logs may not work!", TOSTRING(Patterns::NIXXES_StdHandle));
			}

	#endif

	#if defined(T1X)
			m_PrimServer = ISdkComponent::GetSharedComponents()->GetComponent<PrimServerComponent>();
			if (m_PrimServer.get() && m_PrimServer->IsInitialized() && 
				m_PrimServer->m_cfg.PrimServerCreate) {

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
	#endif

			if (!m_GameInitHook) {
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