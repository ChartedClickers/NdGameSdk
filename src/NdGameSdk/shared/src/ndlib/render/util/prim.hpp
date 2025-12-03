#pragma once

#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/components/SdkSubComponent.hpp"

#include <Utility/helper.hpp>
#include <Utility/assertion/assert.hpp>
#include <Utility/function_ptr.hpp>
#include <glm/vec4.hpp>

#include <NdGameSdk/shared/src/corelib/memory/memory.hpp>

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/ndlib/render/util/PrimServer.hpp>
#elif defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/ndlib/render/util/PrimServer.hpp>
#endif

#include "../text/string-builder.h"

namespace NdGameSdk::ndlib::render::dev { class DebugDrawCommon; }

using namespace NdGameSdk::corelib::memory;
using namespace NdGameSdk::ndlib::render::dev;
using namespace NdGameSdk::ndlib::render::text;

namespace NdGameSdk::ndlib::render::util {

	class NdGameSdk_API PrimServer : public ISdkRegenny<regenny::shared::ndlib::render::util::PrimServer>
	{
	public:
		class NdGameSdk_API InitParams : public ISdkRegenny<regenny::shared::ndlib::render::util::PrimServer::InitParams>
		{
		public:
			InitParams(MemSize pBufferSize);
			InitParams(std::initializer_list<uint32_t> pBufferSizes);
			std::array<MemSize, 0x13> GetMemoryBufferSize();
		};

		void RenderString(DebugStringBase header, void* DebugPrimParams, void* BoundFrame);
	};

	class PrimServerManager : public ISdkSubComponent {
	public:
		explicit PrimServerManager();
		void Init() override;
#if defined(T1X)
		void Create(PrimServer::InitParams* InitParams);
#endif
		void TextPrintPosition(glm::vec4* position, int32_t color, const char* text, uint64_t arg4);
		void TextPrint(DebugStringBase& DebugString);
		void* GetDefaultPrimParams(void* storage);

		PrimServer* s_PrimServer;
	private:
		MEMBER_FUNCTION_PTR(uint64_t,PrimServer_TextPrintPosition, glm::vec4* position, int32_t color, const char* text, uint64_t arg4);
		MEMBER_FUNCTION_PTR(void*, PrimServer_GetDefaultPrimParams, void* storage);
#if defined(T1X)
		MEMBER_FUNCTION_PTR(void, PrimServer_Create, PrimServer*, PrimServer::InitParams*);
#endif

		void* s_DebugStringBaseHandler;
	};


	static_assert(sizeof(PrimServer) == 0x1380, "Size of PrimServer is not correct.");
	static_assert(sizeof(PrimServer::InitParams) == 0x4c, "Size of PrimServer::InitParams is not correct.");
}