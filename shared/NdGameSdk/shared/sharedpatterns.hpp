#pragma once
#include "NdGameSdk/sdkpattern.hpp"

namespace NdGameSdk::Patterns
{

#if defined(T2R)
	static inline const SdkPattern EngineComponents_s_table = { L"48 89 74 24 20 41 54 41 56 41 57 48 83 ec 30 8b f1 45 8b f8 4c 8d 25 ?? ?? ?? ?? 4c 8b f2 48 85 d2 0f 84 ?? ?? ?? ??", +0x14 };
	static inline const SdkPattern EngineComponents_s_ndConfig = { L"48 8d 0d ?? ?? ?? ?? b8 04 00 00 00 48 8d 89 80 00 00 00 c5 f8 10 03 48 8d 9b 80 00 00 00 c5 f8 11 41 80 c5 f8 10 4b 90 c5 f8 11 49 90 c5 f8 10 43 a0 c5 f8 11 41 a0 c5 f8 10 4b b0 c5 f8 11 49 b0 c5 f8 10 43 c0 c5 f8 11 41 c0 c5 f8 10 4b d0 c5 f8 11 49" };

	static inline const SdkPattern GameInit_ReturnHook = { L"40 53 48 83 ec 30 48 8b d9 48 8d 4c 24 20 e8 ?? ?? ?? ?? 8b 10 85 d2 7e 11 c5 f8 10 00 c5 f8 11 03 48 8b c3 48 83 c4 30 5b c3", +0x13 };
	
	static inline const SdkPattern IAllocator_Init = { L"48 89 5c 24 10 55 56 57 41 54 41 55 41 56 41 57 48 8b ec 48 83 ec 50 4c 63 f9 4c 8b f2 33 c9 e8 ?? ?? ?? ?? 84 c0 c7 45 40 07 00 00 00 48 8d 3d ?? ?? ?? ?? 48 8d 1d ?? ?? ?? ?? 48 8d 15 ?? ?? ?? ?? 48 0f 45 df 48 8d 4d 40" };
	static inline const SdkPattern IAllocator_s_TaggedGpuDevHeap = { L"48 83 ec 28 48 8d 15 ?? ?? ?? ?? 48 8d 0d ?? ?? ?? ?? e8 ?? ?? ?? ?? 48 8d 0d ?? ?? ?? ?? 48 83 c4 28 e9 ?? ?? ?? ?? cc cc cc cc cc cc cc cc cc 48 83 ec 28 48 8d 0d ?? ?? ?? ?? e8 ?? ?? ?? ?? 48 8d 0d ?? ?? ?? ?? 48 83 c4 28 e9 ?? ?? ?? ?? 48 83 ec 28 48 8d 0d ?? ?? ?? ?? e8 ?? ?? ?? ?? 48 8d 0d ?? ?? ?? ?? 48 83 c4 28 e9 ?? ?? ?? ??", +0x54 };

	static inline const SdkPattern NIXXES_StdHandle = { L"40 53 48 83 ec 20 48 8b 01 48 8b d9 ff 50 20 48 8b 03 48 8b cb ff 50 30 48 8b c8 48 8d 15 ?? ?? ?? ?? e8 ?? ?? ?? ??" };

