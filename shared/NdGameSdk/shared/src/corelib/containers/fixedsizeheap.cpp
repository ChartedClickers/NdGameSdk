#include "fixedsizeheap.hpp"

namespace NdGameSdk::corelib::containers {
	
	uint64_t FixedSizeHeap::Count() const {
		return this->Get()->m_count;
	}

	uint64_t FixedSizeHeap::GetLastIndex() const {
		return this->Get()->m_lastIndex;
	}
	
	uint64_t FixedSizeHeap::Copy(FixedSizeHeap* srcHeap) {
		always_assert(FixedSizeHeap_Copy == nullptr, "Function pointer was not set!");
		return FixedSizeHeap_Copy(this, srcHeap);
	}

	INIT_FUNCTION_PTR(FixedSizeHeap_FreeIndex);
	INIT_FUNCTION_PTR(FixedSizeHeap_Copy);
	INIT_FUNCTION_PTR(FixedSizeHeap_AddIndex);
}
