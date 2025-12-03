#pragma once

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/corelib/containers/StaticArray.hpp>
#elif defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/corelib/containers/StaticArray.hpp>
#endif

#include "../memory/memory.hpp"

#include <Utility/assertion/assert.hpp>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <initializer_list>
#include <iterator>
#include <span>
#include <type_traits>

namespace NdGameSdk::corelib::containers {

	template<typename T>
	class NdGameSdk_API StaticArray : public ISdkRegenny<regenny::shared::corelib::containers::StaticArray> {
	public:
		using RawArray = regenny::shared::corelib::containers::StaticArray;
		using size_type = uint32_t;

		StaticArray() {
			Reset();
		}

		explicit StaticArray(size_type count,
			uint64_t alignment = alignof(T),
			const char* sourceFunc = __func__,
			uint32_t sourceLine = __LINE__,
			const char* sourceFile = __FILE__,
			corelib::memory::Memory::Context context = corelib::memory::Memory::Context::kAllocInvalid) {

			Reset();
			if (count != 0) {
				AllocateAndBind(count, alignment, sourceFunc, sourceLine, sourceFile, context);
			}
		}

		StaticArray(std::initializer_list<T> values,
			uint64_t alignment = alignof(T),
			const char* sourceFunc = __func__,
			uint32_t sourceLine = __LINE__,
			const char* sourceFile = __FILE__,
			corelib::memory::Memory::Context context = corelib::memory::Memory::Context::kAllocInvalid)
			: StaticArray(static_cast<size_type>(values.size()), alignment, sourceFunc, sourceLine, sourceFile, context) {
			if (!values.size()) {
				return;
			}
			std::copy(values.begin(), values.end(), Data());
		}

		explicit StaticArray(std::span<const T> values,
			uint64_t alignment = alignof(T),
			const char* sourceFunc = __func__,
			uint32_t sourceLine = __LINE__,
			const char* sourceFile = __FILE__,
			corelib::memory::Memory::Context context = corelib::memory::Memory::Context::kAllocInvalid)
			: StaticArray(static_cast<size_type>(values.size()), alignment, sourceFunc, sourceLine, sourceFile, context) {

			if (values.empty()) {
				return;
			}

			std::copy(values.begin(), values.end(), Data());
		}

		[[nodiscard]] T* Data() {
			return reinterpret_cast<T*>(this->Get()->m_data);
		}

		[[nodiscard]] const T* Data() const {
			return reinterpret_cast<const T*>(this->Get()->m_data);
		}

		void BindStorage(T* data, size_type count) {
			auto* raw = this->Get();
			raw->m_data = reinterpret_cast<void*>(data);
			raw->m_size = count;
		}

		void Reset() {
			auto* raw = this->Get();
			raw->m_data = nullptr;
			raw->m_size = 0;
		}

		[[nodiscard]] size_type Size() const {
			return this->Get()->m_size;
		}

		[[nodiscard]] bool IsEmpty() const {
			return Size() == 0;
		}

		T& operator[](size_type index) {
			const bool outOfRange = index >= Size();
			always_assert(outOfRange, "StaticArray::operator[] index out of range");

			auto* data = Data();
			const bool missingData = data == nullptr;
			always_assert(missingData, "StaticArray::operator[] data pointer is null");

			return data[index];
		}

		const T& operator[](size_type index) const {
			const bool outOfRange = index >= Size();
			always_assert(outOfRange, "StaticArray::operator[] index out of range");

			auto* data = Data();
			const bool missingData = data == nullptr;
			always_assert(missingData, "StaticArray::operator[] data pointer is null");

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
			always_assert(empty, "StaticArray::Front called on empty array");
			return (*this)[0];
		}

		const T& Front() const {
			const bool empty = IsEmpty();
			always_assert(empty, "StaticArray::Front called on empty array");
			return (*this)[0];
		}

		T& Back() {
			const bool empty = IsEmpty();
			always_assert(empty, "StaticArray::Back called on empty array");
			return (*this)[Size() - 1];
		}

		const T& Back() const {
			const bool empty = IsEmpty();
			always_assert(empty, "StaticArray::Back called on empty array");
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

		T* AllocateAndBind(size_type count,
			uint64_t alignment = alignof(T),
			const char* sourceFunc = __func__,
			uint32_t sourceLine = __LINE__,
			const char* sourceFile = __FILE__,
			corelib::memory::Memory::Context context = corelib::memory::Memory::Context::kAllocInvalid) {

			if (count == 0) {
				Reset();
				return nullptr;
			}

			auto& memory = corelib::memory::Memory::RequireInstance<corelib::memory::Memory>();

			const size_t requiredBytes = static_cast<size_t>(count) * sizeof(T);
			const bool overflow = count != 0 && requiredBytes / count != sizeof(T);
			always_assert(overflow, "StaticArray::AllocateAndBind size overflow");
			if (overflow) {
				return nullptr;
			}

			if (context != corelib::memory::Memory::Context::kAllocInvalid) {
				memory.PushAllocator(context, sourceFile, static_cast<int>(sourceLine), sourceFunc);
			}

			T* data = memory.Allocate<T>(requiredBytes, alignment, sourceFunc, static_cast<int>(sourceLine), sourceFile);

			if (context != corelib::memory::Memory::Context::kAllocInvalid) {
				memory.PopAllocator();
			}

			const bool allocationFailed = data == nullptr;
			always_assert(allocationFailed, "StaticArray::AllocateAndBind allocation failed");
			if (allocationFailed) {
				return nullptr;
			}

			BindStorage(data, count);
			return data;
		}

		void FreeStorage(const char* sourceFunc = __func__,
			uint32_t sourceLine = __LINE__,
			const char* sourceFile = __FILE__) {

			auto* data = Data();
			if (data != nullptr) {
				auto& memory = corelib::memory::Memory::RequireInstance<corelib::memory::Memory>();
				memory.Free(data, sourceFunc, static_cast<int>(sourceLine), sourceFile);
			}

			Reset();
		}

		static_assert(!std::is_reference_v<T>, "StaticArray element type cannot be a reference");
		static_assert(std::is_trivially_copyable_v<T>, "StaticArray expects trivially copyable element types (raw NDI storage)");
	};

}
