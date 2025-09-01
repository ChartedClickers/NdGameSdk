#include "common-allocator.hpp"
#include "common-game-init.hpp"
#include "./NdGameSdk/shared/sharedpatterns.hpp"
#include <NdGameSdk/components/SdkComponent.hpp>

namespace NdGameSdk::common {

	IAllocator::IAllocator() : ISdkSubComponent(TOSTRING(IAllocator))  {
		auto SharedComponents = GetSharedComponents();
		m_Memory = SharedComponents->GetComponent<Memory>();
	}

	void IAllocator::Init()
	{
		static std::once_flag Initialized;

		std::call_once(Initialized, [this] {

			spdlog::info("Initializing {} patterns...", GetName());

			Patterns::SdkPattern findpattern{};
			auto module = Utility::memory::get_executable();

	#if defined(T2R)
			if (m_Memory->IsDebugMemoryAvailable()) {

				findpattern = Patterns::CommonGame_IAllocator_s_TaggedGpuDevHeap;
				s_TaggedGpuDevHeap = (TaggedHeap*)Utility::ReadLEA32(module,
					findpattern.pattern, wstr(Patterns::CommonGame_IAllocator_s_TaggedGpuDevHeap), findpattern.offset, 3, 7);

				if (!s_TaggedGpuDevHeap) {
					throw SdkComponentEx
					{ std::format("Failed to find TaggedHeap addresses!"),
						SdkComponentEx::ErrorCode::PatternFailed, true };
				}

				findpattern = Patterns::CommonGame_IAllocator_Init;
				auto InitTaggedHeapsJMP = (void*)Utility::FindAndPrintPattern(module
					, findpattern.pattern, wstr(Patterns::CommonGame_IAllocator_Init), (findpattern.offset + 0x4a7));

				m_IAllocator_InitTaggedHeapsHook = Utility::MakeMidHook(InitTaggedHeapsJMP,
					[](SafetyHookContext& ctx) {

						auto pIAllocator = Instance<CommonGame, IAllocator>();
						pIAllocator->m_Memory->m_AllocatorTaggedHeap.SetTaggedGpuDevHeap(s_TaggedGpuDevHeap);
						spdlog::info("TaggedGpuDevHeap installed!");

					}, wstr(Patterns::CommonGame_IAllocator_Init), wstr(InitTaggedHeapsJMP));


				if (!m_IAllocator_InitTaggedHeapsHook) {
					throw SdkComponentEx{ std::format("Failed to create hook {:s} in {:s}!", TOSTRING(m_IAllocator_InitTaggedHeapsHook), TOSTRING(IAllocator)),
						SdkComponentEx::ErrorCode::PatchFailed, true };
				}
			}
	#endif 
		});

	}

	TaggedHeap* NdGameSdk::common::IAllocator::s_TaggedGpuDevHeap = nullptr;
}