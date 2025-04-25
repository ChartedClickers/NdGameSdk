#include "debugdraw-common.hpp"

#include "./NdGameSdk/shared/sharedpatterns.hpp"

namespace NdGameSdk::ndlib::render::dev {

	DebugDrawCommon::DebugDrawCommon() : ISdkComponent("DebugDraw") {}

	DebugDrawCommon::~DebugDrawCommon() {}

	void DebugDrawCommon::TextPrintV(WindowContext* ctx, const TextLayout& layout, const char* fmt, ...) {
		
		if (m_EngineComponents->GetNdGameInfo()->m_DisableFpsStat)
			return;

		va_list args;
		va_start(args, fmt);
		m_Text.TextPrintV(ctx, layout.font_x, layout.font_y, layout.font_scale_x, layout.font_scale_y, fmt, args);
		va_end(args);
	}

	void DebugDrawCommon::PrintToActiveMsgOutput(const char* pStr) {
		m_Msg.PrintToActiveMsgOutput(pStr);
	}

	MsgCon* DebugDrawCommon::GetMsgCon() {
		return m_Msg.s_MsgCon;
	}

	void DebugDrawCommon::Awake() {
		auto SharedComponents = ISdkComponent::GetSharedComponents();
		m_EngineComponents = SharedComponents->GetComponent<EngineComponents>();
		m_Memory = SharedComponents->GetComponent<Memory>();

		AddSubComponent<MsgConDraw>(this);
		AddSubComponent<PrimServerManager>(this);
	}

	void DebugDrawCommon::Initialize()
	{
		static std::once_flag Initialized;

		std::call_once(Initialized, [this] {

			spdlog::info("Initializing {} patterns...", GetName());

			auto MissingDependencies = CheckSdkComponents<Memory, EngineComponents>
				({ m_Memory.get(), m_EngineComponents.get()});

			if (MissingDependencies.has_value()) {
				throw SdkComponentEx
				{ std::format("Missing necessary dependencies: {:s}", MissingDependencies.value()),
					SdkComponentEx::ErrorCode::DependenciesFailed };
			}

			Patterns::SdkPattern findpattern{};
			auto module = Utility::memory::get_executable();
		
			findpattern = Patterns::Msg_s_MsgCon;
			m_Msg.s_MsgCon = (MsgCon*)Utility::ReadLEA32(module,
				findpattern.pattern, wstr(Patterns::Memory_TaggedHeap_TaggedGpuDevHeap), findpattern.offset, 3, 7);

			if (!m_Msg.s_MsgCon) {
				throw SdkComponentEx
				{ std::format("Failed to find addresses!"),
					SdkComponentEx::ErrorCode::PatternFailed, true };
			}

			findpattern = Patterns::WindowContext_WindowContext;
			WindowContext_WindowContext = (WindowContext_WindowContext_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::WindowContext_WindowContext), findpattern.offset);

			findpattern = Patterns::FrameParams_GetFrameParams;
			m_RenderFrameParams.FrameParams_GetFrameParams = (RenderFrameParams::FrameParams_GetFrameParams_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::FrameParams_GetFrameParams), findpattern.offset);

			findpattern = Patterns::Text_textPrintV;
			m_Text.Text_textPrintV = (Text::Text_textPrintV_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::Text_textPrintV), findpattern.offset);

