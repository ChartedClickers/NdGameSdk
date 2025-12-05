#pragma once
#include "level-def-loader.hpp"

namespace NdGameSdk::gamelib::level {
#if defined(T2R)

	LevelDefLoader::BatchRequest* LevelDefLoader::GetBatchRequest() {
		return reinterpret_cast<LevelDefLoader::BatchRequest*>(&this->Get()->m_batchRequest);
	}

	LevelDefLoader::State LevelDefLoader::GetState() const {
		return this->Get()->m_state;
	}

	PoolAllocator* LevelDefLoader::GetLoaderAllocator() const {
		return reinterpret_cast<PoolAllocator*>(&this->Get()->m_allocator);
	}

	Thread* LevelDefLoader::GetLoaderThread() const {
		return reinterpret_cast<Thread*>(&this->Get()->m_thread);
	}

	Mutex* LevelDefLoader::GetLoaderMutex() const {
		return reinterpret_cast<Mutex*>(&this->Get()->m_mutex);
	}

#endif
}
