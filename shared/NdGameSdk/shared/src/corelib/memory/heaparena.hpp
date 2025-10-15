#pragma once

#include "NdGameSdk/sdk.hpp"
#include "memory-map.hpp"

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/corelib/memory/HeapArena.hpp>
#elif defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/corelib/memory/HeapArena.hpp>
#endif

#define HeapArena_Args const char* source_func, uint32_t source_line, const char* source_file
#define HeapArena_Source __func__, __LINE__, __FILE__

namespace NdGameSdk::corelib::memory {

	class NdGameSdk_API HeapArena : public ISdkRegenny<regenny::shared::corelib::memory::HeapArena> {
	public:
		template <typename T = void>
		T* GetMemory() {
			return reinterpret_cast<T*>(this->Get()->m_pMemory);
		}

		template <typename T = void>
		T* GetCurrent() {
			return reinterpret_cast<T*>(this->Get()->m_current);
		}

		MemSize GetSize() const {
			return MemSize(this->Get()->m_sizeFlags >> 2);
		}
	};

	static_assert(sizeof(HeapArena) == 0x50, "HeapArena size mismatch!");
}