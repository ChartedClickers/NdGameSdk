#pragma once

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/corelib/containers/ListArray.hpp>
#elif defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/corelib/containers/ListArray.hpp>
#endif

#include "../memory/memory.hpp"

#include <Utility/assertion/assert.hpp>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <functional>
#include <initializer_list>
#include <memory>
#include <span>
#include <type_traits>
#include <utility>

namespace NdGameSdk::corelib::containers {

	template<typename T>
	class NdGameSdk_API ListArray : public ISdkRegenny<regenny::shared::corelib::containers::ListArray> {
	public:
		using RawArray = regenny::shared::corelib::containers::ListArray;
		using size_type = uint32_t;

		ListArray() {
			Reset();
		}

		explicit ListArray(
			size_type capacity,
			uint64_t alignment = alignof(T),
			const char* sourceFunc = __func__,
			uint32_t sourceLine = __LINE__,
			const char* sourceFile = __FILE__,
			corelib::memory::Memory::Context context = corelib::memory::Memory::Context::kAllocInvalid) {

			Reset();
			if (capacity != 0) {
				Initialize(capacity, alignment, sourceFunc, sourceLine, sourceFile, context);
			}
		}

		ListArray(std::initializer_list<T> values,
			uint64_t alignment = alignof(T),
			const char* sourceFunc = __func__,
			uint32_t sourceLine = __LINE__,
			const char* sourceFile = __FILE__,
			corelib::memory::Memory::Context context = corelib::memory::Memory::Context::kAllocInvalid)
			: ListArray(static_cast<size_type>(values.size()), alignment, sourceFunc, sourceLine, sourceFile, context) {

			if (values.size() == 0) {
				return;
			}

			std::copy(values.begin(), values.end(), Data());
			this->Get()->m_size = static_cast<size_type>(values.size());
		}

		explicit ListArray(std::span<const T> values,
			uint64_t alignment = alignof(T),
			const char* sourceFunc = __func__,
			uint32_t sourceLine = __LINE__,
			const char* sourceFile = __FILE__,
			corelib::memory::Memory::Context context = corelib::memory::Memory::Context::kAllocInvalid)
			: ListArray(static_cast<size_type>(values.size()), alignment, sourceFunc, sourceLine, sourceFile, context) {

			if (values.empty()) {
				return;
			}

			std::copy(values.begin(), values.end(), Data());
			this->Get()->m_size = static_cast<size_type>(values.size());
		}

		[[nodiscard]] T* Data() {
			return reinterpret_cast<T*>(this->Get()->m_data);
		}

		[[nodiscard]] const T* Data() const {
			return reinterpret_cast<const T*>(this->Get()->m_data);
		}

		void BindStorage(T* data, size_type count, size_type capacity) {
			const bool exceeds = count > capacity;
			always_assert(exceeds, "ListArray::BindStorage count exceeds capacity");

			const bool missingData = (data == nullptr) && count != 0;
			always_assert(missingData, "ListArray::BindStorage data pointer is null while count > 0");

			auto* raw = this->Get();
			raw->m_data = reinterpret_cast<void*>(data);
			raw->m_capacity = capacity;
			raw->m_size = count;
		}

		void Reset() {
			auto* raw = this->Get();
			raw->m_data = nullptr;
			raw->m_size = 0;
			raw->m_capacity = 0;
		}

		[[nodiscard]] size_type Size() const {
			return this->Get()->m_size;
		}

		[[nodiscard]] size_type Capacity() const {
			return this->Get()->m_capacity;
		}

		[[nodiscard]] bool IsEmpty() const {
			return Size() == 0;
		}

		[[nodiscard]] bool IsFull() const {
			return Size() >= Capacity();
		}

		T& operator[](size_type index) {
			const bool outOfRange = index >= Size();
			always_assert(outOfRange, "ListArray::operator[] index out of range");

			auto* data = Data();
			const bool missingData = data == nullptr;
			always_assert(missingData, "ListArray::operator[] data pointer is null");

			return data[index];
		}

		const T& operator[](size_type index) const {
			const bool outOfRange = index >= Size();
			always_assert(outOfRange, "ListArray::operator[] index out of range");

			auto* data = Data();
			const bool missingData = data == nullptr;
			always_assert(missingData, "ListArray::operator[] data pointer is null");

			return data[index];
		}

