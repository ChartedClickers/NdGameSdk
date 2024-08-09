#pragma once

#if NDEBUG
#include <Windows.h>
#define BREAK()\
{ \
    if (!IsDebuggerPresent()) \
    { \
        while (true) \
        { \
            Sleep(1000); \
        } \
    } \
    else \
    { \
        __debugbreak(); \
    } \
}
#else
#define BREAK() __debugbreak();
#endif

namespace Assertion
{
    void always_assert_(const char* reason, const char* file_, const char* func, const char* built, size_t line_num, const char* msg = nullptr);
    #define always_assert(reason, message) if (reason) { Assertion::always_assert_(#reason, __FILE__, __FUNCSIG__, __DATE__ " " __TIME__, __LINE__, message); BREAK() }
}