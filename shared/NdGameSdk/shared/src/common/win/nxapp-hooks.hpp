#pragma once
#if defined(T2R)
#include "NdGameSdk/sdk.hpp"
#include <Utility/helper.hpp>

using namespace Utility::memory;

namespace NdGameSdk::common {
	class CommonGame;
}

namespace NdGameSdk::common::win {

	void NxAppHooks_StdHandle_CC();

	class NxAppHooks {
	private:
		friend class ::NdGameSdk::common::CommonGame;
		FunctionHook::Ptr m_StdHandleHook{};
	};

}
#endif