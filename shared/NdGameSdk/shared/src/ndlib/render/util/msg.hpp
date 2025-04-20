#pragma once

#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/components/SdkRegenny.hpp"

#include <Windows.h>
#include <Utility/function_ptr.hpp>

namespace NdGameSdk::ndlib::render::dev {
	class DebugDrawCommon;
}

namespace NdGameSdk::ndlib::render::util
{
	class NdGameSdk_API Msg {
	public:
		void PrintToActiveMsgOutput(const char* pStr);
	private:
		MEMBER_FUNCTION_PTR(void, Msg_PrintToActiveMsgOutput, const char* pStr);
		friend class NdGameSdk::ndlib::render::dev::DebugDrawCommon;
	};
}