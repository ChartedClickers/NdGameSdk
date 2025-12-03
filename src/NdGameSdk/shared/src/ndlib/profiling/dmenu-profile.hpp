#pragma once
#include "NdGameSdk/sdk.hpp"
#include "../debug/nd-dmenu.hpp"

#include <Utility/helper.hpp>
#include <Utility/function_ptr.hpp>

using namespace NdGameSdk::ndlib::debug;

namespace NdGameSdk::ndlib::profiling {
#if defined(T2R)

	void InitProfileMenu(DMENU::Menu* pMenu);

	TYPEDEF_EXTERN_FUNCTION_PTR(void, ProfileCtrl_InitProfileMenu, DMENU::Menu* pMenu);
#endif
}