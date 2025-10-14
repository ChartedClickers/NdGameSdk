#pragma once

#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/components/SdkComponent.hpp"

#include <NdGameSdk/shared/src/corelib/memory/memory.hpp>
#include <NdGameSdk/shared/src/corelib/util/error.hpp>

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/ndlib/render/ndgi/win/WinInitOptions.hpp>
#elif defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/ndlib/render/ndgi/win/WinInitOptions.hpp>
#endif

using namespace NdGameSdk::corelib::memory;
using namespace NdGameSdk::corelib::util;

namespace NdGameSdk::ndlib::render::ndgi::win {

	/* Extern classes */
	class WinInitOptions;

	class NdGameSdk_API NDGI : public ISdkComponent {
	public:
		NDGI();
		SDK_DEPENDENCIES(Memory);

	private:
		void Awake() override;
		void Initialize() override;

		/*Extern Functs*/
		static Err* NDGI_Init(Err* PErr, WinInitOptions* pWinOptions);

		Memory* m_Memory;

		InlineHook m_NDGIInitHook{};

		constexpr static uint64_t kDeformerBufferMiB = 600ull;
	};

	class WinInitOptions : public ISdkRegenny<regenny::shared::ndlib::render::ndgi::win::WinInitOptions> {
	public:
		MemSize GetDeformerChunkBytes() const;
		void SetDeformerChunkBytes(MemSize size);
	};

	static_assert(sizeof(WinInitOptions) == 0x88, "Size of WinInitOptions is not correct.");

}