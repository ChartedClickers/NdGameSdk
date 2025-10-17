#include "debugdraw-common.hpp"
#include "./NdGameSdk/shared/sharedpatterns.hpp"

#include <NdGameSdk/shared/src/ndlib/profiling/profile-ctrl.hpp>
#include <NdGameSdk/shared/src/corelib/job/job-system.hpp>

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

	void DebugDrawCommon::PrimTextPrint(DebugStringBase& DebugString) {
		m_PrimServerMgr->TextPrint(DebugString);
	}

	void DebugDrawCommon::PrimTextPrint(glm::vec4 pos, Color color, float scale, const char* pStr) {
		DebugStringBase hdr { pos, color, scale, 0, const_cast<char*>(pStr) };
		PrimTextPrint(hdr);
	}

	MsgCon* DebugDrawCommon::GetMsgCon() {
		return m_Msg.s_MsgCon;
	}

	void DebugDrawCommon::Awake() {
		auto SharedComponents = ISdkComponent::GetSharedComponents();
		m_EngineComponents = GetDependencyComponent<EngineComponents>(SharedComponents);
		m_Memory = GetDependencyComponent<Memory>(SharedComponents);
		m_RenderFrameParams = GetDependencyComponent<RenderFrameParams>(SharedComponents);

		m_MsgConDraw = AddSubComponent<MsgConDraw>();
		m_PrimServerMgr = AddSubComponent<PrimServerManager>();
	}

	void DebugDrawCommon::Initialize()
	{
		static std::once_flag Initialized;

		std::call_once(Initialized, [this] {

			spdlog::info("Initializing {} patterns...", GetName());

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
				!m_Text.Text_textPrintV ||
				!m_Text.Text2_GetTextWidthHeight ||
				!m_Msg.Msg_PrintToActiveMsgOutput
				) {
				throw SdkComponentEx{ std::format("Failed to find {}:: game functions!", GetName()), SdkComponentEx::ErrorCode::PatternFailed };
			}

			this->InitSubComponentsOnly<MsgConDraw, PrimServerManager>();

			findpattern = Patterns::GameDebugDraw_StaticContextHook;
			auto GameDebugDrawJMP = (void*)Utility::FindAndPrintPattern(module
				, findpattern.pattern, wstr(Patterns::GameDebugDraw_StaticContextHook), findpattern.offset);

			findpattern = Patterns::GameDebugDraw_DebugDrawSid;
			auto DebugDrawSidJMP = (void*)Utility::FindAndPrintPattern(module
				, findpattern.pattern, wstr(Patterns::GameDebugDraw_DebugDrawSid), findpattern.offset);

			if (!GameDebugDrawJMP ||
				!DebugDrawSidJMP
				) {
				throw SdkComponentEx{ std::format("Failed to find addresses!"),
					SdkComponentEx::ErrorCode::PatternFailed };
			}

			m_DebugDrawHook = Utility::MakeMidHook(GameDebugDrawJMP,
				DebugDraw, wstr(Patterns::GameDebugDraw_StaticContextHook), wstr(GameDebugDrawJMP));

			m_DebugDrawSidHook = Utility::MakeMidHook(DebugDrawSidJMP,
				DebugDrawSid, wstr(Patterns::GameDebugDraw_DebugDrawSid), wstr(GameDeDebugDrawSidJMPbugDrawJMP));

			_snprintf_s(this->debug_primtext, sizeof(this->debug_primtext), "I'm primitive, beautiful, and in full bloom within DebugMem.");

		#if defined(T2R)

			if (m_Memory->IsDebugMemoryAvailable()) {
				findpattern = Patterns::GameDebugDraw_StaticContext_ProfilingHook;
				auto ProfileCtrl = GetSharedComponents()->GetComponent<ndlib::profiling::ProfileController>();
				auto ProfilingHookJMP = (void*)Utility::FindAndPrintPattern(module
					, findpattern.pattern, wstr(Patterns::GameDebugDraw_StaticContext_ProfilingHook), findpattern.offset);

				if (ProfileCtrl && ProfilingHookJMP) {
					auto static ProfilingHook = Utility::MakeMidHook(ProfilingHookJMP,
						[](SafetyHookContext& ctx)
						{
							using namespace ndlib::profiling;
							DebugDrawCommon* DebugDraw = DebugDrawCommon::Instance<DebugDrawCommon>();
							auto static ProfileMgr = GetSharedComponents()->GetComponent<ProfileController>()->GetSubComponent<ProfileManager>();

							if (ProfileMgr) {

								static std::once_flag DrawGraphMemAlloc;
								std::call_once(DrawGraphMemAlloc, [DebugDraw, ctx] {
									void* newBlock = DebugDraw->m_Memory->AllocateAtContext<void>(0x60, 0x10, Memory::Context::kAllocDevCpu);
									if (newBlock) {
										*reinterpret_cast<void**>(ctx.rcx) = newBlock;
										std::memset(newBlock, 0, 0x60);
									}
								});

								ProfileMgr->DrawProfiler(ctx.rcx, true);
							}

						}, wstr(Patterns::GameDebugDraw_StaticContext_ProfilingHook), wstr(ProfilingHookJMP));

					if (!ProfilingHook) {
						throw SdkComponentEx{ std::format("Failed to create hook {:s} in {:s}!", TOSTRING(ProfilingHook), GetName()),
							SdkComponentEx::ErrorCode::PatchFailed };
					}
				}
			}
		#endif

		});
	}

	void DebugDrawCommon::DebugDraw(SafetyHookContext& ctx) {

		DebugDrawCommon* DebugDraw = DebugDrawCommon::Instance<DebugDrawCommon>();
		if (!DebugDraw) return;

		static auto ndjob = GetSharedComponents()->GetComponent<corelib::job::NdJob>();

		if (ndjob) {
			ndjob->DisplayJobSystemData();
		}

		auto* frame = DebugDraw->m_RenderFrameParams->GetRenderFrameParams();
		if (frame) {

			if (DebugDraw->m_DebugTextPrintV) {
				WindowContext ctx{};
				WindowContext::GetWindowContext(&ctx, WindowContext::ContextType::DMenuThread, frame->Get()->m_DynamicRenderContext);

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

			if (DebugDraw->m_DebugPrimTextPrint) {
				DebugDraw->m_DebugStringBase.setText(DebugDraw->debug_primtext);
				DebugDraw->PrimTextPrint(DebugDraw->m_DebugStringBase);
			}

			auto pSdkModules = ISdkModule::GetSdkModules();
			for (auto& [hmod, module] : *pSdkModules) {
				if (module && module->IsRegistered()) {
					module->DebugDraw(frame); 
				}
			}
		}
	}

	void DebugDrawCommon::DebugDrawSid(SafetyHookContext& ctx) {
		static const char* SdkModuleInfo = "<UNKNOWN SdkModule>";
	/*	auto pSdkModule = ISdkModule::GetSdkModules()->begin()->second;
		strcpy(SdkModuleInfo, pSdkModule->GetBuildInfoString().c_str());*/
		ctx.r9 = reinterpret_cast<uintptr_t>(SdkModuleInfo);
	}

	DMENU::ItemSubmenu* DebugDrawCommon::CreateDebugDrawMenu(NdDevMenu* pdmenu, DMENU::Menu* pMenu) {

		DebugDrawCommon* DebugDraw = Instance<DebugDrawCommon>();

		if (DebugDraw) {
			DMENU::Menu* DebugDrawMenu = pdmenu->Create_DMENU_Menu("DebugDraw", HeapArena_Source);

			if (DebugDrawMenu) {

				DMENU::ItemFloat::ValueParams scaleRange{ 0.0f, 2.0f };
				DMENU::ItemFloat::ValueParams positionRange{ 0.0f, 2000.0f };
				DMENU::ItemFloat::StepParams steps{ 0.1f, 1.0f };

				pdmenu->Create_DMENU_ItemBool("Debug TextPrintV", DebugDrawMenu, &DebugDraw->m_DebugTextPrintV, nullptr, HeapArena_Source);
				pdmenu->Create_DMENU_ItemFloat("Font Scale X", DebugDrawMenu, &DebugDraw->m_DebugTextLayout.font_scale_x, scaleRange, steps, "Scale X", HeapArena_Source);
				pdmenu->Create_DMENU_ItemFloat("Font Scale Y", DebugDrawMenu, &DebugDraw->m_DebugTextLayout.font_scale_y, scaleRange, steps, "Scale Y", HeapArena_Source);
				pdmenu->Create_DMENU_ItemFloat("Font Pos X", DebugDrawMenu, &DebugDraw->m_DebugTextLayout.font_x, positionRange, steps, "Position X", HeapArena_Source);
				pdmenu->Create_DMENU_ItemFloat("Font Pos Y", DebugDrawMenu, &DebugDraw->m_DebugTextLayout.font_y, positionRange, steps, "Position Y", HeapArena_Source);

				pdmenu->Create_DMENU_TextLineWrapper("PrimServer Manager", DebugDrawMenu, HeapArena_Source);
				pdmenu->Create_DMENU_ItemBool("Debug PrimTextPrint", DebugDrawMenu, &DebugDraw->m_DebugPrimTextPrint, nullptr, HeapArena_Source);

				DMENU::ItemFloat::ValueParams primScaleRange{ 0.0f,  2.0f };
				DMENU::ItemFloat::ValueParams primPosRange{ 0.0f, 2000.0f };
				DMENU::ItemFloat::StepParams  primSteps{ 0.1f,  1.0f };

				pdmenu->Create_DMENU_ItemFloat("Prim Pos X",
					DebugDrawMenu,
					&DebugDraw->m_DebugStringBase->vec.x,
					primPosRange, primSteps, "Position X",
					HeapArena_Source);

				pdmenu->Create_DMENU_ItemFloat("Prim Pos Y",
					DebugDrawMenu,
					&DebugDraw->m_DebugStringBase->vec.y,
					primPosRange, primSteps, "Position Y",
					HeapArena_Source);

				pdmenu->Create_DMENU_ItemFloat("Prim Scale",
					DebugDrawMenu,
					&DebugDraw->m_DebugStringBase->scale,
					primScaleRange, primSteps, "Scale",
					HeapArena_Source);

				pdmenu->Create_DMENU_KeyBoard("Prim Text",
					DebugDrawMenu,
					DebugDraw->debug_primtext,
					sizeof(DebugDraw->debug_primtext), "Prim Text",
					HeapArena_Source);

				pdmenu->Create_DMENU_TextLineWrapper("Prim Color Presets", DebugDrawMenu, HeapArena_Source);

				pdmenu->Create_DMENU_ItemFunction("Green", DebugDrawMenu, PrimColourPresetCB, Color(BasicColors::Green).toUint64(), false, HeapArena_Source);
				pdmenu->Create_DMENU_ItemFunction("White", DebugDrawMenu, PrimColourPresetCB, Color(BasicColors::White).toUint64(), false, HeapArena_Source);
				pdmenu->Create_DMENU_ItemFunction("Cyan", DebugDrawMenu, PrimColourPresetCB, Color(BasicColors::Cyan).toUint64(), false, HeapArena_Source);


				return pdmenu->Create_DMENU_ItemSubmenu(DebugDrawMenu->Name(),
					pMenu, DebugDrawMenu, NULL, NULL, nullptr, HeapArena_Source);
			}

		}

		return nullptr;
	}
	 
	bool DebugDrawCommon::PrimColourPresetCB(DMENU::ItemFunction& item, DMENU::Message msg)
	{
		DebugDrawCommon* DebugDraw = DebugDrawCommon::Instance<DebugDrawCommon>();

		switch (msg)
		{
		case DMENU::Message::OnExecute: {
			if (DebugDraw) {
				const std::uint32_t abgr = static_cast<std::uint32_t>(item.Data());
				DebugDraw->m_DebugStringBase.setColor(abgr);
				return true;
			}

			return false;
		}
		}

		return true; 
	}

}