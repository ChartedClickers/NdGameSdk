#pragma once

#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/components/SdkRegenny.hpp"

#include <Windows.h>
#include <Utility/color.hpp>
#include <Utility/function_ptr.hpp>

#include "../window-context.hpp"

#if defined(T2R)

namespace NdGameSdk::ndlib::render::dev {
	class DebugDrawCommon;
}

namespace NdGameSdk::ndlib::render::util
{
	class NdGameSdk_API Text {
	public:
		void TextPrintV(WindowContext* WindowContext, float font_x, float font_y, float font_scale_x, float font_scale_y, Color color, const char* text);
	private:
		MEMBER_FUNCTION_PTR(void, Text_textPrintV, WindowContext* WindowContext, float font_x, float font_y, float font_scale_x, float font_scale_y, uint32_t color, const char* fmt, ...);
		friend class NdGameSdk::ndlib::render::dev::DebugDrawCommon;
	};
}
#endif