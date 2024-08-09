#include "prim.hpp"
#include "./NdGameSdk/shared/sharedpatterns.hpp"

#include <iostream>
#include <cstdint>
#include <initializer_list>
#include <algorithm>

namespace NdGameSdk::ndlib::render::util {

	PrimServer::InitParams::InitParams(MemSize pBufferSize) {
		auto& memoryBufferSize = this->Get()->m_memoryBufferSize;
		auto ARRAY_SIZE = sizeof(memoryBufferSize) / sizeof(memoryBufferSize[0]);
		uint32_t BufferSize = pBufferSize.GetSize<uint32_t>(SizeUnit::Bytes) / ARRAY_SIZE;
		std::fill(std::begin(memoryBufferSize), std::end(memoryBufferSize), BufferSize);
	}

	PrimServer::InitParams::InitParams(std::initializer_list<uint32_t> pBufferSizes) {
		auto& memoryBufferSize = this->Get()->m_memoryBufferSize;
		auto ARRAY_SIZE = sizeof(memoryBufferSize) / sizeof(memoryBufferSize[0]);

		std::fill(std::begin(memoryBufferSize), std::end(memoryBufferSize), 0x0);
		size_t count = (pBufferSizes.size() < ARRAY_SIZE) ? pBufferSizes.size() : ARRAY_SIZE;
		std::memcpy(memoryBufferSize, pBufferSizes.begin(), count * sizeof(uint32_t));
	}

	std::array<MemSize, 0x13> PrimServer::InitParams::GetMemoryBufferSize() {
		auto& memoryBufferSize = this->Get()->m_memoryBufferSize;
		std::array<MemSize, 0x13> memoryBufferSizeArray;
		std::copy(std::begin(memoryBufferSize), std::end(memoryBufferSize), std::begin(memoryBufferSizeArray));
		return memoryBufferSizeArray;
	}

	PrimServerComponent::PrimServerComponent(PrimServerCfg& cfg) : m_cfg { std::move(cfg) }, ISdkComponent("PrimServer") {}
	
	bool PrimServerComponent::IsCreated() {
		return m_IsCreated;
	}

	void PrimServerComponent::Create(PrimServer::InitParams* InitParams) {
		always_assert(PrimServer_Create == nullptr, "Function pointer was not set!");
		if (!m_IsCreated) {
			PrimServer_Create(m_PrimServer, InitParams);
			m_IsCreated = true;
		}
	}

	void PrimServerComponent::Awake() {
		auto SharedComponents = ISdkComponent::GetSharedComponents();
		m_Memory = SharedComponents->GetComponent<Memory>();
	}

	void PrimServerComponent::Initialize() {

		static std::once_flag Initialized;
		
		std::call_once(Initialized, [this] {

			spdlog::info("Initializing {} patterns...", GetName());

			auto MissingDependencies = CheckSdkComponents
				<Memory>({ m_Memory.get() });

			if (MissingDependencies.has_value()) {
				throw SdkComponentEx
				{ std::format("Missing necessary dependencies: {:s}", MissingDependencies.value()),
					SdkComponentEx::ErrorCode::DependenciesFailed };
			}

			Patterns::SdkPattern findpattern{};
			auto module = Utility::memory::get_executable();

			findpattern = Patterns::PrimServer_PrimServer;
			m_PrimServer = (PrimServer*)Utility::ReadLEA32(module,
				findpattern.pattern, wstr(Patterns::PrimServer_PrimServer), findpattern.offset, 3, 7);

			if (!m_PrimServer) {
				throw SdkComponentEx
				{ std::format("Failed to find addresses!"),
					SdkComponentEx::ErrorCode::PatternFailed };
			}

			findpattern = Patterns::PrimServer_Create;
			PrimServer_Create = (PrimServer_Create_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::PrimServer_Create), findpattern.offset);

			if (!PrimServer_Create) {
				throw SdkComponentEx{ "Failed to find PrimServer:: game functions!", SdkComponentEx::ErrorCode::PatternFailed };
			}

			if (m_cfg.PrimServerCreate) {
				m_Memory->IncreaseMemoryMap(MemoryMapId::ALLOCATION_CPU_MEMORY, MemSize(2560, SizeUnit::Megabytes));
			}

		});
	}
}