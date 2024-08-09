#pragma once
#include "NdGameSdk/sdkpattern.hpp"

namespace NdGameSdk::Patterns
{
#if defined(T1X)
	static inline const SdkPattern EngineComponents_s_table = { L"48 89 6c 24 18 56 41 56 41 57 48 83 ec 30 8b f1 45 8b", +0x13 };
	static inline const SdkPattern EngineComponents_s_ndConfig = { L"B8 04 00 00 00 48 8D ?? ?? ?? ?? ?? 8D 50 7C C5 F8 10 03 C5 F8 11 01 C5 F8 10 4B 10 C5 F8 11 49 10 C5 F8 10 43 20 C5 F8 11 41 20 C5 F8 10 4B 30 C5 F8 11 49 30 C5 F8 10 43 40 C5 F8 11 41 40 C5 F8 10 4B 50 C5 F8 11 49 50 C5 F8 10 43 60 C5 F8 11 41 60", +0x5 };

	static inline const SdkPattern GameInit_ReturnHook = { L"83 23 00 48 83 63 08 00 48 83 C4 40 5B", +0x8 };
	static inline const SdkPattern GameInit_PrimServer_Create = { L"41 ff 90 ?? ?? ?? ?? 48 83 65 ?? 00 48 8d 05 ?? ?? ?? ??" };

	static inline const SdkPattern Memory_AllocateMemoryMap = { L"48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 41 56 41 57 48 83 EC 30 48 8B F2 8B F9 E8 ?? ?? ?? ?? 48 8B D6 8B", +0x42 };
	static inline const SdkPattern Memory_ValidateContext = { L"c7 44 24 20 27 00 00 00 48 8d 15", +0x1d };
	static inline const SdkPattern Memory_ModifyMemoryMap = { L"48 89 5c 24 08 48 89 6c 24 10 48 89 74 24 18 57 48 83 ec 30 48 b8 00 00 00 00 02 00 00 00 48 8b f2 8b e9 48 3b" };
	static inline const SdkPattern Memory_FindMemoryMap = { L"48 8B 05 ?? ?? ?? ?? 48 85 C0 74 ?? 83 38 00 74 ?? 39 08 74 ?? 48 83 C0 20 75 ?? 33" };
	static inline const SdkPattern Memory_GetSize = { L"48 83 EC 28 E8 ?? ?? ?? ?? 48 8B C8 33 C0 48 85 C9 74 ?? 48 8B 41 08 48 83 C4" };
	static inline const SdkPattern Memory_PushAllocator = { L"40 53 55 56 57 41 54 41 56 41 57 48 83 ec ?? 8b 01" };
	static inline const SdkPattern Memory_PopAllocator = { L"48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 30 E8 ?? ?? ?? ?? 33 DB 48 8B F8 48 85" };
	static inline const SdkPattern Memory_Allocate = { L"48 89 5c 24 08 57 48 83 ec 30 8b 02 48 8b f9 48 8d 4c 24 60 89 44 24 60 49 8b d8 ?? ?? ?? ??" };
	static inline const SdkPattern Memory_GetAllocator = { L"48 83 ec 28 8b 01 83 f8 70" };
	static inline const SdkPattern Memory_HeapAllocator_Allocate = { L"48 89 5c 24 ?? 48 89 6c 24 ?? 48 89 74 24 ?? 57 48 83 ec 30 48 85 c9 bf 01 00 00 00 41 8b f1 49 8b e8 48 0f 45 f9 48 8b da e8 ?? ?? 00 00 84 c0 ??" };

	static inline const SdkPattern Memory_clarg_nodebugmem = { L"b3 01 45 85 ff 74 ?? 48 8b 0f", +0x1 };
	static inline const SdkPattern Memory_s_MemoryMap = { L"01 00 00 00 02 00 00 00 00 00 ?? 00 00 00 00 00 00 00 10 00" };
	static inline const SdkPattern Memory_g_pMemoryMap = { L"48 89 5c 24 08 48 89 74 24 10 57 48 83 ec 30 48 ?? ?? ?? ?? ?? 04 00 48 8b", +0xf };

