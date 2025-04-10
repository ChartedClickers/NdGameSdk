#pragma once

#include "NdGameSdk/sdk.hpp"

#include <Windows.h>
#include <Utility/function_ptr.hpp>

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/corelib/memory/TaggedHeap.hpp>
#elif defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/corelib/memory/TaggedHeap.hpp>
#endif

using TaggedHeap = ::regenny::shared::corelib::memory::TaggedHeap;

namespace NdGameSdk::corelib::memory
{
	class AllocatorTaggedHeap {
	public:
		TaggedHeap* SetTaggedGpuDevHeap(TaggedHeap* pTaggedHeap) {
			if (Memory_TaggedHeap_SetTaggedGpuDevHeap != nullptr) {
				return Memory_TaggedHeap_SetTaggedGpuDevHeap(*pTaggedHeap);
			}

			TaggedGpuHeapDev = pTaggedHeap;
			return TaggedGpuHeapDev;
		}
	private:
		TaggedHeap* TaggedGpuHeapDev;
		MEMBER_FUNCTION_PTR(TaggedHeap*, Memory_TaggedHeap_SetTaggedGpuDevHeap, TaggedHeap tag);
		friend class Memory;
	};
}