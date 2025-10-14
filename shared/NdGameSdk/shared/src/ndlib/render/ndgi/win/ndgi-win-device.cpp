#include "ndgi-win-device.hpp"
#include "./NdGameSdk/shared/sharedpatterns.hpp"

namespace NdGameSdk::ndlib::render::ndgi::win {

	NDGI::NDGI() : ISdkComponent(TOSTRING(NDGI)) {}

	void NDGI::Awake() {
		auto SharedComponents = ISdkComponent::GetSharedComponents();
		m_Memory = GetDependencyComponent<Memory>(SharedComponents);
	}

	MemSize AlignToChunk(MemSize size) {
		constexpr uint64_t kChunkStride = 0x100000ull; // 1 MiB
		const uint64_t bytes = size.GetSize<uint64_t>();
		const uint64_t aligned = (bytes + kChunkStride - 1ull) & ~(kChunkStride - 1ull);
		return MemSize(static_cast<double>(aligned));
	}

	void NDGI::Initialize() {

		static std::once_flag Initialized;
		std::call_once(Initialized, [this] {
			spdlog::info("Initializing {} patterns...", GetName());

			Patterns::SdkPattern findpattern{};
			auto module = Utility::memory::get_executable();

			findpattern = Patterns::NDGI_Init;
			auto NDGI_Init = (void*)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::NDGI_Init), findpattern.offset);

			if (!NDGI_Init) {
				throw SdkComponentEx{ std::format("Failed to find {} addresses!", GetName()),
					SdkComponentEx::ErrorCode::PatternFailed };
			}

			m_NDGIInitHook = Utility::MakeSafetyHookInline(NDGI_Init, NDGI::NDGI_Init,
				wstr(Patterns::NDGI_Init), wstr(NDGI::NDGI_Init));


			if (!m_NDGIInitHook) {
				throw SdkComponentEx{ "Failed to create hooks!", SdkComponentEx::ErrorCode::PatchFailed };
			}

	#if defined(T2R)
			if (m_Memory->IsDebugMemoryAvailable()) {
				spdlog::warn("DebugMemory is available, resizing DeformerChunkBytes allocation...");
				/*
				* Be sure WinInitOptions.m_deformerChunkBytes has a properly aligned buffer size.
				* But I am recommending exploring the crash problem more deeply later.
				* T2R-PC crash case: Dev Menu|Tasks|Play Task|seattle-arrival|sea-hub-explore|default (DebugMem Only)
				* Original size: 344.000 MiB
				*/
				const auto alignedSize = AlignToChunk(MemSize(kDeformerBufferMiB, SizeUnit::Megabytes));
				m_Memory->ModifyMemoryMap(MemoryMapId::ALLOCATION_DEFORMER_BUFFER, alignedSize);
			}
	#endif

		});

	}

	Err* NDGI::NDGI_Init(Err* PErr, WinInitOptions* pWinOptions) {
		NDGI* pNDGI = Instance<NDGI>();

	#if defined(T2R)
		if (pNDGI->m_Memory->IsDebugMemoryAvailable()) {
			const auto bufferSize = pNDGI->m_Memory->GetMemSize(MemoryMapId::ALLOCATION_DEFORMER_BUFFER);
			auto alignedSize = AlignToChunk(bufferSize);
			pWinOptions->SetDeformerChunkBytes(alignedSize);
			spdlog::warn("Set DeformerChunkBytes to aligned size: {:8.3f} MiB", alignedSize.GetSize<double>(SizeUnit::Megabytes));
		}
	#endif

		return pNDGI->m_NDGIInitHook.thiscall<Err*>(PErr, pWinOptions);
	}


	MemSize WinInitOptions::GetDeformerChunkBytes() const {
		return MemSize(this->Get()->m_deformerChunkBytes);
	}

	void WinInitOptions::SetDeformerChunkBytes(MemSize size) {
		this->Get()->m_deformerChunkBytes = size.GetSize<uint64_t>(SizeUnit::Bytes);
	}
}