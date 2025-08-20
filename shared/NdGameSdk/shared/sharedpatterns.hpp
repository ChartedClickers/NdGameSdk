#pragma once
#include "NdGameSdk/sdkpattern.hpp"

namespace NdGameSdk::Patterns {

#if defined(T2R)
	static inline const SdkPattern EngineComponents_s_table = { L"48 89 74 24 20 41 54 41 56 41 57 48 83 ec 30 8b f1 45 8b f8 4c 8d 25 ?? ?? ?? ?? 4c 8b f2 48 85 d2 0f 84 ?? ?? ?? ??", +0x14 };
	static inline const SdkPattern EngineComponents_s_ndConfig = { L"48 8d 0d ?? ?? ?? ?? b8 04 00 00 00 48 8d 89 80 00 00 00 c5 f8 10 03 48 8d 9b 80 00 00 00 c5 f8 11 41 80 c5 f8 10 4b 90 c5 f8 11 49 90 c5 f8 10 43 a0 c5 f8 11 41 a0 c5 f8 10 4b b0 c5 f8 11 49 b0 c5 f8 10 43 c0 c5 f8 11 41 c0 c5 f8 10 4b d0 c5 f8 11 49" };

	static inline const SdkPattern CommonGame_GameInit = { L"40 53 48 83 ec 30 48 8b d9 48 8d 4c 24 20 e8 ?? ?? ?? ?? 8b 10 85 d2 7e 11 c5 f8 10 00 c5 f8 11 03 48 8b c3 48 83 c4 30 5b c3" };
	static inline const SdkPattern CommonGame_ProfileCtrl_Initialize = { L"e8 ?? ?? ?? ?? 48 8b 0d ?? ?? ?? ?? 48 8b 01 48 8b d3 ff 90 b0 01 00 00 48 89 75 20 c7 44 24 40 01 00 00 00 48 c7 44 24 38 ff ff ff ff c6 44 24 30 03 4c 89 74 24 28 c7 44 24 20 e7 0e 00 00 4c 8d 0d ?? ?? ?? ?? 4c 8d 45", +0x87 };
	static inline const SdkPattern CommonGame_CommonGameLoop_GameLoopUpdate = { L"c6 05 ?? ?? ?? ?? 01 c6 05 ?? ?? ?? ?? 00 48 8b 05 ?? ?? ?? ?? 48 ff c8 48 83 f8 0b 0f 87 ?? ?? ?? ?? 48 8d 0d", +0xf0 };
	static inline const SdkPattern CommonGame_CommonGameLoop_GameDebugUpdate = { L"48 8d 4d 08 e8 ?? ?? ?? ?? c7 44 24 30 01 00 00 00 4c", +0x51 };
	static inline const SdkPattern CommonGame_CommonMainWin_SystemInit = { L"48 89 5c 24 20 55 56 57 41 54 41 55 41 56 41 57 48 8d ac 24 90 fa ff ff 48 81 ec 70 06 00 00 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 85 60 05 00 00 49 8b f8 4c 63 fa 44 89 7c 24 44 4c 8b e9 49 8b 00 48 89 05" };
	static inline const SdkPattern CommonGame_CommonMainWin_SystemInitReturn = { L"48 89 45 c8 33 d2 8d 4a 1f e8 ?? ?? ?? ?? 48 8d 54 24 70 48 8b c8 e8 ?? ?? ?? ?? 4c 8b cf 44 8b 44 24 44 41 0f b6 d7 48 8b cb e8 ?? ?? ?? ?? 48 8b cb e8 ?? ?? ?? ?? 84 c0 0f 94 c2 48 8d 0d ?? ?? ?? ?? e8 ?? ?? ?? ?? 45 84 e4 74 05", +0x86 };
	static inline const SdkPattern CommonGame_IAllocator_Init = { L"48 89 5c 24 10 55 56 57 41 54 41 55 41 56 41 57 48 8b ec 48 83 ec 50 4c 63 f9 4c 8b f2 33 c9 e8 ?? ?? ?? ?? 84 c0 c7 45 40 07 00 00 00 48 8d 3d ?? ?? ?? ?? 48 8d 1d ?? ?? ?? ?? 48 8d 15 ?? ?? ?? ?? 48 0f 45 df 48 8d 4d 40" };
	static inline const SdkPattern CommonGame_IAllocator_s_TaggedGpuDevHeap = { L"48 83 ec 28 48 8d 15 ?? ?? ?? ?? 48 8d 0d ?? ?? ?? ?? e8 ?? ?? ?? ?? 48 8d 0d ?? ?? ?? ?? 48 83 c4 28 e9 ?? ?? ?? ?? cc cc cc cc cc cc cc cc cc 48 83 ec 28 48 8d 0d ?? ?? ?? ?? e8 ?? ?? ?? ?? 48 8d 0d ?? ?? ?? ?? 48 83 c4 28 e9 ?? ?? ?? ?? 48 83 ec 28 48 8d 0d ?? ?? ?? ?? e8 ?? ?? ?? ?? 48 8d 0d ?? ?? ?? ?? 48 83 c4 28 e9 ?? ?? ?? ??", +0x54 };
	static inline const SdkPattern CommonGame_NIXXES_StdHandle = { L"40 53 48 83 ec 20 48 8b 01 48 8b d9 ff 50 20 48 8b 03 48 8b cb ff 50 30 48 8b c8 48 8d 15 ?? ?? ?? ?? e8 ?? ?? ?? ??" };

	/*NdGame Logs*/
	static inline const SdkPattern CommonGame_PrintF = { L"48 89 4c 24 08 48 89 54 24 10 4c 89 44 24 18 4c 89 4c 24 20 53 57 48 83 ec 38 b9 01 00 00 00 48 8d 7c 24 58 e8 ?? ?? ?? ?? 48 8b d8 e8 ?? ?? ?? ?? 4c 8b 44 24 50 45 33 c9 48 8b d3 48 89 7c 24 20 48 8b 08" };
	static inline const SdkPattern Memory_DumpTaggedHeapMemoryStatsPrintF = { L"c7 44 24 40 05 00 00 00 4c 8b c0 89 7c 24 38 49 8b ce c7 44 24 30 05 00 00 00 c5 7b 11 44 24 28 c5 f8 28 de c4 c1 f9 7e f1 c5 fb 11 7c 24 20 ff d6 4d 8d 7f 01 49 83 ec 01 0f 85 ?? ?? ?? ?? c5 78 28 4c 24", +0x9a };
	static inline const SdkPattern SsManager_PrintF = { L"48 8b cb 48 89 44 24 20 4c 8b cf e8 ?? ?? ?? ?? 48 8b 4c 24 30 48 33 cc e8 ?? ?? ?? ?? 48 8b 5c 24 50 48 83 c4 40 5f c3 cc cc 4c 89 4c", +0x2a };
	static inline const SdkPattern SsManager_WarnPrintF = { SsManager_PrintF.pattern, SsManager_PrintF.offset + 0x10 };
	static inline const SdkPattern SsManager_ErrorPrintF = { L"48 8d 05 ?? ?? ?? ?? 33 d2 4c 8d 05 ?? ?? ?? ?? 48 3b 08 75 03 48 89 10 48 83 c0 08 49 3b c0 7c ef c3", +0x70 };
	static inline const SdkPattern ScriptManager_ErrorPrintF = { L"4d 8b cf 41 b8 ed 02 00 00 49 8b d6 48 8b cd c5 f8 77 e8 ?? ?? ?? ?? 90 c5 f8 77 48 8b 5c 24 60 48 8b 6c 24 68 48 8b 74 24 70 48 83 c4 40 41 5f 41 5e 5f c3", +0x3e };

	static inline const SdkPattern NdSystem_Mutex_Lock = { L"48 89 5c 24 08 48 89 6c 24 10 48 89 74 24 18 57 41 56 41 57 48 83 ec 40 44 8b f2 48 8b f9 85 d2 0f 85" };
	static inline const SdkPattern NdSystem_Mutex_TryLock = { L"48 89 5c 24 10 48 89 6c 24 18 48 89 7c 24 20 41 56 48 83 ec 30 45 33 f6 48 8b d9 44 38 71 14 75 ?? e8 ?? ?? ?? ?? 48 8b f8 48 85 c0 74 ?? b1 01 ff d7 e8 ?? ?? ?? ?? 48 85 c0 74 ?? ff d0" };
	static inline const SdkPattern NdSystem_Mutex_Unlock = { L"40 53 48 83 ec 30 80 79 14 00 48 8b d9 48 89 7c 24 40 75 71 e8 ?? ?? ?? ?? 48 8b f8 48 85 c0 74 04 b1 01 ff d7 e8 ?? ?? ?? ?? 48 85 c0 74 02 ff d0 e8 ?? ?? ?? ?? 48 85 c0 74 02 ff d0" };

	static inline const SdkPattern Memory_g_MemoryMap = { L"48 89 5c 24 18 56 48 83 ec 30 48 83 3d ?? ?? ?? ?? 00 48 8b f2 48 89 6c 24 40 48 8b e9", +0xa };
	static inline const SdkPattern Memory_s_AllocStack = { L"40 57 48 83 ec 30 ba ff ff ff ff 48 8d 0d ?? ?? ?? ?? e8 ?? ?? ?? ?? 48 8d 0d ?? ?? ?? ?? e8 ?? ?? ?? ?? 48 8d 0d", +0x17 };
	static inline const SdkPattern Memory_AllocateMemoryMap = { L"48 83 ec 58 48 89 5c 24 60 48 89 6c 24 68 48 89 7c 24 50 4c 89 6c 24 40 4c 89 74 24 38 4c 8b f2 4c 63 e9 48 8d 15 ?? ?? ?? ?? 48 8d 0d ?? ?? ?? ?? 4c 89 7c 24 30", +0xaa };
	static inline const SdkPattern Memory_ValidateContext = { L"4c 89 6c 24 28 4c 8d 0d ?? ?? ?? ?? 4c 8d 05 ?? ?? ?? ?? c7 44 24 20 27 00 00 00 48 8d", +0x30 };
	static inline const SdkPattern Memory_ModifyMemoryMap = { L"48 89 5c 24 18 48 89 74 24 20 57 48 83 ec 30 48 b8 00 00 00 00 02 00 00 00 48 8b fa 8b f1 48 3b d0 0f 82 a9 00 00 00 48 89 6c 24 40" };
	static inline const SdkPattern Memory_GetSize = { L"48 8b 05 ?? ?? ?? ?? 48 85 c0 74 14 0f 1f 40 00 8b 10 85 d2 74 0a 3b d1 74 09 48 83 c0 20 75 f0 33 c0 c3 48 8b 40 08 c3" };
	static inline const SdkPattern Memory_PushAllocator = { L"48 89 5c 24 08 48 89 6c 24 10 56 57 41 54 41 56 41 57 48 83 ec 30 8b 01 48 8b d9 48 8d 4c 24 70 89 44 24 70 49 8b e9 45 8b f0 4c 8b fa" };
	static inline const SdkPattern Memory_PopAllocator = { L"48 89 5c 24 08 48 89 74 24 10 57 48 83 ec 30 e8 ?? ?? ?? ?? 33 f6 48 8b d8 48 85 c0 75 6d e8 ?? ?? ?? ?? 48 8b f8 48 85 c0 74 04" };
	static inline const SdkPattern Memory_Allocate = { L"40 53 55 56 57 41 56 48 83 ec 40 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 44 24 38 4c 8b b4 24 90 00 00 00 48 85 c9 bf 01 00 00 00 41 8b e9 48 0f 45 f9 49 8b f0 48 8b da e8 ?? ?? ?? ?? 84 c0 74 31 48 8d 54 24 30 b9 03 00 00 00 e8 ?? ?? ?? ?? 48 8b 4c 24 30 4c 8b ce 4c 89 74 24 28 4c 8b c3 48 8b d7 89 6c 24 20 48 8b 01 ff 50 38 e9 9a 00 00 00" };
	static inline const SdkPattern Memory_AllocateAtContext = { L"48 89 5c 24 08 57 48 83 ec 30 8b 02 48 8b f9 48 8d 4c 24 48 89 44 24 48 49 8b d8 e8 ?? ?? ?? ?? 4c 8d 0d ?? ?? ?? ?? 4c 8b c3 4c 89 4c 24 28 48 8b c8 c7 44 24 20 " };
	static inline const SdkPattern Memory_Free = { L"48 85 c9 0f 84 ?? ?? ?? ?? 55 41 54 41 56 41 57 48 83 ec 38 4d 8b f1 48 89 5c 24 68 45 8b f8 4c 8b e2 48 8b e9 e8 ?? ?? ?? ?? 85 c0 74 ?? 48 8d 4c 24 60 89 44 24 60 e8 ?? ?? ?? ?? 48 8b d8 48 85 c0 0f 84 ?? ?? ?? ?? 48 8b 08 48 8b d5 4c 8b 41 68" };
	static inline const SdkPattern Memory_GetAllocator = { L"48 83 ec 28 8b 01 83 f8 73 75 1e e8 ?? ?? ?? ?? 48 8b 0d ?? ?? ?? ??" };
	static inline const SdkPattern Memory_HeapAllocator_PushAllocator = { L"48 89 5c 24 10 48 89 6c 24 18 48 89 74 24 20 48 89 4c 24 08 57 41 56 41 57 48 83 ec 20 4d 8b f1 49 8b f0 48 8b ea 4c 8b f9 33 d2 e8 ?? ?? ?? ?? 90 4d 89 b7 00 01 00 00 48 8b 7c 24 68 49 89 bf 08 01 00 00 8b 5c 24 60 41 89 9f 10 01 00 00 0f b6 44 24 70 41 88 87 14" };
	static inline const SdkPattern Memory_Area_clargnodebugmem = { L"40 b7 01 85 db 0f ?? 7d 00 00 00 8b eb", +0x2 };
	static inline const SdkPattern Memory_Area_bAllocateGpuVm = { L"48 8d 0d ?? ?? ?? ?? e8 ?? ?? ?? ?? e8 ?? ?? ?? ?? 48 8b 54 24 28 4c 8d 0d ?? ?? ?? ?? 45 33 c0 48 8d 0d ?? ?? ?? ?? e8 ?? ?? ?? ?? 0f b6 9c 24 f8 00 00 00 48 8d 0d ?? ?? ?? ?? 0f b6 d3 e8 ?? ?? ?? ?? 48 8d 0d ?? ?? ?? ?? e8 ?? ?? ?? ?? 48 8b 54 24 30 4c 8d 0d ?? ?? ?? ?? 45 33 c0 48 89 05 ?? ?? ?? ?? 48 8d 0d", +0x1e4 };
	static inline const SdkPattern Memory_TaggedHeap_SetTaggedGpuDevHeap = { L"8b 07 48 8d 0d ?? ?? ?? ?? 48 8b 5c 24 40 48 89 34 c1 48 8b 74 24 48 48 83 c4 30 5f c3 cc cc 48 89 0d ?? ?? ?? ?? c3 cc cc cc cc cc cc cc cc 48 89 0d ?? ?? ?? ?? c3 cc cc cc cc cc cc cc cc 48 89 0d ?? ?? ?? ?? c3 cc cc cc cc cc cc cc cc 48 89 0d ?? ?? ?? ?? c3", +0x3f };
	static inline const SdkPattern Memory_TaggedHeap_TaggedGpuDevHeap = { L"8b 07 48 8d 0d ?? ?? ?? ?? 48 8b 5c 24 40 48 89 34 c1 48 8b 74 24 48 48 83 c4 30 5f c3 cc cc 48 89 0d ?? ?? ?? ?? c3 cc cc cc cc cc cc cc cc 48 89 0d ?? ?? ?? ?? c3 cc cc cc cc cc cc cc cc 48 89 0d ?? ?? ?? ?? c3 cc cc cc cc cc cc cc cc 48 89 0d ?? ?? ?? ?? c3", +0x3f };
	static inline const SdkPattern Memory_FixedSizeHeap_FreeIndex = { L"48 89 5c 24 10 48 89 74 24 18 41 56 48 83 ec 30 45 33 c0 48 8b f2 48 8b d9 4c 39 41 40 74 24 48 8b 09 48 8b c2 48 2b c1" };
	static inline const SdkPattern Memory_FixedSizeHeap_Copy = { L"48 89 5c 24 20 56 48 83 ec 30 48 83 79 30 00 48 8b f2 48 89 6c 24 40 48 8b d9 48 89 7c 24 48 4c 89 74 24 50 0f 85 ?? ?? ?? ?? e8 ?? ?? ?? ?? 48 8b f8 48 85 c0 74 04 b1 01 ff d7" };
	static inline const SdkPattern Memory_FixedSizeHeap_AddIndex = { L"44 8b 51 28 33 d2 4c 8b d9 49 83 ea 01 74 2c 4c 8b 41 10 0f 1f 40 00 66" };

