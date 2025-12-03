#pragma once

#include <stdint.h>

#define SDK_NAME "NdGameSdk"
#define SDK_LOG_PATH SDK_NAME ".log"

#if NDEBUG
#define SDK_DEBUG false
#else
#define SDK_DEBUG true
#endif

#define NdGameSdk_API __declspec(dllexport)

#define wstr(s) L#s
#define wxstr(s) wstr(s)
#define TOSTRING(x) #x

#define _rgba(r,g,b,a) (((uint32_t)a << 24) | ((uint32_t)b << 16) | ((uint32_t)g << 8) | r)
#define _rgb(r,g,b) _rgba(r,g,b,255)
