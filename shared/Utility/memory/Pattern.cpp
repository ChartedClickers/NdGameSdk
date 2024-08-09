#include "Pattern.hpp"
#include "Module.hpp"

using namespace std;

namespace Utility::memory
{
	Pattern::Pattern(const char* pattern, wstring name) : m_name { name }
	{
        static auto pattern_to_byte = [](const char* pattern) {
            auto bytes = std::vector<int32_t>{};
            auto start = const_cast<char*>(pattern);
            auto end = const_cast<char*>(pattern) + strlen(pattern);

            for (auto current = start; current < end; ++current) {
                if (*current == '?') {
                    ++current;
                    if (*current == '?')
                        ++current;
                    bytes.push_back(-1);
                }
                else {
                    bytes.push_back(strtoul(current, &current, 16));
                }
            }
            return bytes;
            };

        m_pattern = move(pattern_to_byte(pattern));
	}

	Pattern::Pattern(const wchar_t* pattern, wstring name) : m_name{ name }
	{
        static auto pattern_to_byte = [](const wchar_t* pattern) {
            auto bytes = std::vector<int32_t>{};
            auto start = const_cast<wchar_t*>(pattern);
            auto end = const_cast<wchar_t*>(pattern) + wcslen(pattern);

            for (auto current = start; current < end; ++current) {
                if (*current == L'?') {
                    ++current;
                    if (*current == L'?')
                        ++current;
                    bytes.push_back(-1);
                }
                else {
                    bytes.push_back(wcstoul(current, &current, 16));
                }
            }
            return bytes;
            };

        m_pattern = move(pattern_to_byte(pattern));
	}

    uint8_t* Pattern::find(std::uint8_t* scanBytes, size_t sizeOfImage)
    {
        auto s = m_pattern.size();
        auto d = m_pattern.data();

        for (auto i = 0ul; i < sizeOfImage - s; ++i) {
            bool found = true;
            for (auto j = 0ul; j < s; ++j) {
                if (scanBytes[i + j] != d[j] && d[j] != -1) {
                    found = false;
                    break;
                }
            }
            if (found) {
                return &scanBytes[i];
            }
        }

        return {};

    }

    uint8_t* Pattern::find(HMODULE module)
    {
        auto sizeOfImage = get_module_size(module);

        if (sizeOfImage.has_value()) {
            auto scanBytes = reinterpret_cast<std::uint8_t*>(module);
            return find(scanBytes, sizeOfImage.value());
        }
    }


}