#pragma once
#include "NdGameSdk/sdkpattern.hpp"

namespace NdGameSdk::Patterns
{

#if defined(T2R)
	static inline const SdkPattern EngineComponents_s_table = { L"48 89 74 24 20 41 54 41 56 41 57 48 83 ec 30 8b f1 45 8b f8 4c 8d 25 ?? ?? ?? ?? 4c 8b f2 48 85 d2 0f 84 ?? ?? ?? ??", +0x14 };
	static inline const SdkPattern EngineComponents_s_ndConfig = { L"48 8d 0d ?? ?? ?? ?? b8 04 00 00 00 48 8d 89 80 00 00 00 c5 f8 10 03 48 8d 9b 80 00 00 00 c5 f8 11 41 80 c5 f8 10 4b 90 c5 f8 11 49 90 c5 f8 10 43 a0 c5 f8 11 41 a0 c5 f8 10 4b b0 c5 f8 11 49 b0 c5 f8 10 43 c0 c5 f8 11 41 c0 c5 f8 10 4b d0 c5 f8 11 49" };

	static inline const SdkPattern CommonGame_GameInit = { L"40 53 48 83 ec 30 48 8b d9 48 8d 4c 24 20 e8 ?? ?? ?? ?? 8b 10 85 d2 7e 11 c5 f8 10 00 c5 f8 11 03 48 8b c3 48 83 c4 30 5b c3" };
	static inline const SdkPattern CommonGameLoop_GameDebugUpdate = { L"48 8d 4d 08 e8 ?? ?? ?? ?? c7 44 24 30 01 00 00 00 4c 89 7c 24 28 c7 44 24 20 15 15 00 00 4c 8d 0d ?? ?? ?? ?? 33 d2 44 8d 42 03 48 8d 0d", +0x51 };

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

