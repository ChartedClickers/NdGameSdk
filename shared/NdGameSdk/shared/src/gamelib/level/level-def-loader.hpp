#pragma once

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/gamelib/level/LevelDefLoader.hpp>
#endif

#include <NdGameSdk/shared/src/corelib/system/NdSystem.hpp>
#include <NdGameSdk/shared/src/corelib/memory/allocator-pool.hpp>

namespace NdGameSdk::gamelib::level {
#if defined(T2R)

	using namespace corelib::system::platform;
	using namespace corelib::memory;

	class NdGameSdk_API LevelDefLoader : public ISdkRegenny<regenny::shared::gamelib::level::LevelDefLoader> {
	public:
		using State = regenny::shared::gamelib::level::LevelDefLoader::State;

		class BatchRequest : public ISdkRegenny<regenny::shared::gamelib::level::LevelDefLoader::BatchRequest> {};

		BatchRequest* GetBatchRequest();

		State GetState() const;

		PoolAllocator* GetLoaderAllocator() const;
		Thread* GetLoaderThread() const;
		Mutex* GetLoaderMutex() const;

	};

	static_assert(sizeof(LevelDefLoader) == 0x1690, "Size of LevelDefLoader is not correct.");
	static_assert(sizeof(LevelDefLoader::BatchRequest) == 0x600, "Size of LevelDefLoader::BatchRequest is not correct.");

#endif
}