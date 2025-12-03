#include "window-context.hpp"

namespace NdGameSdk::ndlib::render {

	WindowContext* WindowContext::GetWindowContext(WindowContext* storage, ContextType type, void* params)
	{
		always_assert(WindowContext_WindowContext == nullptr, "WindowContext_WindowContext function pointer is not initialized!");
		return WindowContext_WindowContext(storage, type, params);
	}

	INIT_FUNCTION_PTR(WindowContext_WindowContext);
}
