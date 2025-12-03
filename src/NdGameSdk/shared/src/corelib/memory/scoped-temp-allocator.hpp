#pragma once

#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/components/SdkSubComponent.hpp"

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/corelib/memory/ScopedTempData.hpp>
#include <NdGameSdk/regenny/t2r/shared/corelib/memory/ScopedTempAllocator.hpp>
#elif defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/corelib/memory/ScopedTempData.hpp>
#include <NdGameSdk/regenny/t1x/shared/corelib/memory/ScopedTempAllocator.hpp>
#endif

#include <NdGameSdk/shared/src/corelib/containers/fixed-size-hashtable.hpp>
#include <NdGameSdk/shared/src/corelib/containers/bit-array.hpp>
#include <NdGameSdk/shared/src/corelib/system/platform/mutex.hpp>

#include <Utility/function_ptr.hpp>

#include "allocator-heap.hpp"

namespace NdGameSdk::corelib::memory {

	using namespace corelib::containers;
	class ScopedTempData;
	class ScopedTempAllocator;

	class ScopedTempsComponent final : public ISdkSubComponent {
	public:
		using SdkComponentOwner = Memory;
		explicit ScopedTempsComponent();

		void* InitScopedTempAllocator(ScopedTempAllocator& pScopedTempAllocator, bool pushAllocator, HeapArena_Args);

	private:
		void Init() override;

		/*Extern Functs*/
		// void __cdecl InitializeScopedTempAllocSystem(void *,unsigned __int64,unsigned __int64)
		static void __cdecl InitializeScopedTempAllocSystem(void* poolMemory, uint64_t poolSizeBytes, uint64_t numBlocks);

		/*Extern variables*/
		static ScopedTempData* s_scopedTempData;

		InlineHook m_InitializeScopedTempAllocSystemHook{};

		MEMBER_FUNCTION_PTR(void*, ScopedTempsComponent_ScopedTempAllocator_Init, ScopedTempAllocator* pScopedTempAllocator,
			bool pushAllocator, char const* source_file, int32_t source_line, char const* source_funct);
	};

	class ScopedTempData : public ISdkRegenny<regenny::shared::corelib::memory::ScopedTempData> {
	public:
		using BlockOwner = regenny::shared::corelib::memory::ScopedTempData::BlockOwner;
		using HashNode = regenny::shared::corelib::memory::ScopedTempData::HashNode;

		BitArray<128>& GetUsageMask() const;
		FixedSizeHashTable<HashNode>& GetHashTable();

		uint32_t GetActiveBlocks() const;
		uint32_t GetPeakBlocks() const;
	};

	class ScopedTempAllocator : public ISdkRegenny<regenny::shared::corelib::memory::ScopedTempAllocator> {
	public:
		ScopedTempAllocator() = default;
		~ScopedTempAllocator();

		HeapAllocatorWithOverflow* GetHeapAllocator();
		bool IsNodeInserted();
		bool IsPushedAllocator();
		bool IsStateActive();
	private:
		TYPEDEF_FUNCTION_PTR(void, ScopedTempAllocator_Destructor, ScopedTempAllocator* pScopedTempAllocator);
		friend class ScopedTempsComponent;
	};

}