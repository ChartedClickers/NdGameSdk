#include "frame-params.hpp"

namespace NdGameSdk::ndlib::render
{	
	FrameParams* RenderFrameParams::GetRenderFrameParams() {
		always_assert(FrameParams_GetFrameParams == nullptr, "Function pointer was not set!");
		return FrameParams_GetFrameParams();
	}
}