	static inline const SdkPattern NdJob_g_pJobSysData = { L"48 89 05 ?? ?? ?? ?? 48 8b c8 e8 ?? ?? ?? ?? 49 81 ee ?? ?? ?? ?? 4c 89 75 ?? e8 ?? ?? ?? ?? 48 8b d0 44 8b c7 b9 ?? ?? ?? ?? 48 8b 05 ?? ?? ?? ?? 48 89 54 01 ?? 48 8b 05 ?? ?? ?? ?? 48 89 14 01 48 8b 05 ?? ?? ?? ?? 48 89 54 01 ?? 48 8b 05" };
	static inline const SdkPattern NdJob_g_NdJobHeap = { L"48 89 3d ?? ?? ?? ?? 81 a7 94 00 00 00 ff ff ff 7f 44 89 6d 00 4c 8d 25 ?? ?? ?? ?? 4c 89 64 24 38 c7 44 24 30 59 03 00 00 48 8d 35 ?? ?? ?? ?? 48 89 74 24 28 48 c7 44 24 20 10 00 00 00 4c 8d 4d 00 ba 00 02 00 00 41 b8 20 00 00 00 48 8d 4f 08" };
	static inline const SdkPattern NdJob_s_JobSystem = { L"48 8b 05 ?? ?? ?? ?? 48 85 c0 79 0d 48 c7 05 ?? ?? ?? ?? 05 00 00 00 eb 29 7e 0c 48 ff c8 48 89 05 ?? ?? ?? ?? eb 1b c6 05 ?? ?? ?? ?? 01 eb 12 48" };
	static inline const SdkPattern NdJob_Initialize = { L"48 89 5c 24 18 55 56 57 41 54 41 55 41 56 41 57 48 81 ec f0 04 00 00 48 8d ac 24 c0 00 00 00 48 83 e5 80 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 85 ?? ?? ?? ?? 4c 8b fa 48 89 4d 10 33 ff 48 8d 35 ?? ?? ?? ?? f6 02 7f 74 69" };
	static inline const SdkPattern NdJob_InitializeReturn = { L"e8 ?? ?? ?? ?? b1 01 e8 ?? ?? ?? ?? 48 8b 4d 37 48 33", +0x5 };
	static inline const SdkPattern NdJob_DisplayJobSystemData = { L"40 53 48 83 ec 20 b9 02 00 00 00 e8 ?? ?? ?? ?? 48 8d 0d ?? ?? ?? ?? e8 ?? ?? ?? ?? b9 02 00 00 00 e8 ?? ?? ?? ?? 48 8b 05 ?? ?? ?? ?? 33 db 44 8b cb 8b d3 44 8b 80 88 57 00 00 4c 8d 90 80 56 00 00 0f 1f 40 00 66 66 0f 1f 84" };
	static inline const SdkPattern NdJob_AllocateCounter = { L"48 89 5c 24 08 48 89 6c 24 10 48 89 74 24 18 57 41 54 41 55 41 56 41 57 48 83 ec 30 48 8b 1d ?? ?? ?? ?? 4c 8b ea 48 8b f1 45 8b e0 48 81 c3 80 56 00 00 48 8d 15 ?? ?? ?? ?? 48 8b cb 4d 8b f9 e8 ?? ?? ?? ?? 44 8b b3" };
	static inline const SdkPattern NdJob_WaitForCounter = { L"40 53 56 57 48 83 ec 60 4c 89 6c 24 50 41 8b f0 48 8b fa 48 8b d9 e8 ?? ?? ?? ?? 4c 8b e8 48 83 f8 18 0f 83 25 01" };
	static inline const SdkPattern NdJob_WaitForCounterAndFree = { L"48 89 5c 24 10 48 89 74 24 18 57 48 83 ec 20 48 8b 01 48 8b d9 48 8d 4c 24 30 48 89 44 24 30 e8 ?? ?? ?? ?? 48 8b 3b" };
	static inline const SdkPattern NdJob_FreeCounter = { L"48 89 5c 24 08 48 89 6c 24 10 48 89 74 24 18 57 48 83 ec 20 48 8b 39 48 8b f1 e8 ?? ?? ?? ?? 48 83 f8 18 48 8d 4f 20 0f 93 c2 e8 ?? ?? ?? ?? 33 ed 48 8d 4f 20 48 89 6f 30" };
	static inline const SdkPattern NdJob_TryGetWorkerThreadIndex = { L"65 48 8b 0c 25 58 00 00 00 8b 05 ?? ?? ?? ?? ba 40 00 00 00 48 8b 04 c1 48 8b 14 02 48 c7 c0 ff ff ff ff 48 8b ca 48 0f ba f9 0f 48 0f ba e2 0f 48 0f 42 c1 c3" };
	static inline const SdkPattern NdJob_SetJobLocalStorage = { L"48 89 6c 24 18 48 89 74 24 20 41 56 48 83 ec 30 65 48 8b 04 25 20 00 00 00 4c 8b f2 48 8b e9 48 8b 30 48 85 f6 0f 84 e2" };
	static inline const SdkPattern NdJob_RunJobAndWait = { L"48 89 5c 24 08 48 89 74 24 10 48 89 7c 24 20 55 48 81 ec 60 01 00 00 48 8d ac 24 90 00 00 00 48 83 e5 c0 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 85 c0 00 00 00 33 c0 c7 44 24 40 01 00 00 00 33 f6 48 89 85" };
	static inline const SdkPattern NdJob_RegisterJobArray = { L"48 89 5c 24 08 48 89 74 24 10 48 89 7c 24 18 4c 89 64 24 20 55 41 56 41 57 48 81 ec 30 01 00 00 48 8d" };
	static inline const SdkPattern NdJob_MakeJobHeader = { L"83 61 38 f0 33 c0 48 89 41 10 48 89 41 18 48 89 41 20 48 89 41 28 48 89 41 30 48 b8 ?? ?? ?? ?? ?? ?? ?? f0 48 21 41 40 48 8b c1 48 89 11 4c 89 41 08 c3" };
	static inline const SdkPattern NdJob_IsWorkerThread = { L"48 83 ec ?? e8 ?? ?? ?? ?? 48 83 f8 18 0f 92 c0 48 83 c4 ?? c3" };
	static inline const SdkPattern NdJob_IsRenderFrameJob = { L"40 55 48 81 ec f0 00 00 00 48 8d 6c 24 60 48 83 e5 c0 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 85 80 00 00 00 c5 f9 ef c0 c5 fc 11 45 00 c5 fc 11 45 20 c5 fc 11 45 40 c5 fc 11 45 60 48 8d 4d 00 c5 f8 77 e8 ?? ?? ?? ?? 48 8d 4d 00 e8 ?? ?? ?? ?? 84 c0 74 ?? f6 45 40 08 74" };
	static inline const SdkPattern NdJob_GetCurrentWorkerPriority = { L"48 83 ec 28 e8 ?? ?? ?? ?? 48 83 f8 18 73 49 65 48 8b 04 25 20 00 00 00 48 8b 08 48 83 79 10 00 74 06 48 8b 49 18 eb 12 e8 ?? ?? ?? ?? 48 83 f8 ff b9 18 00 00 00 48 0f 45 c8 48 83 f9 18 73 18 48 8b 05 ?? ?? ?? ?? 48 c1 e1 09 0f b6 84 01 88 0c" };
	static inline const SdkPattern NdJob_GetCurrentWorkerThreadIndex = { L"48 83 ec 28 e8 ?? ?? ?? ?? 48 83 f8 18 72 ?? b8 18 00 00 00 48 83 c4 28 c3" };
	static inline const SdkPattern NdJob_Yield = { L"41 56 48 83 ec 40 e8 ?? ?? ?? ?? 4c 8b f0 e8 ?? ?? ?? ?? 84 c0 0f 85" };
	static inline const SdkPattern NdJob_GetActiveJobId = { L"65 48 8b 04 25 ?? ?? ?? ?? 48 8b 00 48 8b 40 08 c3" };
	static inline const SdkPattern NdJob_TryGetJlsSlotValue = { L"65 48 8b 04 25 20 00 00 00 4c 63 c1 49 c1 e0 04 4c 03 00 49 83 38 00 74 0a 49 8b 40 08 48 89 02 b0 01 c3 32 c0 c3" };
	static inline const SdkPattern NdJob_JlsValueWrite = { L"65 48 8b 04 25 20 00 00 00 4c 63 c9 49 c1 e1 04 4c 03 08 49 89 11 4d 89 41 08 c3" };
	static inline const SdkPattern NdJob_GetJlsValueByIndex = { L"65 48 8b 04 25 20 00 00 00 48 63 c9 48 03 c9 48 8b 00 48 8b 4c c8 08 48 89 0a c3" };
	static inline const SdkPattern NdJob_ClearJlsValueByIndex = { L"65 48 8b 04 25 20 00 00 00 48 63 d1 48 c1 e2 04 48 03 10 33 c0 48 89 02 48 89 42 08 c3" };
	static inline const SdkPattern NdJob_DoesJobLocalStorageIdExist = { L"65 48 8b 04 25 20 00 00 00 48 63 d1 48 03 d2 48 8b 00 48 83 3c d0 00 0f 95 c0 c3" };
	static inline const SdkPattern NdJob_TryGetCurrentJobHeader = { L"40 53 48 83 ec 20 48 8b d9 e8 ?? ?? ?? ?? 48 83 f8 18 73 ?? 65 48 8b 04 25 20 00 00 00 48 8b 10 48 83 7a 10 00 74 ?? 48 8b 4a 18" };

	static inline const SdkPattern ProfileCtrl_Initialize = { L"40 53 48 83 ec 30 48 8b d9 e8 ?? ?? ?? ?? 48 8b c8 e8 ?? ?? ?? ?? 33 c9 e8 ?? ?? ?? ?? 84 c0 74 ?? c7 44 24 48 0b 00 00 00 4c 8d 0d ?? ?? ?? ?? 41 b8 2e 00 00 00 48 8d" };
	static inline const SdkPattern ProfileCtrl_InitProfileMenu = { L"48 8b c4 55 53 56 57 41 56 48 8d 68 a1 48 81 ec c0 00 00 00 c5 f8 29 70 c8 c5 f8 29 78 b8 c5 78 29 40 a8 c5 78 29 48 98 c5 78 29 50 88 c5 78 29 5c 24 60 48 8b f9 33 c9 e8 ?? ?? ?? ?? 84 c0 0f 84" };
	static inline const SdkPattern ProfileCtrl_s_ProfileMgr = { ProfileCtrl_Initialize.pattern, +0xe };
	static inline const SdkPattern ProfileCtrl_ProfileMgr_DrawProfiler = { L"48 89 5c 24 08 57 48 83 ec 20 0f b6 da e8 ?? ?? ?? ?? 48 8b f8 88 98 2a 02 00 00 84 db 0f 84" };