	static inline const SdkPattern Memory_AllocateMemoryMap = { L"48 83 ec 58 48 89 5c 24 60 48 89 6c 24 68 48 89 7c 24 50 4c 89 6c 24 40 4c 89 74 24 38 4c 8b f2 4c 63 e9 48 8d 15 ?? ?? ?? ?? 48 8d 0d ?? ?? ?? ?? 4c 89 7c 24 30", +0xaa };
	static inline const SdkPattern Memory_ValidateContext = { L"4c 89 6c 24 28 4c 8d 0d ?? ?? ?? ?? 4c 8d 05 ?? ?? ?? ?? c7 44 24 20 27 00 00 00 48 8d", +0x30 };
	static inline const SdkPattern Memory_ModifyMemoryMap = { L"48 89 5c 24 18 48 89 74 24 20 57 48 83 ec 30 48 b8 00 00 00 00 02 00 00 00 48 8b fa 8b f1 48 3b d0 0f 82 a9 00 00 00 48 89 6c 24 40" };
	static inline const SdkPattern Memory_GetSize = { L"48 8b 05 ?? ?? ?? ?? 48 85 c0 74 14 0f 1f 40 00 8b 10 85 d2 74 0a 3b d1 74 09 48 83 c0 20 75 f0 33 c0 c3 48 8b 40 08 c3" };
	static inline const SdkPattern Memory_PushAllocator = { L"48 89 5c 24 08 48 89 6c 24 10 56 57 41 54 41 56 41 57 48 83 ec 30 8b 01 48 8b d9 48 8d 4c 24 70 89 44 24 70 49 8b e9 45 8b f0 4c 8b fa" };
	static inline const SdkPattern Memory_PopAllocator = { L"48 89 5c 24 08 48 89 74 24 10 57 48 83 ec 30 e8 ?? ?? ?? ?? 33 f6 48 8b d8 48 85 c0 75 6d e8 ?? ?? ?? ?? 48 8b f8 48 85 c0 74 04" };
	static inline const SdkPattern Memory_HeapAllocator_Allocate = { L"40 53 55 56 57 41 56 48 83 ec 40 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 44 24 38 4c 8b b4 24 90 00 00 00 48 85 c9 bf 01 00 00 00 41 8b e9 48 0f 45 f9 49 8b f0 48 8b da e8 ?? ?? ?? ?? 84 c0 74 31 48 8d 54 24 30 b9 03 00 00 00 e8 ?? ?? ?? ?? 48 8b 4c 24 30 4c 8b ce 4c 89 74 24 28 4c 8b c3 48 8b d7 89 6c 24 20 48 8b 01 ff 50 38 e9 9a 00 00 00" };
	static inline const SdkPattern Memory_GetAllocator = { L"48 83 ec 28 8b 01 83 f8 73 75 1e e8 ?? ?? ?? ?? 48 8b 0d ?? ?? ?? ??" };

	static inline const SdkPattern Memory_Area_clargnodebugmem = { L"40 b7 01 85 db 0f ?? 7d 00 00 00 8b eb", +0x2 };
	static inline const SdkPattern Memory_Area_bAllocateGpuVm = { L"48 8d 0d ?? ?? ?? ?? e8 ?? ?? ?? ?? e8 ?? ?? ?? ?? 48 8b 54 24 28 4c 8d 0d ?? ?? ?? ?? 45 33 c0 48 8d 0d ?? ?? ?? ?? e8 ?? ?? ?? ?? 0f b6 9c 24 f8 00 00 00 48 8d 0d ?? ?? ?? ?? 0f b6 d3 e8 ?? ?? ?? ?? 48 8d 0d ?? ?? ?? ?? e8 ?? ?? ?? ?? 48 8b 54 24 30 4c 8d 0d ?? ?? ?? ?? 45 33 c0 48 89 05 ?? ?? ?? ?? 48 8d 0d", +0x1e4 };

	static inline const SdkPattern Memory_TaggedHeap_SetTaggedGpuDevHeap = { L"8b 07 48 8d 0d ?? ?? ?? ?? 48 8b 5c 24 40 48 89 34 c1 48 8b 74 24 48 48 83 c4 30 5f c3 cc cc 48 89 0d ?? ?? ?? ?? c3 cc cc cc cc cc cc cc cc 48 89 0d ?? ?? ?? ?? c3 cc cc cc cc cc cc cc cc 48 89 0d ?? ?? ?? ?? c3 cc cc cc cc cc cc cc cc 48 89 0d ?? ?? ?? ?? c3", +0x3f };

	static inline const SdkPattern Memory_g_MemoryMap = { L"48 89 5c 24 18 56 48 83 ec 30 48 83 3d ?? ?? ?? ?? 00 48 8b f2 48 89 6c 24 40 48 8b e9", +0xa };
	static inline const SdkPattern Memory_TaggedHeap_TaggedGpuDevHeap = { L"8b 07 48 8d 0d ?? ?? ?? ?? 48 8b 5c 24 40 48 89 34 c1 48 8b 74 24 48 48 83 c4 30 5f c3 cc cc 48 89 0d ?? ?? ?? ?? c3 cc cc cc cc cc cc cc cc 48 89 0d ?? ?? ?? ?? c3 cc cc cc cc cc cc cc cc 48 89 0d ?? ?? ?? ?? c3 cc cc cc cc cc cc cc cc 48 89 0d ?? ?? ?? ?? c3", +0x3F };


	static inline const SdkPattern NdDevMenu_NdDevMenuAppend_Particles = { L"48 89 5c 24 08 48 89 74 24 10 57 48 83 ec 40 48 8b f1 33 c9 e8 ?? ?? ?? ?? 84 c0 0f 84 9d" };

#elif defined(T1X)
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

	static inline const SdkPattern Memory_Area_clargnodebugmem = { L"b3 01 45 85 ff 74 ?? 48 8b 0f", +0x1 };

