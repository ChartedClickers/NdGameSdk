#include "allocator-tagged-heap.hpp"

namespace NdGameSdk::corelib::memory
{
	TaggedHeap* NdGameSdk::corelib::memory::AllocatorTaggedHeap::SetTaggedGpuDevHeap(TaggedHeap* pTaggedHeap)
	{
		if (Memory_TaggedHeap_SetTaggedGpuDevHeap != nullptr) {
			return Memory_TaggedHeap_SetTaggedGpuDevHeap(*pTaggedHeap);
		}

		TaggedGpuHeapDev = pTaggedHeap;
		return TaggedGpuHeapDev;
	}
}
