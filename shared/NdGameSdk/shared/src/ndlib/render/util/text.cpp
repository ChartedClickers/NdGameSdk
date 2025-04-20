#include "text.hpp"

#if defined(T2R)

namespace NdGameSdk::ndlib::render::util
{
	void Text::TextPrintV(WindowContext* WindowContext, float font_x, float font_y, float font_scale_x, float font_scale_y, Color color, const char* text)
	{
		always_assert(Text_textPrintV == nullptr, "function pointer is not initialized!");
		Text_textPrintV(WindowContext, font_x, font_y, font_scale_x, font_scale_y, 0x6D37333B, "%s", text);
	}
}

#endif
