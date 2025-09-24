#pragma once

#include "NdGameSdk/sdk.hpp"
#include "memory.hpp"
#include "allocator-heap.hpp"
#include "memory-map.hpp"
#include "heaparena.hpp"

#include <Utility/function_ptr.hpp>

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/corelib/memory/PoolAllocator.hpp>
#elif defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/corelib/memory/PoolAllocator.hpp>
#endif

namespace NdGameSdk::corelib::memory {

	class NdGameSdk_API PoolAllocator : public ISdkRegenny<regenny::shared::corelib::memory::PoolAllocator, Memory::Allocator> {
	public:
		class PoolStack : public ISdkRegenny<regenny::shared::corelib::memory::PoolAllocator::PoolStack> {};

		PoolStack* GetPoolStack();
		MemSize GetSize() const;

		template <typename T = void>
		T* GetMem() {
			return reinterpret_cast<T*>(this->Get()->m_mem);
		}
	};

	static_assert(sizeof(PoolAllocator) == 0xe0, "PoolAllocator size mismatch");
	
}