#include "robinhood-hash-table.hpp"

#include <cstring>

namespace NdGameSdk::corelib::containers {

	namespace detail::robinhood {

		uint32_t NextOccupied(const OccMask& mask, uint32_t capacity, uint32_t startIndex) {

			if (mask.m_words == nullptr || mask.m_wordCount == 0) {
				return kInvalidIndex;
			}

			if (capacity == 0 || startIndex >= capacity) {
				return kInvalidIndex;
			}

			uint32_t wordIndex = startIndex / BitsPerWord;
			uint32_t bitOffset = startIndex % BitsPerWord;

			uint64_t word = mask.m_words[wordIndex];
			word &= (~0ULL) << bitOffset;

			while (true) {
				if (word != 0) {
					const uint32_t bit = static_cast<uint32_t>(std::countr_zero(word));
					const uint32_t index = wordIndex * BitsPerWord + bit;
					if (index < capacity) {
						return index;
					}
					return kInvalidIndex;
				}

				++wordIndex;
				if (wordIndex >= mask.m_wordCount) {
					break;
				}

				word = mask.m_words[wordIndex];
			}

			return kInvalidIndex;
		}

		void MarkOccupied(OccMask& mask, uint32_t index) {

			if (mask.m_words == nullptr || mask.m_wordCount == 0) {
				return;
			}

			const uint32_t word = index / BitsPerWord;
			if (word >= mask.m_wordCount) {
				return;
			}

			const uint32_t bit = index % BitsPerWord;
			mask.m_words[word] |= (uint64_t{ 1 } << bit);
		}

		void ClearOccupied(OccMask& mask, uint32_t index) {

			if (mask.m_words == nullptr || mask.m_wordCount == 0) {
				return;
			}

			const uint32_t word = index / BitsPerWord;
			if (word >= mask.m_wordCount) {
				return;
			}

			const uint32_t bit = index % BitsPerWord;
			mask.m_words[word] &= ~(uint64_t{ 1 } << bit);
		}

		void ZeroOccupancy(OccMask& mask) {
			if (mask.m_words == nullptr) {
				return;
			}

			if (mask.m_wordCount == 0) {
				*mask.m_words = 0;
				return;
			}

			std::memset(mask.m_words, 0, static_cast<size_t>(mask.m_wordCount) * sizeof(uint64_t));
		}
	}

}
