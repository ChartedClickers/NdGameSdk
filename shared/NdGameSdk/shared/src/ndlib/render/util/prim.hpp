#pragma once

#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/components/SdkSubComponent.hpp"

#include <Utility/helper.hpp>
#include <Utility/assertion/assert.hpp>
#include <Utility/function_ptr.hpp>

#include <NdGameSdk/shared/src/corelib/memory/memory.hpp>

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/ndlib/render/util/PrimServer.hpp>
#elif defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/ndlib/render/util/PrimServer.hpp>
#endif

namespace NdGameSdk::ndlib::render::dev { class DebugDrawCommon; }

using namespace NdGameSdk::corelib::memory;
using namespace NdGameSdk::ndlib::render::dev;

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
	};

	class PrimServerManager : public ISdkSubComponent {
	public:
		explicit PrimServerManager(DebugDrawCommon* pDebugDrawCommon);
		void Init() override;
#if defined(T1X)
		void Create(PrimServer::InitParams* InitParams);
#endif
		PrimServer* s_PrimServer;
	private:
		DebugDrawCommon* m_DebugDrawCommon{};
#if defined(T1X)
		MEMBER_FUNCTION_PTR(void, PrimServer_Create, PrimServer*, PrimServer::InitParams*);
#endif
	};


	static_assert(sizeof(PrimServer) == 0x1380, "Size of PrimServer is not correct.");
	static_assert(sizeof(PrimServer::InitParams) == 0x4c, "Size of PrimServer::InitParams is not correct.");
}