	static inline const SdkPattern ScriptManager_g_ScriptManagerGlobals = { L"48 89 5c 24 08 48 89 74 24 10 48 89 7c 24 18 55 41 54 41 55 41 56 41 57 48 8d ac 24 20 fd ff ff 48 81 ec e0 03 00 00 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 85", +0x42 };
	static inline const SdkPattern ScriptManager_InitializeReturn = { L"80 3D ?? ?? ?? ?? 00 75 19 4D 8B CD 41 B8 13 0F 00 00 49 8B D4 48 8D 0D ?? ?? ?? ?? E8 ?? ?? ?? ?? 90", +0x22 };
	static inline const SdkPattern ScriptManager_Lookup = { L"48 89 5c 24 08 48 89 6c 24 10 48 89 74 24 18 57 48 83 ec 40 48 8b d9 33 d2 8d 4a 03 e8 ?? ?? ?? ?? 48 85 c0 0f 84 ?? ?? ?? ?? 48 85 db 0f 84 ?? ?? ?? ?? c5 f9 ef c0 c5 fc 11 44 24 20 48 8d 3d ?? ?? ?? ?? 48 89 7c 24 20" };
	static inline const SdkPattern ScriptManager_LookupCFunc = { L"40 53 48 83 ec 20 48 8b da e8 ?? ?? ?? ?? 48 85 c0 75 ?? 48 8b c3 48 83 c4 20 5b c3" };
	static inline const SdkPattern ScriptManager_LookupInModule = { L"48 89 5c 24 08 48 89 6c 24 10 57 48 83 ec 20 48 8b d9 33 ed 48 85 c9 0f 84 ?? ?? ?? ?? 48 b8 ca de 18 72 18 1c ?? ?? ?? ??" };
	static inline const SdkPattern ScriptManager_AddModuleRequest = { L"48 89 5c 24 08 48 89 74 24 10 48 89 7c 24 18 41 54 41 56 41 57 48 83 ec 30 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 44 24 28 41 0f b6 f9 45 0f b6 e0 4c 8b fa 48 8b d9 48 8b b4 24 80 00 00 00 48 85 f6 74 03 c6 06 00 83 3a 0b 75 0f 33 c9 e8 ?? ?? ?? ??" };
	static inline const SdkPattern ScriptManager_ReloadModule = { L"48 8b c4 48 89 58 08 48 89 70 10 48 89 78 18 55 41 54 41 55 41 56 41 57 48 8d a8 38 fa ff ff 48 81 ec a0 06 00 00 c5 f8 29 70 c8 c5 f8 29 78 b8 48 8b 05" };
	static inline const SdkPattern ScriptManager_IsLoadModule = { L"48 89 5c 24 08 57 48 81 ec a0 00 00 00 48 8b d9 80 3d ?? ?? ?? ?? 00 75 20 4c 8d 0d ?? ?? ?? ?? 41 b8 9e 0b 00 00 48 8d 15 ?? ?? ?? ?? 48 8d 0d ?? ?? ?? ?? e8 ?? ?? ?? ?? c5 f9 ef c0 33 c0 c5 fc 11 44 24 30 c5 f8 11 44 24 50 48 89 44 24 60 8b 3d ?? ?? ?? ?? 48 8d 0d ?? ?? ?? ??" };
	static inline const SdkPattern ScriptManager_FindExportingModule = { L"48 89 5c 24 08 48 89 6c 24 10 48 89 74 24 18 57 41 54 41 55 41 56 41 57 48 83 ec 50 49 8b f0 0f b6 ea 48 8b f9 e8 ?? ?? ?? ?? 48 85 c0 0f 84 ?? ?? ?? ?? c5 f9 ef c0 c5 fc 11 44 24 30 4c 8d 2d ?? ?? ?? ?? 4c 89 6c 24 30 48 8d 05 ?? ?? ?? ?? 48 89 44 24 38 c7 44 24 48 11 0b 00 00" };

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
	static inline const SdkPattern NdDevMenu_DMENU_Menu_UpdateKeyboard = { L"48 89 5C 24 10 48 89 6C 24 18 48 89 74 24 20 57 41 54 41 55 41 56 41 57 48 81 EC A0 00 00 00 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 84 24 90 00 00 00 4C 8B F1 33 D2 41 BC 01 00 00 00 41 8B CC E8 ?? ?? ?? ?? 4C 8B E8 48 8D 88 10 0A 01 00" };
	static inline const SdkPattern NdDevMenu_DMENU_Menu_DeleteItem = { L"48 89 5c 24 ?? 57 48 83 ec 20 48 8b fa 48 8b d9 33 d2 48 8b 81 b0 00 00 00 8b ca 48 85 c0 74 ?? 48 3b c7 74 ?? 48 8b d0 48 8b 40 40" };
	static inline const SdkPattern NdDevMenu_DMENU_Menu_DeleteAllItems = { L"48 89 5c 24 08 48 89 74 24 18 57 48 83 ec 20 8b f2 48 8b d9 48 8d 05 ?? ?? ?? ?? 48 89 01 c7 44 24 38 11 00 00 00 4c 8d 0d ?? ?? ?? ?? 41 b8 8f 16 00 00 48 8d 15 ?? ?? ?? ?? 48 8d 4c 24 38 e8 ?? ?? ?? ?? 48 8b bb" };
	static inline const SdkPattern NdDevMenu_DMENU_Menu_DeferDeleteAllItems = { L"48 89 5c 24 ?? 48 89 74 24 18 57 48 83 ec 30 0f b6 f2 48 8b d9 c7 44 24 40 11 00 00 00 4c 8d 0d ?? ?? ?? ?? 41 b8 6c 16 00 00 48 8d 15 ?? ?? ?? ?? 48 8d 4c 24 40 e8 ?? ?? ?? ?? 90" };

