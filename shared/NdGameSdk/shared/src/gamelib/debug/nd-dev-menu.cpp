#include "nd-dev-menu.hpp"
#include "./NdGameSdk/shared/sharedpatterns.hpp"

namespace NdGameSdk::gamelib::debug {

	NdDevMenu::NdDevMenu(NdDevMenuCfg& cfg) : m_cfg{ std::move(cfg) }, ISdkComponent("DMENU") {}

	bool NdDevMenu::IsGameDebugMenu() {

		auto& gameinfo = m_EngineComponents->GetNdGameInfo();
		if (gameinfo.Get()) {
			return m_EngineComponents->GetNdGameInfo()->m_DevMode;
		}

		return m_cfg.GameDebugMenu;
	}

	bool NdDevMenu::IsExtendedDebugMenu() {
		return m_cfg.ExtendedDebugMenu;
	}

	void NdDevMenu::Awake() {
		auto SharedComponents = ISdkComponent::GetSharedComponents();
		m_Memory = SharedComponents->GetComponent<Memory>();
		m_EngineComponents = SharedComponents->GetComponent<EngineComponents>();
		m_CommonGame = SharedComponents->GetComponent<CommonGame>();
	}

	void NdDevMenu::Initialize() {
		static std::once_flag Initialized;

		std::call_once(Initialized, [this] {

			spdlog::info("Initializing {} patterns...", GetName());

			auto MissingDependencies = CheckSdkComponents
				<Memory, CommonGame, EngineComponents>
				({ m_Memory.get(), m_CommonGame.get(), m_EngineComponents.get() });

			if (MissingDependencies.has_value()) {
				throw SdkComponentEx
				{ std::format("Missing necessary dependencies: {:s}", MissingDependencies.value()),
					SdkComponentEx::ErrorCode::DependenciesFailed };
			}

			Patterns::SdkPattern findpattern{};
			auto module = Utility::memory::get_executable();

			const unsigned char mov_ecx_0[] = { 0xb9, 0x00, 0x00, 0x00, 0x00, 0x90 };

			findpattern = Patterns::NdDevMenu_GameConfig_DevMode;
			m_GameConfig_DevModePatch = Utility::WritePatchPattern(module, findpattern.pattern, mov_ecx_0, sizeof(mov_ecx_0),
				wstr(Patterns::NdDevMenu_GameConfig_DevMode), findpattern.offset, m_cfg.GameDebugMenu);

			if (!m_GameConfig_DevModePatch) {
				throw SdkComponentEx{ "Failed to patch game functions!", SdkComponentEx::ErrorCode::PatchFailed };
			}

			if (m_GameConfig_DevModePatch->IsEnable()) {
				spdlog::info("GameDebugMenu is enabled!");

	#if defined(T1X)
				if (m_cfg.ExtendedDebugMenu && m_Memory->IsDebugMemoryAvailable()) {

					findpattern = Patterns::NdDevMenu_Assert_UpdateSelectRegionByNameMenu;
					m_Assert_UpdateSelectRegionByNameMenuPatch = Utility::WritePatchNop(module, findpattern.pattern, 0x1,
						wstr(Patterns::NdDevMenu_Assert_UpdateSelectRegionByNameMenu), findpattern.offset);

					findpattern = Patterns::NdDevMenu_Assert_UpdateSelectIgcByNameMenu;
					m_Assert_UpdateSelectIgcByNameMenuPatch = Utility::WritePatchNop(module, findpattern.pattern, 0x1,
						wstr(Patterns::NdDevMenu_Assert_UpdateSelectIgcByNameMenu), findpattern.offset);

					findpattern = Patterns::NdDevMenu_Assert_UpdateSelectSpawnerByNameMenu;
					m_Assert_UpdateSelectSpawnerByNameMenuPatch = Utility::WritePatchNop(module, findpattern.pattern, 0x1,
						wstr(Patterns::NdDevMenu_Assert_UpdateSelectSpawnerByNameMenu), findpattern.offset);

					spdlog::info("ExtendedDebugMenu is enabled!");
				}
	#endif

				findpattern = Patterns::NdDevMenu_DMENU_MenuGroup_SetRootMenu;
				auto SetRootMenuJMP = (void*)Utility::FindAndPrintPattern(module
					, findpattern.pattern, wstr(Patterns::NdDevMenu_DMENU_MenuGroup_SetRootMenu), findpattern.offset + 0x93);

				/*findpattern = Patterns::NdDevMenu_DMENU_Component;
				DMENU::Component::VTable = (regenny::shared::ndlib::debug::DMENU::Component::VTable*)Utility::ReadLEA32(module,
					findpattern.pattern, wstr(Patterns::NdDevMenu_DMENU_Component), findpattern.offset + 0x, 3, 8);*/

				if (!SetRootMenuJMP) {
					throw SdkComponentEx{ std::format("Failed to find {}:: game functions!", GetName()), SdkComponentEx::ErrorCode::PatternFailed };
				}

				m_CommonGame->e_GameInitialized.Subscribe(*[](bool successful) {
					if (successful) {
						auto& DMENU = GetSharedComponents()->
							GetComponent<NdDevMenu>()->m_EngineComponents->m_ndConfig.GetDmenu();

						auto DevMenu = DMENU.DevMenu()->RootMenu();
						DevMenu->SetName((DevMenu->Name() + std::format(" [{}]", SDK_NAME)).c_str());
					}
					});

				m_SetRootMenuHook = Utility::MakeMidHook(SetRootMenuJMP,
					[](SafetyHookContext& ctx)
					{
						auto DevMenu = GetSharedComponents()->GetComponent<NdDevMenu>();
						 
						auto MenuGroup = reinterpret_cast<DMENU::MenuGroup*>(ctx.rdi);
						auto Menu = reinterpret_cast<DMENU::Menu*>(ctx.rbx);

					}, wstr(Patterns::NdDevMenu_DMENU_MenuGroup_SetRootMenu), wstr(SetRootMenuJMP));

			}
		});
	}
}