		T& At(size_type index) {
			return (*this)[index];
		}

		const T& At(size_type index) const {
			return (*this)[index];
		}

		T& Front() {
			const bool empty = IsEmpty();
			always_assert(empty, "ListArray::Front called on empty list");
			return (*this)[0];
		}

		const T& Front() const {
			const bool empty = IsEmpty();
			always_assert(empty, "ListArray::Front called on empty list");
			return (*this)[0];
		}

		T& Back() {
			const bool empty = IsEmpty();
			always_assert(empty, "ListArray::Back called on empty list");
			return (*this)[Size() - 1];
		}

		const T& Back() const {
			const bool empty = IsEmpty();
			always_assert(empty, "ListArray::Back called on empty list");
			return (*this)[Size() - 1];
		}

		T* begin() {
			return Data();
		}

		const T* begin() const {
			return Data();
		}

		const T* cbegin() const {
			return begin();
		}

		T* end() {
			return Data() + static_cast<std::ptrdiff_t>(Size());
		}

		const T* end() const {
			return Data() + static_cast<std::ptrdiff_t>(Size());
		}

		const T* cend() const {
			return end();
		}

		[[nodiscard]] std::span<T> Span() {
			return { Data(), static_cast<std::size_t>(Size()) };
		}

		[[nodiscard]] std::span<const T> Span() const {
			return { Data(), static_cast<std::size_t>(Size()) };
		}

		T* PushBackSlot() {
			auto* raw = this->Get();

			const bool overflow = raw->m_size >= raw->m_capacity;
			always_assert(overflow, "ListArray::PushBackSlot capacity exhausted");
			if (overflow) {
				return nullptr;
			}

			auto* data = Data();
			const bool missingData = data == nullptr;
			always_assert(missingData, "ListArray::PushBackSlot data pointer is null");
			if (missingData) {
				return nullptr;
			}

			T* slot = std::addressof(data[raw->m_size]);
			*slot = T{};
			raw->m_size += 1;
			return slot;
		}

		bool PushBack(const T& value) {
			T* slot = PushBackSlot();
			if (slot == nullptr) {
				return false;
			}

			*slot = value;
			return true;
		}

		void PopBack() {
			auto* raw = this->Get();
			const bool empty = raw->m_size == 0;
			always_assert(empty, "ListArray::PopBack called on empty list");
			if (empty) {
				return;
			}

			auto* data = Data();
			const bool missingData = data == nullptr;
			always_assert(missingData, "ListArray::PopBack data pointer is null");
			if (missingData) {
				raw->m_size = 0;
				return;
			}

			raw->m_size -= 1;
		}

		void EraseAtOrdered(size_type index) {
			auto* raw = this->Get();
			const bool outOfRange = index >= raw->m_size;
			always_assert(outOfRange, "ListArray::EraseAtOrdered index out of range");
			if (outOfRange) {
				return;
			}

			auto* data = Data();
			const bool missingData = data == nullptr;
			always_assert(missingData, "ListArray::EraseAtOrdered data pointer is null");
			if (missingData) {
				raw->m_size = 0;
				return;
			}

			const size_type last = raw->m_size - 1;
			if (index < last) {
				std::memmove(&data[index], &data[index + 1], static_cast<std::size_t>(last - index) * sizeof(T));
			}
			raw->m_size = last;
		}

		T* EraseAt(T* element) {
			auto* raw = this->Get();
			T* data = Data();

			const bool invalid = element == nullptr || data == nullptr;
			always_assert(invalid, "ListArray::EraseAt element/data pointer invalid");
			if (invalid) {
				return nullptr;
			}

			const std::ptrdiff_t index = element - data;
			const bool outOfRange = index < 0 || static_cast<size_type>(index) >= raw->m_size;
			always_assert(outOfRange, "ListArray::EraseAt pointer out of range");
			if (outOfRange) {
				return nullptr;
			}

			const size_type erasedIndex = static_cast<size_type>(index);
			EraseAtOrdered(erasedIndex);

			if (erasedIndex < raw->m_size) {
				return &Data()[erasedIndex];
			}

			return Data() + raw->m_size;
		}

