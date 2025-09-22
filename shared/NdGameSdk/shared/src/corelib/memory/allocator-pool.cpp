#include "allocator-pool.hpp"

namespace NdGameSdk::corelib::memory {

	Memory::MapId PoolAllocator::Debug::GetMapId() {
		return this->Get()->m_mapId;
	}

	Memory::Context PoolAllocator::Debug::GetContext() {
		return this->Get()->m_context;
	}

	uint32_t PoolAllocator::Debug::GetBytesPerBlock() {
		return this->Get()->m_bytesPerBlock;
	}

	MemSize PoolAllocator::GetSize() const {
		return this->Get()->m_size;
	}

	std::string_view PoolAllocator::GetName() {
		return this->Get()->m_displayName;
	}

	PoolAllocator::PoolStack* PoolAllocator::GetPoolStack() {
		return reinterpret_cast<PoolAllocator::PoolStack*>(&this->Get()->m_stack);
	}

	PoolAllocator::Debug* PoolAllocator::GetDebugInfo() {
		return reinterpret_cast<PoolAllocator::Debug*>(&this->Get()->m_debug);
	}

	HeapAllocatorWithOverflow* PoolAllocator::GetHeapAllocator() {
		return reinterpret_cast<HeapAllocatorWithOverflow*>(&this->Get()->m_HeapAllocator);
	}

	bool PoolAllocator::IsPoolAllocDisabled() {
		return this->Get()->m_disablePoolAlloc;
	}
}