	static inline const SdkPattern NdDevMenu_GameConfig_DevMode = { L"8a 8f ?? ?? ?? ?? 84 c9 0f 94 c2 84 c9 0f 95 c1" };
	static inline const SdkPattern NdDevMenu_NdDevMenuAppend_Particles = { L"40 56 48 83 ec 30 48 8b f1 33 c9 e8 ?? ?? ?? ?? 84 c0 0f 84 ?? ?? ?? ?? 48 89 5c 24 40 4c 8d 0d ?? ?? ?? ??" };

	static inline const SdkPattern NdDevMenu_Assert_UpdateSelectRegionByNameMenu = { L"cc 48 85 db 74 ?? 33 c9 ff d3 48 8d 05 ?? ?? ?? ?? c7 44 24 ?? 10 00 00 00 41 b9 8e 00 00 00" };
	static inline const SdkPattern NdDevMenu_Assert_UpdateSelectIgcByNameMenu = { L"cc 48 85 db 74 ?? 33 c9 ff d3 48 8d 05 ?? ?? ?? ?? bb 10 00 00 00 41 b9 84 03 00 00" };
	static inline const SdkPattern NdDevMenu_Assert_UpdateSelectSpawnerByNameMenu = { L"cc 48 85 db 74 ?? 33 c9 ff d3 48 8d 05 ?? ?? ?? ?? c7 44 24 ?? 10 00 00 00 41 b9 a3 00 00 00" };

	static inline const SdkPattern Particle_ParticleManager_Init = { L"48 8b c4 48 89 58 18 48 89 48 08 55 56 57 41 54 41 55 41 56 41 57 48 8d 68 a8 48 81 ec 20 01 00 00 4c 8d ?? ?? ?? ?? 00 c5 f8 29 70 b8 41 bd 36 00 00" };
	static inline const SdkPattern Particle_ParticleInternal_ParticleDebug = { L"48 8d ?? ?? ?? ?? ?? e8 ?? ?? ?? ?? 4c 8b c3 48 8d ?? ?? ?? ?? ?? 48 8b d5 e8 ?? ?? ?? ?? 48 8d ?? ?? ?? ?? ?? 48 89 7c 24" };
	static inline const SdkPattern Particle_ParticleInternal_ParticleDebug_Init = { L"48 89 5c 24 10 48 89 6c 24 18 48 89 74 24 20 57 41 54 41 55 41 56 41 57 48 83 ec 50 48 8d ?? ?? ?? ?? ?? 4c 8b f1 48 89 ?? ?? ?? 80 00 00 00 48 8d ?? ?? ?? ?? ?? 48 89 41 28 b9 00 2d" };
	static inline const SdkPattern Particle_ParticleInternal_ParticleDebug_Constructor = { L"33 d2 b8 11 c0 00 00 66 89 41 18 48 8b c1 89 51 04 89 51 20 66 89 51 24 88 51 26 48 89 51 30 48 89 51 38 48 89 51 40 48 89 51 50 48 89 51 58 48 89 51 60 48 89 51 68 48 89 51 70 48 89 51 78 48 89 91 80 00 00 00 48 89 91 88 00 00 00 48 89 91 90 00 00 00 48 89 91 98 00 00 00 48 89 91 a0 00 00 00 48 89 91 a8 00 00 00 48" };
	static inline const SdkPattern Particle_ParticleInternal_RenderUpdate = { L"4c 8b dc 53 56 48 81 ec a8 00 00 00 48 8b ?? ?? ?? ?? 02 48 33 c4 48 89 84 24 88 00 00 00 4c 8b 0a 48 8b f2 48 8b d9 4d 85" };
	static inline const SdkPattern Particle_ParticleInternal_OnExecuteRootDataSelector = { L"40 53 55 56 57 41 55 48 81 ec 30 01 00 00 48 ?? ?? ?? ?? ?? 02 48 33 c4 48 89 84 24 20 01 00 00 8b da c7 44 24 38 10 00 00 00 48 8b" };


	static inline const SdkPattern PrimServer_PrimServer = { L"48 8b ?? ?? ?? ?? ?? 48 8b d3 4c 8b 01 41 ff 90 b0 01 00 00 48 83 65 08" };
	static inline const SdkPattern PrimServer_Create = { L"40 53 48 83 ec 30 48 8d 0d ?? ?? ?? ?? 48 8b da 48 8d 05 ?? ?? ?? ?? 48 8b d1 41 b9 60 0d 00 00" };


#endif
}