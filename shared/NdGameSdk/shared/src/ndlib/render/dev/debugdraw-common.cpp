#include "debugdraw-common.hpp"

#if defined(T2R)

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
	}

	void DebugDrawCommon::Initialize()
	{
		static std::once_flag Initialized;

		std::call_once(Initialized, [this] {

			spdlog::info("Initializing {} patterns...", GetName());

			auto MissingDependencies = CheckSdkComponents<CommonGame> ({ m_CommonGame.get() });

			if (MissingDependencies.has_value()) {
				throw SdkComponentEx
				{ std::format("Missing necessary dependencies: {:s}", MissingDependencies.value()),
					SdkComponentEx::ErrorCode::DependenciesFailed };
			}

			Patterns::SdkPattern findpattern{};
			auto module = Utility::memory::get_executable();
		
			findpattern = Patterns::WindowContext_WindowContext;
			WindowContext_WindowContext = (WindowContext_WindowContext_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::WindowContext_WindowContext), findpattern.offset);

			findpattern = Patterns::FrameParams_GetFrameParams;
			m_RenderFrameParams.FrameParams_GetFrameParams = (RenderFrameParams::FrameParams_GetFrameParams_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::FrameParams_GetFrameParams), findpattern.offset);

			findpattern = Patterns::Text_textPrintV;
			m_Text.Text_textPrintV = (Text::Text_textPrintV_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::Text_textPrintV), findpattern.offset);

			if (!WindowContext_WindowContext ||
				!m_RenderFrameParams.FrameParams_GetFrameParams ||
				!m_Text.Text_textPrintV
				) {
				throw SdkComponentEx{ std::format("Failed to find {}:: game functions!", GetName()), SdkComponentEx::ErrorCode::PatternFailed };
			}

			s_DebugDraw = this;
			m_CommonGame->e_GameInitialized.Subscribe(this, &DebugDrawCommon::OnGameInitialized);

			findpattern = Patterns::GameDebugDraw_StaticContextHook;
			auto GameDebugDrawJMP = (void*)Utility::FindAndPrintPattern(module
				, findpattern.pattern, wstr(Patterns::GameDebugDraw_StaticContextHook), findpattern.offset);

			m_DebugDrawHook = Utility::MakeMidHook(GameDebugDrawJMP,
				DebugDraw, wstr(Patterns::GameDebugDraw_StaticContextHook), wstr(GameDebugDrawJMP));

		});
	}

	void DebugDrawCommon::DebugDraw(SafetyHookContext& ctx) {
		if (!s_DebugDraw) return; 

		auto* frame = s_DebugDraw->m_RenderFrameParams.GetRenderFrameParams();

		if (frame) {
			WindowContext ctx{};
			WindowContext::GetWindowContext(&ctx, WindowContext::ContextType::Context4, frame->m_DynamicRenderContext);
			char print_text[256]{};
			_snprintf_s(print_text, sizeof(print_text), SDK_NAME);
			s_DebugDraw->m_Text.TextPrintV(&ctx, 50., 120., 0.8, 0.8, Color(BasicColors::White), print_text);

			auto pSdkModules = ISdkModule::GetSdkModules();

			for (auto& [hmod, module] : *pSdkModules)
				if (module && module->IsRegistered()) {
					module->DebugDraw(frame);
				}
		}
	}

	void DebugDrawCommon::OnGameInitialized(bool successful) {
		if (successful) {
			
		}
	}

	DebugDrawCommon* DebugDrawCommon::s_DebugDraw = nullptr;

	}


#endif