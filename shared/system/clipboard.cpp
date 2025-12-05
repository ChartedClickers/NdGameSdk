#include "clipboard.hpp"
#include <windows.h>
#include <string>
#include <algorithm>

namespace Utility::sys {

    std::string GetClipboardAnsi()
    {
        std::string out;

        if (!OpenClipboard(nullptr))
            return out;

        if (HGLOBAL h = GetClipboardData(CF_TEXT)) {
            if (void* p = GlobalLock(h)) {
                out.assign(static_cast<char*>(p));
                GlobalUnlock(h);
            }
        }

        CloseClipboard();

        // keep printable ASCII 0x20–0x7E
        out.erase(std::remove_if(out.begin(), out.end(),
            [](char c) { return c < 0x20 || c > 0x7E; }),
            out.end());

        return out;
    }

}
