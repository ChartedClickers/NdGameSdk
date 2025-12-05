#pragma once
#include "NdGameSdk/sdk.hpp"
#include <helper.hpp>

using namespace Utility::memory;

namespace NdGameSdk::corelib::memory {

	namespace Area {

		class MemoryArea {
		private:
			friend class Memory;
	#if defined(T2R)
			Patch::Ptr m_AllocateGpuVirtualMemoryPatch{};
	#endif
			Patch::Ptr m_clarg_nodebugmemPatch{};
		};
	}

}
