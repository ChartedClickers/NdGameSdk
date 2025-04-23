#include "msg-con-draw.hpp"
#include "../dev/debugdraw-common.hpp"
#include "../frame-params.hpp"

#include "./NdGameSdk/shared/sharedpatterns.hpp"

#if defined(T1X)
#include <NdGameSdk/shared/src/gamelib/statescript/ss-manager.hpp>
using namespace NdGameSdk::gamelib::statescript;
#endif

namespace NdGameSdk::ndlib::render::util {

	MsgConDraw::MsgConDraw(DebugDrawCommon* pDebugDrawCommon, Memory* pMemory) : 
		m_DebugDrawCommon(pDebugDrawCommon), m_Memory(pMemory) {
		s_Instance = this;
	}

	using MsgConDrawBuffersFn = void (*)(const char*);
	uintptr_t MsgConDrawBuffersAddr = NULL;

	uintptr_t Msg_MsgConDrawBuffersHook_ReturnAddr = NULL;
	void Msg_MsgConDrawBuffersHook_SubCC();
	uintptr_t StateScriptPrinterStrncpy_ReturnAddr = NULL;
	void StateScriptPrinterStrncpy_CC();

	void MsgConDraw::MsgConDrawBuffersPatch()
	{
		Patterns::SdkPattern findpattern{};
		auto module = Utility::memory::get_executable();


#if defined(T1X)
		if (m_Memory->IsDebugMemoryAvailable()) {

			/* It's a dirty and broken hack for MsgCon, unfortunately, in T1X specific handler for msgcon is stripped out. 
			Yes, we can rollback this from T2R, but it is taking a long time rn. Thanks, illusion0001, for this method. 
			*/

			MsgConDrawBuffersFn functionPointer = &MsgConDraw::MsgConDrawBuffers;
			std::memcpy(&MsgConDrawBuffersAddr, &functionPointer, sizeof(MsgConDrawBuffersFn));

			findpattern = Patterns::SsManager_StateScriptConsolePrinter;

			auto pStateScriptConsolePrinter = Utility::FindAndPrintPattern(module
				, findpattern.pattern, wstr(Patterns::SsManager_StateScriptConsolePrinter), findpattern.offset);

			StateScriptConsolePrinter = (StateScriptConsolePrinter_ptr)pStateScriptConsolePrinter;
			m_StateScriptPrinterStrncpyHook = Utility::MakeFunctionHook((void*)(pStateScriptConsolePrinter + 0xAD),
				(void*)StateScriptPrinterStrncpy_CC, wstr(StateScriptPrinterStrncpyHook));

			findpattern = Patterns::Msg_MsgConDrawBuffersHook;
			m_Msg_MsgConDrawBuffersHook = Utility::WritePatchPattern_Hook(module, findpattern.pattern, wstr(Patterns::Msg_MsgConDrawBuffersHook),
				findpattern.offset, (void*)Msg_MsgConDrawBuffersHook_SubCC);

			if (!m_Msg_MsgConDrawBuffersHook ||
				!m_StateScriptPrinterStrncpyHook ||
				!StateScriptConsolePrinter) {
				throw SdkComponentEx{ std::format("Failed to create hooks {:s} in {:s}!", TOSTRING(Msg_s_MsgConDrawBuffersHook), TOSTRING(MsgConDraw)),
					SdkComponentEx::ErrorCode::PatchFailed };
			}

			Msg_MsgConDrawBuffersHook_ReturnAddr = m_Msg_MsgConDrawBuffersHook->get_original();
			StateScriptPrinterStrncpy_ReturnAddr = (m_StateScriptPrinterStrncpyHook->get_original() + 0x5);
		}
#endif 

	}

#if defined(T1X)
	void MsgConDraw::MsgConDrawBuffers(const char* msgcon_buffer)
	{
		DebugDrawCommon* DebugDraw{ s_Instance->m_DebugDrawCommon };
		WindowContext ctx{};
		WindowContext::GetWindowContext(&ctx, WindowContext::ContextType::Context4,
			DebugDraw->m_RenderFrameParams.GetRenderFrameParams()->m_DynamicRenderContext);

		auto MsgCon_view = DebugDraw->m_Msg.s_MsgCon->Get();
		StateScriptConsoleInfo Console
		{
			MsgCon_view->m_MsgConLeftPad,
			MsgCon_view->m_MsgConHorizontalSize,
			MsgCon_view->m_MsgConTopPad,
			MsgCon_view->m_MsgConVerticalSize,
			MsgCon_view->m_MsgConScale,
			MsgCon_view->m_MsgConScale,
			MsgCon_view->m_EnableMsgConLineWrap
		};

		StateScriptConsolePrinter((const void*)msgcon_buffer, &ctx, Console);
	}

	int StateScriptPrinterStrncpy(char* dst, char* src)
	{
		// msgcon buffer always start with `'\x1b'`
		memset(dst, 0, 4096);
		strncpy(dst, src, 4096);
		return 4096;
	}

	void __attribute__((naked)) StateScriptPrinterStrncpy_CC()
	{
		__asm
		{
			LEA RCX, [RBP + 0x70];
			MOV RDX, RBX;
			call StateScriptPrinterStrncpy;
			jmp[rip + StateScriptPrinterStrncpy_ReturnAddr];
		}
	}

	void __attribute__((naked)) Msg_MsgConDrawBuffersHook_SubCC()
	{
		__asm {
			mov rcx, r12;
			test rcx, rcx;
			jz exit_;
			cmp word ptr[rcx], 0x5b1b;
			jz call_;
			jmp exit_;
		call_:;
			call MsgConDrawBuffersAddr;
		exit_:;
			jmp[rip + Msg_MsgConDrawBuffersHook_ReturnAddr];
		}
	}
#endif
}