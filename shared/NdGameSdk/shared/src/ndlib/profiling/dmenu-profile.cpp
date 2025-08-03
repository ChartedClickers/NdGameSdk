#include "dmenu-profile.hpp"

namespace NdGameSdk::ndlib::profiling {
#if defined(T2R)

	void InitProfileMenu(DMENU::Menu* pMenu) {
		always_assert(ProfileCtrl_InitProfileMenu == nullptr, "Function pointer was not set!");
		ProfileCtrl_InitProfileMenu(pMenu);
	}

	INIT_FUNCTION_PTR(ProfileCtrl_InitProfileMenu);

#endif
}