#pragma once
#include "NdGameSdk/components/SdkRegenny.hpp"  

#if defined(T2R)  
#include <NdGameSdk/regenny/t2r/shared/corelib/containers/FixedSizeHeap.hpp>  
#elif defined(T1X)  
#include <NdGameSdk/regenny/t1x/shared/corelib/containers/FixedSizeHeap.hpp>  
#endif 

#include <Utility/assertion/assert.hpp>
#include <Utility/function_ptr.hpp>

namespace NdGameSdk::corelib::containers
{
    class FixedSizeHeap;
    TYPEDEF_EXTERN_FUNCTION_PTR(uint64_t, FixedSizeHeap_FreeIndex, FixedSizeHeap* Heap, void* dataIn);
    TYPEDEF_EXTERN_FUNCTION_PTR(uint64_t, FixedSizeHeap_Copy, FixedSizeHeap* Heap, FixedSizeHeap* srcHeap);
    TYPEDEF_EXTERN_FUNCTION_PTR(void*, FixedSizeHeap_AddIndex, FixedSizeHeap* Heap);

    class NdGameSdk_API FixedSizeHeap : public ISdkRegenny<regenny::shared::corelib::containers::FixedSizeHeap>
    {
    public:
        FixedSizeHeap() = default;

        uint64_t Count() const;
        uint64_t GetLastIndex() const;


        template<typename T>
        T* AddIndex() {
            always_assert(FixedSizeHeap_AddIndex == nullptr, "Function pointer was not set!");
            T data = reinterpret_cast<T*>(FixedSizeHeap_AddIndex(this));
            return data;
        };

        template<typename T>
        int64_t FreeIndex(T* dataIn) {
			always_assert(FixedSizeHeap_FreeIndex == nullptr, "Function pointer was not set!");
			return FixedSizeHeap_FreeIndex(this, dataIn);
        };

        uint64_t Copy(FixedSizeHeap* srcHeap);

        /*static Init(struct FixedSizeHeap* heap, uint64_t arg2, int64_t arg3,
            int64_t arg4, int32_t* arg5, uint64_t arg6);*/

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
            uint64_t bitmap = raw->m_usage[qwordIx];
            always_assert(((bitmap >> bitPos) & 1) != 0,
                "FixedSizeHeap::ElementAt – element not in use");

            // pointer math: base + idx * elementSize
            auto base = reinterpret_cast<uint8_t*>(raw->m_data);
            return reinterpret_cast<U*>(base + idx * raw->m_elementSize);
        }

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