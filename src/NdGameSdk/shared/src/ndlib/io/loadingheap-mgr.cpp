#include "loadingheap-mgr.hpp"
#include "./NdGameSdk/shared/sharedpatterns.hpp"

namespace NdGameSdk::ndlib::io {

	LoadingHeapMgr::LoadingHeapMgr() : ISdkComponent(TOSTRING(LoadingHeapMgr)) {}

	void LoadingHeapMgr::Initialize() {
		static std::once_flag Initialized;

		std::call_once(Initialized, [this] {
			spdlog::info("Initializing {} patterns...", GetName());

			Patterns::SdkPattern findpattern{};
			auto module = Utility::memory::get_executable();

			findpattern = Patterns::LoadingHeapMgr_GetLoadingHeap;
			LoadingHeapMgr_GetLoadingHeap = (LoadingHeapMgr_GetLoadingHeap_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::LoadingHeapMgr_GetLoadingHeap), findpattern.offset);

			if (!LoadingHeapMgr_GetLoadingHeap) {
				throw SdkComponentEx{ std::format("Failed to find {} addresses!", GetName()),
					SdkComponentEx::ErrorCode::PatternFailed };
			}

		});
	}

	LoadingHeap* LoadingHeapMgr::GetLoadingHeap(LevelHeapType heapType) {
		always_assert(LoadingHeapMgr_GetLoadingHeap == nullptr, "Function pointer was not set!");
		return LoadingHeapMgr_GetLoadingHeap(heapType);
	}

	INIT_FUNCTION_PTR(LoadingHeapMgr::LoadingHeapMgr_GetLoadingHeap);
}