	static inline const SdkPattern Memory_g_MemoryMap = { L"48 89 5c 24 08 48 89 74 24 10 57 48 83 ec 30 48 ?? ?? ?? ?? ?? 04 00 48 8b", +0xf };

	static inline const SdkPattern ScriptManager_ScriptGlobals = { L"48 89 5c 24 08 48 89 74 24 10 57 48 83 ec 20 48 8b d9 48 63 fa 48 ?? ?? ?? ?? ?? ?? 45 33 c9 4c 89 49", +0x15 };

	static inline const SdkPattern ScriptManager_AddModuleRequest = { L"48 8b c4 48 89 58 08 48 89 70 10 48 89 78 18 4c 89 60 20 55 41 56 41 57 48 8d a8 28 fc ff ff 48 81 ec c0 04 00 00 48 ?? ?? ?? ?? ?? ?? 48 33 c4 48 89 85 b0 03 00 00 48" };
	static inline const SdkPattern ScriptManager_ReloadModule = { L"48 8b c4 48 89 58 08 48 89 70 10 48 89 78 18 55 41 54 41 55 41 56 41 57 48 8d a8 f8 f9 ff ff 48 81 ec e0 06 00 00 c5 f8 29 70 c8 48 ?? ?? ?? ?? ?? ?? 48 33 c4 48 89 85 c0 05 00" };
	static inline const SdkPattern ScriptManager_IsLoadModule = { L"48 8b c4 48 89 58 08 48 89 70 10 48 89 78 18 55 48 8d 68 a1 48 81 ec c0 00 00 00 48 ?? ?? ?? ?? ?? ?? 48 33 c4 48 89 45 47 c5 f9 ef" };

	static inline const SdkPattern NdDevMenu_GameConfig_DevMode = { L"8a 8f ?? ?? ?? ?? 84 c9 0f 94 c2 84 c9 0f 95 c1" };
	static inline const SdkPattern NdDevMenu_NdDevMenuAppend_Particles = { L"40 56 48 83 ec 30 48 8b f1 33 c9 e8 ?? ?? ?? ?? 84 c0 0f 84 ?? ?? ?? ?? 48 89 5c 24 40 4c 8d 0d ?? ?? ?? ??" };

