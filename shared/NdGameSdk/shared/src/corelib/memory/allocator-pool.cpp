#include "allocator-pool.hpp"

namespace NdGameSdk::corelib::memory {

	PoolAllocator::PoolStack* PoolAllocator::GetPoolStack() {
		return reinterpret_cast<PoolAllocator::PoolStack*>(&this->Get()->m_stack);
	}

	MemSize PoolAllocator::GetSize() const {
		return this->Get()->m_size;
	}
}