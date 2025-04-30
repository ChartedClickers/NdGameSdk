#include "common-game-loop.hpp"
#include "./NdGameSdk/shared/sharedpatterns.hpp"

namespace NdGameSdk::common {

	CommonGameLoop::CommonGameLoop(EngineComponents* pEngineComponents, NdDevMenu* pNdDevMenu)
		: m_EngineComponents{ pEngineComponents }, m_NdDevMenu{ pNdDevMenu }, ISdkSubComponent(TOSTRING(CommonGameLoop)) {}

	void CommonGameLoop::Init() {
		
		static std::once_flag Initialized;
		std::call_once(Initialized, [this] {
			spdlog::info("Initializing {} patterns...", GetName());

			Patterns::SdkPattern findpattern{};
			auto module = Utility::memory::get_executable();

			findpattern = Patterns::CommonGameLoop_GameDebugUpdate;
			auto GameDebugUpdateJMP = (void*)Utility::FindAndPrintPattern(module
				, findpattern.pattern, wstr(Patterns::CommonGameLoop_GameDebugUpdate), findpattern.offset);

			m_GameDebugUpdate_DMENU_KeyboardDevMode = Utility::MakeMidHook(GameDebugUpdateJMP,
				[](SafetyHookContext& ctx) {

					static shared_ptr<CommonGameLoop> pCommonGameLoop = GetSharedComponents()->
						GetComponent<CommonGame>()->GetSubComponent<CommonGameLoop>();

					if (pCommonGameLoop->m_NdDevMenu) {
						auto NdConfig = pCommonGameLoop->m_EngineComponents->m_ndConfig;
						pCommonGameLoop->m_NdDevMenu->DMENU_Menu_Update(&NdConfig.GetDmenu());
					}

				}, wstr(Patterns::CommonGameLoop_GameDebugUpdate), wstr(GameDebugUpdateJMP));

		});

	}
}