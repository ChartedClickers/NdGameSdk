#pragma once
#include "NdGameSdk/sdkpattern.hpp"

namespace NdGameSdk::Patterns
{
	static inline const SdkPattern Weapon_GiveWeaponArt = { L"48 83 ec 28 65 48 8b 0c 25 58 00 00 00 8b 05 ?? ?? ?? ?? 41 b8 f8 00 00 00 48 8b 14 c1 41 8b 04 10 39 05 ?? ?? ?? ?? 7f 22 80 3d ?? ?? ?? ?? 00 74 09 48 83 c4 28 e9 55 00 00 00 48 8d" };

	static inline const SdkPattern Player_PlayerMenu_CreateGiveMenuWeaponItems = { L"48 89 5c 24 10 48 89 74 24 18 48 89 7c 24 20 55 41 54 41 55 41 56 41 57 48 8d 6c 24 b0 48 81 ec 50 01 00 00 48 8b 05 ?? ?? ?? ?? 48 33 c4 48 89 45 40 4c 8b e9 48 89 4c 24 50 45 33 f6 41 8b f6 44 89 74 24 44 44 89 74 24 40 e8 ?? ?? ?? ?? 48 89 44 24 58 e8 ?? ?? ?? ?? 4c 8b f8" };
	static inline const SdkPattern Player_PlayerMenu_GiveMenuWeapon_Main = { L"48 8d 15 ?? ?? ?? ?? 48 8b cb e8 ?? ?? ?? ?? eb 03 49 8b c6 48 8b d0 49 8b cd e8 ?? ?? ?? ??", 0x7 };
	static inline const SdkPattern Player_PlayerMenu_GiveMenuWeapon_Entry = { L"4c 8d 05 ?? ?? ?? ?? 48 8d 15 ?? ?? ?? ?? 48 8d 4d 80 e8 ?? ?? ?? ?? 90 83 ce 01 89 74 24 44 89 74 24 40 48 8d 50 18 4c 89 74 24 28 4c 89 74 24 20", 0x7 };
	static inline const SdkPattern Player_PlayerMenu_GiveMenuWeapon_SubMenu = { L"48 8d 15 ?? ?? ?? ?? 48 8b cb e8 ?? ?? ?? ?? 4c 8b e0 eb 03 4d 8b e6 b9 c8 00 00 00 e8 ?? ?? ?? ??", 0x7 };
	static inline const SdkPattern Player_PlayerMenu_GiveMenuWeapon_SubSection = { L"48 8d 15 ?? ?? ?? ?? 48 8b cb e8 ?? ?? ?? ?? eb 03 49 8b c6 48 8b d0 49 8b cc e8 ?? ?? ?? ?? ff c7 48 83 c6 08 41 3b 3f", 0x7 };
}