#pragma once
#include "NdGameSdk/sdkpattern.hpp"

namespace NdGameSdk::Patterns
{
	static inline const SdkPattern Weapon_GiveWeaponArt = { L"48 83 ec 28 65 48 8b 04 25 58 00 00 00 ba 80 00 00 00 48 8b 08 8b 04 0a 39 ?? ?? ?? ?? ?? 0f ?? ?? 00 00 00 48 ?? ?? ?? ?? ?? 06 e8 ?? ?? ?? ?? 83 ?? ?? ?? ?? 06 ff 75 ?? 48 ba 25 23 22 84 e4 9c f2 cb 48 8d ?? ?? ?? ?? 00 4c 8b c2 41 b9 0a 00 00 00 49 bb b3 01 00 00 00 01 00 00 48 0f be 01 48 ff c1 4c 33 c0 4d 0f af c3 49 83" };

	static inline const SdkPattern Player_PlayerMenu_CreateGiveMenuWeaponItems = { L"48 8b c4 48 89 58 10 48 89 70 18 48 89 78 20 55 41 54 41 55 41 56 41 57 48 8d 68 98 48 81 ec 40 01 00 00 48 8b ?? ?? ?? ?? ?? ?? 33 c4 48 89 45 30 33 ff 48 89 4c 24 40 89 7c 24 30 4c 8b f1 e8 ?? ?? ?? ?? 48 89 44 24" };
	static inline const SdkPattern Player_PlayerMenu_GiveMenuWeapon_Main = { L"48 8d 15 ?? ?? ?? ?? 40 88 7c 24 20 4c 8b 0c 0e 49 8b cd e8 ?? ?? ??", 0x7 };
	static inline const SdkPattern Player_PlayerMenu_GiveMenuWeapon_SubMenu = { L"48 8d 15 ?? ?? ?? ?? 49 8b cf e8 ?? ?? ?? ?? 4c 8b e8", 0x7 };
	static inline const SdkPattern Player_PlayerMenu_GiveMenuWeapon_Entry = { L"4c 8d 05 ?? ?? ?? ?? 48 8d 15 ?? ?? ?? ?? 48 8d 4d 90 e8 ?? ?? ?? ?? 48 89 7c 24 28 45 33 c9 4d 8b c5 48 89 7c 24 20 49 8b cf 48 8d 50 18", 0x7 };
	static inline const SdkPattern Player_PlayerMenu_GiveMenuWeapon_SubSection = { L"48 8d 15 ?? ?? ?? ?? 40 88 7c 24 20 4e 8b 0c 29 48 8b 4c 24 58", 0x10 };
}