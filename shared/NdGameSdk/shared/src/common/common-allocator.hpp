#pragma once

#include "NdGameSdk/sdk.hpp"
#include <Utility/helper.hpp>
#include <NdGameSdk/shared/src/corelib/memory/memory.hpp>

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/corelib/memory/TaggedHeap.hpp>
#elif defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/corelib/memory/TaggedHeap.hpp>
#endif

using TaggedHeap = ::regenny::shared::corelib::memory::TaggedHeap;
using namespace NdGameSdk::corelib::memory;

namespace NdGameSdk::common {

	class CommonGame;

	class IAllocator : public ISdkSubComponent {
	public:
		explicit IAllocator();
		void Init() override;
	private:
		MidHook m_IAllocator_InitTaggedHeapsHook{};

		/*Extern variables*/
		static TaggedHeap* s_TaggedGpuDevHeap;
	};
}