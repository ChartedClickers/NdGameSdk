#pragma once

#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/components/SdkSubComponent.hpp"

#include <Utility/helper.hpp>

#include "../window-context.hpp"

namespace NdGameSdk::ndlib::render::dev {
	class DebugDrawCommon;
}

using namespace NdGameSdk::ndlib::render::dev;

namespace NdGameSdk::ndlib::render::util {

	// TODO: Refactor to ndlib\util\msg-con-draw.hpp

	class MsgConDraw : public ISdkSubComponent {
	public:
		explicit MsgConDraw();
		void Init() override;
	private:
		static void MsgConDrawBuffers(const char* msgcon_buffer);
#if defined(T1X)
		Utility::memory::FunctionHook::Ptr m_StateScriptPrinterStrncpyHook{};
		Utility::memory::FunctionHook::Ptr m_Msg_MsgConDrawBuffersHook{};
#endif
	};
}
