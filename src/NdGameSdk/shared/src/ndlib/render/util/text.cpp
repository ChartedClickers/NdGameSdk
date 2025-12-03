#include "text.hpp"

#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <glm/vec2.hpp>

namespace NdGameSdk::ndlib::render::util
{
	void Text::TextPrintV(WindowContext* WindowContext, float font_x, float font_y, float font_scale_x, float font_scale_y, const char* fmt, ...)
	{
		always_assert(Text_textPrintV == nullptr, "function pointer is not initialized!");

		va_list args;
		va_start(args, fmt);
		int required = std::vsnprintf(nullptr, 0, fmt, args);
		va_end(args);
		if (required < 0) required = 0;

		std::vector<char> temp(required + 1);

		va_start(args, fmt);
		std::vsnprintf(temp.data(), temp.size(), fmt, args);
		va_end(args);

		constexpr float NEWLINE_SPACING = 0.6f;
		char* text = temp.data();
		float basefont_x = font_x;

		while (text && *text)
		{
			uint32_t code = *(uint32_t*)(text + 3);
			uint32_t color = _rgb(255, 255, 255);

			switch (code)
			{
			case 0x6D31333B: color = _rgb(255, 0, 0);   break; // red
			case 0x6D32333B: color = _rgb(0, 255, 0);   break; // green
			case 0x6D33333B: color = _rgb(255, 255, 0); break; // yellow
			case 0x6D34333B: color = _rgb(0, 0, 255);   break; // blue
			case 0x6D35333B: color = _rgb(210, 0, 210); break; // magenta
			case 0x6D36333B: color = _rgb(0, 255, 255); break; // cyan
			case 0x6D37333B: color = _rgb(255, 255, 255); break; // white
			}


			// —— existing ANSI branch ——
			if (text[0] == '\x1b' && text[1] == '[' && text[2] == '0' && text[3] == ';')
			{
				
				const char* next_esc = std::strchr(text + 1, '\x1b');
				size_t   text_size = next_esc
					? size_t(next_esc - (text + 7))
					: strlen(text + 7);
				char text_[4096] = {};
				size_t cpy = (std::min)(text_size, sizeof(text_) - 1u);
				strncpy_s(text_, text + 7, cpy);

				// measure & draw
				vec2 charSize{};
				GetTextWidthHeight(&charSize,
					0x80000000,
					text_,
					font_scale_x,
					font_scale_y);
				Text_textPrintV(WindowContext,
					font_x, font_y,
					font_scale_x, font_scale_y,
					color,
					"%s",
					text_);

				// newline handling
				if (strchr(text_, '\n'))
				{
					int lines = 1;
					for (const char* p = text_; (p = strchr(p + 1, '\n'));)
						++lines;
					font_y += charSize.y * NEWLINE_SPACING * lines;
					font_x = basefont_x;
				}
				else
				{
					font_x += charSize.x;
				}

				text += 7 + text_size;
				continue;
			}

			// —— new plain‑text branch ——
			{
				const char* next_esc = std::strchr(text, '\x1b');
				size_t run_len = next_esc
					? size_t(next_esc - text)
					: strlen(text);

				char buf[4096] = {};
				size_t cpy = (std::min)(run_len, sizeof(buf) - 1u);
				strncpy_s(buf, text, cpy);

				// measure…
				vec2 size{};
				GetTextWidthHeight(&size,
					0x80000000,
					buf,
					font_scale_x,
					font_scale_y);

				Text_textPrintV(WindowContext,
					font_x, font_y,
					font_scale_x, font_scale_y,
					color,
					buf);

				if (strchr(buf, '\n'))
				{
					int lines = 1;
					for (const char* p = buf; (p = strchr(p + 1, '\n'));)
						++lines;
					font_y += size.y * NEWLINE_SPACING * lines;
					font_x = basefont_x;
				}
				else
				{
					font_x += size.x;
				}

				text += run_len;
			}
		}
	}

	void Text::GetTextWidthHeight(vec2* text_pos, uint32_t mask, const char* text, float font_size, float max_size)
	{
		always_assert(Text2_GetTextWidthHeight == nullptr, "function pointer is not initialized!");
		Text2_GetTextWidthHeight(text_pos, mask, text, font_size, max_size);
	}
}
