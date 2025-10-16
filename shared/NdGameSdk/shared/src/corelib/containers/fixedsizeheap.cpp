#include "fixedsizeheap.hpp"

#include <cstring>
#include <limits>

namespace NdGameSdk::corelib::containers {
	
	uint64_t FixedSizeHeap::Count() const {
		return this->Get()->m_activeCount;
	}

	uint64_t FixedSizeHeap::GetLastIndex() const {
		return this->Get()->m_lastIndex;
	}
	
	uint64_t FixedSizeHeap::Copy(FixedSizeHeap* srcHeap) {
		always_assert(Memory_FixedSizeHeap_Copy == nullptr, "Function pointer was not set!");
		return Memory_FixedSizeHeap_Copy(this, srcHeap);
	}

	uint64_t FixedSizeHeap::Reset() {
		auto* raw = this->Get();
		raw->m_activeCount = 0;
		std::memset(raw->m_pUsage, 0, static_cast<size_t>(raw->m_usageWordCount) << 3);
		const uint64_t last = raw->m_numElements != 0 ? raw->m_numElements - 1 : 0;
		raw->m_lastIndex = last;
		return last;
	}

	INIT_FUNCTION_PTR(FixedSizeHeap::Memory_FixedSizeHeap_Init);
	INIT_FUNCTION_PTR(FixedSizeHeap::Memory_FixedSizeHeap_FreeIndex);
	INIT_FUNCTION_PTR(FixedSizeHeap::Memory_FixedSizeHeap_Copy);
	INIT_FUNCTION_PTR(FixedSizeHeap::Memory_FixedSizeHeap_AddIndex);
}
