#include "frame-params.hpp"
#include "./NdGameSdk/shared/sharedpatterns.hpp"

namespace NdGameSdk::ndlib {

	RenderFrameParams::RenderFrameParams() : ISdkComponent(TOSTRING(RenderFrameParams)) {}

	void RenderFrameParams::Initialize() {

		static std::once_flag Initialized;
		std::call_once(Initialized, [this] {
			spdlog::info("Initializing {} patterns...", GetName());

			Patterns::SdkPattern findpattern{};
			auto module = Utility::memory::get_executable();

			findpattern = Patterns::RenderFrameParams_s_FrameParams;
			s_FrameParams = (FrameParams::InitParams*)Utility::ReadLEA32(module,
				findpattern.pattern, wstr(Patterns::RenderFrameParams_s_FrameParams), findpattern.offset, 3, 7);

			findpattern = Patterns::RenderFrameParams_InitializeFrameParamsReturn;
			auto FrameParamsInitReturn = (void*)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::RenderFrameParams_InitializeFrameParamsReturn), findpattern.offset);

			if (!s_FrameParams ||
				!FrameParamsInitReturn) {
				throw SdkComponentEx{ std::format("Failed to find {}:: addresses!", GetName()),
					SdkComponentEx::ErrorCode::PatternFailed };
			}

			findpattern = Patterns::RenderFrameParams_GetFrameParams;
			RenderFrameParams_GetFrameParams = (RenderFrameParams_GetFrameParams_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::RenderFrameParams_GetFrameParams), findpattern.offset);

			findpattern = Patterns::RenderFrameParams_GetCurrentFrameParams;
			RenderFrameParams_GetCurrentFrameParams = (RenderFrameParams_GetCurrentFrameParams_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::RenderFrameParams_GetCurrentFrameParams), findpattern.offset);

			findpattern = Patterns::RenderFrameParams_IsFrameReady;
			RenderFrameParams_IsFrameReady = (RenderFrameParams_IsFrameReady_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::RenderFrameParams_IsFrameReady), findpattern.offset);

		#if defined(T2R)
			findpattern = Patterns::RenderFrameParams_GetCurrentFrameNumber;
			RenderFrameParams_GetCurrentFrameNumber = (RenderFrameParams_GetCurrentFrameNumber_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::RenderFrameParams_GetCurrentFrameNumber), findpattern.offset);
		#endif

			if (!RenderFrameParams_GetFrameParams ||
				!RenderFrameParams_GetCurrentFrameParams ||
				!RenderFrameParams_IsFrameReady
				#if defined(T2R)
				|| !RenderFrameParams_GetCurrentFrameNumber
				#endif
				) {
				throw SdkComponentEx{ std::format("Failed to find {}:: game functions!", GetName()),
					SdkComponentEx::ErrorCode::PatternFailed };
			}

		});
	}

	FrameParams* RenderFrameParams::GetFrameParams(uint64_t FrameNumber) {
		always_assert(RenderFrameParams_GetFrameParams == nullptr, "Function pointer was not set!");
		return RenderFrameParams_GetFrameParams(FrameNumber);
	}

	FrameParams* RenderFrameParams::GetRenderFrameParams() {
		always_assert(RenderFrameParams_GetCurrentFrameParams == nullptr, "Function pointer was not set!");
		return RenderFrameParams_GetCurrentFrameParams();
	}

	const uint64_t RenderFrameParams::GetCurrentFrameNumber() {
	#if defined(T2R)
		always_assert(RenderFrameParams_GetCurrentFrameNumber == nullptr, "Function pointer was not set!");
		return RenderFrameParams_GetCurrentFrameNumber();
	#else 
		FrameParams* currentFrameParams = GetRenderFrameParams();
		return currentFrameParams ? currentFrameParams->GetFrameNumber() : 0;
	#endif
	}

	bool RenderFrameParams::IsFrameReady(uint64_t FrameNumber) {
		always_assert(RenderFrameParams_IsFrameReady == nullptr, "Function pointer was not set!");
		return RenderFrameParams_IsFrameReady(FrameNumber);
	}

	uint64_t FrameParams::GetFrameNumber() const {
		return this->Get()->m_frameNumber;
	}
}