	/*DebugDraw*/
	static inline const SdkPattern GameFramePreRenderUpdate = { L"48 89 5c 24 08 48 89 74 24 10 48 89 7c 24 18 4c 89 74 24 20 55 48 81 ec 20 06 00 00 48 8d ac 24 90 00 00 00 48 83 e5 c0 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 85 80 05 00 00 c5 f9 ef c0 c5 fc 11 85 80 02 00 00 c5 fc 11 85 a0 02 00 00 c5 fc 11 85 c0 02 00 00 c5 fc 11 85 e0 02 00 00 45 33 c0 48 8d 15 ?? ?? ?? ?? 48 8d 8d 80 02 00 00" };
	static inline const SdkPattern GameDebugDraw_StaticContextHook = { L"e8 ?? ?? ?? ?? 48 89 44 24 20 44 0f b6 cf 44 0f b6 c6 48 8b d5 48 8b cb e8 ?? ?? ?? ?? e8 ?? ?? ?? ?? 0f 1f 40 00 66 66 0f 1f 84 00 00 00 00 00 48 8b 5c 24 40 48 8b 6c 24 48 48 8b 74 24 58 48 83 c4 30 5f c3", +0x30 };
	static inline const SdkPattern GameDebugDraw_DebugDrawSid = { L"44 88 A5 ?? ?? ?? ?? 45 38 A7 ?? ?? ?? ?? 74 2D 49 8D 87 ?? ?? ?? ?? 48 89 44 24 20 4C 8D 0D ?? ?? ?? ?? 4C 8D 05 ?? ?? ?? ?? BA 80 00 00 00 48 8D 8D", +0x4D };
	static inline const SdkPattern WindowContext_WindowContext = { L"48 89 5c 24 18 48 89 6c 24 20 56 48 83 ec 30 80 3d ?? ?? ?? ?? 00 49 8b f0 48 63 ea 48 8b d9 74 ?? 33 c0 c7 01 ff ff ff ff 48 89 41 08 48 89 41 10 48 89 41 18 48 8b c1 c7 41 20 ff ff ff ff 48 8b 5c 24 50 48 8b 6c 24 58" };
	static inline const SdkPattern FrameParams_GetFrameParams = { L"40 57 48 83 ec 30 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 44 24 28 e8 ?? ?? ?? ?? 0f b6 f8 84 c0 74 ?? 48 8d 54 24 20 b9 02 00 00 00 e8 ?? ?? ?? ?? 84 c0 74 ?? 48 8b 44 24 20 48 8b 4c 24 28 48 33 cc e8 ?? ?? ?? ?? 48 83 c4 30 5f c3" };
	static inline const SdkPattern Text_textPrintV = { L"4c 8b dc 48 83 ec 58 c5 fa 10 84 24 80 00 00 00 49 8d 43 40 49 89 43 f0 49 8b 43 38 49 89 43 e8 33 c0 89 44 24 38 89 44 24 30 8b 84 24 88 00 00 00 89 44 24 28 c5 fa 11 44 24 20" };
	static inline const SdkPattern Text2_GetTextWidthHeight = { L"4c 8b dc 53 56 57 48 81 ec f0 00 00 00 c4 c1 78 29 73 d8 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 84 24 d0 00 00 00 33 c0 48 8b f1 48 8d 4c 24 40 41 89 43 a0 49 89 43 a8 49 8b f8 c5 f8 28 f3 8b da" };
	static inline const SdkPattern Msg_s_MsgCon = { L"4c 8b dc 48 81 ec 88 00 00 00 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 44 24 70 48 8d 05 ?? ?? ?? ?? 49 c7 43 a0 00 10 00 00 49 89 43 98 49 8d 4b 98 48 8d 05", +0x81 };
	static inline const SdkPattern Msg_PrintToActiveMsgOutput = { L"48 89 4c 24 08 48 89 54 24 10 4c 89 44 24 18 4c 89 4c 24 20 48 83 ec 38 48 85 c9 75 ?? 48 89 5c 24 30 e8 ?? ?? ?? ?? 48 8b d8 48 85 c0 74 ?? b1 01 ff d3 e8 ?? ?? ?? ?? 48 85 c0 74 ?? ff d0 e8 ?? ?? ?? ?? 48 85 c0 74" };

