#pragma once

#include "NdGameSdk/sdk.hpp"
#include <Utility/helper.hpp>
#include <NdGameSdk/shared/src/corelib/memory/memory.hpp>

using namespace NdGameSdk::corelib::memory;

namespace NdGameSdk::common {

	class CommonGame;

	class IAllocator {
	private:
		void Init(CommonGame& pcommongame, Memory& pmemory);
		friend class NdGameSdk::common::CommonGame;
		MidHook m_IAllocator_InitTaggedHeapsHook{};
	};


}