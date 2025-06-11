#include "player-menu.hpp"
#include "./NdGameSdk/ndgame/t1x/ndgamepatterns.hpp"

#include <stdio.h>
#include <stdlib.h>

namespace NdGameSdk::game::player {

	PlayerMenu::PlayerMenu(weapon::Weapon* pWeaponProcess) : m_WeaponProcess(pWeaponProcess) {}

	using GiveWeaponArtFn = ndlib::script::ScriptValue* (weapon::Weapon::*)();
	uintptr_t GiveWeaponArtFunctAddr[0x2];

	uintptr_t GiveMenuWeaponMain_Main_ReturnAddr = NULL;
	void GiveMenuWeaponMain_Main_CC();
	uintptr_t GiveMenuWeaponMain_SubMenu_ReturnAddr = NULL;
	void GivePlayerWeapon_SubMenuCC();
	uintptr_t GiveMenuWeaponMain_Entry_ReturnAddr = NULL;
	void GivePlayerWeapon_EntryCC();
	uintptr_t GiveMenuWeaponMain_SubSection_ReturnAddr = NULL;
	void GivePlayerWeapon_SubCC();

	void PlayerMenu::GiveMenuWeaponItemsPatch(/*DMENU::Menu* pMenu*/) {

			GiveWeaponArtFn functionPointer = &weapon::Weapon::GiveWeaponArt;
			std::memcpy(&GiveWeaponArtFunctAddr[0x0], &functionPointer, sizeof(GiveWeaponArtFn));
			GiveWeaponArtFunctAddr[0x1] = reinterpret_cast<uintptr_t>(m_WeaponProcess);

			Patterns::SdkPattern findpattern{};
			auto module = Utility::memory::get_executable();

			findpattern = Patterns::Player_PlayerMenu_GiveMenuWeapon_Main;
			m_GiveMenuWeaponMainHook = Utility::WritePatchPattern_Hook(module, findpattern.pattern, wstr(Patterns::Player_PlayerMenu_GiveMenuWeapon_Main),
				findpattern.offset, (void*)GiveMenuWeaponMain_Main_CC);

			findpattern = Patterns::Player_PlayerMenu_GiveMenuWeapon_SubMenu;
			m_GiveMenuWeaponSubMenuHook = Utility::WritePatchPattern_Hook(module, findpattern.pattern, wstr(Patterns::Player_PlayerMenu_GiveMenuWeapon_SubMenu),
				findpattern.offset, (void*)GivePlayerWeapon_SubMenuCC);

			findpattern = Patterns::Player_PlayerMenu_GiveMenuWeapon_Entry;
			m_GiveMenuWeaponEntryHook = Utility::WritePatchPattern_Hook(module, findpattern.pattern, wstr(Patterns::Player_PlayerMenu_GiveMenuWeapon_Entry),
				findpattern.offset, (void*)GivePlayerWeapon_EntryCC);

			findpattern = Patterns::Player_PlayerMenu_GiveMenuWeapon_SubSection;
			m_GiveMenuWeaponSubSectionHook = Utility::WritePatchPattern_Hook(module, findpattern.pattern, wstr(Patterns::Player_PlayerMenu_GiveMenuWeapon_SubSection),
				findpattern.offset, (void*)GivePlayerWeapon_SubCC);

			if (!m_GiveMenuWeaponMainHook ||
				!m_GiveMenuWeaponSubMenuHook ||
				!m_GiveMenuWeaponEntryHook ||
				!m_GiveMenuWeaponSubSectionHook) {
				throw SdkComponentEx{ "Failed to patch game functions!", SdkComponentEx::ErrorCode::PatchFailed };
			}

			GiveMenuWeaponMain_Main_ReturnAddr = m_GiveMenuWeaponMainHook->get_original();
			GiveMenuWeaponMain_SubMenu_ReturnAddr = m_GiveMenuWeaponSubMenuHook->get_original();
			GiveMenuWeaponMain_Entry_ReturnAddr = m_GiveMenuWeaponEntryHook->get_original();
			GiveMenuWeaponMain_SubSection_ReturnAddr = m_GiveMenuWeaponSubSectionHook->get_original();
	}

    const char* GivePlayerWeaponMain(const int32_t index, const int32_t mode)
    {
		static const char* weapon_subentry_names[] = { "Melee", "Joel", "Ellie", "Throwables", "Consumables", "Misc" };
		static const constexpr uint32_t GivePlayerWeapon_EntryListMax = sizeof(weapon_subentry_names) / sizeof(weapon_subentry_names[0]);
		static const char* string_index = nullptr;

		string_index = nullptr;

		if (index <= GivePlayerWeapon_EntryListMax) {
			switch (mode) {
			case 1:
			case 2:
			{
				string_index = weapon_subentry_names[index];
				break;
			}
			default: {
				static char temp_str[128];
				memset((void*)temp_str, 0, sizeof(temp_str));
				return temp_str;
			}
			}
		}

        if (string_index[0] == '\0')
            string_index = "(null)";

        return string_index;
    }

	void __attribute__((naked)) GiveMenuWeaponMain_Main_CC() {
		__asm {
			push rcx;
			push r9;
			mov rcx, qword ptr[r15 + 0x10];
			mov r9, qword ptr[rsi + rcx];
			mov rdx, qword ptr[r9 + 0x38];
			pop r9;
			pop rcx;
			jmp[rip + GiveMenuWeaponMain_Main_ReturnAddr];
		}
	}

	void __attribute__((naked)) GivePlayerWeapon_SubCC() {
		__asm {
			push rcx;
			push rdi;
			push r9;
			push r8;
			push r15;
			push r14;
			push rsi;
			push rdx;
			mov rcx, [GiveWeaponArtFunctAddr + 0x8];
			call[rip + GiveWeaponArtFunctAddr];
			pop rdx;
			mov r15, rax;
			xor rdi, rdi;
			mov r14d, edi;
			mov rsi, rdi;
		iteration:;
			mov rax, qword ptr[r15 + 0x8];
			cmp qword ptr[rax + rsi], rdi
			je _continue;
			cmp qword ptr[rsi + rax], r9
			jne _continue;
			mov rcx, qword ptr[r15 + 0x10];
			mov r9, qword ptr[rsi + rcx];
			mov rdx, qword ptr[r9 + 0x38];
			jmp code_exit;
		_continue:;
			inc r14d;
			add rsi, 0x8;
			cmp r14d, dword ptr[r15];
			jl iteration;
		code_exit:;
			pop rsi;
			pop r14;
			pop r15;
			pop r8;
			pop r9;
			pop rdi;
			pop rcx;
			jmp[rip + GiveMenuWeaponMain_SubSection_ReturnAddr];
		}
	}

	void __attribute__((naked)) GivePlayerWeapon_SubMenuCC() {
		__asm {
			mov ecx, esi;
			mov edx, 1;
			call GivePlayerWeaponMain;
			mov rdx, rax;
			jmp[rip + GiveMenuWeaponMain_SubMenu_ReturnAddr];
		}
	}

	void __attribute__((naked)) GivePlayerWeapon_EntryCC() {
		__asm {
			mov ecx, esi;
			mov edx, 2;
			call GivePlayerWeaponMain;
			mov r8, rax;
			jmp[rip + GiveMenuWeaponMain_Entry_ReturnAddr];
		}
	}

}