	static inline const SdkPattern NdDevMenu_DMENU_Component = { L"40 53 57 41 57 48 83 ec 30 45 33 ff c7 41 68 c8 c8 c8 ff 4c 89 b9 80 00 00 00 48 ?? ?? ?? ?? 56 02 48 ?? ?? ?? ?? da 4c 89 79 30 48 8b f9 44 89 79 4e 4c 89 79 38 4c 89" };
	static inline const SdkPattern NdDevMenu_DMENU_MenuGroup = { L"48 89 5c 24 08 57 48 83 ec 20 41 8b d8 48 8b f9 e8 ?? ?? ?? ?? 88 9f a0 00 00 00 48 ?? ?? ?? ?? 56 02 33 db 48 ?? ?? ?? ?? 9f c8 00 00 00 b9 00 10 00 00 48 89 9f 20 03 00 00 48 89 9f 28 03 00 00 48 89 9f a8 00 00 00 48 89 9f b0 00 00 00" };
	static inline const SdkPattern NdDevMenu_DMENU_Menu = { L"48 89 5c 24 08 57 48 83 ec 20 41 8b d8 48 8b f9 e8 ?? ?? ?? ?? 48 ?? ?? ?? ?? 56 02 89 9f b8 00 00 00 48 ?? ?? ?? ?? 48 ?? ?? ?? ?? 48 89 87 a0 00 00 00 89 87 a8 00 00 00 48 89 87 b0 00 00 00 88 87 bc 00 00 00 48" };
	static inline const SdkPattern NdDevMenu_DMENU_ItemLine = { L"33 c0 c7 41 68 c8 c8 c8 ff 48 89 41 30 89 41 4e 48 89 41 38 48 89 41 40 89 41 48" };
	static inline const SdkPattern NdDevMenu_DMENU_ItemSubText = { L"48 89 5c 24 08 57 48 83 ec 20 48 8b da 48 8b f9 e8 ?? ?? ?? ?? 33 c0 48 89 9f b0 00 00 00 48 8b 5c 24 30 48 89 87 a0 00 00 00 48 89 47 60 48 89 87 80 00 00 00" };
	static inline const SdkPattern NdDevMenu_DMENU_ItemSubmenu = { L"48 89 5c 24 08 48 89 74 24 10 57 48 83 ec 20 49 8b d9 49 8b f0 48 8b f9 e8 ?? ?? ?? ?? 48 8b 44 24 50 33 c9 48 89 47 60 48 8b 44 24 58" };
	static inline const SdkPattern NdDevMenu_DMENU_ItemBool = { L"48 89 5c 24 08 48 89 74 24 10 57 48 83 ec 20 49 8b d9 49 8b f8 48 8b f1 e8 ?? ?? ?? ?? 33 c9 48 89 9e 80 00 00 00 48 8b 5c 24 30 48 8d 05 ?? ?? ?? ?? 48 89 06 48 8d 05 ?? ?? ?? ?? 48 89 86 b0 00 00 00 48 89 8e a0 00 00 00 48 89 4e 60 c7 86 a8 00 00 00 03 00 00 00 0f b6 07 88 86 b8 00 00 00 48 8b c6 48 89 7e 60 48 89 4e 58 c7 86 a0 00 00 00 01 00 00 00 48 8b 74 24 38 48 83 c4 20 5f c3" };
	static inline const SdkPattern NdDevMenu_DMENU_ItemDecimal = { L"48 89 5c 24 08 48 89 74 24 10 57 48 83 ec 20 49 8b f9 49 8b d8 48 8b f1 e8 ?? ?? ?? ?? 48 8b 44 24 58 33 c9 66 c7 86 b0 00 00 00 00 07" };
	static inline const SdkPattern NdDevMenu_DMENU_ItemFloat = { L"48 89 5c 24 08 48 89 74 24 10 57 48 83 ec 20 49 8b f9 49 8b d8 48 8b f1 e8 ?? ?? ?? ?? 48 8b 44 24 58 33 c9 48 89 8e 00 01 00 00 48 89 8e 08 01 00 00 48 89 86 80 00 00 00" };
	static inline const SdkPattern NdDevMenu_DMENU_ItemFunction = { L"48 89 5c 24 08 48 89 74 24 10 57 48 83 ec 20 49 8b d9 49 8b f8 48 8b f1 e8 ?? ?? ?? ?? 33 c9 48 89 5e 60 48 8b 5c 24 30 48 8d 05 ?? ?? ?? ?? 48 89 06 0f b6 44 24 50 88 86 c1 00 00 00 48 8b c6 48 89 8e a0 00 00 00 c7 86 a8 00 00 00 05 00 00 00" };
	static inline const SdkPattern NdDevMenu_DMENU_ItemSelection = { L"48 89 5c 24 08 48 89 74 24 10 57 48 83 ec 20 49 8b d9 49 8b f8 48 8b f1 e8 ?? ?? ?? ?? 8b 44 24 68 33 c9 89 86 a0 00 00 00 48 8b 44 24 70 48 89 86 80 00 00 00" };

	static inline const SdkPattern NdDevMenu_DMENU_MenuGroup_SetRootMenu = { L"48 85 d2 0f ?? ?? ?? ?? 00 48 89 5c 24 08 57 48 83 ec 20 48 8b 81 b0 00 00 00 48 8b da 48 8b f9 48 3b" };
	static inline const SdkPattern NdDevMenu_DMENU_Menu_AppendComponent = { L"40 53 48 83 ec ?? 48 8b 81 b0 00 00 00 48 8b da 48 85 c0 74 22 66 66 66 0f 1f 84 00 00 00 00 00 48 8b d0 48 8b 40 40 48 85 c0 75 f4 48 85 d2 74 06 48 89 5a 40 eb 07 48 89 99 b0 00 00 00 48 8b d3 48 c7 43 40 00 00 00 00 48 89 4b 38 e8 ?? ?? ?? ?? 48 8b c3 48 83 c4 20 5b c3" };
	static inline const SdkPattern NdDevMenu_DMENU_Menu_DeleteItem = { L"48 89 5c 24 10 57 48 83 ec 20 48 8b 81 b0 00 00 00 48 8b fa 33 d2 48 8b d9 8b ca 48 85" };
	static inline const SdkPattern NdDevMenu_DMENU_Menu_DeleteAllItems = { L"48 89 5c 24 ?? 48 89 74 24 ?? 57 48 83 ec ?? 0f b6 f2 c7 44 24 ?? 10 00 00 00" };
	static inline const SdkPattern NdDevMenu_DMENU_DecimalCallBack = { L"48 89 5c 24 08 57 48 83 ec 20 48 8b 59 60 83 ea 05 74 ?? 83 ea 02 74 ?? 83 fa 01 75 ?? 48 8b 0d ?? ?? ?? ?? 8b 3b 48 85 c9" };

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

	static inline const SdkPattern Memory_s_MemoryMap = { L"01 00 00 00 02 00 00 00 00 00 ?? 00 00 00 00 00 00 00 10 00" };
}