#pragma once
#include <cstdint>
#include <bit>

namespace NdGameSdk::corelib::system {
	inline constexpr float s_ticksToSec = std::bit_cast<float>(0x2B5A740Eu);
}