	static inline const SdkPattern PrimServer_PrimServer = { L"48 89 8d 80 00 00 00 48 89 75 18 c7 44 24 40 01 00 00 00 48 c7 44 24 38 ff ff ff ff c6 44 24 30 03 4c 89 74 24 28 c7 44 24 20 df 0e 00 00 4c 8d 0d", 0x5b };
	static inline const SdkPattern PrimServer_TextPrintPosition = { L"4c 89 44 24 18 4c 89 4c 24 20 53 55 56 57 48 81 ec a8 02 00 00 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 84 24 90 02 00 00 49 8b f8 48 8d ac 24 e8 02 00 00 8b da 48 8b f1" };
	static inline const SdkPattern PrimServer_GetDefaultPrimParams = { L"48 89 5c 24 08 57 48 83 ec 20 48 8b d9 e8 ?? ?? ?? ?? 88 43 01 40 b7 01 66 c7 43 02 00 01 48 c7 43 08 00 00 00 00 e8 ?? ?? ?? ?? 48 85 c0 74 08" };
	static inline const SdkPattern PrimServer_DebugStringBaseHandler = { L"48 89 6c 24 28 48 8d 94 24 90 00 00 00 4c 8b cf 48 c7 44 24 20 00 00 00 00 41 b8 00 02 00 00 48 8b 08 48 83 c9 01 e8 ?? ?? ?? ?? 48 8b 05 ?? ?? ?? ?? 48 8b 08 48 8b a9 c8 00 00 00 e8 ?? ?? ?? ?? 88 44 24 31 40 b7 01 66 c7 44 24 32 00 01 e8 ?? ?? ?? ?? 48 85 c0 74 08 0f b6 78 09 40 c0 ef 07 48 8b 05 ?? ?? ?? ?? 4c 8d 44 24 30 c5 f8 10 06 c5", +0x8D };


#elif defined(T1X)
	static inline const SdkPattern EngineComponents_s_table = { L"48 89 6c 24 18 56 41 56 41 57 48 83 ec 30 8b f1 45 8b", +0x13 };
	static inline const SdkPattern EngineComponents_s_ndConfig = { L"B8 04 00 00 00 48 8D ?? ?? ?? ?? ?? 8D 50 7C C5 F8 10 03 C5 F8 11 01 C5 F8 10 4B 10 C5 F8 11 49 10 C5 F8 10 43 20 C5 F8 11 41 20 C5 F8 10 4B 30 C5 F8 11 49 30 C5 F8 10 43 40 C5 F8 11 41 40 C5 F8 10 4B 50 C5 F8 11 49 50 C5 F8 10 43 60 C5 F8 11 41 60", +0x5 };

	static inline const SdkPattern CommonGame_GameInit = { L"40 53 48 83 ec 40 80 3d ?? ?? ?? ?? 00 48 8b d9 74 0c 48 8d 4c 24 20 e8 ?? ?? ?? ?? eb 0a 48 8d 4c 24 30"};
	static inline const SdkPattern CommonGame_PrimServer_Create = { L"41 ff 90 ?? ?? ?? ?? 48 83 65 ?? 00 48 8d 05 ?? ?? ?? ??" };
	static inline const SdkPattern CommonGameLoop_GameDebugUpdate = { L"48 8b 0d ?? ?? ?? ?? 48 8b 01 ff 90 a0 00 00 00 e8 ?? ?? ?? ?? e8 ?? ?? ?? ?? 33 d2 89 5c 24 30 4c 89 6c 24 28 4c 8d 0d ?? ?? ?? ?? 48 8d 0d ?? ?? ?? ?? c7 44 24 20 42 15 00 00 44 8d 42 03 e8 ?? ?? ?? ?? 44 38 3d ?? ?? ?? ?? 74 11", +0x8A };

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

