#pragma once

#include <string>
#include <string_view>
#include <cstdarg>
#include <Windows.h>

using namespace std;

namespace Utility::memory
{
	string ConvertToNarrow(wstring_view str);
	wstring ConvertToWide(std::string_view str);
}