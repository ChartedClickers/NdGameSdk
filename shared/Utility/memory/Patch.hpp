#pragma once

#include <memory>
#include <vector>
#include <optional>
#include <string>
#include <Windows.h>

#include "Pattern.hpp"
#include "Address.hpp"

using namespace std;

namespace Utility::memory
{
	class Patch {
	public:	
		using Ptr = unique_ptr<Patch>;
		Patch(uintptr_t Address, const std::vector<int16_t>& patchb, wstring name, bool enable);
		virtual ~Patch();
		bool toggle(bool state);
		bool IsEnable();
		Address GetPatchAddress() const noexcept { return m_address; }
		size_t GetPatchSize() const noexcept { return m_patchb.size(); }
		wstring GetName() const noexcept { return m_name; }

		static Ptr create(uintptr_t Address, const std::vector<int16_t>& patchb, wstring name, bool enable = true);
		static Ptr create_nop(uintptr_t Address, uint32_t length, wstring name, bool enable = true);
		static bool PatchBytes(uintptr_t Address, const unsigned char* pattern, unsigned int numBytes);
		static bool PatchBytes(uintptr_t Address, const std::vector<int16_t>& patchb);
		static optional<DWORD> protect(uintptr_t Address, size_t size, DWORD protection);
	private:
		uintptr_t m_address;
		wstring  m_name;
		vector<int16_t> m_patchb;
		vector<int16_t> m_original_patchb;
		bool m_enabled;
	};
}