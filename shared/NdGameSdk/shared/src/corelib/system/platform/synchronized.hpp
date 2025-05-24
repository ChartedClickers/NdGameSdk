#pragma once
#include <cstdint>
#include <bit>

namespace NdGameSdk::corelib::system::platform {

	inline constexpr float s_ticksToSec = std::bit_cast<float>(0x2B5A740Eu);

	static_assert(std::bit_cast<std::uint32_t>(s_ticksToSec) == 0x2B5A740Eu, "s_ticksToSec bit-pattern must match NDGame constant");
}