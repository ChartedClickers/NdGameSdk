#include "msg-con-draw.hpp"
#include "../dev/debugdraw-common.hpp"
#include "../frame-params.hpp"

#include "./NdGameSdk/shared/sharedpatterns.hpp"

namespace NdGameSdk::ndlib::render::util {

	MsgConDraw::MsgConDraw(DebugDrawCommon* pDebugDrawCommon, Memory* pMemory) : 
		m_DebugDrawCommon(pDebugDrawCommon), m_Memory(pMemory) {
		s_Instance = this;
	}

	void MsgConDraw::MsgConDrawBuffersPatch()
	{
		Patterns::SdkPattern findpattern{};
		auto module = Utility::memory::get_executable();

#if defined(T1X)
		if (m_Memory->IsDebugMemoryAvailable()) {

			findpattern = Patterns::Msg_MsgConDrawBuffers;
			auto MsgConDrawBuffersJMP = (void*)Utility::FindAndPrintPattern(module
				, findpattern.pattern, wstr(Patterns::MsgConDrawBuffers), findpattern.offset);

			m_MsgConDraw_MsgConDrawBuffers = Utility::MakeMidHook(MsgConDrawBuffersJMP,
				[](SafetyHookContext& ctx) {

					if (auto* frame = s_Instance->m_DebugDrawCommon->m_RenderFrameParams.GetRenderFrameParams())
					{
						
					}

					
				}, wstr(Patterns::Msg_MsgConDrawBuffers), wstr(MsgConDrawBuffersJMP));


			if (!m_MsgConDraw_MsgConDrawBuffers) {
				throw SdkComponentEx{ std::format("Failed to create hook {:s} in {:s}!", TOSTRING(m_MsgConDraw_MsgConDrawBuffers), TOSTRING(MsgConDraw)),
					SdkComponentEx::ErrorCode::PatchFailed };
			}
		}
#endif 

	}

}