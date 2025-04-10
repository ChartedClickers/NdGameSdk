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
		TaggedHeap* SetTaggedGpuDevHeap() {
			always_assert(Memory_TaggedHeap_SetTaggedGpuDevHeap == nullptr, "Function pointer was not set!");
			return Memory_TaggedHeap_SetTaggedGpuDevHeap(*s_TaggedGpuDevHeap);
		}
	private:
		TaggedHeap* s_TaggedGpuDevHeap;
		MEMBER_FUNCTION_PTR(TaggedHeap*, Memory_TaggedHeap_SetTaggedGpuDevHeap, TaggedHeap tag);
		friend class Memory;
	};
}