#pragma once



#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/components/SdkRegenny.hpp"

#include <Utility/helper.hpp>
#include <Utility/function_ptr.hpp>

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/ndlib/render/WindowContext.hpp>
#elif defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/ndlib/render/WindowContext.hpp>
#endif

#include "frame-params.hpp"

namespace NdGameSdk::ndlib::render::dev {
	class DebugDrawCommon;
}

namespace NdGameSdk::ndlib::render {

	class NdGameSdk_API WindowContext : public ISdkRegenny<regenny::shared::ndlib::render::WindowContext> {
	public:
		using ContextType = ::regenny::shared::ndlib::render::WindowContextType;
		static WindowContext* GetWindowContext(WindowContext* storage, ContextType type, void* params);
	private:
		friend class NdGameSdk::ndlib::render::dev::DebugDrawCommon;
	};

	static_assert(sizeof(WindowContext) == 0x30, "Size of WindowContext is not correct.");
	TYPEDEF_EXTERN_FUNCTION_PTR(WindowContext*, WindowContext_WindowContext, WindowContext* Context, WindowContext::ContextType ContextType, void* FrameParams);

}

