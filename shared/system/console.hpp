#pragma once
#include <windows.h>
#include <cstdio>

namespace Utility::sys {

	bool AllocConsole();
	bool HasAttachedConsole();

}
