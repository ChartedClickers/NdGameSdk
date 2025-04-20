#pragma once

#include "NdGameSdk/sdk.hpp"

#include <Windows.h>
#include <Utility/function_ptr.hpp>

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/ndlib/FrameParams.hpp>
#elif defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/ndlib/FrameParams.hpp>
#endif

namespace NdGameSdk::ndlib::render::dev {
	class DebugDrawCommon;
}

using FrameParams = ::regenny::shared::ndlib::FrameParams;

namespace NdGameSdk::ndlib::render
{
	class NdGameSdk_API RenderFrameParams {
	public:
		 FrameParams* GetRenderFrameParams();
	private:
		MEMBER_FUNCTION_PTR(FrameParams*, FrameParams_GetFrameParams);
		friend class NdGameSdk::ndlib::render::dev::DebugDrawCommon;
	};
}

