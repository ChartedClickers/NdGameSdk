#if defined(T1X)
#include "memory.hpp"
#include "./NdGameSdk/shared/sharedpatterns.hpp"

#include <codecvt>

namespace NdGameSdk::corelib::memory {

	Memory::Memory(MemoryCfg& cfg) : m_cfg { std::move(cfg) }, ISdkComponent(TOSTRING(Memory)) {}

	uintptr_t Memory_Allocate_ReturnAddr = NULL;
	void Memory_Allocate_CC();

	bool Memory::IsMemoryMapMapped() {
		return m_MemoryMapMapped;
	}

	bool Memory::IsDebugMemoryAvailable() {

		if (m_IsDebugMemoryAvailablePatch) {
			return m_IsDebugMemoryAvailablePatch->IsEnable();
		}

		return m_cfg.DebugMemory;
	}

	MemoryMapEntry* Memory::GetMemoryMapEntry(MemoryMapId MapId) {

		if (m_MemoryMapMapped) {
	#if defined(T1X)
			always_assert(Memory_FindMemoryMap == nullptr, "Function pointer was not set!");
			return Memory_FindMemoryMap(MapId);
	#else
			always_assert(g_MemoryMap == nullptr, "g_MemoryMap was not set!");
			if (*(uintptr_t*)g_MemoryMap != NULL)
			{
				auto pMemoryMap = reinterpret_cast<MemoryMapEntry*>(g_MemoryMap);
				while (*(uintptr_t*)pMemoryMap != NULL) {
					if (pMemoryMap->Id() == MapId)
						return pMemoryMap;

					pMemoryMap++;
				}
			}
	#endif
		}

		return m_MemoryMap.s_MemoryMap.at(MapId);
	}

	MemSize Memory::GetMemSize(MemoryMapId MapId) {
		if (m_MemoryMapMapped) {
			always_assert(Memory_GetSize == nullptr, "Function pointer was not set!");
			uint64_t size = Memory_GetSize(MapId);
			return MemSize(size);
		} 

		auto MapEntry = GetMemoryMapEntry(MapId);
		always_assert(MapEntry == nullptr, "Invalid Memory Map Id!");
		return MapEntry->Size();
	}

	Memory::Allocator* Memory::GetAllocator(MemoryContextType context_type) {
		always_assert(Memory_GetAllocator == nullptr, "Function pointer was not set!");
		return Memory_GetAllocator(&context_type);
	}

	void Memory::ModifyMemoryMap(MemoryMapEntry* MapEntry, MemSize newSizeForId) {
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> wstring_converter{};
		auto model_view = MapEntry->Get();

		constexpr uint64_t size_mb = (1024ULL * 1024ULL);
		uint64_t CURRENT_ALLOCATION_SIZE = model_view->m_size;
		uint64_t MODIFIED_ALLOCATION_SIZE = newSizeForId.GetSize<uint64_t>(SizeUnit::Bytes);

		if (m_MemoryMapMapped) {
			always_assert(Memory_ModifyMemoryMap == nullptr, "Function pointer was not set!");
			Memory_ModifyMemoryMap(MapEntry->Id(), MODIFIED_ALLOCATION_SIZE);
		}
		else {
			m_resizedmaps.erase(MapEntry->Id());
			auto patch = Utility::WritePatchAddress_Value(Utility::memory::get_executable(),
				sizeof(MODIFIED_ALLOCATION_SIZE), (uint64_t)&model_view->m_size, &MODIFIED_ALLOCATION_SIZE,
				wstring_converter.from_bytes(model_view->m_name).c_str());
			m_resizedmaps.emplace(MapEntry->Id(),std::move(patch));
		}

		spdlog::warn("Modified allocation size {}: {:8.3f} MiB -> {:8.3f} MiB", model_view->m_name,
			static_cast<double>(CURRENT_ALLOCATION_SIZE) / size_mb, static_cast<double>(MODIFIED_ALLOCATION_SIZE) / size_mb);
	}

