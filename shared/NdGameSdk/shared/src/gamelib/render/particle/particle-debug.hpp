#pragma once

#include "NdGameSdk/sdk.hpp"

#include <Windows.h>
#include <Utility/function_ptr.hpp>
#include <Utility/memory/Patch.hpp>

namespace NdGameSdk::gamelib::render::particle
{
	class ParticleManager;

	namespace ParticleInternal
	{
		class ParticleDebug {
		private:
			void* Constructor(void* allocator_);
			void Init(void* allocator_);

			uintptr_t* g_pParticleDebug{};

			Utility::memory::Patch::Ptr m_ParticleDebug_RenderUpdate{};

			friend class ParticleManager;
			MEMBER_FUNCTION_PTR(void, ParticleDebug_Init, uint64_t* pParticleDebug);
			MEMBER_FUNCTION_PTR(void*, ParticleDebug_ParticleDebug, void* allocator_);
		};
	}
}