#pragma once
#include "NdGameSdk/sdk.hpp"

#include <map>

#if defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/corelib/memory/MemoryMapEntry.hpp>
#elif defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/corelib/memory/MemoryMapEntry.hpp>
#endif

using MemoryMapId = ::regenny::shared::corelib::memory::MapId;
using MemoryContextType = ::regenny::shared::corelib::memory::Context;

namespace NdGameSdk::corelib::memory
{
	enum SizeUnit { Bytes, Kilobytes, Megabytes };

	struct NdGameSdk_API MemSize {
	public:
		MemSize(double value, SizeUnit unit = SizeUnit::Bytes);
		MemSize(const MemSize& other) : _value(other._value) {};
		MemSize() : _value(0x0) {};

		MemSize& operator+=(const MemSize& other) {
			this->_value += other._value;
			return *this;
		}

		MemSize& operator-=(const MemSize& other) {
			this->_value -= other._value;
			return *this;
		}

		friend MemSize operator+(MemSize lhs, const MemSize& rhs) {
			lhs += rhs;
			return lhs;
		}

		friend MemSize operator-(MemSize lhs, const MemSize& rhs) {
			lhs -= rhs;
			return lhs;
		}

		friend bool operator==(const MemSize& lhs, const MemSize& rhs) {
			return lhs._value == rhs._value;
		}

		friend bool operator!=(const MemSize& lhs, const MemSize& rhs) {
			return !(lhs == rhs);
		}

		friend bool operator<(const MemSize& lhs, const MemSize& rhs) {
			return lhs._value < rhs._value;
		}

		friend bool operator>(const MemSize& lhs, const MemSize& rhs) {
			return rhs < lhs;
		}

		friend bool operator<=(const MemSize& lhs, const MemSize& rhs) {
			return !(rhs < lhs);
		}

		friend bool operator>=(const MemSize& lhs, const MemSize& rhs) {
			return !(lhs < rhs);
		}

		template <typename T>
		T GetSize(SizeUnit unit = SizeUnit::Bytes) {
			switch (unit) {
			case SizeUnit::Bytes:
				return static_cast<T>(_value);
			case SizeUnit::Kilobytes:
				return static_cast<T>(_value / 1024ULL);
			case SizeUnit::Megabytes:
				return static_cast<T>(_value / (1024ULL * 1024ULL));
			default:
				throw std::invalid_argument("Unknown size unit");
			}
		}
	private:
		uint64_t _value;
	};

	class NdGameSdk_API MemoryMapEntry : public ISdkRegenny<regenny::shared::corelib::memory::MemoryMapEntry>
	{
	public:
		MemoryMapId Id();
		MemoryContextType ContextType();
		std::string name();
		MemSize Size();
		void PrintDebugMapEntryInfo();
	};

	static_assert(sizeof(MemoryMapEntry) == 0x20, "Size of MemoryMapEntry is not correct.");

	class MemoryMap {
		friend class Memory;
		std::map<MemoryMapId, MemoryMapEntry*> s_MemoryMap{};
		std::map<MemoryMapId, MemoryMapEntry*> s_MoreguiMap{};
		std::map<MemoryMapId, MemoryMapEntry*> s_SpeechWhiteListMap{};
		std::map<MemoryMapId, MemoryMapEntry*> s_OffsiteMap{};
	};
}