#include "allocator-heap.hpp"

namespace NdGameSdk::corelib::memory {

	HeapArena* HeapAllocatorWithOverflow::GetHeapArena() {
		return reinterpret_cast<HeapArena*>(&this->Get()->m_HeapArena);
	}

	MemSize HeapAllocatorWithOverflow::GetSize() const {
		return this->Get()->m_size;
	}

	void HeapAllocator::PushAllocator(void* pData, size_t heap_size, HeapArena_Args) {
		always_assert(Memory_HeapAllocator_PushAllocator == nullptr, "Function pointer was not set!");
		Memory_HeapAllocator_PushAllocator(this, pData, heap_size, source_file, source_line, source_func, false);
	}

	INIT_FUNCTION_PTR(HeapAllocator::Memory_HeapAllocator_PushAllocator);
}