	static inline const SdkPattern ScriptManager_g_ScriptManagerGlobals = { L"48 89 5c 24 08 48 89 74 24 10 48 89 7c 24 18 55 41 54 41 55 41 56 41 57 48 8d ac 24 20 fd ff ff 48 81 ec e0 03 00 00 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 85", +0x42 };
	static inline const SdkPattern ScriptManager_InitializeReturn = { L"80 3d ?? ?? ?? ?? 00 75 19 4d 8b cd 41 b8 13 0f 00 00 49 8b d4 48 8d 0d ?? ?? ?? ?? e8 ?? ?? ?? ?? 90", +0x22 };
	static inline const SdkPattern ScriptManager_InitializeModuleIndexReturn = { L"80 3d ?? ?? ?? ?? 00 75 19 4d 8b cd 41 b8 33 10 00 00 48 8b d7 48 8d 0d ?? ?? ?? ?? e8 ?? ?? ?? ?? 90 48 8d 0d ?? ?? ?? ?? e8 ?? ?? ?? ?? 48 8b f8 48", +0xa8 };
	static inline const SdkPattern ScriptManager_Lookup = { L"48 89 5c 24 08 48 89 6c 24 10 48 89 74 24 18 57 48 83 ec 40 48 8b d9 33 d2 8d 4a 03 e8 ?? ?? ?? ?? 48 85 c0 0f 84 ?? ?? ?? ?? 48 85 db 0f 84 ?? ?? ?? ?? c5 f9 ef c0 c5 fc 11 44 24 20 48 8d 3d ?? ?? ?? ?? 48 89 7c 24 20" };
	static inline const SdkPattern ScriptManager_LookupSymbol = { L"40 53 48 83 ec 20 48 8b da e8 ?? ?? ?? ?? 48 85 c0 75 ?? 48 8b c3 48 83 c4 20 5b c3" };
	static inline const SdkPattern ScriptManager_LookupInModule = { L"48 89 5c 24 08 48 89 6c 24 10 57 48 83 ec 20 48 8b d9 33 ed 48 85 c9 0f 84 ?? ?? ?? ?? 48 b8 ca de 18 72 18 1c ?? ?? ?? ??" };
	static inline const SdkPattern ScriptManager_BindValue = { L"4c 8b dc 49 89 5b 08 49 89 6b 10 49 89 73 18 49 89 7b 20 41 54 41 56 41 57 48 83 ec 60 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 44 24 50 41 0f b6 f0 48 8b ea 48 8b d9 c5 f9 ef c0 c5 fc 11 44 24 20 4c 8d 35 ?? ?? ?? ?? 4d 89 73 a8 4c 8d 3d ?? ?? ?? ?? 4d 89 7b b0 c7 44 24 38 38 04 00 00 4c 8d 25 ?? ?? ?? ?? 4d 89 63 b8 80" };
	static inline const SdkPattern ScriptManager_UnbindValue = { L"48 8b c4 48 89 58 08 48 89 68 10 48 89 70 18 57 41 56 41 57 48 83 ec 40 48 8b d9 c5 f9 ef c0 c5 fc 11 40 c8 48 8d 2d ?? ?? ?? ?? 48 89 68 c8 4c 8d 35 ?? ?? ?? ?? 4c 89 70 d0 c7 40 e0 08 0d 00 00 4c 8d 3d ?? ?? ?? ?? 4c 89 78 d8 80" };
	static inline const SdkPattern ScriptManager_ScriptModuleAdd = { L"48 8b c4 48 89 58 08 48 89 68 18 48 89 50 10 56 57 41 56 48 83 ec 50 48 8b fa 48 8b d9 c5 f9 ef c0 c5 fc 11 40 c8 48 8d 35 ?? ?? ?? ?? 48 89 70 c8 48 8d" };
	static inline const SdkPattern ScriptManager_ScriptModuleRemove = { L"48 8b c4 48 89 58 08 48 89 68 10 48 89 70 18 57 41 56 41 57 48 83 ec 40 48 8b d9 c5 f9 ef c0 c5 fc 11 40 c8 48 8d 2d ?? ?? ?? ?? 48 89 68 c8 4c 8d 35 ?? ?? ?? ?? 4c 89 70 d0 c7 40 e0 ed 02 00 00 4c 8d 3d" };
	static inline const SdkPattern ScriptManager_RemoveModule = { L"48 89 5c 24 08 48 89 6c 24 10 48 89 74 24 18 48 89 7c 24 20 41 54 41 56 41 57 48 81 ec c0 00 00 00 48 8b 05" };
	static inline const SdkPattern ScriptManager_AddModuleInfo = { L"48 8b c4 48 89 58 08 48 89 68 10 48 89 70 18 57 48 83 ec 40 48 8b d9 c5 f9 ef c0 c5 fc 11 40 d8 48 8d 3d ?? ?? ?? ?? 48 89 78 d8 48 8d" };
	static inline const SdkPattern ScriptManager_LoadModuleFromFile = { L"48 89 5c 24 08 48 89 6c 24 20 56 57 41 54 41 56 41 57 48 83 ec 60 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 44 24 50 45 8b f9 49 8b e8 48 8b f2 48 8b d9 4c 8b b4 24 b0 00 00 00 41 83 3e 0b 75 0f" };
	static inline const SdkPattern ScriptManager_AddModuleRequest = { L"48 89 5c 24 08 48 89 74 24 10 48 89 7c 24 18 41 54 41 56 41 57 48 83 ec 30 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 44 24 28 41 0f b6 f9 45 0f b6 e0 4c 8b fa 48 8b d9 48 8b b4 24 80 00 00 00 48 85 f6 74 03 c6 06 00 83 3a 0b 75 0f 33 c9 e8 ?? ?? ?? ??" };
	static inline const SdkPattern ScriptManager_ReloadModule = { L"48 8b c4 48 89 58 08 48 89 70 10 48 89 78 18 55 41 54 41 55 41 56 41 57 48 8d a8 38 fa ff ff 48 81 ec a0 06 00 00 c5 f8 29 70 c8 c5 f8 29 78 b8 48 8b 05" };
	static inline const SdkPattern ScriptManager_IsLoadModule = { L"48 89 5c 24 08 57 48 81 ec a0 00 00 00 48 8b d9 80 3d ?? ?? ?? ?? 00 75 20 4c 8d 0d ?? ?? ?? ?? 41 b8 9e 0b 00 00 48 8d 15 ?? ?? ?? ?? 48 8d 0d ?? ?? ?? ?? e8 ?? ?? ?? ?? c5 f9 ef c0 33 c0 c5 fc 11 44 24 30 c5 f8 11 44 24 50 48 89 44 24 60 8b 3d ?? ?? ?? ?? 48 8d 0d ?? ?? ?? ??" };
	static inline const SdkPattern ScriptManager_FindExportingModule = { L"48 89 5c 24 08 48 89 6c 24 10 48 89 74 24 18 57 41 54 41 55 41 56 41 57 48 83 ec 50 49 8b f0 0f b6 ea 48 8b f9 e8 ?? ?? ?? ?? 48 85 c0 0f 84 ?? ?? ?? ?? c5 f9 ef c0 c5 fc 11 44 24 30 4c 8d 2d ?? ?? ?? ?? 4c 89 6c 24 30 48 8d 05 ?? ?? ?? ?? 48 89 44 24 38 c7 44 24 48 11 0b 00 00" };
	static inline const SdkPattern ScriptManager_GetDebugModuleBucket = { L"48 8b 74 24 50 48 89 74 24 40 40 b5 01 40 88 6c 24 48 0f 1f 40 00 66 66 0f 1f 84 00 00 00 00 00 41 b8 01 00 00 00 49 bf", +0xf0 };
	static inline const SdkPattern ScriptManager_ModuleInfo_LookupModuleByDcEntry = { L"48 89 5c 24 10 48 89 74 24 18 48 89 7c 24 20 41 56 48 81 ec b0 00 00 00 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 84 24 a0 00 00 00 44 8b 0d ?? ?? ?? ?? 33 c0 4c 8b 1d ?? ?? ?? ?? 48 8b fa 48 89 44 24 60 33 d2 48 8b c1 45 33 f6 49 f7 f1 c5 f9 ef c0 8b c2" };
	static inline const SdkPattern ScriptManager_ModuleInfo_LookupDcEntry = { L"48 89 5c 24 08 48 89 6c 24 10 48 89 74 24 18 57 48 83 ec 20 33 ed 48 89 51 10 49 8b d8 48 89 29 48 89 69 08 48 8b fa 48 89 59 18 48 8b f1 40 88 69 24 c7 41 20 ff ff ff ff" };
	static inline const SdkPattern ScriptManager_ModuleInfo_FetchModule = { L"48 89 5c 24 08 48 89 6c 24 10 48 89 74 24 18 48 89 7c 24 20 41 56 48 83 ec 40 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 44 24 38 48 8b d9 80 3d ?? ?? ?? ?? 00 75 07 b0 01 e9 ?? ?? ?? ?? 40 32 ed 33 f6 48 89 74 24 20 40 32" };
	static inline const SdkPattern ScriptManager_ScriptModule_FetchScriptModuleEntry = { L"48 89 5c 24 08 44 8b 49 38 45 33 d2 41 83 e9 01 48 8b 59 40 4c 8b c2 78 ?? 0f 1f 80 00 00 00 00 43 8d 04 11 99 2b c2 d1 f8 48 63 c8 48 8d 14 49 4c 39" };

	static inline const SdkPattern PackageMgr_Init = { L"48 89 5c 24 10 48 89 74 24 18 48 89 7c 24 20 55 41 54 41 55 41 56 41 57 48 8d ac 24 ?? ?? ?? ?? 48 81 ec 70 02 00 00 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 85 60 01 00 00 48 8b fa 48 8b d9 48 81 c1 68 47 00 00 33 d2 41 b8 00 08 00" };
	static inline const SdkPattern PackageMgr_InitReturn = { L"e8 ?? ?? ?? ?? 48 8b 4b 68 49 03 cf e8 ?? ?? ?? ?? 48 8b 83 d8 00 00 00 89 34 b8 41 ff c6 44 3b 33 72 ?? 48 8b c6 48 87 05 ?? ?? ?? ?? 89 75 c8 48 8d 15 ?? ?? ?? ?? 48 8d 4d c8 e8 ?? ?? ?? ?? 48 8d 93 80 04 00 00 48 8d 4d c8 e8 ?? ?? ?? ?? 33 d2 48 8d 4d 18 e8 ?? ?? ?? ?? 48 8d 93 c0 04", +0xe9 };
	static inline const SdkPattern PackageMgr_ProcessLoginQueue = { L"48 89 5c 24 08 48 89 6c 24 10 48 89 74 24 18 57 41 56 41 57 48 83 ec 60 c5 f8 29 74 24 50 c5 f8 28 f1 48 8b f9 33 ed 40 38 2d ?? ?? ?? ?? 0f 84 ?? ?? ?? ?? 8d 4d 02" };
	static inline const SdkPattern PackageMgr_ProcessLoginQueueUpdate = { L"e8 ?? ?? ?? ?? 49 2b c7 48 8b c8 e8 ?? ?? ?? ?? c5 f8 2f f0 77 ?? 3b af ?? ?? ?? ?? 0f 82 ?? ?? ?? ?? 48 8b 4f 30 48 85 c9 74 ?? 48 8b 01 0f b6 97 ?? ?? ?? ?? 0a 97 ?? ?? ?? ?? ff 50 18", +0x45 };
	static inline const SdkPattern PackageMgr_GetPackageById = { L"48 89 5c 24 18 48 89 54 24 10 55 56 57 48 8d 6c 24 ?? 48 81 ec ?? ?? ?? ?? c5 f9 ef c0 33 c0 4c 8d 45 ?? 48 8b f9 48 89 45 ?? c5 fc 11 45 b7 c5 f8 11 45 d7 48 8d 55 b7 48 83 c1 78 c5 f8 77" };
	static inline const SdkPattern PackageMgr_GetProcessingInfoFromPackage = { L"48 85 d2 74 ?? 48 2b 51 68 48 b8" };
	static inline const SdkPattern PackageMgr_GetPackageStatusById = { L"48 81 ec c8 00 00 00 8b 41 58 4c 8b d1 83 e8 01 78 ?? 44 8b 59 58 41 3b c3 7d" };
	static inline const SdkPattern PackageMgr_GetPackageByIndex = { L"48 63 c2 48 69 d0 00 1b 00 00 48 03 51 ?? 0f b6 8a ?? ?? ?? ?? 83 e9 01 74 0f 83 e9 02 74 0a 83 e9 01 74 0a 83 f9 01 75 09 45 84 c0 75 04" };
	static inline const SdkPattern PackageMgr_UpdatePackageStatus = { L"0f b6 c2 88 51 08 83 f8 12 77 ?? 4c 8d 05 ?? ?? ?? ??" };
	static inline const SdkPattern PackageMgr_SetPackageStatus = { L"0f b6 41 08 83 f8 12 77 ?? 4c 8d 05 ?? ?? ?? ?? 41 8b 94 80 ?? ?? ?? ?? 49 03 d0 ff e2" };
	static inline const SdkPattern PackageMgr_PreparePackageForLoading = { L"44 88 44 24 18 55 53 56 57 41 54 41 55 41 56 48 8d 6c 24 d9 48 81 ec e0 00 00 00 48 63 01 33 f6 4c 8b f2 4c 8b e1 85 c0 7e ?? 4c 8b 51 68 48 8b d0 45 33 c9" };
	static inline const SdkPattern PackageMgr_LogoutPackage = { L"40 57 41 54 41 57 48 81 ec d0 00 00 00 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 84 24 b0 00 00 00 48 8b fa 4c 8b f9 33 d2 33 c9 e8 ?? ?? ?? ?? 48 85 c0 74 09 33 d2 33 c9 e8 ?? ?? ?? ?? 48 8b 07 ff 88" };
	static inline const SdkPattern PackageMgr_PackageQueuesIdle = { L"83 79 58 00 7f 27 83 b9 e8 00" };
	static inline const SdkPattern PackageMgr_RequestLoadPackage = { L"40 53 55 56 57 48 81 ec d8 00 00 00 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 84 24 c8 00 00 00 49 8b d8 48 8b e9 45 33 c0 48 8d 8c 24 c0 00 00 00 41 8b f9 48 8b f2 e8 ?? ?? ?? ?? 8b 84 24 20 01 00 00 48 8d 4c 24 30 89 84 24" };
	static inline const SdkPattern PackageMgr_RequestLogoutPackage = { L"4c 8b dc 48 81 ec c8 00 00 00 33 c0 48 83 c1 50 41 89 43 ec 49 89 43 f0 48 89 54 24 28 48 8d 54 24 20 88 44 24 30 c7" };
	static inline const SdkPattern PackageMgr_RequestReloadPackage = { L"4c 8b dc 55 48 81 ec f0 00 00 00 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 84 24 c8 00 00 00 49 89 5b 10 48 8b e9 49 89 73 18 48 8b da 49 89 7b f0 4d 89 73 e8 e8 ?? ?? ?? ?? 45 33 f6 48 89 5c 24 28 48 8d 54 24 20 44 89 b4 24 b4" };
	static inline const SdkPattern PackageMgr_AddRequest = { L"8b 41 08 4c 8b c9 8b 49 0c 4c 8b d2 3b c1 0f 8d ?? ?? ?? ?? 4d 63 41 04 ff c0 41 89 41 08 33 d2 41 8d 40 01 3b c1 0f 44 c2 4b 8d 14 80 41 89 41 04 b0 01 c4 c1 78 10 02 48 c1 e2 05 49 03 51 10 c5 f8 11 02 c4 c1 78 10 4a 10" };
	static inline const SdkPattern PackageMgr_PackageProcessingInfo_GetStatusString = { L"40 57 48 83 ec 30 0f b6 f9 40 80 ff 13 72 ?? 48 89 5c 24 40 e8 ?? ?? ?? ?? 48 8b d8 48 85 c0 74 ?? b1 01 ff d3 e8 ?? ?? ?? ?? 48 85 c0 74 ?? ff d0" };
	static inline const SdkPattern PackageMgr_Package_ResolvePakItem = { L"48 b8 d5 05 a8 19 5f 99 ?? ?? 48 3b c8 0f 87 ?? ?? ?? ?? 0f 84 ?? ?? ?? ?? 48 b8 3d d9 7d 83 ad dd ?? ?? 48 3b c8 0f 87 ?? ?? ?? ?? 0f 84 ?? ?? ?? ?? 48 b8 21 84" };
	static inline const SdkPattern PackageMgr_Package_GetStatusString = { L"57 48 83 ec 30 0f b6 f9 40 80 ff 06 72 7b 48 89 5c 24 40 e8 ?? ?? ?? ff 48 8b d8 48 85 c0 74 04 b1 01 ff d3 e8 ?? ?? ?? ff 48 85 c0 74 02 ff d0 e8 ?? ?? ?? ff 48 85 c0 74 02 ff d0" };
	static inline const SdkPattern PackageMgr_GetPakHdrPageEntry = { L"48 89 74 24 10 48 89 7c 24 18 41 56 48 83 ec 30 4c 8b f2 41 8b f8 48 8b f1 44 3b 41 10 72 7b 48 89 5c 24 40 e8 ?? ?? ?? ?? 48 8b d8 48 85 c0 74 04 b1 01 ff d3" };
	static inline const SdkPattern PackageMgr_ResolvePakPagePtr = { L"48 83 ec 18 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 04 24 41 8b c0 8b 44 82 20 0f ba e0 18 73 26 44 2b 82 9c 09 00 00 41 c1 e0 15 49 63 c0 48" };

