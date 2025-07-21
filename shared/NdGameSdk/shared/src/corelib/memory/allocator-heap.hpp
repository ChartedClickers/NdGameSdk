#pragma once

#include "NdGameSdk/sdk.hpp"
#include "memory-map.hpp"

#include <Windows.h>
#include <Utility/function_ptr.hpp>

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/corelib/memory/HeapAllocator.hpp>
#elif defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/corelib/memory/HeapAllocator.hpp>
#endif

namespace NdGameSdk::corelib::memory
{
	namespace HeapAllocator
	{
		#define HeapArena_Args const char* source_func, uint32_t source_line, const char* source_file
		#define HeapArena_Source __func__, __LINE__, __FILE__

		class HeapArena {
		public:
			//class NdGameSdk_API HeapAllocator : public ISdkRegenny<regenny::shared::corelib::memory::HeapAllocator, regenny::shared::corelib::memory::Allocator> {};
		private:
			friend class Memory;
			MEMBER_FUNCTION_PTR(void, Memory_HeapAllocator_PushAllocator, void* pHeapAllocator, void* pData, size_t heap_size, const char* file, int line, const char* func, bool arg7);
			// MEMBER_FUNCTION_PTR(void* Memory_HeapAllocator_Allocate);
		};

	}
}