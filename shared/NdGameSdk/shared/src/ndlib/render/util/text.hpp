#pragma once

#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/components/SdkRegenny.hpp"

#include <Windows.h>
#include <Utility/color.hpp>
#include <glm/vec2.hpp>
#include <Utility/function_ptr.hpp>

#include "../window-context.hpp"

namespace NdGameSdk::ndlib::render::dev {
	class DebugDrawCommon;
}

using namespace glm;

namespace NdGameSdk::ndlib::render::util
{
	class NdGameSdk_API Text {
	public:
		void TextPrintV(WindowContext* WindowContext, float font_x, float font_y, float font_scale_x, float font_scale_y, const char* fmt, ...);
		void GetTextWidthHeight(vec2* text_pos, uint32_t mask, const char* text, float font_size, float max_size);
	private:
		MEMBER_FUNCTION_PTR(void, Text_textPrintV, WindowContext* WindowContext, float font_x, float font_y, float font_scale_x, float font_scale_y, uint32_t color, const char* fmt, ...);
		MEMBER_FUNCTION_PTR(void, Text2_GetTextWidthHeight, vec2* text_pos, uint32_t mask, const char* text, float font_size, float max_size);

		friend class NdGameSdk::ndlib::render::dev::DebugDrawCommon;
	};
}