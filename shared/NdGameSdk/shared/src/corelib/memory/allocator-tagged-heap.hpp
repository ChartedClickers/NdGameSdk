#pragma once

#include "NdGameSdk/sdk.hpp"

#include <Windows.h>
#include <Utility/function_ptr.hpp>

#include "../containers/tagged-heap.hpp"

using namespace NdGameSdk::corelib::containers;

namespace NdGameSdk::corelib::memory
{
	class AllocatorTaggedHeap {
	public:
		TaggedHeap* SetTaggedGpuDevHeap(TaggedHeap* pTaggedHeap);
	private:
		TaggedHeap* TaggedGpuHeapDev;
		MEMBER_FUNCTION_PTR(TaggedHeap*, Memory_TaggedHeap_SetTaggedGpuDevHeap, TaggedHeap tag);
		friend class Memory;
	};
}