#include "Patch.hpp"

namespace Utility::memory
{
	Patch::Patch(uintptr_t Address, const std::vector<int16_t>& patchb, wstring name, bool enable)
		: m_address{ Address }, m_name{ name }, m_patchb { patchb }
	{
		m_original_patchb.resize(m_patchb.size());
		unsigned int iter = 0;
		for (auto& byte : m_original_patchb) {
			byte = *(uint8_t*)(m_address + iter++);
		}

		toggle(enable);
	}

	Patch::~Patch() {
		toggle(false);
	}

	unique_ptr<Patch> Patch::create(uintptr_t Address, const std::vector<int16_t>& patchb, wstring name, bool enable) {
		return make_unique<Patch>(Address, patchb, name, enable);
	}

	unique_ptr<Patch> Patch::create_nop(uintptr_t Address, uint32_t length, wstring name, bool enable)
	{
		std::vector<decltype(m_patchb)::value_type> bytes; bytes.resize(length);
		std::fill(bytes.begin(), bytes.end(), 0x90);
		return make_unique<Patch>(Address, bytes, name, enable);
	}

	optional<DWORD> Patch::protect(uintptr_t Address, size_t size, DWORD protection) {

		DWORD oldProtect{};
		if (VirtualProtect((LPVOID)Address, size, protection, &oldProtect) != FALSE) {
			return oldProtect;
		}

		return {};
	}


	bool Patch::PatchBytes(uintptr_t Address, const unsigned char* pattern, unsigned int numBytes) {

		auto oldProtection = protect(Address, numBytes, PAGE_EXECUTE_READWRITE);

		if (!oldProtection) {
			return false;
		}

		memcpy((LPVOID)Address, pattern, numBytes);
		protect(Address, numBytes, *oldProtection);

		return true;
	}

	bool Patch::PatchBytes(uintptr_t Address, const std::vector<int16_t>& patchb) {

		auto oldProtection = protect(Address, patchb.size(), PAGE_EXECUTE_READWRITE);

		if (!oldProtection) {
			return false;
		}

		unsigned int iter = 0;
		for (auto byte : patchb) {
			if (byte >= 0 && byte <= 0xFF) {
				*(uint8_t*)(Address + iter) = (uint8_t)byte;
			}

			++iter;
		}

		FlushInstructionCache(GetCurrentProcess(), (LPCVOID)Address, patchb.size());
		protect(Address, patchb.size(), *oldProtection);

		return true;
	}

	bool Patch::toggle(bool state) {
		return state ? (m_enabled = PatchBytes(m_address, m_patchb)) 
			: !(m_enabled = !PatchBytes(m_address, m_original_patchb));
	}

	bool Patch::IsEnable() {
		return m_enabled;
	}
}