	static inline const SdkPattern ScriptManager_g_ScriptManagerGlobals = { L"48 89 5c 24 08 48 89 74 24 10 57 48 83 ec 20 48 8b d9 48 63 fa 48 ?? ?? ?? ?? ?? ?? 45 33 c9 4c 89 49", +0x15 };
	static inline const SdkPattern ScriptManager_InitializeReturn = { L"4c 8d 0d ?? ?? ?? ?? 4c 8b c3 49 8b d6 48 8b cf e8 ?? ?? ?? ?? 4c 8b c3 44 89 64 24 40 48 8d 54 24 40 48 8b cb e8 ?? ?? ?? ?? 48 85 c0 74 10 48 89 38 44 89 70 08 48 89 05 ?? ?? ?? ?? eb 08 48 83 25 ?? ?? ?? ?? 00", +0x68 };
	static inline const SdkPattern ScriptManager_Lookup = { L"48 89 5c 24 10 48 89 4c 24 08 57 48 83 ec 60 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 44 24 50 48 83 3d" };
	static inline const SdkPattern ScriptManager_LookupCFunc = { L"40 53 48 83 ec ?? 48 8b da e8 ?? ?? ?? ?? 48 85 c0 75 ?? 48 8b c3 eb ?? 48 8b 00 48 83 c4 ?? 5b c3" };
	static inline const SdkPattern ScriptManager_LookupInModule = { L"48 89 4c 24 08 57 48 83 ec 50 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 44 24 48 33 ff 48 8b d9 48 85 c9 0f 84 ?? ?? ?? ?? 48 b9 25 23 22 84 e4 9c" };
	static inline const SdkPattern ScriptManager_AddModuleRequest = { L"48 8b c4 48 89 58 08 48 89 70 10 48 89 78 18 4c 89 60 20 55 41 56 41 57 48 8d a8 28 fc ff ff 48 81 ec c0 04 00 00 48 ?? ?? ?? ?? ?? ?? 48 33 c4 48 89 85 b0 03 00 00 48" };
	static inline const SdkPattern ScriptManager_ReloadModule = { L"48 8b c4 48 89 58 08 48 89 70 10 48 89 78 18 55 41 54 41 55 41 56 41 57 48 8d a8 f8 f9 ff ff 48 81 ec e0 06 00 00 c5 f8 29 70 c8 48 ?? ?? ?? ?? ?? ?? 48 33 c4 48 89 85 c0 05 00" };
	static inline const SdkPattern ScriptManager_IsLoadModule = { L"48 8b c4 48 89 58 08 48 89 70 10 48 89 78 18 55 48 8d 68 a1 48 81 ec c0 00 00 00 48 ?? ?? ?? ?? ?? ?? 48 33 c4 48 89 45 47 c5 f9 ef" };
	static inline const SdkPattern ScriptManager_FindExportingModule = { L"4c 8b dc 49 89 5b 08 49 89 73 10 49 89 7b 18 4d 89 63 20 41 55 41 56 41 57 48 83 ec 60 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 44 24 58 48 8b 05 ?? ?? ?? ?? 49 8b f8 44 8a ea 48 8b f1 48 85 c0 0f 84 ?? ?? ?? ?? c5 f9 ef c0 c5 fc 11 44 24 38" };

	static inline const SdkPattern NdDevMenu_GameConfig_DevMode = { L"8a 8f ?? ?? ?? ?? 84 c9 0f 94 c2 84 c9 0f 95 c1" };
	static inline const SdkPattern NdDevMenu_NdDevMenuAppend_Particles = { L"40 56 48 83 ec 30 48 8b f1 33 c9 e8 ?? ?? ?? ?? 84 c0 0f 84 ?? ?? ?? ?? 48 89 5c 24 40 4c 8d 0d ?? ?? ?? ??" };

	static inline const SdkPattern NdDevMenu_DMENU_Component = { L"40 53 57 41 57 48 83 ec 30 45 33 ff c7 41 68 c8 c8 c8 ff 4c 89 b9 80 00 00 00 48 ?? ?? ?? ?? 56 02 48 ?? ?? ?? ?? da 4c 89 79 30 48 8b f9 44 89 79 4e 4c 89 79 38 4c 89" };
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
	static inline const SdkPattern NdDevMenu_Assert_UpdateSelectRegionByNameMenu = { L"cc 48 85 db 74 ?? 33 c9 ff d3 48 8d 05 ?? ?? ?? ?? c7 44 24 ?? 10 00 00 00 41 b9 8e 00 00 00" };
	static inline const SdkPattern NdDevMenu_Assert_UpdateSelectIgcByNameMenu = { L"cc 48 85 db 74 ?? 33 c9 ff d3 48 8d 05 ?? ?? ?? ?? bb 10 00 00 00 41 b9 84 03 00 00" };
	static inline const SdkPattern NdDevMenu_Assert_UpdateSelectSpawnerByNameMenu = { L"cc 48 85 db 74 ?? 33 c9 ff d3 48 8d 05 ?? ?? ?? ?? c7 44 24 ?? 10 00 00 00 41 b9 a3 00 00 00" };

