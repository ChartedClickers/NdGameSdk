#pragma once

#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/components/SdkComponent.hpp"

#include <Windows.h>
#include <Utility/function_ptr.hpp>

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/ndlib/FrameParams.hpp>
#elif defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/ndlib/FrameParams.hpp>
#endif

namespace NdGameSdk::ndlib::render::dev {
    class DebugDrawCommon;
}

namespace NdGameSdk::ndlib {

	class NdGameSdk_API FrameParams : public ISdkRegenny<regenny::shared::ndlib::FrameParams> {
	public:
		static constexpr uint32_t kFrameParamsCount = 0x12;

		class InitParams : public ISdkRegenny<regenny::shared::ndlib::FrameParams::InitParams> {
        public:
            static constexpr std::size_t kSlots = FrameParams::kFrameParamsCount;

            FrameParams* GetFrameParams() {
                return reinterpret_cast<FrameParams*>(this->Get()->m_ringBase);
            }

            std::size_t sizeOfFrameParams() const { return this->Get()->m_ringBase ? kSlots : 0; }

            FrameParams& AtFrameParams(std::size_t i) {
                return GetFrameParams()[i];
            }

            FrameParams& forFrame(uint64_t frameNumber) {
                return AtFrameParams(static_cast<std::size_t>(frameNumber % kSlots));
            }

            struct Iterator {
                FrameParams* cur{};
                FrameParams* end{};
                Iterator& operator++() { ++cur; return *this; }
                bool operator!=(const Iterator& o) const { return cur != o.cur; }
                FrameParams& operator*()  const { return *cur; }
                FrameParams* operator->() const { return  cur; }
            };

            Iterator begin() {
                auto* b = GetFrameParams();
                return { b, b ? b + kSlots : b };
            }
            Iterator end() {
                auto* b = GetFrameParams();
                auto* e = b ? b + kSlots : b;
                return { e, e };
            }

            FrameParams& operator[](std::size_t i) { return AtFrameParams(i); }
		};

		uint64_t GetFrameNumber() const;
	};

	class NdGameSdk_API RenderFrameParams : public ISdkComponent {
	public:
		RenderFrameParams();

		FrameParams* GetFrameParams(uint64_t FrameNumber);
		FrameParams* GetRenderFrameParams();
		const uint64_t GetCurrentFrameNumber();
		bool IsFrameReady(uint64_t FrameNumber);

	private:
        void Initialize() override;

		/*Extern variables*/
		FrameParams::InitParams* s_FrameParams;

		MEMBER_FUNCTION_PTR(FrameParams*, RenderFrameParams_GetFrameParams, uint64_t FrameNumber);
		MEMBER_FUNCTION_PTR(FrameParams*, RenderFrameParams_GetCurrentFrameParams);
		MEMBER_FUNCTION_PTR(bool, RenderFrameParams_IsFrameReady, uint64_t FrameNumber);

#if defined (T2R)
		MEMBER_FUNCTION_PTR(uint64_t, RenderFrameParams_GetCurrentFrameNumber);
#endif
	};

#if defined(T2R)
	static_assert(sizeof(FrameParams) == 0x17900, "Size of FrameParams is not correct.");
#elif defined(T1X)
	static_assert(sizeof(FrameParams) == 0x17580, "Size of FrameParams is not correct.");
#endif

}

