#include "console.hpp"

namespace Utility::sys {

	bool AllocConsole() {

		bool result = ::AllocConsole();

		if (result) {
			freopen_s(reinterpret_cast<FILE**>(stdin), "conin$", "r", stdin);
			freopen_s(reinterpret_cast<FILE**>(stdout), "conout$", "w", stdout);
			freopen_s(reinterpret_cast<FILE**>(stderr), "conout$", "w", stderr);

			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			DWORD dwMode = 0;
			GetConsoleMode(hConsole, &dwMode);
			printf_s("dwMode: 0x08%x\n", dwMode);

			// enable ansi color formatting
			dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
			printf_s("dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING: 0x08%x\n", dwMode);
			SetConsoleMode(hConsole, dwMode);
			printf_s("The console has been successfully initialized\n");
		}

		return result;
	}

	bool HasAttachedConsole() {
		if (::GetConsoleWindow() != nullptr) {
			return true;
		}
		const HANDLE stdoutHandle = ::GetStdHandle(STD_OUTPUT_HANDLE);
		if (stdoutHandle == nullptr || stdoutHandle == INVALID_HANDLE_VALUE) {
			return false;
		}
		DWORD consoleMode{};
		return ::GetConsoleMode(stdoutHandle, &consoleMode) != 0;
	}

}
