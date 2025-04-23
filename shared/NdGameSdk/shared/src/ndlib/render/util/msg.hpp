#pragma once

#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/components/SdkRegenny.hpp"

#include <Windows.h>
#include <Utility/function_ptr.hpp>

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/corelib/util/MsgCon.hpp>
#elif defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/corelib/util/MsgCon.hpp>
#endif

namespace NdGameSdk::ndlib::render::dev {
	class DebugDrawCommon;
}

namespace NdGameSdk::ndlib::render::util
{
	class MsgCon : public ISdkRegenny<::regenny::shared::corelib::util::MsgCon> {};

	class NdGameSdk_API Msg {
	public:
		void PrintToActiveMsgOutput(const char* pStr);
		MsgCon* s_MsgCon;
	private:
		MEMBER_FUNCTION_PTR(void, Msg_PrintToActiveMsgOutput, const char* pStr);
		friend class NdGameSdk::ndlib::render::dev::DebugDrawCommon;
	};

	static_assert(sizeof(MsgCon) == 0x118, "Size of MsgCon is not correct.");
}