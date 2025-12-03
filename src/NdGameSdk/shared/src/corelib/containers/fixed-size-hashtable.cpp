#include "fixed-size-hashtable.hpp"

namespace NdGameSdk::corelib::containers {

	namespace detail {

		uint32_t UpdatePeakFlagsOnInsert(uint32_t currentFlags, uint64_t newCount) {
			constexpr uint32_t peakMask = static_cast<uint32_t>(
				regenny::shared::corelib::containers::FixedSizeHashTable::Flags::PeakMask);

			const uint32_t baseFlags = currentFlags & ~peakMask;
			uint32_t peak = currentFlags & peakMask;

			if (newCount > peak) {
				const uint32_t clamped = newCount > peakMask ? peakMask
					: static_cast<uint32_t>(newCount);
				peak = clamped;
			}

			return baseFlags | peak;
		}
	}

}
