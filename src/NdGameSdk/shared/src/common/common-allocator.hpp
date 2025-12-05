#pragma once

#include "NdGameSdk/sdk.hpp"

#include <NdGameSdk/shared/src/corelib/containers/tagged-heap.hpp>
#include <NdGameSdk/shared/src/corelib/memory/memory.hpp>

#include <helper.hpp>

using namespace NdGameSdk::corelib::memory;

namespace NdGameSdk::common {

	class CommonGame;

	class IAllocator : public ISdkSubComponent {
	public:
		explicit IAllocator();
	private:
		void Awake() override;
		void Init() override;

		Memory* m_Memory{ nullptr };

		MidHook m_IAllocator_InitTaggedHeapsHook{};

		/*Extern variables*/
		static TaggedHeap* s_TaggedGpuDevHeap;
	};
}
