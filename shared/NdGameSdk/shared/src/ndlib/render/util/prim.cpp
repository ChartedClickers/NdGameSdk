#include "prim.hpp"
#include "./NdGameSdk/shared/sharedpatterns.hpp"
#include "../dev/debugdraw-common.hpp"

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

	void PrimServer::RenderString(DebugStringBase header, void* DebugPrimParams, void* BoundFrame) {
		auto* primSrv = this->Get();
		primSrv->vftable->RenderString(header.Get(), DebugPrimParams, BoundFrame);
	}

	PrimServerManager::PrimServerManager() : ISdkSubComponent("PrimServer") {}

#if defined(T1X)
	void PrimServerManager::Create(PrimServer::InitParams* InitParams) {
		always_assert(PrimServer_Create == nullptr, "Function pointer was not set!");
		static std::once_flag IsCreated;
		std::call_once(IsCreated, [this, InitParams] {
			PrimServer_Create(s_PrimServer, InitParams);
		});
	}
#endif

	void PrimServerManager::TextPrintPosition(glm::vec4* position, int32_t color, const char* text, uint64_t arg4) {
		always_assert(PrimServer_TextPrintPosition == nullptr, "Function pointer was not set!");
		PrimServer_TextPrintPosition(position, color, text, arg4);
	}

	void PrimServerManager::TextPrint(DebugStringBase& DebugString) {
		always_assert(s_PrimServer->Get() == nullptr, "PrimServer pointer was not set!");
		uint64_t primParams[0x10]{};
		PrimServer_GetDefaultPrimParams(primParams);
		DebugString->vftable = s_DebugStringBaseHandler;
		s_PrimServer->RenderString(DebugString, &primParams, nullptr);
	} 

	void* PrimServerManager::GetDefaultPrimParams(void* storage) {
		always_assert(PrimServer_GetDefaultPrimParams == nullptr, "Function pointer was not set!");
		PrimServer_GetDefaultPrimParams(storage);
	}

	void PrimServerManager::Init() {

		static std::once_flag Initialized;
		
		std::call_once(Initialized, [this] {

			spdlog::info("Initializing {} patterns...", GetName());
			DebugDrawCommon* DebugDraw{ GetParentComponent<DebugDrawCommon>() };

			if (DebugDraw->m_Memory->IsDebugMemoryAvailable()) {

				Patterns::SdkPattern findpattern{};
				auto module = Utility::memory::get_executable();

				findpattern = Patterns::PrimServer_PrimServer;
				s_PrimServer = (PrimServer*)Utility::ReadLEA32(module,
					findpattern.pattern, wstr(Patterns::PrimServer_PrimServer), findpattern.offset, 3, 7);

				findpattern = Patterns::PrimServer_DebugStringBaseHandler;
				s_DebugStringBaseHandler = (MsgCon*)Utility::ReadLEA32(module,
					findpattern.pattern, wstr(Patterns::PrimServer_DebugStringBaseHandler), findpattern.offset, 3, 7);

				if (!s_PrimServer ||
					!s_DebugStringBaseHandler) {
					throw SdkComponentEx
					{ std::format("Failed to find addresses!"),
						SdkComponentEx::ErrorCode::PatternFailed };
				}

	#if defined(T1X)
				findpattern = Patterns::PrimServer_Create;
				PrimServer_Create = (PrimServer_Create_ptr)Utility::FindAndPrintPattern(module,
					findpattern.pattern, wstr(Patterns::PrimServer_Create), findpattern.offset);

				if (!PrimServer_Create) {
					throw SdkComponentEx{ "Failed to find PrimServer:: game functions for T1X!", SdkComponentEx::ErrorCode::PatternFailed };
				}

				DebugDraw->m_Memory->IncreaseMemoryMap(MemoryMapId::ALLOCATION_CPU_MEMORY, MemSize(2560, SizeUnit::Megabytes));
	#endif

				findpattern = Patterns::PrimServer_TextPrintPosition;
				PrimServer_TextPrintPosition = (PrimServer_TextPrintPosition_ptr)Utility::FindAndPrintPattern(module,
					findpattern.pattern, wstr(Patterns::PrimServer_TextPrintPosition), findpattern.offset);

				findpattern = Patterns::PrimServer_GetDefaultPrimParams;
				PrimServer_GetDefaultPrimParams = (PrimServer_GetDefaultPrimParams_ptr)Utility::FindAndPrintPattern(module,
					findpattern.pattern, wstr(Patterns::PrimServer_GetDefaultPrimParams), findpattern.offset);

				if (!PrimServer_TextPrintPosition || 
					!PrimServer_GetDefaultPrimParams) {
					throw SdkComponentEx{ "Failed to find PrimServer:: game functions!", SdkComponentEx::ErrorCode::PatternFailed };
				}

			}

		});
	}
}