	static inline const SdkPattern NdDevMenu_GameConfig_DevMode = { L"41 0f b6 8c 24 13 3f 00 00 84 c9 0f 94 c2 84 c9 0f 95 c1", +0xb };
	static inline const SdkPattern NdDevMenu_NdDevMenuAppend_Particles = { L"48 89 5c 24 08 48 89 74 24 10 57 48 83 ec 40 48 8b f1 33 c9 e8 ?? ?? ?? ?? 84 c0 0f 84 9d" };
	static inline const SdkPattern NdDevMenu_DMENU_Component = { L"40 53 57 41 57 48 83 ec 30 45 33 ff c7 41 68 c8 c8 c8 ff 4c 89 b9 80 00 00 00 48 8d 05 ?? ?? ?? ?? 48 89 01 48 8b da 4c 89 79 30 48 8b f9 44 89 79 4e 4c 89 79 38 4c 89 79 40 44 89 79 48 66 44 89 79 4c 4c 89 79 58 4c 89 79 60 4c 89 b9 90 00 00 00 c7 41 6c ff ff 00 ff c7 41 70 b0 ff b0 ff 66 44 89 79 74 66 44 89 b9 98 00 00 00 4c 89 79 78 4c 89 b9 88 00 00 00 4c 89 79 08 48 85 d2" };
	static inline const SdkPattern NdDevMenu_DMENU_MenuGroup = { L"48 89 5c 24 10 48 89 4c 24 08 57 48 83 ec 20 41 8b d8 48 8b f9 e8 ?? ?? ?? ?? 90 48 8d 05 ?? ?? ?? ?? 48 89 07 88 9f a0 00 00 00 33 db 48 89 9f a8 00 00 00 48 89 9f b0 00 00 00 48 89 9f b8 00 00 00 66 c7 87 c0 00 00 00 00 01 48 89 9f c8 00 00 00 48 89 9f d0 00 00 00 48 89 9f d8 00 00 00 88 9f f0 00 00 00 48 89 9f 00 03 00 00 89 9f 08 03 00 00 48 89 9f 20 03" };
	static inline const SdkPattern NdDevMenu_DMENU_Menu = { L"48 89 5c 24 08 57 48 83 ec 20 41 8b d8 48 8b f9 e8 ?? ?? ?? ?? 48 8d 05 ?? ?? ?? ?? 89 9f b8 00 00 00 48 8b 5c 24 30 48 89 07 33 c0 48 89 87 a0 00 00 00 89 87 a8 00 00 00" };
	static inline const SdkPattern NdDevMenu_DMENU_KeyBoard = { L"48 89 5c 24 08 48 89 74 24 10 57 48 83 ec 20 8b da 49 8b f9 49 8b d0 48 8b f1 e8 ?? ?? ?? ?? 48 8d 05 ?? ?? ?? ?? 89 9e ?? ?? ?? ??" };
	static inline const SdkPattern NdDevMenu_DMENU_ItemDecimal = { L"48 89 8e f8 00 00 00 48 89 86 f0 00 00 00 48 89 5e 60 48 8d 05 ?? ?? ?? ?? 48 3b f8 75 0c c6 46 74 01 48 8b ce e8 ?? ?? ?? ?? 80 7c 24 68 00 74 29 48 8b 06 4c 8b 80 b8 00 00 00 48 8d 05 ?? ?? ?? ?? ba 10 00 00 00 48 8b ce 4c 3b c0 75 07", +0x71 };
	static inline const SdkPattern NdDevMenu_DMENU_ItemFloat = { L"48 89 5c 24 10 48 89 74 24 18 48 89 4c 24 08 57 48 83 ec 20 49 8b f9 49 8b d8 48 8b f1 e8 ?? ?? ?? ?? 33 c9 48 89 8e a0 00 00 00 c7 86 a8 00 00 00 01 00 00 00 48 89 4e 60 48 8b 44 24 58 48 89 86 80 00 00 00 66 c7 86 b0 00 00 00 00 07 48 8d 05 ?? ?? ?? ??" };
	static inline const SdkPattern NdDevMenu_DMENU_ItemFunction = { L"48 89 5c 24 08 48 89 74 24 10 57 48 83 ec 20 49 8b d9 49 8b f8 48 8b f1 e8 ?? ?? ?? ?? 33 c9 48 89 5e 60 48 8b 5c 24 30 48 8d 05 ?? ?? ?? ?? 48 89 06 0f b6 44 24 50 48 89 8e a0 00 00 00 c7 86 a8 00 00 00 05 00 00 00 48 89 8e 80 00 00 00 48 89 be b0 00 00 00" };
	static inline const SdkPattern NdDevMenu_DMENU_ItemSelection = { L"48 89 5c 24 10 48 89 74 24 18 48 89 4c 24 08 57 48 83 ec 20 49 8b d9 49 8b f8 48 8b f1 e8 ?? ?? ?? ?? 8b 44 24 68 89 86 a0 00 00 00 33 c9 89 8e a4 00 00 00 c7 86 a8 00 00 00 04 00 00 00 48 8b 44 24 70 48 89 86 80 00 00 00 48 8d 05 ?? ?? ?? ?? 48 89 06 48 89 9e b0 00 00 00 48 8b 44 24 60 48 89 86 b8" };
	static inline const SdkPattern NdDevMenu_DMENU_DecimalCallBack = { L"48 89 5c 24 08 57 48 83 ec 20 48 8b 79 60 48 8b d9 83 ea 05 0f 84 ?? ?? ?? ?? 83 ea 02 0f 84 ?? ?? ?? ?? 83 ea 01 0f 84 ?? ?? ?? ?? 83 ea 08 74 41 83 fa 01 0f 85 ?? ?? ?? ?? 48 8b 01 ff 90 a8 00 00 00 83 f8 04 75 15 8b 83 d8 00 00 00 89 07 48 98 48 8b 5c 24 30 48 83 c4 20 5f c3" };
	static inline const SdkPattern NdDevMenu_DMENU_MenuGroup_SetRootMenu = { L"48 85 d2 0f 84 96 00 00 00 48 89 5c 24 08 57 48 83 ec 20 48 8b da 48 8b f9 48 8b 81 b0 00 00 00 48 3b d0 74 70 48 85 c0 74 43" };
	static inline const SdkPattern NdDevMenu_DMENU_Menu_AppendComponent = { L"40 56 57 41 56 48 83 ec 20 80 3d ?? ?? ?? ?? 00 48 8b f2 4c 8b f1 0f 84 ?? ?? ?? ?? 48 8b ca e8 ?? ?? ?? ?? 84 c0 0f 85 ?? ?? ?? ?? 48 8b 06 48 8b ce 48 89 5c 24 40 4c 89 64 24 50 4c 89 7c 24 58 ff 50 68 33 c9 48 85 c0 74 10" };
	static inline const SdkPattern NdDevMenu_DMENU_Menu_UpdateKeyboard = { L"48 89 5c 24 10 48 89 6c 24 18 48 89 74 24 20 57 41 54 41 55 41 56 41 57 48 81 ec a0 00 00 00 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 84 24 90 00 00 00 4c 8b f1 33 d2 41 bc 01 00 00 00 41 8b cc e8 ?? ?? ?? ?? 4c 8b e8 48 8d 88 10 0a 01 00" };
	static inline const SdkPattern NdDevMenu_DMENU_Menu_DeleteItem = { L"48 89 5c 24 ?? 57 48 83 ec 20 48 8b fa 48 8b d9 33 d2 48 8b 81 b0 00 00 00 8b ca 48 85 c0 74 ?? 48 3b c7 74 ?? 48 8b d0 48 8b 40 40" };
	static inline const SdkPattern NdDevMenu_DMENU_Menu_DeleteAllItems = { L"48 89 5c 24 08 48 89 74 24 18 57 48 83 ec 20 8b f2 48 8b d9 48 8d 05 ?? ?? ?? ?? 48 89 01 c7 44 24 38 11 00 00 00 4c" };
	static inline const SdkPattern NdDevMenu_DMENU_Menu_DeferDeleteAllItems = { L"48 89 5c 24 ?? 48 89 74 24 18 57 48 83 ec 30 0f b6 f2 48 8b d9 c7 44 24 40 11 00 00 00 4c 8d 0d ?? ?? ?? ?? 41 b8 6c 16 00 00 48 8d 15 ?? ?? ?? ?? 48 8d 4c 24 40 e8 ?? ?? ?? ?? 90" };
	static inline const SdkPattern NdDevMenu_DMENU_Menu_UpdateItems_FavoriteItemKeyCode = { L"e9 ?? ?? ?? ?? 48 8b 8f 28 01 00 00 48 0f ba e1 0e 73 ?? 8b 87 38 01 00 00 48 0f ba e0 0a 72 ?? 48 0f ba e1 0a 73 ?? 8b 87 38 01 00 00 48 0f ba e0 0e 72", +0x4e };
	static inline const SdkPattern NdDevMenu_DMENU_Menu_Update_KeyboardSearchState = { L"41 b9 ff ff ff ff 41 b0 01 48 8b cd e8 ?? ?? ?? ?? 44 0f b6 e8 b2 01 49 8d 8f 10 0a 01 00 e8 ?? ?? ?? ?? 49 0f ba a7 20 0a", +0x32 };
	static inline const SdkPattern NdDevMenu_DMENU_KeyBoard_Handler_ClipBoardHook = { L"48 63 4b 08 3b c8 7d 2a 48 63 d0 4c 8b c1 48 3b ca 7d 10 49 8d 3c 0e 48 8b ca 49 2b c8 48 8d 77 01 f3 a4 45 88 7c 16 ff 49 b8 ?? ?? ?? ?? ?? ?? ?? ?? 44 38 7b 05 74 2c 41 83 f9 2e 75 26 b1 01 32 d2 44 38 7b 04 75 2b 41", +0x87 };
	static inline const SdkPattern NdDevMenu_DMENU_s_IsKeyboardComponentActive = { NdDevMenu_DMENU_Menu_UpdateKeyboard.pattern, +0xfa };
	static inline const SdkPattern NdDevMenu_DMENU_s_IsKeyboardSearchActive = { NdDevMenu_DMENU_Menu_UpdateKeyboard.pattern, +0x133 };

	static inline const SdkPattern RenderFrameParams_s_FrameParams = { L"48 89 1d ?? ?? ?? ?? 48 8b 15 ?? ?? ?? ?? b9 00 40 0b 00 e8 ?? ?? ?? ?? 48 8b c8 48 89 05 ?? ?? ?? ?? 48 05 00 e0 01 00 48 89 05" };
	static inline const SdkPattern RenderFrameParams_InitializeFrameParamsReturn = { L"e8 ?? ?? ?? ?? 48 89 1d ?? ?? ?? ?? 48 8d 8c 24 90 00 00 00 48 8b 94 24 90 00 00 00 ff 92 90 00 00 00 89 2e eb 06 c7 06 04 00 f1 0c 48 89 6e 08 48 8d 8c 24 90", +0x3d };
	static inline const SdkPattern RenderFrameParams_GetFrameParams = { L"40 53 48 83 ec 30 48 8b d9 48 85 c9 78 48 48 8b 05 ?? ?? ?? ?? 48 3b c8 7f 3c 48 2b c1 48 83 f8 10 0f 87" };
	static inline const SdkPattern RenderFrameParams_GetCurrentFrameParams = { L"40 57 48 83 ec 30 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 44 24 28 e8 ?? ?? ?? ?? 0f b6 f8 84 c0 74 ?? 48 8d 54 24 20 b9 02 00 00 00 e8 ?? ?? ?? ?? 84 c0 74 ?? 48 8b 44 24 20 48 8b 4c 24 28 48 33 cc e8 ?? ?? ?? ?? 48 83 c4 30 5f c3" };
	static inline const SdkPattern RenderFrameParams_IsFrameReady = { L"80 3d ?? ?? ?? ?? 00 75 ?? 48 85 c9 78 ?? 48 8b 05 ?? ?? ?? ?? 48 3b c8 7f ?? 48 2b c1 48 83 f8 10 77" };
	static inline const SdkPattern RenderFrameParams_GetCurrentFrameNumber = { L"48 83 ec 28 e8 ?? ?? ?? ?? 48 85 c0 74 08 48 8b 00 48 83 c4 28 c3 48 83 c4 28 c3" };

