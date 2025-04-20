#pragma once

#include "NdGameSdk/sdk.hpp"
#include <Utility/helper.hpp>
#include <NdGameSdk/shared/src/corelib/memory/memory.hpp>

#include "../window-context.hpp"

using namespace NdGameSdk::corelib::memory;

namespace NdGameSdk::ndlib::render::dev {
	class DebugDrawCommon;
}

using namespace NdGameSdk::ndlib::render::dev;

namespace NdGameSdk::ndlib::render::util {

	class MsgConDraw {
	public:
		explicit MsgConDraw(DebugDrawCommon* pDebugDrawCommon, Memory* pMemory);
		void MsgConDrawBuffersPatch();
	private:
		DebugDrawCommon* m_DebugDrawCommon{};
		Memory* m_Memory{};
		MidHook m_MsgConDraw_MsgConDrawBuffers{};
		inline static MsgConDraw* s_Instance = nullptr;

	};
}
