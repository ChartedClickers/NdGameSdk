#pragma once
#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/components/SdkComponent.hpp"

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/ndlib/io/LoadingHeapMgr.hpp>
#elif defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/ndlib/io/LoadingHeapMgr.hpp>
#endif

#include <helper.hpp>
#include <function_ptr.hpp>

#include "loadingheap.hpp"

namespace NdGameSdk::ndlib::io {

	class LoadingHeapMgr final : public ISdkComponent {
	public:
		using LevelHeapType = regenny::shared::ndlib::io::LoadingHeapMgr::LevelHeapType;

		LoadingHeapMgr();

		/*Extern Functs*/
		LoadingHeap* GetLoadingHeap(LevelHeapType heapType);

	private:
		void Initialize() override;

		TYPEDEF_FUNCTION_PTR(LoadingHeap*, LoadingHeapMgr_GetLoadingHeap, LevelHeapType pHeapType);

	};

}
