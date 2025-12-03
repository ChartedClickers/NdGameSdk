#include "scoped-temp-allocator.hpp"
#include "./NdGameSdk/shared/sharedpatterns.hpp"

#include <Utility/helper.hpp>
#include <Utility/global_resolver.hpp>

#include <format>
#include <mutex>

namespace NdGameSdk::corelib::memory {

	ScopedTempsComponent::ScopedTempsComponent() : ISdkSubComponent(TOSTRING(ScopedTempsComponent), InitPolicy::Manual) {}
	
	void ScopedTempsComponent::Init() {
		static std::once_flag Initialized;

		std::call_once(Initialized, [this]() {
			spdlog::info("Initializing {} patterns...", GetName());

			Patterns::SdkPattern findpattern{};
			auto module = Utility::memory::get_executable();

			findpattern = Patterns::ScopedTempsComponent_InitializeScopedTempAllocSystem;
			auto InitializeScopedTempAllocSystemAddr = (void*)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::ScopedTempsComponent_InitializeScopedTempAllocSystem), findpattern.offset);

			findpattern = Patterns::ScopedTempsComponent_ScopedTempAllocator_s_scopedTempData;
			s_scopedTempData = Utility::GlobalResolver::RipSlotOrNull<ScopedTempData>(module, findpattern.pattern,
				wstr(Patterns::ScopedTempsComponent_ScopedTempAllocator_s_scopedTempData),
				findpattern.offset);

			if (!InitializeScopedTempAllocSystemAddr ||
				!s_scopedTempData) {
				throw SdkComponentEx{ std::format("Failed to find {} addresses!", GetName()),
					SdkComponentEx::ErrorCode::PatternFailed };
			}

			findpattern = Patterns::ScopedTempsComponent_ScopedTempAllocator_Init;
			ScopedTempsComponent_ScopedTempAllocator_Init = (ScopedTempsComponent_ScopedTempAllocator_Init_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::ScopedTempsComponent_ScopedTempAllocator_Init), findpattern.offset);

			findpattern = Patterns::ScopedTempsComponent_ScopedTempAllocator_Destructor;
			ScopedTempAllocator::ScopedTempAllocator_Destructor = (ScopedTempAllocator::ScopedTempAllocator_Destructor_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::ScopedTempsComponent_ScopedTempAllocator_Destructor), findpattern.offset);

			if (!ScopedTempsComponent_ScopedTempAllocator_Init ||
				!ScopedTempAllocator::ScopedTempAllocator_Destructor) {
				throw SdkComponentEx{ std::format("Failed to find {}:: game functions!", GetName()), SdkComponentEx::ErrorCode::PatternFailed };
			}

			m_InitializeScopedTempAllocSystemHook = Utility::MakeSafetyHookInline(InitializeScopedTempAllocSystemAddr,
				ScopedTempsComponent::InitializeScopedTempAllocSystem,
				wstr(Patterns::ScopedTempsComponent_InitializeScopedTempAllocSystem), wstr(ScopedTempsComponent::InitializeScopedTempAllocSystem));

			if (!m_InitializeScopedTempAllocSystemHook) {
				throw SdkComponentEx{ "Failed to create hooks!", SdkComponentEx::ErrorCode::PatchFailed };
			}
		});
	}

	void __cdecl ScopedTempsComponent::InitializeScopedTempAllocSystem(void* poolMemory, uint64_t poolSizeBytes, uint64_t numBlocks) {
		auto* pScopedTempsComponent = Instance<SdkComponentOwner, ScopedTempsComponent>();
		pScopedTempsComponent->m_InitializeScopedTempAllocSystemHook.thiscall<void>(poolMemory, poolSizeBytes, numBlocks);
		return;
	}

	void* ScopedTempsComponent::InitScopedTempAllocator(ScopedTempAllocator& pScopedTempAllocator, bool pushAllocator, HeapArena_Args) {
		always_assert(ScopedTempsComponent_ScopedTempAllocator_Init == nullptr, "Function pointer was not set!");
		return ScopedTempsComponent_ScopedTempAllocator_Init(&pScopedTempAllocator, pushAllocator, source_file, source_line, source_func);
	}

	BitArray<128>& ScopedTempData::GetUsageMask() const {
		return reinterpret_cast<BitArray<128>&>(this->Get()->m_usageMask);
	}

	FixedSizeHashTable<ScopedTempData::HashNode>& ScopedTempData::GetHashTable() {
		return reinterpret_cast<FixedSizeHashTable<ScopedTempData::HashNode>&>(this->Get()->m_table);
	}

	uint32_t ScopedTempData::GetActiveBlocks() const {
		return this->Get()->m_activeBlocks;
	}

	uint32_t ScopedTempData::GetPeakBlocks() const {
		return this->Get()->m_peakBlocks;
	}

	HeapAllocatorWithOverflow* ScopedTempAllocator::GetHeapAllocator() {
		return reinterpret_cast<HeapAllocatorWithOverflow*>(this->Get()->m_block);
	}

	bool ScopedTempAllocator::IsNodeInserted() {
		return this->Get()->m_nodeInserted;
	}

	bool ScopedTempAllocator::IsPushedAllocator() {
		return this->Get()->m_pushedAllocator;
	}

	bool ScopedTempAllocator::IsStateActive() {
		return this->Get()->m_stateActive;
	}

	ScopedTempAllocator::~ScopedTempAllocator() {
		auto* Raw = this->Get();
		if (Raw->m_pushedAllocator || !Raw->m_stateActive || Raw->m_nodeInserted) {
			always_assert(ScopedTempAllocator_Destructor == nullptr, "Function pointer was not set!");
			ScopedTempAllocator_Destructor(this);
		}
	}

	ScopedTempData* ScopedTempsComponent::s_scopedTempData = nullptr;
	INIT_FUNCTION_PTR(ScopedTempAllocator::ScopedTempAllocator_Destructor);

}
