#include "memory-map.hpp"

namespace NdGameSdk::corelib::memory {

	MemSize::MemSize(double value, SizeUnit unit) {
		switch (unit) {
		case SizeUnit::Bytes:
			_value = static_cast<uint64_t>(value);
			break;
		case SizeUnit::Kilobytes:
			_value = static_cast<uint64_t>(value * 1024ULL);
			break;
		case SizeUnit::Megabytes:
			_value = static_cast<uint64_t>(value * 1024ULL * 1024ULL);
			break;
		default:
			throw std::invalid_argument("Unknown size unit");
		}
	}

	MemoryMapId MemoryMapEntry::Id() {
		return this->Get()->m_id;
	}

	MemoryContextType MemoryMapEntry::ContextType() {
		return this->Get()->m_context;
	}

	std::string MemoryMapEntry::name() {
		return this->Get()->m_name;
	}

	MemSize MemoryMapEntry::Size() {
		return MemSize(this->Get()->m_size, SizeUnit::Bytes);
	}

	void MemoryMapEntry::PrintDebugMapEntryInfo() {
		auto model_view = this->Get();
		spdlog::debug("Context {}: {:<40}: {:8.3f} MiB / {:11.3f} KiB / {:10} B",
			static_cast<uint32_t>(model_view->m_context), name(),
			Size().GetSize<double>(SizeUnit::Megabytes), Size().GetSize<double>(SizeUnit::Kilobytes), Size().GetSize<uint64_t>(SizeUnit::Bytes));
	}
}