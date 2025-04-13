#pragma once

#if defined(T1X)


#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/components/SdkComponent.hpp"

#include <Utility/helper.hpp>
#include <Utility/assertion/assert.hpp>
#include <Utility/function_ptr.hpp>

#include <NdGameSdk/shared/src/corelib/memory/memory.hpp>

#if defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/ndlib/render/util/PrimServer.hpp>
#endif

using namespace NdGameSdk::corelib::memory;

namespace NdGameSdk::common {
	class CommonGame;
}

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

	class PrimServerComponent : public ISdkComponent
	{
	public:
		PrimServerComponent();
		NdGameSdk_API bool IsCreated();
		void Create(PrimServer::InitParams* InitParams);
	private:
		void Awake() override;
		void Initialize() override;

		bool m_IsCreated{};

		PrimServer* m_PrimServer;
		
		shared_ptr<Memory> m_Memory;

		friend class NdGameSdk::common::CommonGame;
		MEMBER_FUNCTION_PTR(void, PrimServer_Create, PrimServer*, PrimServer::InitParams*);
	};

	static_assert(sizeof(PrimServer) == 0x1370, "Size of PrimServer is not correct.");
	static_assert(sizeof(PrimServer::InitParams) == 0x4c, "Size of PrimServer::InitParams is not correct.");
}
#endif