#pragma once
#include <vector>
#include <string>
#include <Windows.h>
#include <optional>

using namespace std;

namespace Utility::memory
{
	class Pattern {
	public:
		Pattern() = delete;
		Pattern(const char* pattern, wstring name);
		Pattern(const wchar_t* pattern, wstring name);
		~Pattern() = default;

		uint8_t* find(std::uint8_t* scanBytes, size_t sizeOfImage);
		uint8_t* find(HMODULE module);
		wstring patternName() const noexcept { return m_name; }
		size_t patternLength() const noexcept { return m_pattern.size(); }

	private:
		wstring m_name;
		std::vector<int32_t> m_pattern;
	};

}