	static inline const SdkPattern Particle_ParticleManager_Init = { L"48 8b c4 48 89 58 18 48 89 48 08 55 56 57 41 54 41 55 41 56 41 57 48 8d 68 a8 48 81 ec 20 01 00 00 4c 8d ?? ?? ?? ?? 00 c5 f8 29 70 b8 41 bd 36 00 00" };
	static inline const SdkPattern Particle_ParticleInternal_ParticleDebug = { L"48 8d ?? ?? ?? ?? ?? e8 ?? ?? ?? ?? 4c 8b c3 48 8d ?? ?? ?? ?? ?? 48 8b d5 e8 ?? ?? ?? ?? 48 8d ?? ?? ?? ?? ?? 48 89 7c 24" };
	static inline const SdkPattern Particle_ParticleInternal_ParticleDebug_Init = { L"48 89 5c 24 10 48 89 6c 24 18 48 89 74 24 20 57 41 54 41 55 41 56 41 57 48 83 ec 50 48 8d ?? ?? ?? ?? ?? 4c 8b f1 48 89 ?? ?? ?? 80 00 00 00 48 8d ?? ?? ?? ?? ?? 48 89 41 28 b9 00 2d" };
	static inline const SdkPattern Particle_ParticleInternal_ParticleDebug_Constructor = { L"33 d2 b8 11 c0 00 00 66 89 41 18 48 8b c1 89 51 04 89 51 20 66 89 51 24 88 51 26 48 89 51 30 48 89 51 38 48 89 51 40 48 89 51 50 48 89 51 58 48 89 51 60 48 89 51 68 48 89 51 70 48 89 51 78 48 89 91 80 00 00 00 48 89 91 88 00 00 00 48 89 91 90 00 00 00 48 89 91 98 00 00 00 48 89 91 a0 00 00 00 48 89 91 a8 00 00 00 48" };
	static inline const SdkPattern Particle_ParticleInternal_RenderUpdate = { L"4c 8b dc 53 56 48 81 ec a8 00 00 00 48 8b ?? ?? ?? ?? 02 48 33 c4 48 89 84 24 88 00 00 00 4c 8b 0a 48 8b f2 48 8b d9 4d 85" };
	static inline const SdkPattern Particle_ParticleInternal_OnExecuteRootDataSelector = { L"40 53 55 56 57 41 55 48 81 ec 30 01 00 00 48 ?? ?? ?? ?? ?? 02 48 33 c4 48 89 84 24 20 01 00 00 8b da c7 44 24 38 10 00 00 00 48 8b" };

