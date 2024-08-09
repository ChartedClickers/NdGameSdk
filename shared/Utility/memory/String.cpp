#include "String.hpp"

namespace Utility::memory {

	string ConvertToNarrow(wstring_view str)
	{
		auto length = WideCharToMultiByte(CP_UTF8, 0, str.data(), (int)str.length(), nullptr, 0, nullptr, nullptr);
		string narrowStr{};

		narrowStr.resize(length);
		WideCharToMultiByte(CP_UTF8, 0, str.data(), (int)str.length(), (LPSTR)narrowStr.c_str(), length, nullptr, nullptr);

		return narrowStr;
	}

	wstring memory::ConvertToWide(std::string_view str)
	{
		auto length = MultiByteToWideChar(CP_UTF8, 0, str.data(), (int)str.length(), nullptr, 0);
		wstring wideStr{};

		wideStr.resize(length);
		MultiByteToWideChar(CP_UTF8, 0, str.data(), (int)str.length(), (LPWSTR)wideStr.c_str(), length);

		return wideStr;
	}
}

