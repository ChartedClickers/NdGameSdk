#pragma once
#if defined(T1X)
#include "particle-debug.hpp"

namespace NdGameSdk::gamelib::render::particle
{
	namespace ParticleInternal
	{
		void* ParticleDebug::Constructor(void* allocator_) {
			always_assert(ParticleDebug_ParticleDebug == nullptr, "Function pointer was not set!");
			return ParticleDebug_ParticleDebug(allocator_);
		}

		void ParticleDebug::Init(void* allocator_) {
			always_assert(ParticleDebug_Init == nullptr, "Function pointer was not set!");
			ParticleDebug_Init((uint64_t*)allocator_);
		}
	}
}
#endif