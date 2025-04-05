#if defined(T2R)	
#include "nxapp-hooks.hpp"

namespace NdGameSdk::common::win {

	void __attribute__((naked)) NxAppHooks_StdHandle_CC() {
		__asm {
			push rbx;
			mov al, 0x1;
			pop rbx;
			ret;
		}
	}
}
#endif