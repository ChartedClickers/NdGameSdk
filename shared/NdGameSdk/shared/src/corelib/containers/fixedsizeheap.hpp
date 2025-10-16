#pragma once

#if defined(T2R)  
#include <NdGameSdk/regenny/t2r/shared/corelib/containers/FixedSizeHeap.hpp>  
#elif defined(T1X)  
#include <NdGameSdk/regenny/t1x/shared/corelib/containers/FixedSizeHeap.hpp>  
#endif 

#include "../memory/memory.hpp"

#include <Utility/assertion/assert.hpp>
#include <Utility/function_ptr.hpp>

#include <limits>

namespace NdGameSdk::corelib::containers {

	class FixedSizeHeap;
	template<typename NodeT> class FixedSizeHashTable;

	namespace detail {
		struct ContainerMemoryAccess {
		private:
			static inline corelib::memory::Memory* s_memory{ nullptr };
			friend class ::NdGameSdk::corelib::containers::FixedSizeHeap;
			template<typename> friend class ::NdGameSdk::corelib::containers::FixedSizeHashTable;
			friend class NdGameSdk::corelib::memory::Memory;
		};
	}

    class NdGameSdk_API FixedSizeHeap : public ISdkRegenny<regenny::shared::corelib::containers::FixedSizeHeap> {
    public:
        FixedSizeHeap() = default;

        uint64_t Count() const;
        uint64_t GetLastIndex() const;

        template<typename T>
        void Init(uint64_t numElements, uint64_t elemSize, T* pDataBase,
            corelib::memory::Memory::Context* memContext, uint64_t alignment, HeapArena_Args) {
            always_assert(Memory_FixedSizeHeap_Init == nullptr, "Function pointer was not set!");
            always_assert(alignment == 0, "FixedSizeHeap::Init alignment must be non-zero");

            const uint64_t alignedElemSize = (elemSize + (alignment - 1)) & ~(alignment - 1);

            const bool overflow = numElements != 0 && alignedElemSize > (std::numeric_limits<uint64_t>::max)() / numElements;
            always_assert(overflow, "FixedSizeHeap::Init allocation size overflow");

            const uint64_t allocationSize = alignedElemSize * numElements;

            T* dataBase = pDataBase;
            if (dataBase == nullptr && allocationSize > 0) {
                if (memContext != nullptr && *memContext != corelib::memory::Memory::Context::kAllocInvalid) {
                    dataBase = detail::ContainerMemoryAccess::s_memory->AllocateAtContext<T*>(allocationSize, alignment, *memContext);
                }
                else {
                    dataBase = detail::ContainerMemoryAccess::s_memory->Allocate<T*>(allocationSize, alignment, source_func, static_cast<int>(source_line), source_file);
                }
            }

            Memory_FixedSizeHeap_Init(this, numElements, elemSize, dataBase, memContext, alignment, source_file, source_line, source_func);

        }

        template<typename T>
        T* AddIndex() {
            always_assert(Memory_FixedSizeHeap_AddIndex == nullptr, "Function pointer was not set!");
            T data = reinterpret_cast<T*>(Memory_FixedSizeHeap_AddIndex(this));
            return data;
        };

        template<typename T>
        int64_t FreeIndex(T* dataIn) {
			always_assert(Memory_FixedSizeHeap_FreeIndex == nullptr, "Function pointer was not set!");
			return Memory_FixedSizeHeap_FreeIndex(this, dataIn);
        };

        uint64_t Copy(FixedSizeHeap* srcHeap);
		uint64_t Reset();

        template<typename T>
        class TypedIterator {
        public:
            explicit TypedIterator(FixedSizeHeap* owner) : m_owner(owner) {}

            T* operator()(int64_t entryIndex, int64_t* outIndex) {
                return FixedSizeHeap::ElementAt<T>(m_owner, entryIndex, outIndex);
            }

        private:
            FixedSizeHeap* m_owner;
        };

        template<typename T>
        class TypedConstIterator {
        public:
            explicit TypedConstIterator(const FixedSizeHeap* owner)
                : m_owner(owner) {}

            const T* operator()(int64_t entryIndex, int64_t* outIndex) const {
                return FixedSizeHeap::ElementAt<const T>(
                    const_cast<FixedSizeHeap*>(m_owner), entryIndex, outIndex);
            }

        private:
            const FixedSizeHeap* m_owner;
        };

    private:
        template<typename U>
        static U* ElementAt(FixedSizeHeap* owner, int64_t entryIndex, int64_t* outIndex) {
            if (outIndex) *outIndex = entryIndex;
            auto raw = owner->Get();

            // bitmap test: [entryIndex>>6] >> (entryIndex&0x3F) & 1
            uint64_t idx = static_cast<uint64_t>(entryIndex);
            uint64_t qwordIx = idx >> 6;
            uint32_t bitPos = static_cast<uint32_t>(idx & 0x3F);
            uint64_t bitmap = raw->m_pUsage[qwordIx];
            always_assert(((bitmap >> bitPos) & 1) != 0,
                "FixedSizeHeap::ElementAt element not in use");

            // pointer math: base + idx * elementSize
            auto base = reinterpret_cast<uint8_t*>(raw->m_pData);
            return reinterpret_cast<U*>(base + idx * raw->m_elementSize);
        }

        TYPEDEF_FUNCTION_PTR(void, Memory_FixedSizeHeap_Init, FixedSizeHeap* Heap, uint64_t numElements, uint64_t elemSize,
            void* pDataBase, corelib::memory::Memory::Context* memContext, uint64_t alignment, const char* source_file, uint32_t source_line, const char* source_funct);
        TYPEDEF_FUNCTION_PTR(uint64_t, Memory_FixedSizeHeap_FreeIndex, FixedSizeHeap* Heap, void* dataIn);
        TYPEDEF_FUNCTION_PTR(uint64_t, Memory_FixedSizeHeap_Copy, FixedSizeHeap* Heap, FixedSizeHeap* srcHeap);
        TYPEDEF_FUNCTION_PTR(void*, Memory_FixedSizeHeap_AddIndex, FixedSizeHeap* Heap);
		friend class NdGameSdk::corelib::memory::Memory;
    };

    static_assert(sizeof(FixedSizeHeap) == 0x58, "Size of FixedSizeHeap is not correct.");

    //-----------------------------------------------------------------------------
    // Example usage:
    //----------------------------------------------------------------------------- 
    // FixedSizeHeap* heap = /* obtain wrapper instance */;
    // int64_t handle = heap->AddIndex<MyStruct>();
    // FixedSizeHeap::TypedIterator<MyStruct> iter(heap);
    // MyStruct* ptr = iter(handle, nullptr);
    // FixedSizeHeap::TypedConstIterator<MyStruct> citer(heap);
    // const MyStruct* cptr = citer(handle, nullptr);
    // void* rawPtr = FixedSizeHeap::TypedIterator<void>(heap)(handle, nullptr);
    //----------------------------------------------------------------------------- 
}