	void Memory::ModifyMemoryMap(MemoryMapId MapId, MemSize newSizeForId) {
		auto MapEntry = GetMemoryMapEntry(MapId);
		always_assert(MapEntry == nullptr, "Invalid Memory Map Id!");
		ModifyMemoryMap(MapEntry, newSizeForId);
	}

	void Memory::IncreaseMemoryMap(MemoryMapId MapId, MemSize AddSizeForId) {
		auto CurrentMemSize = GetMemSize(MapId);
		if (CurrentMemSize < AddSizeForId) {
			ModifyMemoryMap(MapId, CurrentMemSize + (AddSizeForId - CurrentMemSize));
		}
	}

	void Memory::PushAllocator(MemoryContextType context_type, const char* file, int line_num, const char* func) {
		always_assert(Memory_PushAllocator == nullptr, "Function pointer was not set!");
		Memory_PushAllocator(&context_type, file, line_num, func);
	}

	void Memory::PopAllocator() {
		always_assert(Memory_PopAllocator == nullptr, "Function pointer was not set!");
		Memory_PopAllocator();
	}

	std::map<MemoryMapId, MemoryMapEntry*>& Memory::GetStaticMemoryMapEntries() {
		return m_MemoryMap.s_MemoryMap;
	}

	void Memory::Initialize()
	{
		static std::once_flag Initialized;

		std::call_once(Initialized, [this] {

			spdlog::info("Initializing {} patterns...", GetName());

			Patterns::SdkPattern findpattern{};
			auto module = Utility::memory::get_executable();

			findpattern = Patterns::Memory_s_MemoryMap;
			auto s_MemoryMap = (MemoryMapEntry*)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::Memory_s_MemoryMap), findpattern.offset);

			findpattern = Patterns::Memory_g_MemoryMap;
			g_MemoryMap = (MemoryMapEntry*)Utility::ReadLEA32(module,
				findpattern.pattern, wstr(Patterns::Memory_g_MemoryMap), findpattern.offset, 3, 8);

			if (!s_MemoryMap ||
				!g_MemoryMap) {
				throw SdkComponentEx
				{ std::format("Failed to find addresses!"),
					SdkComponentEx::ErrorCode::PatternFailed, true };
			}

			findpattern = Patterns::Memory_AllocateMemoryMap;
			auto SetMemoryMapJMP = (void*)Utility::FindAndPrintPattern(module
				, findpattern.pattern, wstr(Patterns::Memory_AllocateMemoryMap), findpattern.offset);

			findpattern = Patterns::Memory_ModifyMemoryMap;
			Memory_ModifyMemoryMap = (Memory_ModifyMemoryMap_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::Memory_ModifyMemoryMap), findpattern.offset);

