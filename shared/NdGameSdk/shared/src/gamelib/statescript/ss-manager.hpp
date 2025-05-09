#pragma once
#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/components/SdkRegenny.hpp"

#include <Utility/helper.hpp>
#include <Utility/function_ptr.hpp>

#if defined(T1X)
#include <NdGameSdk/shared/src/ndlib/render/window-context.hpp>
#include <NdGameSdk/regenny/t1x/shared/gamelib/state_script/StateScriptConsoleInfo.hpp>

using namespace NdGameSdk::ndlib::render;

namespace NdGameSdk::gamelib::statescript {

	class StateScriptConsoleInfo : public ISdkRegenny<regenny::shared::gamelib::state_script::StateScriptConsoleInfo> {
	public:
		StateScriptConsoleInfo() = default;

		StateScriptConsoleInfo(
			uint32_t pos_x,
			uint32_t size_x,
			uint32_t pos_y,
			uint32_t size_y,
			float font_size_x,
			float font_size_y,
			bool line_wrap
		) {
			auto self = this->Get();
			self->pos_x = pos_x;
			self->size_x = size_x;
			self->pos_y = pos_y;
			self->size_y = size_y;
			self->font_size_x = font_size_x;
			self->font_size_y = font_size_y;
			self->line_warp = line_wrap;
		}
	};

	// Dirty MsgCon hack for \shared\src\ndlib\render\util\msg-con-draw.cpp
	TYPEDEF_EXTERN_FUNCTION_PTR(void, StateScriptConsolePrinter,
		const void* ssConsolePtr,
		void* WindowContext,
		const struct StateScriptConsoleInfo ConsoleInfo);
};
#endif