	/*DebugDraw*/
	static inline const SdkPattern GameFramePreRenderUpdate = { L"48 8b c4 48 89 58 08 48 89 70 10 48 89 78 18 55 41 54 41 55 41 56 41 57 48 81 ec a0 03 00 00 48 8d a8 c8 fc ff ff 48 83 e5 c0 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 85 00 03 00 00" };
	static inline const SdkPattern GameDebugDraw_StaticContextHook = { L"e8 ?? ?? ?? ?? 44 0f b6 cf 48 89 44 24 20 44 0f b6 c6 48 8b d5 48 8b cb e8 ?? ?? ?? ?? 48 8b 74 24 48", +0x32 };
	static inline const SdkPattern GameDebugDraw_DebugDrawSid = { L"c5 fa 10 8d c0 01 00 00 c5 7a 10 64 24 78 45 33 ed eb 82 48 85 c0 0f 84 ba 00 00", +0x23 };
	static inline const SdkPattern WindowContext_WindowContext = { L"48 8b c4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 56 48 83 ec ?? 33 ff 49 8b f0 40 38 3d ?? ?? ?? ?? 8b ea 48 8b d9" };
	static inline const SdkPattern FrameParams_GetFrameParams = { L"40 53 48 83 ec 20 e8 ?? ?? ?? ?? 8a d8 84 c0 74 1a 48 8d 54 24 30 b9 02 00 00 00 e8 ?? ?? ?? ?? 84 c0 74 07 48 8b 44 24 30 eb 6a e8 6c 00 00 00 4c 8b 05" };
	static inline const SdkPattern Text_textPrintV = { L"4c 8b dc 48 83 ec 58 c5 fa 10 84 24 80 00 00 00 49 8d 43 40 49 89 43 f0 49 8b 43 38 49 89 43 e8 ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? 8b 84 24 88 00 00 00 89 44 24 28 c5 fa 11 44 24 20" };
	static inline const SdkPattern Text2_GetTextWidthHeight = { L"48 8b c4 53 56 57 48 81 ec ?? ?? ?? ?? c5 f8 29 70 ?? 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 84 24 ?? ?? ?? ?? 48 8b f1 49 8b f8 48 8d 4c 24 40 8b da c5 f8 28 f3 e8 ?? ?? ?? ??" };
	static inline const SdkPattern Msg_s_MsgCon = { L"4c 8b dc 53 48 81 ec 80 00 00 00 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 44 24 70 b9 00 a0 00 00 49 c7 43 a0 00 10 00 00 48 8d 05 ?? ?? ?? ?? 49 c7 43 b0 00 80 00 00 49 89 43 98 48 8d 05 ?? ?? ?? ?? 49 89 43 a8 48 8d 05 ?? ?? ?? ?? 49 89 43 b8 48 8d 05", +0x7e };
	static inline const SdkPattern Msg_PrintToActiveMsgOutput = { L"48 8b c4 48 89 48 08 48 89 50 10 4c 89 40 18 4c 89 48 20 53 48 83 ec 30 48 85 c9 75 ?? 48 8b 1d ?? ?? ?? ?? 48 85 db 74 ?? b1 01 ff d3 48 8b 05 ?? ?? ?? ?? 48 85 c0 74 ??" };
	static inline const SdkPattern Msg_MsgConDrawBuffersHook = { L"8a 4c 24 30 e8 ?? ?? ?? ?? 48 8b 4d ef 48 33 cc e8 ?? ?? ?? ??", +0x9 };

	static inline const SdkPattern PrimServer_PrimServer = { L"48 8b ?? ?? ?? ?? ?? 48 8b d3 4c 8b 01 41 ff 90 b0 01 00 00 48 83 65 08" };
	static inline const SdkPattern PrimServer_Create = { L"40 53 48 83 ec 30 48 8d 0d ?? ?? ?? ?? 48 8b da 48 8d 05 ?? ?? ?? ?? 48 8b d1 41 b9 60 0d 00 00" };
	static inline const SdkPattern PrimServer_TextPrintPosition = { L"4c 89 44 24 18 4c 89 4c 24 20 55 53 56 57 48 8d ac 24 48 fe ff ff 48 81 ec b8 02 00 00 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 85 ?? ?? ?? ?? 8b da 48 8d 85" };
	static inline const SdkPattern PrimServer_GetDefaultPrimParams = { L"40 53 48 83 ec 20 48 8b d9 e8 ?? ?? ?? ?? 48 83 63 08 00 88 43 01 66 c7 43 02 00 01 e8 ?? ?? ?? ?? 48 83 63 08 00 88 03 48 8b c3 48 83 c4 20" };
	static inline const SdkPattern PrimServer_DebugStringBaseHandler = { L"48 8b 05 ?? ?? ?? ?? 48 8d 4d 90 48 8b 10 48 8b b2 c8 00 00 00 48 8d 54 24 30 e8 ?? ?? ?? ?? c5 f8 10 07 c5 fa 10 0d ?? ?? ?? ?? 33 c9 89 5c 24 60 88 4c 24 68 48 8d 54 24 40 48 89 4c 24 6c 45 33 c9 48 8d 0d ?? ?? ?? ??", +0x42 };

