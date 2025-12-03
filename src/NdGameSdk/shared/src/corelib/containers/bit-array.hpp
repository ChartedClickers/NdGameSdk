#pragma once

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/corelib/containers/BitArray.hpp>
#elif defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/corelib/containers/BitArray.hpp>
#endif

#include "../memory/memory.hpp"

#include <Utility/assertion/assert.hpp>

#include <algorithm>
#include <bit>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <functional>
#include <limits>
#include <type_traits>
#include <utility>

namespace NdGameSdk::corelib::containers {

	template<std::size_t NumBits>
	class NdGameSdk_API BitArray : public ISdkRegenny<regenny::shared::corelib::containers::BitArray> {
	public:
		using RawArray = regenny::shared::corelib::containers::BitArray;
		using word_type = uint64_t;

		static constexpr std::size_t kBitsPerWord = 64;
		static constexpr std::size_t kBitCount = NumBits;
		static constexpr std::size_t kWordCount = (kBitCount + (kBitsPerWord - 1)) / kBitsPerWord;

		BitArray() {
			ResetAll();
		}

		explicit BitArray(bool value) {
			AssignAll(value);
		}

		static BitArray CreateFilled(bool value) {
			BitArray out{};
			out.AssignAll(value);
			return out;
		}

		static BitArray CreateFromWords(const word_type (&words)[kWordCount]) {
			BitArray out{};
			std::memcpy(out.Words(), words, sizeof(words));
			out.MaskUnusedBits();
			return out;
		}

		[[nodiscard]] static constexpr std::size_t BitCount() {
			return kBitCount;
		}

		[[nodiscard]] static constexpr std::size_t WordCount() {
			return kWordCount;
		}

		[[nodiscard]] word_type* Words() {
			return reinterpret_cast<word_type*>(this->Get()->m_bits);
		}

		[[nodiscard]] const word_type* Words() const {
			return reinterpret_cast<const word_type*>(this->Get()->m_bits);
		}

		void ResetAll() {
			std::fill_n(Words(), kWordCount, word_type{ 0 });
		}

		void SetAll() {
			std::fill_n(Words(), kWordCount, (std::numeric_limits<word_type>::max)());
			MaskUnusedBits();
		}

		void AssignAll(bool value) {
			if (value) {
				SetAll();
			} else {
				ResetAll();
			}
		}

		void SetBit(std::size_t bit) {
			auto [index, mask] = Locate(bit);
			auto* words = Words();
			words[index] |= mask;
		}

		void ResetBit(std::size_t bit) {
			auto [index, mask] = Locate(bit);
			auto* words = Words();
			words[index] &= ~mask;
		}

		void AssignBit(std::size_t bit, bool value) {
			if (value) {
				SetBit(bit);
			} else {
				ResetBit(bit);
			}
		}

		[[nodiscard]] bool TestBit(std::size_t bit) const {
			auto [index, mask] = Locate(bit);
			const auto* words = Words();

			word_type value = words[index];
			if constexpr (HasPartialLastWord()) {
				if (index == kWordCount - 1) {
					value &= kLastWordMask;
				}
			}

			return (value & mask) != 0;
		}

		[[nodiscard]] bool Any() const {
			const auto* words = Words();
			for (std::size_t i = 0; i < kWordCount; ++i) {
				word_type word = words[i];
				if constexpr (HasPartialLastWord()) {
					if (i == kWordCount - 1) {
						word &= kLastWordMask;
					}
				}

				if (word != 0) {
					return true;
				}
			}
			return false;
		}

		[[nodiscard]] bool None() const {
			return !Any();
		}

		[[nodiscard]] bool All() const {
			const auto* words = Words();
			for (std::size_t i = 0; i + 1 < kWordCount; ++i) {
				if (words[i] != (std::numeric_limits<word_type>::max)()) {
					return false;
				}
			}

			if constexpr (HasPartialLastWord()) {
				return (words[kWordCount - 1] & kLastWordMask) == kLastWordMask;
			} else {
				return words[kWordCount - 1] == (std::numeric_limits<word_type>::max)();
			}
		}

		[[nodiscard]] std::size_t CountBits() const {
			const auto* words = Words();
			std::size_t total = 0;
			for (std::size_t i = 0; i < kWordCount; ++i) {
				word_type word = words[i];
				if constexpr (HasPartialLastWord()) {
					if (i == kWordCount - 1) {
						word &= kLastWordMask;
					}
				}
				total += static_cast<std::size_t>(std::popcount(word));
			}
			return total;
		}

		template<typename Fn>
		void ForEachSetBit(Fn&& fn) const {
			const auto* words = Words();
			for (std::size_t wordIndex = 0; wordIndex < kWordCount; ++wordIndex) {
				word_type word = words[wordIndex];
				if constexpr (HasPartialLastWord()) {
					if (wordIndex == kWordCount - 1) {
						word &= kLastWordMask;
					}
				}

				while (word != 0) {
					const unsigned long bitOffset = static_cast<unsigned long>(std::countr_zero(word));
					const std::size_t bit = wordIndex * kBitsPerWord + static_cast<std::size_t>(bitOffset);
					std::invoke(std::forward<Fn>(fn), bit);
					word &= word - 1;
				}
			}
		}

	private:
		static constexpr bool HasPartialLastWord() {
			return (kBitCount % kBitsPerWord) != 0;
		}

		static constexpr word_type ComputeLastMask() {
			if constexpr (HasPartialLastWord()) {
				const std::size_t used = kBitCount % kBitsPerWord;
				return (word_type{ 1 } << used) - 1;
			} else {
				return (std::numeric_limits<word_type>::max)();
			}
		}

		static constexpr word_type kLastWordMask = ComputeLastMask();

		static std::pair<std::size_t, word_type> Locate(std::size_t bit) {
			const bool outOfRange = bit >= kBitCount;
			always_assert(outOfRange, "BitArray::Locate bit index out of range");
			if (outOfRange) {
				return { 0, word_type{ 0 } };
			}

			const std::size_t wordIndex = bit / kBitsPerWord;
			const std::size_t bitOffset = bit % kBitsPerWord;
			return { wordIndex, word_type{ 1 } << bitOffset };
		}

		void MaskUnusedBits() {
			if constexpr (HasPartialLastWord()) {
				auto* words = Words();
				words[kWordCount - 1] &= kLastWordMask;
			}
		}

		static_assert(kBitCount > 0, "BitArray requires at least one bit");
		static_assert(kWordCount > 0, "BitArray word count must be positive");
	};

}