	/*DebugDraw*/
	static inline const SdkPattern GameFramePreRenderUpdate = { L"48 89 5c 24 08 48 89 74 24 10 48 89 7c 24 18 4c 89 74 24 20 55 48 81 ec 20 06 00 00 48 8d ac 24 90 00 00 00 48 83 e5 c0 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 85 80 05 00 00 c5 f9 ef c0 c5 fc 11 85 80 02 00 00 c5 fc 11 85 a0 02 00 00 c5 fc 11 85 c0 02 00 00 c5 fc 11 85 e0 02 00 00 45 33 c0 48 8d 15 ?? ?? ?? ?? 48 8d 8d 80 02 00 00" };
	static inline const SdkPattern GameDebugDraw_StaticContextHook = { L"e8 ?? ?? ?? ?? 48 89 44 24 20 44 0f b6 cf 44 0f b6 c6 48 8b d5 48 8b cb e8 ?? ?? ?? ?? e8 ?? ?? ?? ?? 0f 1f 40 00 66 66 0f 1f 84 00 00 00 00 00 48 8b 5c 24 40 48 8b 6c 24 48 48 8b 74 24 58 48 83 c4 30 5f c3", +0x30 };
	static inline const SdkPattern GameDebugDraw_StaticContext_ProfilingHook = { L"e8 ?? ?? ?? ?? 48 8b d8 48 8b 7d 08 48 8d 15 ?? ?? ?? ?? 48 8b 0f e8 ?? ?? ?? ?? c5 fb 10 0d", +0x39 };
	static inline const SdkPattern GameDebugDraw_DebugDrawSid = { L"44 88 a5 ?? ?? ?? ?? 45 38 a7 ?? ?? ?? ?? 74 2d 49 8d 87 ?? ?? ?? ?? 48 89 44 24 20 4c 8d 0d ?? ?? ?? ?? 4c 8d 05 ?? ?? ?? ?? ba 80 00 00 00 48 8d 8d", +0x4d };
	static inline const SdkPattern WindowContext_WindowContext = { L"48 89 5c 24 18 48 89 6c 24 20 56 48 83 ec 30 80 3d ?? ?? ?? ?? 00 49 8b f0 48 63 ea 48 8b d9 74 ?? 33 c0 c7 01 ff ff ff ff 48 89 41 08 48 89 41 10 48 89 41 18 48 8b c1 c7 41 20 ff ff ff ff 48 8b 5c 24 50 48 8b 6c 24 58" };
	static inline const SdkPattern Text_textPrintV = { L"4c 8b dc 48 83 ec 58 c5 fa 10 84 24 80 00 00 00 49 8d 43 40 49 89 43 f0 49 8b 43 38 49 89 43 e8 33 c0 89 44 24 38 89 44 24 30 8b 84 24 88 00 00 00 89 44 24 28 c5 fa 11 44 24 20" };
	static inline const SdkPattern Text2_GetTextWidthHeight = { L"4c 8b dc 53 56 57 48 81 ec f0 00 00 00 c4 c1 78 29 73 d8 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 84 24 d0 00 00 00 33 c0 48 8b f1 48 8d 4c 24 40 41 89 43 a0 49 89 43 a8 49 8b f8 c5 f8 28 f3 8b da" };
	static inline const SdkPattern Msg_s_MsgCon = { L"4c 8b dc 48 81 ec 88 00 00 00 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 44 24 70 48 8d 05 ?? ?? ?? ?? 49 c7 43 a0 00 10 00 00 49 89 43 98 49 8d 4b 98 48 8d 05", +0x81 };
	static inline const SdkPattern Msg_PrintToActiveMsgOutput = { L"48 89 4c 24 08 48 89 54 24 10 4c 89 44 24 18 4c 89 4c 24 20 48 83 ec 38 48 85 c9 75 ?? 48 89 5c 24 30 e8 ?? ?? ?? ?? 48 8b d8 48 85 c0 74 ?? b1 01 ff d3 e8 ?? ?? ?? ?? 48 85 c0 74 ?? ff d0 e8 ?? ?? ?? ?? 48 85 c0 74" };

	static inline const SdkPattern PrimServer_PrimServer = { L"48 89 8d 80 00 00 00 48 89 75 18 c7 44 24 40 01 00 00 00 48 c7 44 24 38 ff ff ff ff c6 44 24 30 03 4c 89 74 24 28 c7 44 24 20 df 0e 00 00 4c 8d 0d", 0x5b };
	static inline const SdkPattern PrimServer_TextPrintPosition = { L"4c 89 44 24 18 4c 89 4c 24 20 53 55 56 57 48 81 ec a8 02 00 00 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 84 24 90 02 00 00 49 8b f8 48 8d ac 24 e8 02 00 00 8b da 48 8b f1" };
	static inline const SdkPattern PrimServer_GetDefaultPrimParams = { L"48 89 5c 24 08 57 48 83 ec 20 48 8b d9 e8 ?? ?? ?? ?? 88 43 01 40 b7 01 66 c7 43 02 00 01 48 c7 43 08 00 00 00 00 e8 ?? ?? ?? ?? 48 85 c0 74 08" };
	static inline const SdkPattern PrimServer_DebugStringBaseHandler = { L"48 89 6c 24 28 48 8d 94 24 90 00 00 00 4c 8b cf 48 c7 44 24 20 00 00 00 00 41 b8 00 02 00 00 48 8b 08 48 83 c9 01 e8 ?? ?? ?? ?? 48 8b 05 ?? ?? ?? ?? 48 8b 08 48 8b a9 c8 00 00 00 e8 ?? ?? ?? ?? 88 44 24 31 40 b7 01 66 c7 44 24 32 00 01 e8 ?? ?? ?? ?? 48 85 c0 74 08 0f b6 78 09 40 c0 ef 07 48 8b 05 ?? ?? ?? ?? 4c 8d 44 24 30 c5 f8 10 06 c5", +0x8d };

#elif defined(T1X)
	static inline const SdkPattern EngineComponents_s_table = { L"48 89 6c 24 18 56 41 56 41 57 48 83 ec 30 8b f1 45 8b", +0x13 };
	static inline const SdkPattern EngineComponents_s_ndConfig = { L"b8 04 00 00 00 48 8d ?? ?? ?? ?? ?? 8d 50 7c c5 f8 10 03 c5 f8 11 01 c5 f8 10 4b 10 c5 f8 11 49 10 c5 f8 10 43 20 c5 f8 11 41 20 c5 f8 10 4b 30 c5 f8 11 49 30 c5 f8 10 43 40 c5 f8 11 41 40 c5 f8 10 4b 50 c5 f8 11 49 50 c5 f8 10 43 60 c5 f8 11 41 60", +0x5 };

	static inline const SdkPattern CommonGame_GameInit = { L"40 53 48 83 ec 40 80 3d ?? ?? ?? ?? 00 48 8b d9 74 0c 48 8d 4c 24 20 e8 ?? ?? ?? ?? eb 0a 48 8d 4c 24 30"};
	static inline const SdkPattern CommonGame_PrimServer_Create = { L"ff 90 b0 01 00 00 48 83 65 08 00 4c 8d 0d ?? ?? ?? ?? 44 89 64 24 40 4c 8d 45 08 48 83 4c 24 38 ff 48 8d 8d c0 00 00 00 c6 44 24 30 03 41" };
	static inline const SdkPattern CommonGame_CommonGameLoop_GameLoopUpdate = { L"e8 ?? ?? ?? ?? 48 8b ?? ?? ?? ?? 05 e8 ?? ?? ?? ?? 48 8b 8d c0 00 00 00 48 33 cc e8 ?? ?? ?? ?? 4c 8d 9c 24 60 01 00 00 49 8b 5b 38 49 8b 73 40 49 8b 7b 48 49 8b", +0x11 };
	static inline const SdkPattern CommonGame_CommonGameLoop_GameDebugUpdate = { L"48 8b 0d ?? ?? ?? ?? 48 8b 01 ff 90 a0 00 00 00 e8 ?? ?? ?? ?? e8 ?? ?? ?? ?? 33 d2 89 5c 24 30 4c 89 6c 24 28 4c 8d 0d ?? ?? ?? ?? 48 8d 0d", +0x8a };
	static inline const SdkPattern CommonGame_CommonMainWin_SystemInit = { L"48 89 5c 24 20 55 56 57 41 54 41 56 48 83 ec 40 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 44 24 38 49 8b f0 89 15 ?? ?? ?? ?? 8b fa 4c 89 05 ?? ?? ?? ?? 4c 8b f1" };
	static inline const SdkPattern CommonGame_CommonMainWin_SystemInitReturn = { L"48 83 63 20 00 48 8d 05 ?? ?? ?? ?? 48 89 03 eb 02 33 db 48 8b cb e8 ?? ?? ?? ?? 40 8a cd e8 ?? ?? ?? ?? 4c 8b ce 44 8b c7 40 8a d5 48 8b cb e8 ?? ?? ?? ?? 48 8b cb e8 ?? ?? ?? ?? 84 c0 74 10 c6 05 ?? ?? ?? ?? 00 c6 05", +0x6c };

	/*NdGame Logs*/
	static inline const SdkPattern CommonGame_PrintF = { L"48 8b c4 48 89 48 08 48 89 50 10 4c 89 40 18 4c 89 48 20 53 48 83 ec 20 b9 01 00 00 00 48 8d 58 10 e8 ?? ?? ?? ?? 48 8b 54 24 30 4c 8b cb 45 33 c0 48 8b c8" };
	static inline const SdkPattern CommonGame_ErrorPrintF = { L"48 8b c4 48 89 48 08 48 89 50 10 4c 89 40 18 4c 89 48 20 53 57 48 83 ec 28" };
	static inline const SdkPattern SsManager_PrintF = { L"48 8b c4 48 89 48 08 48 89 50 10 4c 89 40 18 4c 89 48 20 53 48 83 ec 20 b9 18 00 00 00 48 8d 58 10 e8 ?? ?? ?? ??" };
	static inline const SdkPattern SsManager_WarnPrintF = { L"4c 89 44 24 18 4c 89 4c 24 20 c3 cc 48 89 5c 24 08 57 48 83 ec 30" };
	static inline const SdkPattern SsManager_ErrorPrintF = { L"48 89 54 24 10 4c 89 44 24 18 4c 89 4c 24 20 c3 48 89 54 24 10 4c 89 44 24 18 4c 89 4c 24 20 c3 48 89 5c 24 18 48 89 74 24 20 55 57 41 55 41 56 41 57 48 8d ac 24 60 fc ff ff" };
	static inline const SdkPattern ScriptManager_ErrorPrintF = { L"48 8b c4 48 89 48 08 48 89 50 10 4c 89 40 18 4c 89 48 20 53 48 83 ec 20 8b ?? ?? ?? ?? ?? ?? 8d 58 10 e8 ?? ?? ?? ??" };

	static inline const SdkPattern NdSystem_Mutex_Lock = { L"48 83 ec 40 44 8b f2 48 8b f9 85 d2 0f 85 ?? ?? ?? ?? e8 ?? ?? ?? ?? 48 8b d8 48 85 c0 74 04 b1 01 ff d3 e8 ?? ?? ?? ?? 48 85 c0 74 02 ff d0" -0x14 };
	static inline const SdkPattern NdSystem_Mutex_TryLock = { L"40 57 48 83 ec 20 48 8b f9 4c 8b ca 48 83 c1 04 48 85 d2 74 ?? 48 89 5c 24 30 48 c7 c0 ff ff ff ff 48 ff c0 80 3c 02 00 75 ?? 83 f8 20 ba 1f 00 00 00 0f 4c d0 48 63 da 49 8b d1 4c 8b c3 e8 ?? ?? ?? ?? c6 44 3b 04 00 48 8b 5c 24 30 c5 f8 77 48 83 c4 20 5f c3", +0x70 };
	static inline const SdkPattern NdSystem_Mutex_Unlock = { L"40 53 48 83 ec 30 80 79 14 00 48 8b d9 48 89 7c 24 40 75 ?? e8 ?? ?? ?? ?? 48 8b f8 48 85 c0 74 ?? b1 01 ff d7 e8 ?? ?? ?? ?? 48 85 c0 74 ?? ff d0 e8 ?? ?? ?? ?? 48 85 c0 74 ?? ff d0" };

