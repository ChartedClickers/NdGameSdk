#pragma once

#include "NdGameSdk/sdk.hpp"
#include "memory-map.hpp"

#include <Windows.h>
#include <Utility/function_ptr.hpp>

namespace NdGameSdk::corelib::memory
{
	namespace HeapAllocator
	{
		class HeapArena {
		public:
			template <typename ClassType = void>
			NdGameSdk_API ClassType* Allocate(size_t heap_size, MemoryContextType heap_alignmemt, const char* func, int line, const char* file) {
				always_assert(Memory_HeapArena_Allocate == nullptr, "Function pointer was not set!");
				return (ClassType*)Memory_HeapArena_Allocate(heap_size, heap_alignmemt, func, line, file);
			}
		private:
			friend class Memory;
			MEMBER_FUNCTION_PTR(void*, Memory_HeapArena_Allocate, size_t heap_size, MemoryContextType heap_alignmemt, const char* func, int line, const char* file);
		};
	}
}