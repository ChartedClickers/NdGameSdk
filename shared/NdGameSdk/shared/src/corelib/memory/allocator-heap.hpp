#pragma once

#include "NdGameSdk/sdk.hpp"
#include "memory.hpp"
#include "heaparena.hpp"

#include <Utility/function_ptr.hpp>

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/corelib/memory/HeapAllocatorWithOverflow.hpp>
#include <NdGameSdk/regenny/t2r/shared/corelib/memory/HeapAllocator.hpp>
#elif defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/corelib/memory/HeapAllocatorWithOverflow.hpp>
#include <NdGameSdk/regenny/t1x/shared/corelib/memory/HeapAllocator.hpp>
#endif

namespace NdGameSdk::corelib::memory {

	class NdGameSdk_API HeapAllocatorWithOverflow : public ISdkRegenny<regenny::shared::corelib::memory::HeapAllocatorWithOverflow, Memory::Allocator> {
	public:
		template <typename T = void>
		T* GetData() {
			return reinterpret_cast<T*>(this->Get()->m_Data);
		}

		HeapArena* GetHeapArena();
		MemSize GetSize() const;
	};

	class NdGameSdk_API HeapAllocator : public ISdkRegenny<regenny::shared::corelib::memory::HeapAllocator, HeapAllocatorWithOverflow> {
	public:
		void PushAllocator(void* pData, size_t heap_size, HeapArena_Args);
	private:
		TYPEDEF_FUNCTION_PTR(void, Memory_HeapAllocator_PushAllocator, HeapAllocator* pHeapAllocator, void* pData, size_t heap_size, const char* file, int line, const char* func, bool arg7);
		friend class Memory;
	};

	static_assert(sizeof(HeapAllocatorWithOverflow) == 0x100, "HeapAllocatorWithOverflow size mismatch!");
	static_assert(sizeof(HeapAllocator) == 0x120, "HeapAllocator size mismatch!");
}