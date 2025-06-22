#include "package.hpp"

namespace NdGameSdk::ndlib::io {
#if defined(T2R)
	size_t Package::GetSize() const {
		return this->Get()->m_size;
	}

	size_t Package::GetHdrSize() const {
		return this->Get()->m_hdrSize;
	}

	size_t Package::GetDataSize() const {
		return this->Get()->m_dataSize;
	}

	uint32_t Package::GetNumAllocatedPages() const {
		return this->Get()->m_numAllocatedPages;
	}

	uint32_t Package::GetNumPages() const {
		return this->Get()->m_pageCt;
	}

	void* Package::GetVirtualMemoryAddressRange() const {
		return reinterpret_cast<void*>(this->Get()->m_VirtualMemoryAddressRange);
	}

	Level* Package::GetLevel() const {
		return reinterpret_cast<Level*>(this->Get()->m_Level);
	}

	const char* Package::GetName() const {
		return this->Get()->m_packname;
	}

	const char* Package::GetPackPath() const {
		return this->Get()->m_packfilepath;
	}

	StringId64 Package::GetPackId() const {
		return this->Get()->m_packid;
	}

	StringId64 Package::GetPackPathId() const {
		return this->Get()->m_packfilepathid;
	}

	Package::Status Package::GetStatus() const {
		return this->Get()->m_status;
	}

	std::string Package::GetStatusString() {
		return GetStatusString(this->GetStatus());
	}

	std::string Package::GetStatusString(Status status) {
	#if defined(T2R) || defined(T1X)
		always_assert(PackageMgr_Package_GetStatusString == nullptr, "Function pointer was not set!");
		return PackageMgr_Package_GetStatusString(status);
	#else
		switch (status) {
		case Status::PackageStatusUnused:
			return "Unused";
		case Status::PackageStatusInvalid:
			return "Invalid";
		case Status::PackageStatusFailedOptionalFile:
			return "FailedOptionalFile";
		case Status::PackageStatusLoading:
			return "Loading";
		case Status::PackageStatusLoaded:
			return "Loaded";
		case Status::PackageStatusUnloading:
			return "Unloading";
		default:
			return "Unknown";
		}
	#endif
	}

	const char* Package::ResItem::GetResourceName() const {
		auto resNameOffset = this->Get()->m_resNameStrOffset;
		if (resNameOffset == 0) return nullptr;
		return reinterpret_cast<const char*>(this->Get()) + resNameOffset;
	}

	size_t Package::ResItem::GetPageSize() const {
		return this->Get()->m_pageSize;
	}

	StringId64 Package::ResItem::GetResourceId() const {
		return this->Get()->m_ResourceId;
	}

	StringId64 Package::ResItem::GetResourceTypeId() const {
		return this->Get()->m_resourceTypeId;
	}

	Package::ItemId Package::ResItem::GetResourceType() const {
		return static_cast<Package::ItemId>(this->Get()->m_resourceTypeId);
	}

	uint32_t PakLoginTableEntry::GetMaxResources() const {
		return this->Get()->m_MaxResources;
	}

	PakLoginTableEntry::ResourcePair* PakLoginTableEntry::GetPairs() {
		return reinterpret_cast<ResourcePair*>(&this->Get()->m_wantedPage);
	}

	const PakLoginTableEntry::ResourcePair* PakLoginTableEntry::GetPairs() const {
		return reinterpret_cast<const ResourcePair*>(&this->Get()->m_wantedPage);
	}

	uint32_t PakLoginTableEntry::ResourcePair::GetPageIdx() const {
		return this->Get()->m_pageIdx;
	}

	uint32_t PakLoginTableEntry::ResourcePair::GetItemOfs() const {
		return this->Get()->m_itemOfs;
	}

	INIT_FUNCTION_PTR(PackageMgr_Package_ResolvePakItem);
	INIT_FUNCTION_PTR(PackageMgr_Package_GetStatusString);

#endif
}