#include "debugdraw-common.hpp"

#include "./NdGameSdk/shared/sharedpatterns.hpp"

namespace NdGameSdk::ndlib::render::dev {

	DebugDrawCommon::DebugDrawCommon() : ISdkComponent("DebugDraw") {}

	DebugDrawCommon::~DebugDrawCommon() {
		if (IsInitialized()) {
			m_CommonGame->e_GameInitialized.Unsubscribe({ this, &DebugDrawCommon::OnGameInitialized });
		}
	}

	void DebugDrawCommon::Awake() {
		auto SharedComponents = ISdkComponent::GetSharedComponents();
		m_CommonGame = SharedComponents->GetComponent<CommonGame>();
		m_EngineComponents = SharedComponents->GetComponent<EngineComponents>();
		m_MsgConDraw.emplace(this, SharedComponents->GetComponent<Memory>().get());
	}

	void DebugDrawCommon::Initialize()
	{
		static std::once_flag Initialized;

		std::call_once(Initialized, [this] {

			spdlog::info("Initializing {} patterns...", GetName());

			auto MissingDependencies = CheckSdkComponents<CommonGame, EngineComponents> 
				({ m_CommonGame.get(), m_EngineComponents.get()});

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

			s_Instance = this;
			m_CommonGame->e_GameInitialized.Subscribe(this, &DebugDrawCommon::OnGameInitialized);

			findpattern = Patterns::GameDebugDraw_StaticContextHook;
			auto GameDebugDrawJMP = (void*)Utility::FindAndPrintPattern(module
				, findpattern.pattern, wstr(Patterns::GameDebugDraw_StaticContextHook), findpattern.offset);

			m_DebugDrawHook = Utility::MakeMidHook(GameDebugDrawJMP,
				DebugDraw, wstr(Patterns::GameDebugDraw_StaticContextHook), wstr(GameDebugDrawJMP));

			m_MsgConDraw->MsgConDrawBuffersPatch();

		});
	}

	void DebugDrawCommon::DebugDraw(SafetyHookContext& ctx) {

		if (!s_Instance || s_Instance->m_EngineComponents->GetNdGameInfo()->m_DisableFpsStat) return;

		if (s_Instance->m_CustomMsgCon) {
			s_Instance->m_Msg.PrintToActiveMsgOutput(ANSI_CYN "==============" SDK_NAME " Debug Info ==============\n" ANSI_RESET);

			s_Instance->m_Msg.PrintToActiveMsgOutput(ANSI_GRN "TEST INFO\n");

			s_Instance->m_Msg.PrintToActiveMsgOutput(ANSI_WHT "--------------------------------------------------\n");
		}

		if (s_Instance->m_CustomTextPrintV) {
			auto* frame = s_Instance->m_RenderFrameParams.GetRenderFrameParams();
			if (frame) {
				WindowContext ctx{};
				WindowContext::GetWindowContext(&ctx, WindowContext::ContextType::Context4, frame->m_DynamicRenderContext);
				s_Instance->m_Text.TextPrintV(&ctx, 50., 150., 0.6, 0.6, ANSI_RED "The" " " ANSI_GRN "quick" " " ANSI_YEL "brown" " " ANSI_BLU  "fox\n\n\n" ANSI_MAG "jumps" " " ANSI_CYN "over" " " ANSI_WHT "the\n" ANSI_RED "lazy" " " ANSI_WHT "dog");
				s_Instance->m_Text.TextPrintV(&ctx, 50., 100., 0.8, 0.8, SDK_NAME);

				auto pSdkModules = ISdkModule::GetSdkModules();

				for (auto& [hmod, module] : *pSdkModules)
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
				pdmenu->Create_DMENU_ItemBool("CustomDebugDraw TextPrintV", DebugDrawMenu, &s_Instance->m_CustomTextPrintV, nullptr, HeapArena_Source);
				pdmenu->Create_DMENU_ItemBool("CustomDebugDraw CustomMsgCon", DebugDrawMenu, &s_Instance->m_CustomMsgCon, nullptr, HeapArena_Source);
				return pdmenu->Create_DMENU_ItemSubmenu(DebugDrawMenu->Name(),
					pMenu, DebugDrawMenu, NULL, NULL, nullptr, HeapArena_Source);
			}

		}

		return nullptr;
	}

	void DebugDrawCommon::OnGameInitialized(bool successful) {
		if (successful) {
			
		}
	}

	DebugDrawCommon* DebugDrawCommon::s_Instance = nullptr;

	}