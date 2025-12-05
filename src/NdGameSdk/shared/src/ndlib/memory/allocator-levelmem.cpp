#include "allocator-levelmem.hpp"

namespace NdGameSdk::ndlib::memory {

#if defined(T2R)

	uint32_t LevelMemAllocator::GetBlockSize() const {
		return this->Get()->m_blockSize;
	}

	bool LevelMemAllocator::IsBlockAllocatorActive() const {
		return this->Get()->m_blockAllocatorActive;
	}

	bool LevelMemAllocator::IsUseCacheBlocks() const {
		return this->Get()->m_useCacheBlocks;
	}

	PackageMgrInternal* LevelMemAllocator::GetPackageMgr() {
		return reinterpret_cast<PackageMgrInternal*>(this->Get()->m_packageMgr);
	}

	LoadingHeap* LevelMemAllocator::GetLoadingHeap() {
		return reinterpret_cast<LoadingHeap*>(this->Get()->m_LoadingHeap);
	}

	Package* LevelMemAllocator::GetPackage() {
		return reinterpret_cast<Package*>(this->Get()->m_package);
	}

	uint64_t LevelMemAllocator::CacheBlock::GetBufferSize() const {
		return this->Get()->m_bufferSize;
	}

	uint64_t LevelMemAllocator::CacheBlock::GetBytesRequested() const {
		return this->Get()->m_bytesRequested;
	}

	uint64_t LevelMemAllocator::CacheBlock::GetBytesAccounted() const {
		return this->Get()->m_bytesAccounted;
	}

#endif

}
