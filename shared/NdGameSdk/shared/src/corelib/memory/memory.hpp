#pragma once

#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/config/MemoryCfg.hpp"
#include "NdGameSdk/components/SdkComponent.hpp"

#include "memory-map.hpp"
#include "heaparena.hpp"
#include "allocator-tagged-heap.hpp"
#include "memory-area-win.hpp"

#include <Utility/helper.hpp>

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/corelib/memory/Allocator.hpp>
#elif defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/corelib/memory/Allocator.hpp>
#endif

namespace NdGameSdk::corelib::memory 
{
	#define Memory_Source __FILE__, __LINE__, __func__

	class Memory : public ISdkComponent {
	public:
		Memory(MemoryCfg& cfg);
		SdkEvent<corelib::memory::Memory*> e_MemoryMapMapped{true};

		class NdGameSdk_API Allocator : public ISdkRegenny<regenny::shared::corelib::memory::Allocator> 
		{
			void PrintDebugAllocatorInfo();
		};

		NdGameSdk_API bool IsMemoryMapMapped();
		NdGameSdk_API bool IsDebugMemoryAvailable();

		NdGameSdk_API MemoryMapEntry* GetMemoryMapEntry(MemoryMapId MapId);
		NdGameSdk_API MemSize GetMemSize(MemoryMapId MapId);
		NdGameSdk_API Allocator* GetAllocator(MemoryContextType context_type);

		NdGameSdk_API void ModifyMemoryMap(MemoryMapEntry* MapEntry, MemSize newSizeForId);
		NdGameSdk_API void ModifyMemoryMap(MemoryMapId MapId, MemSize newSizeForId);
		NdGameSdk_API void IncreaseMemoryMap(MemoryMapId MapId, MemSize AddSizeForId);

		NdGameSdk_API void PushAllocator(MemoryContextType context_type, const char* file, int line_num, const char* func);
		NdGameSdk_API void PopAllocator();

		HeapAllocator::HeapArena m_HeapArena{};
		Area::MemoryArea m_MemArea{};
#if defined(T2R)
		AllocatorTaggedHeap m_AllocatorTaggedHeap{};
#endif
		std::map<MemoryMapId, MemoryMapEntry*>& GetStaticMemoryMapEntries();

	private:
		void Initialize() override;
		bool m_MemoryMapMapped{};
		MemoryCfg m_cfg{};

		MemoryMap m_MemoryMap{};
		MemoryMapEntry* g_MemoryMap{};

		MidHook m_SetMemoryMapHook{};
		FunctionHook::Ptr m_AllocateHook{};
		std::map<MemoryMapId,Patch::Ptr> m_resizedmaps{};

		Patch::Ptr m_ValidateContextPatch{};
		Patch::Ptr m_IsDebugMemoryAvailablePatch{};

		MEMBER_FUNCTION_PTR(void*, Memory_Allocate, size_t heap_size, MemoryContextType* memory_context, size_t align);
		MEMBER_FUNCTION_PTR(uintptr_t*, Memory_ModifyMemoryMap, MemoryMapId MapId, uint64_t newSizeForId);
		MEMBER_FUNCTION_PTR(uint64_t, Memory_GetSize, MemoryMapId MapId);
		MEMBER_FUNCTION_PTR(uint64_t, Memory_PushAllocator, MemoryContextType* memory_context, const char* file, int line_num, const char* func);
		MEMBER_FUNCTION_PTR(uint64_t, Memory_PopAllocator);
		MEMBER_FUNCTION_PTR(Allocator*, Memory_GetAllocator, MemoryContextType* memory_context);

#if defined(T1X)
		MEMBER_FUNCTION_PTR(MemoryMapEntry*, Memory_FindMemoryMap, MemoryMapId);
#endif

	};
}