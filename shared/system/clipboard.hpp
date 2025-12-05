#pragma once
#include <string>

namespace Utility::sys {

	/// Get ANSI text from the system clipboard.
	/// Returns empty string on error / unsupported format.
	[[nodiscard]] std::string GetClipboardAnsi();

}
