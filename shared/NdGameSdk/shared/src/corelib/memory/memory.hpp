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

namespace NdGameSdk::corelib::memory {

	#define Memory_Source __FILE__, __LINE__, __func__

	class Memory : public ISdkComponent {
	public:
		Memory();
		SdkEvent<corelib::memory::Memory*> e_MemoryMapMapped{true};

		using Context = MemoryContextType;
		using MapId = MemoryMapId;

		/* Extern classes */
		class NdGameSdk_API Allocator : public ISdkRegenny<regenny::shared::corelib::memory::Allocator> {
		public:
			using VTable = regenny::shared::corelib::memory::Allocator::VTable;

			template <typename ClassType = void>
			ClassType* PostAllocate(size_t heap_size, uint64_t heap_alignmemt, const char* func, int line, const char* file) {
				auto* pAllocator = this->Get();
				return (ClassType*)reinterpret_cast<VTable*>(&pAllocator->vftable)->PostAllocate(
					heap_size,
					heap_alignmemt,
					const_cast<char*>(func),
					static_cast<uint32_t>(line),
					const_cast<char*>(file)
				);
			}

			const char* GetName() const;
			StringId64 GetHash() const;
			bool IsInitialized() const;
		};

		NdGameSdk_API bool IsMemoryMapMapped();
		NdGameSdk_API bool IsDebugMemoryAvailable();

		NdGameSdk_API MemoryMapEntry* GetMemoryMapEntry(MemoryMapId MapId);
		NdGameSdk_API MemSize GetMemSize(MemoryMapId MapId);

		NdGameSdk_API void ModifyMemoryMap(MemoryMapEntry* MapEntry, MemSize newSizeForId);
		NdGameSdk_API void ModifyMemoryMap(MemoryMapId MapId, MemSize newSizeForId);
		NdGameSdk_API void IncreaseMemoryMap(MemoryMapId MapId, MemSize AddSizeForId);

        template <typename TAllocator = Allocator*>
        requires std::derived_from<std::remove_pointer_t<TAllocator>, Allocator>
		NdGameSdk_API TAllocator* GetAllocator(MemoryContextType context_type) {
			always_assert(Memory_GetAllocator == nullptr, "Function pointer was not set!");
			return (TAllocator*)Memory_GetAllocator(&context_type);
		}

		// Always use PushAllocator and PopAllocator for allocation memory.
		template <typename ClassType = void>
		NdGameSdk_API ClassType* Allocate(size_t heap_size, uint64_t heap_alignmemt, const char* func, int line, const char* file) {
			always_assert(Memory_Allocate == nullptr, "Function pointer was not set!");
			spdlog::debug("Allocating memory for ClassType: {}, Size: {}, Alignment: {}, File: {}, Line: {}, Function: {}",
				typeid(ClassType).name(), heap_size, heap_alignmemt, file, line, func);
			return (ClassType*)Memory_Allocate(heap_size, heap_alignmemt, file, line, func);
		}

		NdGameSdk_API void Free(void* pData, const char* func, int line, const char* file) {
			always_assert(Memory_Free == nullptr, "Function pointer was not set!");
			spdlog::debug("Freeing memory at address: {}, File: {}, Line: {}, Function: {}",
				reinterpret_cast<uintptr_t>(pData), file, line, func);
			Memory_Free(pData, file, line, func);
		}

		template <typename ClassType = void>
		NdGameSdk_API ClassType* AllocateAtContext(size_t heap_size, uint64_t heap_alignmemt, MemoryContextType memory_context) {
		#if defined(T2R) || defined(T1X)
			always_assert(Memory_AllocateAtContext == nullptr, "Function pointer was not set!");
			spdlog::debug("Allocating memory at context: {}, ClassType: {}, Size: {}, Alignment: {}",
				static_cast<int>(memory_context), typeid(ClassType).name(), heap_size, heap_alignmemt);
			return (ClassType*)Memory_AllocateAtContext(heap_size, &memory_context, heap_alignmemt);
		#else 
			Allocator* pAllocator = GetAllocator(memory_context);
			always_assert(pAllocator == nullptr, "Invalid Memory Context Type!");
			spdlog::debug("Allocating memory at context: {}, ClassType: {}, Size: {}, Alignment: {}",
				static_cast<int>(memory_context), typeid(ClassType).name(), heap_size, heap_alignmemt);
			return pAllocator->PostAllocate<ClassType>(heap_size, heap_alignmemt, Memory_Source);
		#endif
		}

		NdGameSdk_API void PushAllocator(MemoryContextType context_type, const char* file, int line_num, const char* func);
		NdGameSdk_API void PopAllocator();

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

#if defined(T1X)
		Patch::Ptr m_BootstrapAppHeapsPatch{};
#endif

		MEMBER_FUNCTION_PTR(void*, Memory_Allocate, size_t heap_size, uint64_t heap_alignmemt, const char* file, int line, const char* func);
		MEMBER_FUNCTION_PTR(void*, Memory_AllocateAtContext, size_t heap_size, MemoryContextType* memory_context, size_t heap_alignmemt);
		MEMBER_FUNCTION_PTR(void, Memory_Free, void* pData, const char* file, int line, const char* func);

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