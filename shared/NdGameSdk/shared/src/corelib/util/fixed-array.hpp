#pragma once
#include <NdGameSdk/sdkregenny.hpp>

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/corelib/util/FixedArray.hpp>
#elif defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/corelib/util/FixedArray.hpp>
#endif

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <initializer_list>
#include <iterator>
#include <span>
#include <type_traits>
#include <utility>

#include <Utility/assertion/assert.hpp>

namespace NdGameSdk::corelib::util {

	namespace detail {
		// Internal raw structure for FixedArray
		template<typename T, uint32_t TCapacity>
		struct FixedArrayRaw {
			T m_items[TCapacity];
			uint32_t m_count;
		};
	}

	template<typename T, uint32_t TCapacity, typename TRaw = detail::FixedArrayRaw<T, TCapacity>>
	class NdGameSdk_API FixedArray : public ISdkRegenny<TRaw> {
	public:
		using RawArray = TRaw;
		using value_type = T;
		using size_type = uint32_t;
		using iterator = T*;
		using const_iterator = const T*;

		FixedArray() noexcept {
			Clear();
		}

		explicit FixedArray(std::initializer_list<T> values) noexcept {
			Clear();
			Assign(values.begin(), values.end());
		}

		explicit FixedArray(std::span<const T> values) noexcept {
			Clear();
			Assign(values.begin(), values.end());
		}

		[[nodiscard]] constexpr size_type Capacity() const noexcept {
			return kCapacity;
		}

		[[nodiscard]] size_type Size() const noexcept {
			return Raw()->m_count;
		}

		[[nodiscard]] bool IsEmpty() const noexcept {
			return Size() == 0;
		}

		[[nodiscard]] bool IsFull() const noexcept {
			return Size() >= kCapacity;
		}

		void Clear(bool zeroMemory = false) noexcept {
			if (zeroMemory) {
				std::memset(Data(), 0, sizeof(T) * kCapacity);
			}
			Raw()->m_count = 0;
		}

		T& operator[](size_type index) noexcept {
			return At(index);
		}

		const T& operator[](size_type index) const noexcept {
			return At(index);
		}

		T& At(size_type index) noexcept {
			const bool outOfRange = index >= Size();
			always_assert(outOfRange, "FixedArray::At index out of range");
			return Data()[index];
		}

		const T& At(size_type index) const noexcept {
			const bool outOfRange = index >= Size();
			always_assert(outOfRange, "FixedArray::At index out of range");
			return Data()[index];
		}

		T& Front() noexcept {
			const bool empty = IsEmpty();
			always_assert(empty, "FixedArray::Front called on empty array");
			return Data()[0];
		}

		const T& Front() const noexcept {
			const bool empty = IsEmpty();
			always_assert(empty, "FixedArray::Front called on empty array");
			return Data()[0];
		}

		T& Back() noexcept {
			const bool empty = IsEmpty();
			always_assert(empty, "FixedArray::Back called on empty array");
			return Data()[Size() - 1];
		}

		const T& Back() const noexcept {
			const bool empty = IsEmpty();
			always_assert(empty, "FixedArray::Back called on empty array");
			return Data()[Size() - 1];
		}

		T& back() noexcept {
			return Back();
		}

		const T& back() const noexcept {
			return Back();
		}

		void PushBack(const T& value) noexcept {
			const bool full = IsFull();
			always_assert(full, "FixedArray::PushBack capacity exhausted");
			Data()[Size()] = value;
			++Raw()->m_count;
		}

		void push_back(const T& value) noexcept {
			PushBack(value);
		}

		template<typename... TArgs>
		T& EmplaceBack(TArgs&&... args) noexcept(std::is_nothrow_constructible_v<T, TArgs...>) {
			const bool full = IsFull();
			always_assert(full, "FixedArray::EmplaceBack capacity exhausted");
			T* slot = &Data()[Size()];
			*slot = T(std::forward<TArgs>(args)...);
			++Raw()->m_count;
			return *slot;
		}

		template<typename... TArgs>
		T& emplace_back(TArgs&&... args) noexcept(std::is_nothrow_constructible_v<T, TArgs...>) {
			return EmplaceBack(std::forward<TArgs>(args)...);
		}

		void PopBack() noexcept {
			const bool empty = IsEmpty();
			always_assert(empty, "FixedArray::PopBack called on empty array");
			--Raw()->m_count;
		}

		void pop_back() noexcept {
			PopBack();
		}

		[[nodiscard]] T* Data() noexcept {
			return Raw()->m_items;
		}

		[[nodiscard]] const T* Data() const noexcept {
			return Raw()->m_items;
		}

		[[nodiscard]] iterator begin() noexcept {
			return Data();
		}

		[[nodiscard]] const_iterator begin() const noexcept {
			return Data();
		}

		[[nodiscard]] const_iterator cbegin() const noexcept {
			return begin();
		}

		[[nodiscard]] iterator end() noexcept {
			return Data() + static_cast<std::ptrdiff_t>(Size());
		}

		[[nodiscard]] const_iterator end() const noexcept {
			return Data() + static_cast<std::ptrdiff_t>(Size());
		}

		[[nodiscard]] const_iterator cend() const noexcept {
			return end();
		}

		[[nodiscard]] std::span<T> Span() noexcept {
			return { Data(), static_cast<std::size_t>(Size()) };
		}

		[[nodiscard]] std::span<const T> Span() const noexcept {
			return { Data(), static_cast<std::size_t>(Size()) };
		}

	private:
		RawArray* Raw() noexcept {
			return this->Get();
		}

		const RawArray* Raw() const noexcept {
			return this->Get();
		}

		template<typename Iterator>
		void Assign(Iterator first, Iterator last) noexcept {
			const size_type count = static_cast<size_type>(std::distance(first, last));
			const bool exceeds = count > kCapacity;
			always_assert(exceeds, "FixedArray::Assign source exceeds capacity");

			if (count == 0) {
				return;
			}

			std::copy(first, last, Data());
			Raw()->m_count = count;
		}

		static constexpr size_type kCapacity = TCapacity;
		static_assert(TCapacity > 0, "FixedArray capacity must be greater than zero");
		static_assert(!std::is_reference_v<T>, "FixedArray element type cannot be a reference");
		static_assert(std::is_trivially_copyable_v<T>, "FixedArray expects trivially copyable element types");

	};

}
