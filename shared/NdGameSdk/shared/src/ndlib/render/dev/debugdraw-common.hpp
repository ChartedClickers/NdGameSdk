#pragma once

#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/components/SdkComponent.hpp"
#include "NdGameSdk/components/SdkModule.hpp"

#include <Utility/helper.hpp>
#include <Utility/function_ptr.hpp>

#include <NdGameSdk/shared/src/ndlib/engine-components.hpp>
#include <NdGameSdk/shared/src/corelib/memory/memory.hpp>
#include <NdGameSdk/shared/src/gamelib/debug/nd-dev-menu.hpp>


#include "../window-context.hpp"
#include "../frame-params.hpp"
#include "../util/text.hpp"
#include "../util/msg.hpp"
#include "../util/prim.hpp"
#include "../util/msg-con-draw.hpp"

using namespace NdGameSdk::gamelib::debug;
using namespace NdGameSdk::ndlib::render;
using namespace NdGameSdk::ndlib::render::util;

namespace NdGameSdk::ndlib::render::dev {

	class NdGameSdk_API DebugDrawCommon : public ISdkComponent {
	public:
		struct TextLayout {
			float font_x;
			float font_y;
			float font_scale_x;
			float font_scale_y;
		};

		DebugDrawCommon();
		~DebugDrawCommon();

		MsgCon* GetMsgCon();
		void TextPrintV(WindowContext* ctx, const TextLayout& layout, const char* fmt, ...);
		void PrintToActiveMsgOutput(const char* pStr);

		RenderFrameParams m_RenderFrameParams{};
	private:
		void Awake() override;
		void Initialize() override;

		static DMENU::ItemSubmenu* CreateDebugDrawMenu(NdDevMenu* pdmenu, DMENU::Menu* pMenu);
		static void DebugDraw(SafetyHookContext& ctx);

		bool m_DebugTextPrintV{};
		TextLayout m_DebugTextLayout{ 50., 100., 0.8, 0.8 };

		Text m_Text{};
		Msg m_Msg{};

		MidHook m_DebugDrawHook{};

		shared_ptr<EngineComponents> m_EngineComponents;
		shared_ptr<Memory> m_Memory;

		optional<MsgConDraw> m_MsgConDraw;
		optional<PrimServerManager> m_PrimServerMgr;

		static DebugDrawCommon* s_Instance;

		friend class ISdkModule;
		friend class MsgConDraw;
		friend class PrimServerManager;
		friend class NdDevMenu;
	};
}