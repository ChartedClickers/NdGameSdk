#pragma once
#include "NdGameSdk/sdk.hpp"

#include <NdGameSdk/shared/src/corelib/memory/memory.hpp>
#include <NdGameSdk/shared/src/corelib/job/job-system.hpp>
#include <NdGameSdk/shared/src/ndlib/io/package-mgr.hpp>
#include <NdGameSdk/shared/src/ndlib/io/package.hpp>
#include <NdGameSdk/shared/src/ndlib/io/loadingheap.hpp>

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/ndlib/memory/LevelMemAllocator.hpp>
#endif

#if defined(T2R)

namespace NdGameSdk::ndlib::memory {

	using namespace corelib::memory;
	using namespace corelib::job;
	using namespace ndlib::io;

	class NdGameSdk_API LevelMemAllocator : public ISdkRegenny<regenny::shared::ndlib::memory::LevelMemAllocator, Memory::Allocator> {
	public:
		struct CacheBlock : public ISdkRegenny<regenny::shared::ndlib::memory::LevelMemAllocator::CacheBlock> {

			template <typename T = void>
			T* GetBuffer() {
				return reinterpret_cast<T*>(this->Get()->m_pBuffer);
			}

			template <typename T = void>
			T* GetCursor() {
				return reinterpret_cast<T*>(this->Get()->m_pCursor);
			}

			uint64_t GetBufferSize() const;
			uint64_t GetBytesRequested() const;
			uint64_t GetBytesAccounted() const;
		};

		CacheBlock& GetCacheBlock(size_t index) {
			auto* raw = this->Get();
			always_assert(index >= NdJob::kMaxWorkerThreads, "LevelMemAllocator::GetCacheBlock index out of range");
			return *reinterpret_cast<CacheBlock*>(&raw->m_cacheBlock[index]);
		}

		uint32_t GetBlockSize() const;

		bool IsBlockAllocatorActive() const;
		bool IsUseCacheBlocks() const;

		PackageMgr* GetPackageMgr();
		LoadingHeap* GetLoadingHeap();
		Package* GetPackage();
	};

	static_assert(sizeof(LevelMemAllocator) - sizeof(Memory::Allocator) == 0x3F0, "LevelMemAllocator size mismatch");
	static_assert(sizeof(LevelMemAllocator::CacheBlock) == 0x28, "LevelMemAllocator::CacheBlock size mismatch");
	static_assert(sizeof(regenny::shared::ndlib::memory::LevelMemAllocator::m_cacheBlock) / sizeof(regenny::shared::ndlib::memory::LevelMemAllocator::CacheBlock) 
		== NdJob::kMaxWorkerThreads, "LevelMemAllocator::m_cacheBlock count mismatch");
}

#endif