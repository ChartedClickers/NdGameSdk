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

			findpattern = Patterns::CommonGameLoop_GameLoopUpdate;
			auto GameLoopUpdateJMP = (void*)Utility::FindAndPrintPattern(module
				, findpattern.pattern, wstr(Patterns::CommonGameLoop_GameLoopUpdate), findpattern.offset);

			findpattern = Patterns::CommonGameLoop_GameDebugUpdate;
			auto GameDebugUpdateJMP = (void*)Utility::FindAndPrintPattern(module
				, findpattern.pattern, wstr(Patterns::CommonGameLoop_GameDebugUpdate), findpattern.offset);

			if (!GameLoopUpdateJMP || !GameDebugUpdateJMP) {
				throw SdkComponentEx
				{ std::format("Failed to find addresses!"),
					SdkComponentEx::ErrorCode::PatternFailed };
			}

			m_GameLoopUpdate = Utility::MakeMidHook(GameLoopUpdateJMP, GameLoopUpdate, wstr(Patterns::CommonGameLoop_GameLoopUpdate), wstr(GameLoopUpdateJMP));
			m_GameDebugUpdate = Utility::MakeMidHook(GameDebugUpdateJMP, GameDebugUpdate, wstr(Patterns::CommonGameLoop_GameDebugUpdate), wstr(GameDebugUpdateJMP));

			if (!m_GameLoopUpdate || !m_GameDebugUpdate) {
				throw SdkComponentEx{ std::format("Failed to create hooks!"),
					SdkComponentEx::ErrorCode::PatchFailed };
			}

		});
	}

	void CommonGameLoop::GameLoopUpdate(SafetyHookContext& ctx) {
		using NdKeyboardKey = NdFrameState::NdKeyboardLayer::Key;

#ifndef NDEBUG
		static shared_ptr<CommonGameLoop> pCommonGameLoop = GetSharedComponents()->
			GetComponent<CommonGame>()->GetSubComponent<CommonGameLoop>();
		auto NdFrameState = pCommonGameLoop->m_EngineComponents->GetNdFrameState();
		auto kbd = NdFrameState.GetIMEKeyboard();

		if (kbd->isDebugKeyboard()) {

			if (kbd->wasPressed(NdKeyboardKey::V)) {
				spdlog::debug("User pressed V");
			}

			if (kbd->isCtrlDown() && kbd->wasPressed(NdKeyboardKey::V)) {
				spdlog::debug("User pressed Ctrl + V");
			}

			kbd->DebugkeysPressed();
		}
#endif
	}

	void CommonGameLoop::GameDebugUpdate(SafetyHookContext& ctx) {
		static shared_ptr<CommonGameLoop> pCommonGameLoop = GetSharedComponents()->
			GetComponent<CommonGame>()->GetSubComponent<CommonGameLoop>();

		if (pCommonGameLoop->m_NdDevMenu) {
			auto NdConfig = pCommonGameLoop->m_EngineComponents->m_ndConfig;
			pCommonGameLoop->m_NdDevMenu->DMENU_Menu_Update(&NdConfig.GetDmenu());
		}

	}


}