	static inline const SdkPattern Memory_g_MemoryMap = { L"48 89 5c 24 08 48 89 74 24 10 57 48 83 ec 30 48 ?? ?? ?? ?? ?? 04 00 48 8b", +0xf };
	static inline const SdkPattern Memory_s_AllocStack = { L"48 2b 15 ?? ?? ?? ?? 4c 8d 05 ?? ?? ?? ?? 48 c1 fa 0a 48 8b ca 83 e2 3f 48 c1 e9 06 49 8b 04 c8 48 0f b3 d0 49 89 04 c8 c3", +0x7 };
	static inline const SdkPattern Memory_AllocateMemoryMap = { L"48 89 5c 24 08 48 89 6c 24 10 48 89 74 24 18 57 41 56 41 57 48 83 ec 30 48 8b f2 8b f9 e8 ?? ?? ?? ?? 48 8b d6 8b", +0x42 };
	static inline const SdkPattern Memory_ValidateContext = { L"c7 44 24 20 27 00 00 00 48 8d 15", +0x1d };
	static inline const SdkPattern Memory_ModifyMemoryMap = { L"48 89 5c 24 08 48 89 6c 24 10 48 89 74 24 18 57 48 83 ec 30 48 b8 00 00 00 00 02 00 00 00 48 8b f2 8b e9 48 3b" };
	static inline const SdkPattern Memory_FindMemoryMap = { L"48 8b 05 ?? ?? ?? ?? 48 85 c0 74 ?? 83 38 00 74 ?? 39 08 74 ?? 48 83 c0 20 75 ?? 33" };
	static inline const SdkPattern Memory_GetSize = { L"48 83 ec 28 e8 ?? ?? ?? ?? 48 8b c8 33 c0 48 85 c9 74 ?? 48 8b 41 08 48 83 c4" };
	static inline const SdkPattern Memory_PushAllocator = { L"40 53 55 56 57 41 54 41 56 41 57 48 83 ec ?? 8b 01" };
	static inline const SdkPattern Memory_PopAllocator = { L"48 89 5c 24 08 48 89 74 24 10 57 48 83 ec 30 e8 ?? ?? ?? ?? 33 db 48 8b f8 48 85" };
	static inline const SdkPattern Memory_Allocate = { L"48 89 5c 24 ?? 48 89 6c 24 ?? 48 89 74 24 ?? 57 48 83 ec 30 48 85 c9 bf 01 00 00 00 41 8b f1 49 8b e8 48 0f 45 f9 48 8b da e8 ?? ?? 00 00 84 c0 ??" };
	static inline const SdkPattern Memory_AllocateAtContext = { L"48 89 5c 24 08 57 48 83 ec 30 8b 02 48 8b f9 48 8d 4c 24" };
	static inline const SdkPattern Memory_Free = { L"48 85 c9 74 66 48 89 5c 24 10 48 89 6c 24 18 48 89 74 24 20 57 48 83 ec 30 49 8b f9 41 8b f0 48 8b ea 48 8b d9 e8 ?? ?? ?? ?? 48 8b cb 85 c0 0f 85 ?? ?? ?? ?? e8 ?? ?? ?? ?? 48 85 c0 74 ?? 4c 8b 10" };
	static inline const SdkPattern Memory_GetAllocator = { L"48 83 ec 28 8b 01 83 f8 70" };
	static inline const SdkPattern Memory_HeapAllocator_PushAllocator = { L"48 89 5c 24 08 48 89 6c 24 10 48 89 74 24 18 57 41 56 41 57 48 83 ec 20 48 8b ea 4d 8b f1 33 d2 49 8b f0 4c 8b f9 e8 ?? ?? ?? ?? 8a 44 24 70 4c 8b c6 48 8b 7c 24 68 48 8b d5 8b 5c 24 60 49 8b cf 41 88 87" };
	static inline const SdkPattern Memory_Area_clargnodebugmem = { L"b3 01 45 85 ff 74 ?? 48 8b 0f", +0x1 };
	static inline const SdkPattern Memory_BootstrapAppHeaps = { L"b9 19 00 00 00 e8 ?? ?? ?? ?? 48 85 c0 74 06 48 8b 78 08 eb 02 33 ff 4d 85 c9 74 1b 41 b8 04 00 00 00 c7 44 24 40 05 00 00 00 48 8d 54 24 40 49 8b c9", +0x57 };
	static inline const SdkPattern Memory_FixedSizeHeap_FreeIndex = { L"48 89 5c 24 08 48 89 6c 24 10 48 89 74 24 18 57 48 83 ec 30 48 8b 41 10 48 8b f9 48 63 ea b1 01 48 8b f5 83 e5 3f 48 c1" };
	static inline const SdkPattern Memory_FixedSizeHeap_Copy = { L"48 89 5c 24 08 48 89 74 24 10 48 89 7c 24 18 41 56 48 83 ec 30 48 83 79 30 00 4c 8b f2 48 8b d9 0f 85 91 00 00 00 48 8b 3d ?? ?? ?? ?? 48 85 ff 74 04 b1 01 ff d7 48 8b 05 ?? ?? ?? ?? 48 85 c0 74 02 ff d0 48 8b 05" };
	static inline const SdkPattern Memory_FixedSizeHeap_AddIndex = { L"48 89 5c 24 08 57 48 83 ec 20 48 8b d9 48 83 c1 10 e8 ?? ?? ?? ?? 4c 8b d0 48 83 f8 ff 74 3e 48 3b 43 30 73 38 48 ff 43 40 49 8b d2 48 0f af 43 38 4c 8b 43 10 4d 8b ca 48 03 03 83" };

	static inline const SdkPattern NdJob_g_pJobSysData = { L"48 89 05 ?? ?? ?? ?? e8 ?? ?? ?? ?? 48 8d 8d 90 02 00 00 49 81 ef 80 6d 02 00 ff 15 ?? ?? ?? ?? 48 8b 85 90 02 00 00 8b d6 41 b8 00 54" };
	static inline const SdkPattern NdJob_g_NdJobHeap = { L"48 89 05 ?? ?? ?? ?? e8 ?? ?? ?? ?? 48 8b 3d ?? ?? ?? ?? 48 85 ff 0f 84 ?? ?? ?? ?? 48 83 cb ff 44 8b 67 08 48 8d 8d ?? ?? ?? ?? 4c 8b 0d ?? ?? ?? ?? 41 ba c5 9d 1c 81 44 89 a5 88 02 00 00 41 bb" };
	static inline const SdkPattern NdJob_s_JobSystem = { L"48 8b 05 ?? ?? ?? ?? 48 85 c0 79 0d 48 c7 05 ?? ?? ?? ?? 05 00 00 00 eb 26 7e 0c 48 ff c8 48 89 05" };
	static inline const SdkPattern NdJob_Initialize = { L"48 89 5c 24 18 55 56 57 41 54 41 55 41 56 41 57 48 81 ec 00 05 00 00 48 8d ac 24 ?? ?? ?? ?? 48 83 e5 80 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 85 30 04 00 00 33 f6 48 89 4d 00 f6 02 7f 4c 8d" };
	static inline const SdkPattern NdJob_InitializeReturn = { L"e8 ?? ?? ?? ?? b1 01 e8 ?? ?? ?? ?? 48 8b 4d 00 48 33 cc e8 ?? ?? ?? ?? 4c 8d 9c 24 30 01 00 00 49 8b 73 10 49 8b 7b 18 4d 8b 73 20 c4 c1 78 28 73 f0 c4 c1 78 28 7b e0 49 8b e3 5d c3", +0x5 };
	static inline const SdkPattern NdJob_DisplayJobSystemData = { L"40 53 48 83 ec 20 bb 02 00 00 00 8b cb e8 ?? ?? ?? ?? 48 8d 0d ?? ?? ?? ?? e8 ?? ?? ?? ?? 8b cb e8 ?? ?? ?? ?? 4c 8b 15 ?? ?? ?? ?? 49 8d 8a 80 56" };
	static inline const SdkPattern NdJob_AllocateCounter = { L"48 89 5c 24 10 48 89 74 24 18 57 41 56 41 57 48 83 ec 40 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 44 24 38 4c 8b f1 41 8b f0 48 8b 0d ?? ?? ?? ?? 4c 8b fa 83 ca ff 49 8b f9 48 8d 99 80 56 00 00 48 81 c1 00 58 00 00 e8 ?? ?? ?? ?? 48 8b cb" };
	static inline const SdkPattern NdJob_WaitForCounter = { L"40 53 55 56 57 41 55 41 56 41 57 48 83 ec 40 41 8b f0 48 8b fa 4c 8b f1 e8 ?? ?? ?? ?? 4c 8b e8 48 83 f8 18" };
	static inline const SdkPattern NdJob_WaitForCounterAndFree = { L"40 53 48 83 ec 20 48 8b 01 48 8b d9 48 8d 4c 24 30 48 89 44 24 30 e8 ?? ?? ?? ?? 48 8b 03 48 8d 4c 24 30 48 89 44 24 30 e8 ?? ?? ?? ?? 48 83 c4 20 5b c3" };
	static inline const SdkPattern NdJob_FreeCounter = { L"40 53 48 83 ec 20 48 8b d9 33 d2 48 8b 09 e8 ?? ?? ?? ?? 48 8b 0d ?? ?? ?? ?? 83 ca ff 48 81 c1 00 58" };
	static inline const SdkPattern NdJob_TryGetWorkerThreadIndex = { L"65 48 8b 0c 25 ?? ?? ?? ?? 8b 05 ?? ?? ?? ?? ba 48 00 00 00 48 8b 04 c1 48 8b 14 02 48 c7 c0" };
	static inline const SdkPattern NdJob_SetJobLocalStorage = { L"48 8b c4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 56 48 83 ec 30 65 48 8b 04 25 ?? ?? ?? ?? 48 8b ea 4c 8b f1 48 8b 38 48 85 ff 0f 84" };
	static inline const SdkPattern NdJob_RunJobAndWait = { L"48 89 5c 24 08 48 89 74 24 10 55 57 41 56 48 81 ec 60 01 00 00 48 8d ac 24 90 00 00 00 48 83 e5 c0 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 85 c0" };
	static inline const SdkPattern NdJob_RegisterJobArray = { L"40 53 55 56 57 41 56 48 83 ec 40 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 44 24 38 48 8b 84 24 a8" };
    static inline const SdkPattern NdJob_MakeJobHeader = { L"83 61 38 f0 33 c0 48 89 41 10 48 89 41 18 48 89 41 20 48 89 41 28 48 89 41 30 48 b8" };
    static inline const SdkPattern NdJob_IsWorkerThread = { L"48 83 ec 28 e8 ?? ?? ?? ?? 48 83 f8 18 0f 92 c0 48 83 c4 28 c3" };
    static inline const SdkPattern NdJob_GetCurrentWorkerPriority = { L"48 83 ec 28 e8 ?? ?? ?? ?? 48 8b c8 48 83 f8 18 73 14 48 8b 05" };
	static inline const SdkPattern NdJob_GetCurrentWorkerThreadIndex = { L"48 83 ec 28 e8 ?? ?? ?? ?? 84 c0 75 07 b8 18 00 00 00 eb 35 48 83 64 24 30 00 48 8d 54 24 30 b9 01 00 00 00 e8 ?? ?? ?? ?? 84 c0 74 07 48 8b 44 24 30 eb 15" };
	static inline const SdkPattern NdJob_Yield = { L"48 89 5c 24 08 48 89 6c 24 10 48 89 74 24 18 57 48 83 ec 30 e8 ?? ?? ?? ?? 48 8b e8 e8 ?? ?? ?? ?? 84 c0 0f 85" };
	static inline const SdkPattern NdJob_TryGetJlsSlotValue = { L"65 48 8b 04 25 20 00 00 00 4c 63 c1 49 c1 e0 04 4c 03 00" };
	static inline const SdkPattern NdJob_TryGetCurrentJobHeader = { L"40 53 48 83 ec 20 48 8b d9 e8 ?? ?? ?? ?? 48 83 f8 18 0f 82 ?? ?? ?? ?? 32 c0 c5 f8 77 48 83 c4 20 5b c3" };