			findpattern = Patterns::Memory_FindMemoryMap;
			Memory_FindMemoryMap = (Memory_FindMemoryMap_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::Memory_FindMemoryMap), findpattern.offset);

			findpattern = Patterns::Memory_GetSize;
			Memory_GetSize = (Memory_GetSize_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::Memory_GetSize), findpattern.offset);

			findpattern = Patterns::Memory_PushAllocator;
			Memory_PushAllocator = (Memory_PushAllocator_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::Memory_PushAllocator), findpattern.offset);

			findpattern = Patterns::Memory_PopAllocator;
			Memory_PopAllocator = (Memory_PopAllocator_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::Memory_PopAllocator), findpattern.offset);

			findpattern = Patterns::Memory_GetAllocator;
			Memory_GetAllocator = (Memory_GetAllocator_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::Memory_GetAllocator), findpattern.offset);

			findpattern = Patterns::Memory_HeapAllocator_Allocate;
			m_HeapArena.Memory_HeapArena_Allocate = (HeapAllocator::HeapArena::Memory_HeapArena_Allocate_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::Memory_HeapAllocator_Allocate), findpattern.offset);

			if (!SetMemoryMapJMP ||
				!Memory_ModifyMemoryMap ||
				!Memory_FindMemoryMap ||
				!Memory_GetSize ||
				!Memory_PushAllocator ||
				!Memory_PopAllocator ||
				!Memory_GetAllocator ||
				!m_HeapArena.Memory_HeapArena_Allocate
				) { throw SdkComponentEx { std::format("Failed to find {}:: game functions!", GetName()), SdkComponentEx::ErrorCode::PatternFailed, true }; }

			constexpr uint64_t size_mb = (1024ULL * 1024ULL);
			uint64_t TotalMapSize = 0;

			while (*(uintptr_t*)s_MemoryMap != NULL) {
				auto& pMemoryMap = *s_MemoryMap;
				m_MemoryMap.s_MemoryMap.insert({ pMemoryMap->m_id, s_MemoryMap});
				pMemoryMap.PrintDebugMapEntryInfo();
				TotalMapSize += pMemoryMap->m_size;
				s_MemoryMap++;
			}

			spdlog::info("Loaded {} Memory Map Entries with total size {:8.3f} MiB", m_MemoryMap.s_MemoryMap.size(), static_cast<double>(TotalMapSize) / size_mb);

			m_SetMemoryMapHook = Utility::MakeMidHook(SetMemoryMapJMP,
				[](SafetyHookContext& ctx)
				{
					auto memory = GetSharedComponents()->GetComponent<Memory>();
					memory->m_MemoryMapMapped = true;
					memory->InvokeSdkEvent(memory->e_MemoryMapMapped, memory.get());

				}, wstr(Patterns::Memory_AllocateMemoryMap), wstr(SetMemoryMapJMP));


			std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> wstring_converter{};

			if (!m_cfg.ModifiedMapEntries.empty()) {
				spdlog::warn("custom resize Memory Map is configured in Config");
				spdlog::info("Resizing static MemoryMap...");

				for (auto& [MapId, ModifiedMapSize] : m_cfg.ModifiedMapEntries) {
					MemoryMapEntry* MapEntry = GetMemoryMapEntry(MapId);

					if (!MapEntry) {
						throw SdkComponentEx
						{ std::format("MapEntry with {} ID hasn't been found in the static Memory Map!", static_cast<uint32_t>(MapId)),
							SdkComponentEx::ErrorCode::PatchFailed, false };
					}

					uint64_t MODIFIED_ALLOCATION_SIZE = ModifiedMapSize.GetSize<uint64_t>(SizeUnit::Bytes);
					ModifyMemoryMap(MapEntry, MODIFIED_ALLOCATION_SIZE);
					TotalMapSize += MODIFIED_ALLOCATION_SIZE;
				}

				spdlog::info("Total size after modified {:8.3f} MiB", static_cast<double>(TotalMapSize) / size_mb);

			}

