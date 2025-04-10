#include "common-allocator.hpp"
#include "common-game-init.hpp"
#include "./NdGameSdk/shared/sharedpatterns.hpp"
#include <NdGameSdk/components/SdkComponent.hpp>

namespace NdGameSdk::common {

	void SetHeapTags() {

	}

	void IAllocator::Init(CommonGame& pcommongame, Memory& pmemory)
	{

		Patterns::SdkPattern findpattern{};
		auto module = Utility::memory::get_executable();

	#if defined(T2R)
		if (pmemory.IsDebugMemoryAvailable()) {
			findpattern = Patterns::IAllocator_Init;
			auto InitTaggedHeapsJMP = (void*)Utility::FindAndPrintPattern(module
				, findpattern.pattern, wstr(Patterns::GameInit_PrimServer_Create), (findpattern.offset + 0x4a7));

			m_IAllocator_InitTaggedHeapsHook = Utility::MakeMidHook(InitTaggedHeapsJMP,
				[](SafetyHookContext& ctx)
				{
					SetHeapTags();
					//auto CommonGame = GetSharedComponents()->GetComponent<CommonGame>();

				}, wstr(Patterns::IAllocator_Init), wstr(InitTaggedHeapsJMP));


			if (!m_IAllocator_InitTaggedHeapsHook) {
				throw SdkComponentEx{ std::format("Failed to create hook {:s} in {:s}!", TOSTRING(m_IAllocator_InitTaggedHeapsHook), TOSTRING(IAllocator)),
					SdkComponentEx::ErrorCode::PatchFailed };
			}
		}
	#endif 

	}
}