	static inline const SdkPattern ScriptManager_g_ScriptManagerGlobals = { L"48 89 5c 24 08 48 89 74 24 10 57 48 83 ec 20 48 8b d9 48 63 fa 48 ?? ?? ?? ?? ?? ?? 45 33 c9 4c 89 49", +0x15 };
	static inline const SdkPattern ScriptManager_InitializeReturn = { L"4c 8d 0d ?? ?? ?? ?? 4c 8b c3 49 8b d6 48 8b cf e8 ?? ?? ?? ?? 4c 8b c3 44 89 64 24 40 48 8d 54 24 40 48 8b cb e8 ?? ?? ?? ?? 48 85 c0 74 10 48 89 38 44 89 70 08 48 89 05 ?? ?? ?? ?? eb 08 48 83 25 ?? ?? ?? ?? 00", +0x68 };
	static inline const SdkPattern ScriptManager_InitializeModuleIndexReturn = { L"49 8b c9 e8 ?? ?? ?? ?? 41 ff c4 48 83 c6 28 44 3b 27 0f 8c 5c ff ff ff", +0xe3 };
	static inline const SdkPattern ScriptManager_Lookup = { L"48 89 5c 24 10 48 89 4c 24 08 57 48 83 ec 60 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 44 24 50 48 83 3d" };
	static inline const SdkPattern ScriptManager_LookupSymbol = { L"40 53 48 83 ec ?? 48 8b da e8 ?? ?? ?? ?? 48 85 c0 75 ?? 48 8b c3 eb ?? 48 8b 00 48 83 c4 ?? 5b c3" };
	static inline const SdkPattern ScriptManager_LookupInModule = { L"48 89 4c 24 08 57 48 83 ec 50 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 44 24 48 33 ff 48 8b d9 48 85 c9 0f 84 ?? ?? ?? ?? 48 b9 25 23 22 84 e4 9c" };
	static inline const SdkPattern ScriptManager_BindValue = { L"48 89 5c 24 08 48 89 74 24 10 57 48 83 ec 70 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 44 24 60 c5 f9 ef c0 41 8a f8 4c 8d 0d ?? ?? ?? ?? 48 8b f2 48 8b d9 c5 fc 11 44 24 40 41 b8 27 02 00" };
	static inline const SdkPattern ScriptManager_UnbindValue = { L"40 53 48 83 ec 70 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 44 24 60 c5 f9 ef c0 48 8b d9 4c 8d 0d ?? ?? ?? ?? c5 fc 11 44 24 40 41 b8 53 0f 00 00 48 8d 15 ?? ?? ?? ?? 48 8d 4c 24" };
	static inline const SdkPattern ScriptManager_ScriptModuleAdd = { L"48 89 5c 24 08 48 89 54 24 10 57 48 83 ec 70 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 44 24 60 c5 f9 ef c0 48 8b fa 4c 8d 0d ?? ?? ?? ?? 48 8b d9 48 8d 15 ?? ?? ?? ?? c5 fc 11 44 24 40 41 b8 c5 03 00 00 48 8d 4c 24 40 c5 f8 77 e8 ?? ?? ?? ?? 48 8b 47 48 48 85 c0 74 06 80 78 5e 00 75 1c 4c 8d 8c 24 88" };
	static inline const SdkPattern ScriptManager_ScriptModuleRemove = { L"40 53 48 83 ec 70 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 44 24 60 c5 f9 ef c0 48 8b d9 4c 8d 0d ?? ?? ?? ?? c5 fc 11 44 24 40 41 b8 d7 03 00 00 48 8d 15 ?? ?? ?? ?? 48 8d 4c 24 40 c5" };
	static inline const SdkPattern ScriptManager_RemoveModule = { L"48 8b c4 48 89 58 08 48 89 70 10 48 89 78 18 55 41 56 41 57 48 8d 68 a1 48 81 ec c0 00 00 00 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 45 37 48 83 65 a7 00" };
	static inline const SdkPattern ScriptManager_AddModuleInfo = { L"40 53 48 83 ec 50 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 44 24 40 c5 f9 ef c0 48 8b d9 4c 8d 0d ?? ?? ?? ?? c5 fc 11 44 24 20 41 b8 87 03 00 00 48 8d" };
	static inline const SdkPattern ScriptManager_LoadModuleFromFile = { L"48 89 5c 24 08 48 89 74 24 10 55 57 41 54 41 56 41 57 48 8b ec 48 83 ec 70 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 45 f8 48 8b 7d 50 45 8b e1 4d 8b f8 48 8b d9 83 3f 0a 0f 84 ?? ?? ?? ?? e8 ?? ?? ?? ?? 84 c0 75 ?? 48 8b cb" };
	static inline const SdkPattern ScriptManager_AddModuleRequest = { L"48 8b c4 48 89 58 08 48 89 70 10 48 89 78 18 4c 89 60 20 55 41 56 41 57 48 8d a8 28 fc ff ff 48 81 ec c0 04 00 00 48 ?? ?? ?? ?? ?? ?? 48 33 c4 48 89 85 b0 03 00 00 48" };
	static inline const SdkPattern ScriptManager_ReloadModule = { L"48 8b c4 48 89 58 08 48 89 70 10 48 89 78 18 55 41 54 41 55 41 56 41 57 48 8d a8 f8 f9 ff ff 48 81 ec e0 06 00 00 c5 f8 29 70 c8 48 ?? ?? ?? ?? ?? ?? 48 33 c4 48 89 85 c0 05 00" };
	static inline const SdkPattern ScriptManager_IsLoadModule = { L"48 8b c4 48 89 58 08 48 89 70 10 48 89 78 18 55 48 8d 68 a1 48 81 ec c0 00 00 00 48 ?? ?? ?? ?? ?? ?? 48 33 c4 48 89 45 47 c5 f9 ef" };
	static inline const SdkPattern ScriptManager_FindExportingModule = { L"4c 8b dc 49 89 5b 08 49 89 73 10 49 89 7b 18 4d 89 63 20 41 55 41 56 41 57 48 83 ec 60 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 44 24 58 48 8b 05 ?? ?? ?? ?? 49 8b f8 44 8a ea 48 8b f1 48 85 c0 0f 84 ?? ?? ?? ?? c5 f9 ef c0 c5 fc 11 44 24 38" };
	static inline const SdkPattern ScriptManager_ModuleInfo_LookupModuleByDcEntry = { L"4c 8b dc 49 89 5b 10 49 89 6b 18 48 89 4c 24 08 56 57 41 56 48 81 ec a0 00 00 00 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 84 24 90 00 00 00 c5 f9 ef c0 c5 fc 11 44 24 58 33 c0 4d 8d 43 08 c5 f8 11 44 24 78 48" };
	static inline const SdkPattern ScriptManager_ModuleInfo_LookupDcEntry = { L"48 89 5c 24 08 57 48 83 ec 20 48 83 21 00 83 cf ff 48 83 61 08 00 48 8b d9 89 79 20 48 89 51 10 4c 89 41 18 c6 41 24 00 48 8b" };
	static inline const SdkPattern ScriptManager_ModuleInfo_FetchModule = { L"48 89 5c 24 08 57 48 83 ec 30 33 ff 48 8b d9 40 38 3d ?? ?? ?? ?? 75 04 b0 01 eb 28 48 8d 4c 24 20 e8 ?? ?? ?? ?? 48 8b cb e8 ?? ?? ?? ?? 48 85 c0 74 04 40 8a 78 5c 48" };
	static inline const SdkPattern ScriptManager_ScriptModule_FetchScriptModuleEntry = { L"44 8b 49 38 45 33 d2 41 83 e9 01 4c 8b 59 40 4c 8b c2 78 2a b9 02 00 00 00 43 8d 04 11 99 f7 f9 48 63 c8 48 8d 14 49 4d 39 04 d3 73" };

	static inline const SdkPattern NdDevMenu_GameConfig_DevMode = { L"8a 8f ?? ?? ?? ?? 84 c9 0f 94 c2 84 c9 0f 95 c1" };
	static inline const SdkPattern NdDevMenu_NdDevMenuAppend_Particles = { L"40 56 48 83 ec 30 48 8b f1 33 c9 e8 ?? ?? ?? ?? 84 c0 0f 84 ?? ?? ?? ?? 48 89 5c 24 40 4c 8d 0d ?? ?? ?? ??" };

	static inline const SdkPattern NdDevMenu_DMENU_Component = { L"40 53 57 41 57 48 83 ec 30 45 33 ff c7 41 68 c8 c8 c8 ff 4c 89 b9 80 00 00 00 48 ?? ?? ?? ?? ?? ?? 48 ?? ?? ?? ?? da 4c 89 79 30 48 8b f9 44 89 79 4e 4c 89 79 38 4c 89 79 40 44 89" };
	static inline const SdkPattern NdDevMenu_DMENU_MenuGroup = { L"48 89 5c 24 08 57 48 83 ec 20 41 8b d8 48 8b f9 e8 ?? ?? ?? ?? 88 9f a0 00 00 00 48 ?? ?? ?? ?? 56 02 33 db 48 ?? ?? ?? ?? 9f c8 00 00 00 b9 00 10 00 00 48 89 9f 20 03 00 00 48 89 9f 28 03 00 00 48 89 9f a8 00 00 00 48 89 9f b0 00 00 00" };
	static inline const SdkPattern NdDevMenu_DMENU_Menu = { L"48 89 5c 24 08 57 48 83 ec 20 41 8b d8 48 8b f9 e8 ?? ?? ?? ?? 48 ?? ?? ?? ?? 56 02 89 9f b8 00 00 00 48 ?? ?? ?? ?? 48 ?? ?? ?? ?? 48 89 87 a0 00 00 00 89 87 a8 00 00 00 48 89 87 b0 00 00 00 88 87 bc 00 00 00 48" };
	static inline const SdkPattern NdDevMenu_DMENU_KeyBoard = { L"48 89 5c 24 08 48 89 74 24 10 57 48 83 ec 30 48 8b 44 24 60 41 8b f1 45 33 c9 48 89 44 24 28 83" };
	static inline const SdkPattern NdDevMenu_DMENU_ItemDecimal = { L"48 89 5c 24 08 48 89 74 24 10 57 48 83 ec 20 49 8b f9 49 8b d8 48 8b f1 e8 ?? ?? ?? ?? 48 8b 44 24 58 33 c9 66 c7 86 b0 00 00 00 00 07" };
	static inline const SdkPattern NdDevMenu_DMENU_ItemFloat = { L"48 89 5c 24 08 48 89 74 24 10 57 48 83 ec 20 49 8b f9 49 8b d8 48 8b f1 e8 ?? ?? ?? ?? 48 8b 44 24 58 33 c9 48 89 8e 00 01 00 00 48 89 8e 08 01 00 00 48 89 86 80 00 00 00" };
	static inline const SdkPattern NdDevMenu_DMENU_ItemFunction = { L"48 89 5c 24 08 48 89 74 24 10 57 48 83 ec 20 49 8b d9 49 8b f8 48 8b f1 e8 ?? ?? ?? ?? 33 c9 48 89 5e 60 48 8b 5c 24 30 48 8d 05 ?? ?? ?? ?? 48 89 06 0f b6 44 24 50 88 86 c1 00 00 00 48 8b c6 48 89 8e a0 00 00 00 c7 86 a8 00 00 00 05 00 00 00" };
	static inline const SdkPattern NdDevMenu_DMENU_ItemSelection = { L"48 89 5c 24 08 48 89 74 24 10 57 48 83 ec 20 49 8b d9 49 8b f8 48 8b f1 e8 ?? ?? ?? ?? 8b 44 24 68 33 c9 89 86 a0 00 00 00 48 8b 44 24 70 48 89 86 80 00 00 00" };
	static inline const SdkPattern NdDevMenu_DMENU_DecimalCallBack = { L"48 89 5c 24 08 57 48 83 ec 20 48 8b 59 60 83 ea 05 74 ?? 83 ea 02 74 ?? 83 fa 01 75 ?? 48 8b 0d ?? ?? ?? ?? 8b 3b 48 85 c9" };
	static inline const SdkPattern NdDevMenu_DMENU_MenuGroup_SetRootMenu = { L"48 85 d2 0f ?? ?? ?? ?? 00 48 89 5c 24 08 57 48 83 ec 20 48 8b 81 b0 00 00 00 48 8b da 48 8b f9 48 3b" };
	static inline const SdkPattern NdDevMenu_DMENU_Menu_AppendComponent = { L"40 53 48 83 ec ?? 48 8b 81 b0 00 00 00 48 8b da 48 85 c0 74 22 66 66 66 0f 1f 84 00 00 00 00 00 48 8b d0 48 8b 40 40 48 85 c0 75 f4 48 85 d2 74 06 48 89 5a 40 eb 07 48 89 99 b0 00 00 00 48 8b d3 48 c7 43 40 00 00 00 00 48 89 4b 38 e8 ?? ?? ?? ?? 48 8b c3 48 83 c4 20 5b c3" };
	static inline const SdkPattern NdDevMenu_DMENU_Menu_UpdateKeyboard = { L"40 55 56 41 54 41 55 48 81 ec b8 00 00 00 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 84 24 a0 00 00 00 48 8b f1 41 bc 01 00 00 00 41 8b cc 33 d2 e8 ?? ?? ?? ?? 48 8b e8 48 89 44 24 30 4c 8d a8 90 02 01 00 49 8b cd e8 ?? ?? ?? ?? 84 c0 0f 84 3e 06 00 00" };
	static inline const SdkPattern NdDevMenu_DMENU_Menu_DeleteItem = { L"48 89 5c 24 10 57 48 83 ec 20 48 8b 81 b0 00 00 00 48 8b fa 33 d2 48 8b d9 8b ca 48 85" };
	static inline const SdkPattern NdDevMenu_DMENU_Menu_DeleteAllItems = { L"48 89 5c 24 08 48 89 74 24 18 57 48 83 ec 20 48 8d 05 ?? ?? ?? ?? c7 44 24 38 10 00 00 00 48 89 01 4c 8d 0d ?? ?? ?? ?? 8b f2 48 8b d9 48 8d 4c 24 38 41 b8 83 13 00 00 48 8d 15 ?? ?? ?? ?? e8 ?? ?? ?? ?? 48 8b bb ?? ?? 00 00 48 85 ff 74 68 80 bb bc 00 00 00 00 74 0e 48 8b 07 ba 01 00 00 00 48 8b cf ff 50 10 48" };
	static inline const SdkPattern NdDevMenu_DMENU_Menu_DeferDeleteAllItems = { L"48 89 5c 24 ?? 48 89 74 24 ?? 57 48 83 ec 20 0f b6 f2 c7 44 24 30 10 00 00 00 48 8b d9 48 8d 15 ?? ?? ?? ?? 48 8d 4c 24 30 41 b8 60 13 00 00 4c 8d 0d ?? ?? ?? ?? e8 ?? ?? ?? ?? 48 8b bb ?? ?? 00 00 48 85 ff 74 6f 40 84 f6 74 17 80 bb bc" };
	static inline const SdkPattern NdDevMenu_DMENU_Menu_Update_KeyboardSearchState = { L"41 b9 ff ff ff ff 41 b0 01 48 8b ce e8 ?? ?? ?? ?? b2 01 48 8d 8d ?? ?? ?? ?? 44 0f b6 e8 e8 ?? ?? ?? ?? 48 b9 ?? ?? ?? ?? ?? ?? ?? ?? 48 85 8d ?? ?? ?? ?? 0f 84 11 01 00 00 84 c0 0f 84 09 01 00 00 b2 01 48 8d 8d", +0x3a };
	static inline const SdkPattern NdDevMenu_DMENU_KeyBoard_Handler_ClipBoardHook = { L"45 88 54 16 ff 49 b8 ?? ?? ?? ?? ?? ?? ?? ?? 44 38 53 05 74 2c 41 83 f9 2e 75 26 b1 01 32 d2 44 38 53 04 75 2b 41 8d 41 9f 83 f8 19 76 0f 41 8d 41 d8 83 f8 37 77 19 49 0f a3 c0 73 13 b0 01", +0x64 };
	static inline const SdkPattern NdDevMenu_DMENU_s_IsKeyboardComponentActive = { NdDevMenu_DMENU_Menu_UpdateKeyboard.pattern, +0x109 };
	static inline const SdkPattern NdDevMenu_DMENU_s_IsKeyboardSearchActive = { NdDevMenu_DMENU_Menu_UpdateKeyboard.pattern, +0x143 };
	static inline const SdkPattern NdDevMenu_Assert_UpdateSelectRegionByNameMenu = { L"cc 48 85 db 74 ?? 33 c9 ff d3 48 8d 05 ?? ?? ?? ?? c7 44 24 ?? 10 00 00 00 41 b9 8e 00 00 00" };
	static inline const SdkPattern NdDevMenu_Assert_UpdateSelectIgcByNameMenu = { L"cc 48 85 db 74 ?? 33 c9 ff d3 48 8d 05 ?? ?? ?? ?? bb 10 00 00 00 41 b9 84 03 00 00" };
	static inline const SdkPattern NdDevMenu_Assert_UpdateSelectSpawnerByNameMenu = { L"cc 48 85 db 74 ?? 33 c9 ff d3 48 8d 05 ?? ?? ?? ?? c7 44 24 ?? 10 00 00 00 41 b9 a3 00 00 00" };