#if defined(T1X)
			findpattern = Patterns::NdDevMenu_NdDevMenuAppend_Particles;
			auto ParticlesMenu = Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::NdDevMenu_NdDevMenuAppend_Particles), findpattern.offset);

			if (!ParticlesMenu) {
				throw SdkComponentEx
				{ std::format("Failed to find T1X addresses!"),
					SdkComponentEx::ErrorCode::PatternFailed, true };
			}

			int32_t OffsetToisDebugMemoryAval = 0;
			ParticlesMenu = ParticlesMenu + 0xc;
			OffsetToisDebugMemoryAval = *(uint32_t*)(ParticlesMenu);
			m_IsDebugMemoryAvailablePatch = Utility::WritePatchAddress(module,
				ParticlesMenu + OffsetToisDebugMemoryAval + 4, { 0xb0, 0x01, 0xc3 }, wstr(m_IsDebugMemoryAvailablePatch), IsDebugMemoryAvailable());

			if (m_IsDebugMemoryAvailablePatch->IsEnable()) {

				spdlog::warn("DebugMemory is enabled in Config");
				Memory::IncreaseMemoryMap(MemoryMapId::ALLOCATION_CPU_MEMORY, 2000 * size_mb);

				findpattern = Patterns::Memory_clarg_nodebugmem;
				uint8_t byte_0 = 0;
				m_clarg_nodebugmemPatch = Utility::WritePatchPattern(module, findpattern.pattern, &byte_0, sizeof(byte_0),
					wstr(Patterns::Memory_clarg_nodebugmem), findpattern.offset);

				// even if we don't have funcs for only custom dmenu, lets increase retail memory always
				static std::map<MemoryMapId, Patch::Ptr> ModifiedContextMaps{};
				spdlog::warn("changing all kAllocDevCpu allocation to kAllocAppCpu");
				for (auto& [MapId, MapEntry] : m_MemoryMap.s_MemoryMap) {

					if (MapEntry->ContextType() == MemoryContextType::kAllocDevCpu)
					{
						auto model_view = MapEntry->Get();
						MemoryContextType CURRENT_CONTEXT_TYPE = model_view->m_context;
						MemoryContextType MODIFIED_CONTEXT_TYPE = MemoryContextType::kAllocAppCpu;

						auto patch = Utility::WritePatchAddress_Value(module, sizeof(MODIFIED_CONTEXT_TYPE),
							(uint64_t)&model_view->m_context, &MODIFIED_CONTEXT_TYPE,
							wstring_converter.from_bytes(model_view->m_name).c_str());

						spdlog::warn("Modified ContextType {}: {} -> {}", model_view->m_name,
							static_cast<uint32_t>(CURRENT_CONTEXT_TYPE), static_cast<uint32_t>(MODIFIED_CONTEXT_TYPE));

						ModifiedContextMaps.emplace(MapEntry->Id(), std::move(patch));

					}
				}

				findpattern = Patterns::Memory_Allocate;
				m_AllocateHook = Utility::WritePatchPattern_Hook(module, findpattern.pattern, wstr(Patterns::Memory_Allocate),
					findpattern.offset, (void*)Memory_Allocate_CC);

				if (!m_AllocateHook) {
					throw SdkComponentEx{ "Failed to create Memory_Allocate hook for override MemoryContextType!",
						SdkComponentEx::ErrorCode::PatchFailed, true };
				}

				Memory_Allocate_ReturnAddr = m_AllocateHook->get_original();

			}
			if (!m_cfg.ModifiedMapEntries.empty() || m_IsDebugMemoryAvailablePatch->IsEnable()) {
				findpattern = Patterns::Memory_ValidateContext;
				m_ValidateContextPatch = Utility::WritePatchNop(module, findpattern.pattern, 0x1,
				wstr(Patterns::Memory_ValidateContext), findpattern.offset);
			}
	#endif

		});
	}

	void Memory::Allocator::PrintDebugAllocatorInfo() {
		//TODO 
		/*
		*  printf_s("Memory_GetCtx at 0x%p 0x%x: %40s (0x%016llx - 0x%016llx) %llu bytes\n",
                    ret,
                    i,
                    ret->context_name,
                    ret->start_addr,
                    ret->end_addr,
                    ret->heap_size);
		*/
	}

	void __attribute__((naked)) Memory_Allocate_CC()
	{
		__asm
		{
			mov eax, [rdx];
			// code by infogram
			cmp eax, MemoryContextType::kAllocDebugDevMenu;
			je retail_memory_type;
			// extra check
			cmp eax, MemoryContextType::kAllocDevCpu;
			jnz code_exit;
		retail_memory_type:;
			mov eax, MemoryContextType::kAllocScriptData;
			mov[rdx], eax;
		code_exit:;
			jmp[rip + Memory_Allocate_ReturnAddr];
		}
	}
}
#endif