			findpattern = Patterns::Text2_GetTextWidthHeight;
			m_Text.Text2_GetTextWidthHeight = (Text::Text2_GetTextWidthHeight_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::Text2_GetTextWidthHeight), findpattern.offset);

			findpattern = Patterns::Msg_PrintToActiveMsgOutput;
			m_Msg.Msg_PrintToActiveMsgOutput = (Msg::Msg_PrintToActiveMsgOutput_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::Msg_PrintToActiveMsgOutput), findpattern.offset);

			if (!WindowContext_WindowContext ||
				!m_RenderFrameParams.FrameParams_GetFrameParams ||
				!m_Text.Text_textPrintV ||
				!m_Text.Text2_GetTextWidthHeight ||
				!m_Msg.Msg_PrintToActiveMsgOutput
				) {
				throw SdkComponentEx{ std::format("Failed to find {}:: game functions!", GetName()), SdkComponentEx::ErrorCode::PatternFailed };
			}

			this->InitSubComponents();

			s_Instance = this;

			findpattern = Patterns::GameDebugDraw_StaticContextHook;
			auto GameDebugDrawJMP = (void*)Utility::FindAndPrintPattern(module
				, findpattern.pattern, wstr(Patterns::GameDebugDraw_StaticContextHook), findpattern.offset);

			m_DebugDrawHook = Utility::MakeMidHook(GameDebugDrawJMP,
				DebugDraw, wstr(Patterns::GameDebugDraw_StaticContextHook), wstr(GameDebugDrawJMP));

		});
	}

	void DebugDrawCommon::DebugDraw(SafetyHookContext& ctx) {
		if (!s_Instance) return;
		DebugDrawCommon* DebugDraw{ s_Instance };

		auto* frame = s_Instance->m_RenderFrameParams.GetRenderFrameParams();
		if (frame) {

			if (DebugDraw->m_DebugTextPrintV) {
				WindowContext ctx{};
				WindowContext::GetWindowContext(&ctx, WindowContext::ContextType::Context4, frame->m_DynamicRenderContext);

				const auto& layout = DebugDraw->m_DebugTextLayout;
				char debug_text[256]{};
				_snprintf_s(debug_text, sizeof(debug_text),
					"%s: scale(%.2f %.2f) pos(%.2f %.2f)",
					SDK_NAME,
					layout.font_scale_x, layout.font_scale_y,
					layout.font_x, layout.font_y
				);

				DebugDraw->TextPrintV(&ctx, layout, debug_text);
				DebugDraw->TextPrintV(&ctx, { 50., 150., 0.6, 0.6 }, ANSI_RED "The" " " ANSI_GRN "quick" " " ANSI_YEL "brown" " " ANSI_BLU  "fox\n\n\n" ANSI_MAG "jumps" " " ANSI_CYN "over" " " ANSI_WHT "the\n" ANSI_RED "lazy" " " ANSI_WHT "dog");
			}

			auto pSdkModules = ISdkModule::GetSdkModules();
			for (auto& [hmod, module] : *pSdkModules) {
				if (module && module->IsRegistered()) {
					module->DebugDraw(frame);
				}
			}
		}
	}


	DMENU::ItemSubmenu* DebugDrawCommon::CreateDebugDrawMenu(NdDevMenu* pdmenu, DMENU::Menu* pMenu) {
		if (s_Instance) {
			DMENU::Menu* DebugDrawMenu = pdmenu->Create_DMENU_Menu("DebugDraw", HeapArena_Source);

			if (DebugDrawMenu) {

				DMENU::ItemFloat::ValueParams scaleRange{ 0.0f, 2.0f };
				DMENU::ItemFloat::ValueParams positionRange{ 0.0f, 2000.0f };
				DMENU::ItemFloat::StepParams steps{ 0.1f, 1.0f };

				pdmenu->Create_DMENU_ItemBool("Debug TextPrintV", DebugDrawMenu, &s_Instance->m_DebugTextPrintV, nullptr, HeapArena_Source);
				pdmenu->Create_DMENU_ItemFloat("Font Scale X", DebugDrawMenu, &s_Instance->m_DebugTextLayout.font_scale_x, scaleRange, steps, "Scale X", HeapArena_Source);
				pdmenu->Create_DMENU_ItemFloat("Font Scale Y", DebugDrawMenu, &s_Instance->m_DebugTextLayout.font_scale_y, scaleRange, steps, "Scale Y", HeapArena_Source);
				pdmenu->Create_DMENU_ItemFloat("Font Pos X", DebugDrawMenu, &s_Instance->m_DebugTextLayout.font_x, positionRange, steps, "Position X", HeapArena_Source);
				pdmenu->Create_DMENU_ItemFloat("Font Pos Y", DebugDrawMenu, &s_Instance->m_DebugTextLayout.font_y, positionRange, steps, "Position Y", HeapArena_Source);

				return pdmenu->Create_DMENU_ItemSubmenu(DebugDrawMenu->Name(),
					pMenu, DebugDrawMenu, NULL, NULL, nullptr, HeapArena_Source);
			}

		}

		return nullptr;
	}

	DebugDrawCommon* DebugDrawCommon::s_Instance = nullptr;

}