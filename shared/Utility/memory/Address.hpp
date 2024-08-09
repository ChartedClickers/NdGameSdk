#pragma once

#include <string>

using namespace std;

namespace Utility::memory
{
	struct Address {
	public:
		Address(void* ptr) : m_ptr(ptr) {};
		Address(uintptr_t addr) : m_ptr((void*)addr) {};

		void* get() const {
			return m_ptr;
		}

		template <typename T>
		Address offset(T offset) const {
			return Address(offset + (uintptr_t)m_ptr);
		}

		template <typename T>
		T as() const {
			return (T)m_ptr;
		}

		operator uintptr_t() const {
			return (uintptr_t)m_ptr;
		}

		operator void* () const {
			return m_ptr;
		}

		bool operator ==(bool val) {
			return ((m_ptr && val) || (!m_ptr && !val));
		}

		bool operator !=(bool val) {
			return !(*this == val);
		}

		bool operator ==(uintptr_t val) {
			return ((uintptr_t)m_ptr == val);
		}

		bool operator !=(uintptr_t val) {
			return !(*this == val);
		}

		bool operator ==(void* val) {
			return (m_ptr == val);
		}

		bool operator !=(void* val) {
			return !(*this == val);
		}

	private:
		void* m_ptr { nullptr };
	};
}