		template<typename Predicate>
		bool EraseFirstIf(Predicate&& pred) {
			auto* raw = this->Get();
			auto* data = Data();
			if (raw->m_size == 0 || data == nullptr) {
				return false;
			}

			for (size_type i = 0; i < raw->m_size; ++i) {
				if (std::invoke(std::forward<Predicate>(pred), data[i])) {
					EraseAtOrdered(i);
					return true;
				}
			}

			return false;
		}

		void Clear(bool zeroMemory = false) {
			auto* raw = this->Get();
			if (zeroMemory) {
				auto* data = Data();
				if (data != nullptr) {
					std::memset(data, 0, static_cast<std::size_t>(raw->m_capacity) * sizeof(T));
				}
			}
			raw->m_size = 0;
		}

		T* AllocateStorage(size_type capacity,
			uint64_t alignment = alignof(T),
			const char* sourceFunc = __func__,
			uint32_t sourceLine = __LINE__,
			const char* sourceFile = __FILE__,
			corelib::memory::Memory::Context context = corelib::memory::Memory::Context::kAllocInvalid) {

			auto* raw = this->Get();

			if (capacity == 0) {
				FreeStorage(false, sourceFunc, sourceLine, sourceFile);
				return nullptr;
			}

			auto& memory = corelib::memory::Memory::RequireInstance<corelib::memory::Memory>();

			const size_t elementSize = sizeof(T);
			const size_t bytes = static_cast<size_t>(capacity) * elementSize;
			const bool overflow = capacity != 0 && bytes / capacity != elementSize;
			always_assert(overflow, "ListArray::AllocateStorage size overflow");

			if (overflow) {
				return nullptr;
			}

			if (context != corelib::memory::Memory::Context::kAllocInvalid) {
				memory.PushAllocator(context, sourceFile, static_cast<int>(sourceLine), sourceFunc);
			}

			T* data = memory.Allocate<T>(bytes, alignment, sourceFunc, static_cast<int>(sourceLine), sourceFile);

			if (context != corelib::memory::Memory::Context::kAllocInvalid) {
				memory.PopAllocator();
			}

			const bool allocationFailed = data == nullptr && bytes != 0;
			always_assert(allocationFailed, "ListArray::AllocateStorage allocation failed");
			if (allocationFailed) {
				return nullptr;
			}

			raw->m_data = reinterpret_cast<void*>(data);
			raw->m_capacity = capacity;
			if (raw->m_size > capacity) {
				raw->m_size = capacity;
			}

			return data;
		}

		void FreeStorage(bool zeroMemoryBeforeFree = false,
			const char* sourceFunc = __func__,
			uint32_t sourceLine = __LINE__,
			const char* sourceFile = __FILE__) {

			auto* raw = this->Get();
			auto* data = Data();
			if (data != nullptr) {
				if (zeroMemoryBeforeFree) {
					std::memset(data, 0, static_cast<std::size_t>(raw->m_capacity) * sizeof(T));
				}

				auto& memory = corelib::memory::Memory::RequireInstance<corelib::memory::Memory>();
				memory.Free(data, sourceFunc, static_cast<int>(sourceLine), sourceFile);
			}

			raw->m_data = nullptr;
			raw->m_size = 0;
			raw->m_capacity = 0;
		}

		bool Initialize(size_type capacity,
			uint64_t alignment = alignof(T),
			const char* sourceFunc = __func__,
			uint32_t sourceLine = __LINE__,
			const char* sourceFile = __FILE__,
			corelib::memory::Memory::Context context = corelib::memory::Memory::Context::kAllocInvalid) {

			T* storage = AllocateStorage(capacity, alignment, sourceFunc, sourceLine, sourceFile, context);
			if (storage == nullptr && capacity != 0) {
				return false;
			}

			auto* raw = this->Get();
			raw->m_size = 0;
			return true;
		}

		void Detach() {
			auto* raw = this->Get();
			raw->m_data = nullptr;
			raw->m_size = 0;
			raw->m_capacity = 0;
		}

		static_assert(!std::is_reference_v<T>, "ListArray element type cannot be a reference");
		static_assert(std::is_trivially_copyable_v<T>, "ListArray expects trivially copyable element types (raw NDI storage)");
	};

}

