#pragma once

#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/components/SdkComponent.hpp"
#include "NdGameSdk/components/SdkModule.hpp"

#include <Utility/helper.hpp>
#include <Utility/function_ptr.hpp>

#include <NdGameSdk/shared/src/common/common-game-init.hpp>
#include <NdGameSdk/shared/src/ndlib/engine-components.hpp>
#include <NdGameSdk/shared/src/corelib/memory/memory.hpp>
#include <NdGameSdk/shared/src/gamelib/debug/nd-dev-menu.hpp>


#include "../window-context.hpp"
#include "../frame-params.hpp"
#include "../util/text.hpp"
#include "../util/msg.hpp"
#include "../util/msg-con-draw.hpp"

using namespace NdGameSdk::common;
using namespace NdGameSdk::gamelib::debug;
using namespace NdGameSdk::ndlib::render;
using namespace NdGameSdk::ndlib::render::util;

namespace NdGameSdk::ndlib::render::dev {

	class DebugDrawCommon : public ISdkComponent {
	public:
		DebugDrawCommon();
		~DebugDrawCommon();

		RenderFrameParams m_RenderFrameParams{};
		Text m_Text{};
		Msg m_Msg{};

		static DMENU::ItemSubmenu* CreateDebugDrawMenu(NdDevMenu* pdmenu, DMENU::Menu* pMenu);
	private:
		void Awake() override;
		void Initialize() override;

		void OnGameInitialized(bool successful);

		static void DebugDraw(SafetyHookContext& ctx);

		bool m_CustomTextPrintV{};
		bool m_CustomMsgCon{};
		MidHook m_DebugDrawHook{};

		shared_ptr<CommonGame> m_CommonGame;
		shared_ptr<EngineComponents> m_EngineComponents;
		optional<MsgConDraw> m_MsgConDraw;

		static DebugDrawCommon* s_Instance;

		friend class ISdkModule;
	};
}