	static inline const SdkPattern Particle_ParticleManager_Init = { L"48 8b c4 48 89 58 18 48 89 48 08 55 56 57 41 54 41 55 41 56 41 57 48 8d 68 a8 48 81 ec 20 01 00 00 4c 8d ?? ?? ?? ?? 00 c5 f8 29 70 b8 41 bd 36 00 00" };
	static inline const SdkPattern Particle_ParticleInternal_ParticleDebug = { L"48 8d ?? ?? ?? ?? ?? e8 ?? ?? ?? ?? 4c 8b c3 48 8d ?? ?? ?? ?? ?? 48 8b d5 e8 ?? ?? ?? ?? 48 8d ?? ?? ?? ?? ?? 48 89 7c 24" };
	static inline const SdkPattern Particle_ParticleInternal_ParticleDebug_Init = { L"48 89 5c 24 10 48 89 6c 24 18 48 89 74 24 20 57 41 54 41 55 41 56 41 57 48 83 ec 50 48 8d ?? ?? ?? ?? ?? 4c 8b f1 48 89 ?? ?? ?? 80 00 00 00 48 8d ?? ?? ?? ?? ?? 48 89 41 28 b9 00 2d" };
	static inline const SdkPattern Particle_ParticleInternal_ParticleDebug_Constructor = { L"33 d2 b8 11 c0 00 00 66 89 41 18 48 8b c1 89 51 04 89 51 20 66 89 51 24 88 51 26 48 89 51 30 48 89 51 38 48 89 51 40 48 89 51 50 48 89 51 58 48 89 51 60 48 89 51 68 48 89 51 70 48 89 51 78 48 89 91 80 00 00 00 48 89 91 88 00 00 00 48 89 91 90 00 00 00 48 89 91 98 00 00 00 48 89 91 a0 00 00 00 48 89 91 a8 00 00 00 48" };
	static inline const SdkPattern Particle_ParticleInternal_RenderUpdate = { L"4c 8b dc 53 56 48 81 ec a8 00 00 00 48 8b ?? ?? ?? ?? 02 48 33 c4 48 89 84 24 88 00 00 00 4c 8b 0a 48 8b f2 48 8b d9 4d 85" };
	static inline const SdkPattern Particle_ParticleInternal_OnExecuteRootDataSelector = { L"40 53 55 56 57 41 55 48 81 ec 30 01 00 00 48 ?? ?? ?? ?? ?? 02 48 33 c4 48 89 84 24 20 01 00 00 8b da c7 44 24 38 10 00 00 00 48 8b" };

	static inline const SdkPattern RenderFrameParams_s_FrameParams = { L"48 89 1d ?? ?? ?? ?? e8 ?? ?? ?? ?? ba 06 00 00 00 48 8d 0d ?? ?? ?? ?? 44 8d 72 fb 48 89 01 48 05 00 e0 01 00 48 8d 49 08 49 2b d6 75 ee 49 8b df 44 89 74 24 28 4c 8d 0d" };
	static inline const SdkPattern RenderFrameParams_InitializeFrameParamsReturn = { L"48 8b 0d ?? ?? ?? ?? 4c 8b c6 48 8b d0 e8 ?? ?? ?? ?? 48 8b 45 80 48 8d 4d 80 48 89", +0x37 };
	static inline const SdkPattern RenderFrameParams_GetFrameParams = { L"48 89 5c 24 08 48 89 74 24 10 57 48 83 ec 30 48 8b d9 48 85 c9 78 47 48 8b 05 ?? ?? ?? ?? 48 3b c8 7f 3b 48 2b c1 48 83 f8 10 0f 87" };
	static inline const SdkPattern RenderFrameParams_GetCurrentFrameParams = { L"40 53 48 83 ec 20 e8 ?? ?? ?? ?? 8a d8 84 c0 74 ?? 48 8d 54 24 30 b9 02 00 00 00 e8 ?? ?? ?? ?? 84 c0 74 ?? 48 8b 44 24 30 eb ?? e8 ?? ?? ?? ?? 4c 8b 05 ?? ?? ?? ?? 84 c0 4c 0f 45 05" };
	static inline const SdkPattern RenderFrameParams_IsFrameReady = { L"45 33 c0 44 38 05 ?? ?? ?? ?? 75 ?? 48 85 c9 78 ?? 48 8b 05 ?? ?? ?? ?? 48 3b c8 7f ?? 48 2b c1 48 83 f8 10 77" };

	/*DebugDraw*/
	static inline const SdkPattern GameFramePreRenderUpdate = { L"48 8b c4 48 89 58 08 48 89 70 10 48 89 78 18 55 41 54 41 55 41 56 41 57 48 81 ec a0 03 00 00 48 8d a8 c8 fc ff ff 48 83 e5 c0 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 85 00 03 00 00" };
	static inline const SdkPattern GameDebugDraw_StaticContextHook = { L"e8 ?? ?? ?? ?? 44 0f b6 cf 48 89 44 24 20 44 0f b6 c6 48 8b d5 48 8b cb e8 ?? ?? ?? ?? 48 8b 74 24 48", +0x32 };
	static inline const SdkPattern GameDebugDraw_DebugDrawSid = { L"c5 fa 10 8d 18 02 00 00 c5 7a 10 6c 24 78 eb ?? 48 85 c0 0f 84 ?? ?? ?? ?? 4c 8d", +0x20 };
	static inline const SdkPattern WindowContext_WindowContext = { L"48 8b c4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 56 48 83 ec ?? 33 ff 49 8b f0 40 38 3d ?? ?? ?? ?? 8b ea 48 8b d9" };
	static inline const SdkPattern Text_textPrintV = { L"4c 8b dc 48 83 ec 58 c5 fa 10 84 24 80 00 00 00 49 8d 43 40 49 89 43 f0 49 8b 43 38 49 89 43 e8 ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? 8b 84 24 88 00 00 00 89 44 24 28 c5 fa 11 44 24 20" };
	static inline const SdkPattern Text2_GetTextWidthHeight = { L"48 8b c4 53 56 57 48 81 ec ?? ?? ?? ?? c5 f8 29 70 ?? 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 84 24 ?? ?? ?? ?? 48 8b f1 49 8b f8 48 8d 4c 24 40 8b da c5 f8 28 f3 e8 ?? ?? ?? ??" };
	static inline const SdkPattern Msg_s_MsgCon = { L"4c 8b dc 53 48 81 ec 80 00 00 00 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 44 24 70 b9 00 a0 00 00 49 c7 43 a0 00 10 00 00 48 8d 05 ?? ?? ?? ?? 49 c7 43 b0 00 80 00 00 49 89 43 98 48 8d 05 ?? ?? ?? ?? 49 89 43 a8 48 8d 05 ?? ?? ?? ?? 49 89 43 b8 48 8d 05", +0x7e };
	static inline const SdkPattern Msg_PrintToActiveMsgOutput = { L"48 8b c4 48 89 48 08 48 89 50 10 4c 89 40 18 4c 89 48 20 53 48 83 ec 30 48 85 c9 75 ?? 48 8b 1d ?? ?? ?? ?? 48 85 db 74 ?? b1 01 ff d3 48 8b 05 ?? ?? ?? ?? 48 85 c0 74 ??" };
	static inline const SdkPattern Msg_MsgConDrawBuffersHook = { L"8a 4c 24 30 e8 ?? ?? ?? ?? 48 8b 4d ef 48 33 cc e8 ?? ?? ?? ??", +0x9 };

	static inline const SdkPattern PrimServer_PrimServer = { L"48 8b ?? ?? ?? ?? ?? ?? 8b d3 ?? 8b 01 ?? 90 b0 01 00 00 48 83 65 08" };
	static inline const SdkPattern PrimServer_Create = { L"40 53 48 83 ec 30 48 8b da 48 8d 05 ?? ?? ?? ?? 48 8d 15 ?? ?? ?? ?? 48 89 44 24 20 41 b9 60 0d 00 00 4c 8d 05 ?? ?? ?? ?? 48 8d 0d ?? ?? ?? ?? e8 ?? ?? ?? ?? 48 8b d3" };
	static inline const SdkPattern PrimServer_TextPrintPosition = { L"4c 89 44 24 18 4c 89 4c 24 20 55 53 56 57 48 8d ac 24 48 fe ff ff 48 81 ec b8 02 00 00 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 85 ?? ?? ?? ?? 8b da 48 8d 85" };
	static inline const SdkPattern PrimServer_GetDefaultPrimParams = { L"40 53 48 83 ec 20 48 8b d9 e8 ?? ?? ?? ?? 48 83 63 08 00 88 43 01 66 c7 43 02 00 01 e8 ?? ?? ?? ?? 48 83 63 08 00 88 03 48 8b c3 48 83 c4 20" };
	static inline const SdkPattern PrimServer_DebugStringBaseHandler = { L"48 8b 05 ?? ?? ?? ?? 48 8d 4d 90 48 8b 10 48 8b b2 c8 00 00 00 48 8d 54 24 30 e8 ?? ?? ?? ?? c5 f8 10 07 c5 fa 10 0d ?? ?? ?? ?? 33 c9 89 5c 24 60 88 4c 24 68 48 8d 54 24 40 48 89 4c 24 6c 45 33 c9 48 8d 0d ?? ?? ?? ??", +0x42 };

	static inline const SdkPattern SsManager_StateScriptConsolePrinter = { L"48 89 5c 24 ?? 55 56 57 41 54 41 55 41 56 41 57 48 8d ac 24 ?? ?? ?? ?? b8 d0 11 00 00 e8 ?? ?? ?? ?? 48 2b e0 c5 f8 29 b4 24 ?? ?? ?? ?? c5 f8 29 bc 24 ?? ?? ?? ?? c5 78 29 84 24 ?? ?? ?? ?? c5 78 29 8c 24 ?? ?? ?? ?? c5 78 29 94 24 ?? ?? ?? ?? 48 8b 05 ?? ?? ?? ??" };

#endif

#if defined(T2R) || defined(T1X) 

	static inline const SdkPattern NdSystem_CreateThread = { L"40 53 55 56 57 41 56 48 81 ec 60 02 00 00 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 84 24 50 02 00 00 48 8d 44 24 30 48 8b fa 8b 12 48 8b e9 48 89 44 24 28 45 33 f6 33 c9 c7 44 24 20 04 00 00 00 44 89 74 24 30 e8 ?? ?? ?? ?? 48 8b f0 48 85 c0 75 6d" };
	static inline const SdkPattern NdSystem_ReleaseThreadHandle = { L"48 89 6c 24 10 48 89 74 24 18 57 48 83 ec 40 48 8b 31 33 ed 48 8b f9 48 85 f6 75 77 48 89 5c 24 50 e8 ?? ?? ?? ?? 48 8b d8 48 85 c0 74 04 b1 01 ff d3 e8 ?? ?? ?? ?? 48 85 c0 74 02 ff d0 e8 ?? ?? ?? ?? 48 85 c0 74 02 ff d0 e8 ?? ?? ?? ?? 48 85 c0 74 2b 48 89 6c 24 28 4c 8d 0d" };
	static inline const SdkPattern NdSystem_Thread_Join = { L"48 89 5c 24 18 56 48 83 ec 30 f6 41 0c 01 48 8b f1 48 89 7c 24 48 0f 85 ?? ?? ?? ??" };
	static inline const SdkPattern NdSystem_CreateMutex = { L"48 89 5c 24 10 48 89 6c 24 18 56 48 83 ec 30 33 ed 48 8b da 48 8b f1 40 38 6a 14 74 ?? 48 89 7c 24 40 e8 ?? ?? ?? ?? 48 8b f8 48 85 c0 74 ?? b1 01 ff d7" };

	static inline const SdkPattern Memory_s_MemoryMap = { L"01 00 00 00 02 00 00 00 00 00 ?? 00 00 00 00 00 00 00 10 00" };

	static inline const SdkPattern NdDevMenu_DMENU_String = { L"48 89 5c 24 ?? 48 89 74 24 ?? 57 48 83 ec 20 49 8b f1 49 8b d8 48 8b f9 e8 ?? ?? ?? ?? 48 8d 05 ?? ?? ?? ?? 48 89 5f 60 48 8b 5c 24 ?? 48 89 07" };
	static inline const SdkPattern NdDevMenu_DMENU_ItemPlaceHolder = { L"48 89 5c 24 08 57 48 83 ec 20 49 8b d8 48 8b f9 e8 ?? ?? ?? ?? 33 c0 48 8b cf 48 89 87 a0 00 00 00 48 2b cb 89 87 a8 00 00 00 48 89 47 60 48 89 87 80 00 00 00 48 8d 05 ?? ?? ?? ?? 48 89 07 90 0f b6 03 88 84 19 b0 00 00 00 48 8d 5b 01 84 c0 75 ee 48 8b 5c 24 30 48 8b c7 48 83 c4 20 5f c3", +0x170 };
	static inline const SdkPattern NdDevMenu_DMENU_ItemLine = { L"33 c0 c7 41 68 c8 c8 c8 ff 48 89 41 30 89 41 4e 48 89 41 38 48 89 41 40 89 41 48" };
	static inline const SdkPattern NdDevMenu_DMENU_ItemSubText = { L"48 89 5c 24 08 57 48 83 ec 20 48 8b da 48 8b f9 e8 ?? ?? ?? ?? 33 c0 48 89 9f b0 00 00 00 48 8b 5c 24 30 48 89 87 a0 00 00 00 48 89 47 60 48 89 87 80 00 00 00" };
	static inline const SdkPattern NdDevMenu_DMENU_ItemSubmenu = { L"48 89 5c 24 08 48 89 74 24 10 57 48 83 ec 20 49 8b d9 49 8b f0 48 8b f9 e8 ?? ?? ?? ?? 48 8b 44 24 50 33 c9 48 89 47 60 48 8b 44 24 58" };
	static inline const SdkPattern NdDevMenu_DMENU_ItemBool = { L"48 89 5c 24 08 48 89 74 24 10 57 48 83 ec 20 49 8b d9 49 8b f8 48 8b f1 e8 ?? ?? ?? ?? 33 c9 48 89 9e 80 00 00 00 48 8b 5c 24 30 48 8d 05 ?? ?? ?? ?? 48 89 06 48 8d 05 ?? ?? ?? ?? 48 89 86 b0 00 00 00 48 89 8e a0 00 00 00 48 89 4e 60 c7 86 a8 00 00 00 03 00 00 00 0f b6 07 88 86 b8 00 00 00 48 8b c6 48 89 7e 60 48 89 4e 58 c7 86 a0 00 00 00 01 00 00 00 48 8b 74 24 38 48 83 c4 20 5f c3" };

#endif

}