	static inline const SdkPattern SsManager_StateScriptConsolePrinter = { L"48 89 5c 24 ?? 55 56 57 41 54 41 55 41 56 41 57 48 8d ac 24 ?? ?? ?? ?? b8 d0 11 00 00 e8 ?? ?? ?? ?? 48 2b e0 c5 f8 29 b4 24 ?? ?? ?? ?? c5 f8 29 bc 24 ?? ?? ?? ?? c5 78 29 84 24 ?? ?? ?? ?? c5 78 29 8c 24 ?? ?? ?? ?? c5 78 29 94 24 ?? ?? ?? ?? 48 8b 05 ?? ?? ?? ??" };

#endif

#if defined(T2R) || defined(T1X) 

	static inline const SdkPattern Memory_s_MemoryMap = { L"01 00 00 00 02 00 00 00 00 00 ?? 00 00 00 00 00 00 00 10 00" };

	static inline const SdkPattern NdDevMenu_DMENU_String = { L"48 89 5c 24 ?? 48 89 74 24 ?? 57 48 83 ec 20 49 8b f1 49 8b d8 48 8b f9 e8 ?? ?? ?? ?? 48 8d 05 ?? ?? ?? ?? 48 89 5f 60 48 8b 5c 24 ?? 48 89 07" };
	static inline const SdkPattern NdDevMenu_DMENU_ItemPlaceHolder = { L"48 89 5c 24 08 57 48 83 ec 20 49 8b d8 48 8b f9 e8 ?? ?? ?? ?? 33 c0 48 8b cf 48 89 87 a0 00 00 00 48 2b cb 89 87 a8 00 00 00 48 89 47 60 48 89 87 80 00 00 00 48 8d 05 ?? ?? ?? ?? 48 89 07 90 0f b6 03 88 84 19 b0 00 00 00 48 8d 5b 01 84 c0 75 ee 48 8b 5c 24 30 48 8b c7 48 83 c4 20 5f c3", +0x170 };
	static inline const SdkPattern NdDevMenu_DMENU_ItemLine = { L"33 c0 c7 41 68 c8 c8 c8 ff 48 89 41 30 89 41 4e 48 89 41 38 48 89 41 40 89 41 48" };
	static inline const SdkPattern NdDevMenu_DMENU_ItemSubText = { L"48 89 5c 24 08 57 48 83 ec 20 48 8b da 48 8b f9 e8 ?? ?? ?? ?? 33 c0 48 89 9f b0 00 00 00 48 8b 5c 24 30 48 89 87 a0 00 00 00 48 89 47 60 48 89 87 80 00 00 00" };
	static inline const SdkPattern NdDevMenu_DMENU_ItemSubmenu = { L"48 89 5c 24 08 48 89 74 24 10 57 48 83 ec 20 49 8b d9 49 8b f0 48 8b f9 e8 ?? ?? ?? ?? 48 8b 44 24 50 33 c9 48 89 47 60 48 8b 44 24 58" };
	static inline const SdkPattern NdDevMenu_DMENU_ItemBool = { L"48 89 5c 24 08 48 89 74 24 10 57 48 83 ec 20 49 8b d9 49 8b f8 48 8b f1 e8 ?? ?? ?? ?? 33 c9 48 89 9e 80 00 00 00 48 8b 5c 24 30 48 8d 05 ?? ?? ?? ?? 48 89 06 48 8d 05 ?? ?? ?? ?? 48 89 86 b0 00 00 00 48 89 8e a0 00 00 00 48 89 4e 60 c7 86 a8 00 00 00 03 00 00 00 0f b6 07 88 86 b8 00 00 00 48 8b c6 48 89 7e 60 48 89 4e 58 c7 86 a0 00 00 00 01 00 00 00 48 8b 74 24 38 48 83 c4 20 5f c3" };

#endif

}