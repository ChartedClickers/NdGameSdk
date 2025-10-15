#pragma once
#include "NdGameSdk/sdkderived.hpp"
#include "NdGameSdk/shared/shared.hpp"

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/ndlib/io/FileSystemData.hpp>
#include <NdGameSdk/regenny/t2r/shared/ndlib/io/StorageCore.hpp>
#include <NdGameSdk/regenny/t2r/shared/ndlib/io/FileRecord.hpp>
#include <NdGameSdk/regenny/t2r/shared/ndlib/io/FhOpenAccess.hpp>
#include <NdGameSdk/regenny/t2r/shared/ndlib/io/FhOpenFlags.hpp>
#endif

#include <NdGameSdk/shared/src/corelib/util/error.hpp>

#include "file-system-archive.hpp"

#include <string_view>
#include <Windows.h>
#include <dstorage.h>

#include <Utility/helper.hpp>
#include <Utility/function_ptr.hpp>

using namespace NdGameSdk::corelib::util;

namespace regenny::shared::ndlib::io {
#if defined(T2R)

	constexpr std::uint32_t FHO_ACCESS_MASK = 0x3u;

	using __ff_u32 = std::underlying_type_t<FhOpenFlags>;

	constexpr FhOpenFlags operator|(FhOpenFlags a, FhOpenFlags b) noexcept {
		return static_cast<FhOpenFlags>(static_cast<__ff_u32>(a) | static_cast<__ff_u32>(b));
	}

	constexpr FhOpenFlags operator&(FhOpenFlags a, FhOpenFlags b) noexcept {
		return static_cast<FhOpenFlags>(static_cast<__ff_u32>(a) & static_cast<__ff_u32>(b));
	}

	constexpr FhOpenFlags operator^(FhOpenFlags a, FhOpenFlags b) noexcept {
		return static_cast<FhOpenFlags>(static_cast<__ff_u32>(a) ^ static_cast<__ff_u32>(b));
	}

	constexpr FhOpenFlags operator~(FhOpenFlags a) noexcept {
		return static_cast<FhOpenFlags>(~static_cast<__ff_u32>(a));
	}

	inline FhOpenFlags& operator|=(FhOpenFlags& a, FhOpenFlags b) noexcept { a = a | b; return a; }
	inline FhOpenFlags& operator&=(FhOpenFlags& a, FhOpenFlags b) noexcept { a = a & b; return a; }
	inline FhOpenFlags& operator^=(FhOpenFlags& a, FhOpenFlags b) noexcept { a = a ^ b; return a; }

	using __fa_u32 = std::underlying_type_t<FhOpenAccess>;

	constexpr FhOpenFlags operator|(FhOpenFlags f, FhOpenAccess a) noexcept {
		return static_cast<FhOpenFlags>((static_cast<__ff_u32>(f) & ~FHO_ACCESS_MASK) |
			(static_cast<__fa_u32>(a) & FHO_ACCESS_MASK));
	}

	constexpr FhOpenFlags operator|(FhOpenAccess a, FhOpenFlags f) noexcept { return f | a; }

	constexpr FhOpenFlags make_open(FhOpenAccess a, FhOpenFlags f = static_cast<FhOpenFlags>(0)) noexcept {
		return static_cast<FhOpenFlags>((static_cast<__ff_u32>(f) & ~FHO_ACCESS_MASK) |
			(static_cast<__fa_u32>(a) & FHO_ACCESS_MASK));
	}

	constexpr FhOpenFlags set_access(FhOpenFlags f, FhOpenAccess a) noexcept { return f | a; }

	constexpr FhOpenAccess access_of(FhOpenFlags f) noexcept {
		return static_cast<FhOpenAccess>(static_cast<__ff_u32>(f) & FHO_ACCESS_MASK);
	}

	constexpr FhOpenAccess sanitized_access(FhOpenFlags f) noexcept {
		auto a = access_of(f);
		// binary coerces 3 → READ
		return (a == FhOpenAccess::FHO_ACCESS_RESERVED3) ? FhOpenAccess::FHO_ACCESS_READ : a;
	}

	constexpr FhOpenFlags flags_only(FhOpenFlags f) noexcept {
		return static_cast<FhOpenFlags>(static_cast<__ff_u32>(f) & ~FHO_ACCESS_MASK);
	}

	constexpr bool has_any(FhOpenFlags f, FhOpenFlags m) noexcept {
		return (static_cast<__ff_u32>(f) & static_cast<__ff_u32>(m)) != 0;
	}

	constexpr bool has_all(FhOpenFlags f, FhOpenFlags m) noexcept {
		return (flags_only(f) & m) == m;
	}

	static_assert((static_cast<__ff_u32>(FhOpenFlags::FHOF_ALLOW_CREATE) & FHO_ACCESS_MASK) == 0, "flag/access overlap");
	static_assert((static_cast<__ff_u32>(FhOpenFlags::FHOF_TRUNCATE) & FHO_ACCESS_MASK) == 0, "flag/access overlap");
	static_assert((static_cast<__ff_u32>(FhOpenFlags::FHOF_MODE_04) & FHO_ACCESS_MASK) == 0, "flag/access overlap");
	static_assert((static_cast<__ff_u32>(FhOpenFlags::FHOF_DIRECT_IO) & FHO_ACCESS_MASK) == 0, "flag/access overlap");


#endif
}

namespace NdGameSdk::ndlib::io {
#if defined(T2R)

	class FileSystem;
	using FsResult = Err;
	using FhOpenAccess = regenny::shared::ndlib::io::FhOpenAccess;
	using FhOpenFlags = regenny::shared::ndlib::io::FhOpenFlags;

	class NdGameSdk_API FileRecord : public ISdkRegenny<regenny::shared::ndlib::io::FileRecord> {
	public:
		using HandleObjType = regenny::shared::ndlib::io::FileRecord::HandleObjType;
		using FileState = regenny::shared::ndlib::io::FileRecord::FileState;

		inline const wchar_t* GetPath() const;
		inline uint64_t GetPathLen() const;
		inline std::wstring_view GetPathView() const;

		std::wstring GetFileName() const;
		std::wstring GetExtension() const;
		std::wstring GetFileNameWithoutExtension() const;

		bool IsWin32Handle() const;
		bool IsDirectStorageFile() const;
		bool HasValidHandle() const;

		bool TryGetByHandleInfo(BY_HANDLE_FILE_INFORMATION& out) const;

		template<typename T>
		T GetHandleObject() const {
			auto* self = this->Get();

			if constexpr (std::is_same_v<T, HANDLE>) {
				if (self->m_handleObj.m_type != HandleObjType::kHandleWin32)
					return INVALID_HANDLE_VALUE;
				return reinterpret_cast<HANDLE>(self->m_handleObj.m_obj);
			}
			else if constexpr (std::is_same_v<T, IDStorageFile*>) {
				if (self->m_handleObj.m_type != HandleObjType::kHandleDSFile)
					return nullptr;
				return reinterpret_cast<IDStorageFile*>(self->m_handleObj.m_obj);
			}
			else {
				static_assert(always_false_v<T>, "GetHandleObject<T>: unsupported T. Use HANDLE or IDStorageFile*");
			}
		}

		uint64_t GetFileSize() const;
		uint32_t GetRefCount() const;
		uint32_t GetOpenIndex() const;

		HandleObjType GetHandleType() const;
		FileState GetFileState() const;

		FileRecord* Left()   const { return reinterpret_cast<FileRecord*>(this->Get()->m_left); }
		FileRecord* Right()  const { return reinterpret_cast<FileRecord*>(this->Get()->m_right); }
		FileRecord* Parent() const { return reinterpret_cast<FileRecord*>(this->Get()->m_parent); }
		bool IsHeader() const { return this->Get()->m_isHeader; }

		FileRecord* NextInOrder(FileRecord* header) const {
			auto x = const_cast<FileRecord*>(this);
			if (x->Right() && !x->Right()->IsHeader()) {
				x = x->Right();
				while (x->Left() && !x->Left()->IsHeader()) x = x->Left();
				return x;
			}
			auto y = x->Parent();
			while (y && !y->IsHeader() && x == y->Right()) { x = y; y = y->Parent(); }
			return y;
		}

		FileRecord* PrevInOrder(FileRecord* header) const {
			auto x = const_cast<FileRecord*>(this);
			if (x->Left() && !x->Left()->IsHeader()) {
				x = x->Left();
				while (x->Right() && !x->Right()->IsHeader()) x = x->Right();
				return x;
			}
			auto y = x->Parent();
			while (y && !y->IsHeader() && x == y->Left()) { x = y; y = y->Parent(); }
			return y;
		}

		static FileRecord* Leftmost(FileRecord* header) {
			if (!header) return nullptr;
			auto x = header->Left(); // MSVC-style: header->left = leftmost
			return (x && !x->IsHeader()) ? x : header;
		}

		static FileRecord* Rightmost(FileRecord* header) {
			if (!header) return nullptr;
			auto x = header->Right(); // header->right = rightmost
			return (x && !x->IsHeader()) ? x : header;
		}
	private:
		inline std::wstring_view GetFileNameView() const;
		inline std::wstring_view GetExtensionView() const;
		inline std::wstring_view GetFileNameWithoutExtensionView() const;
	};

	class NdGameSdk_API StorageCore : public ISdkRegenny<regenny::shared::ndlib::io::StorageCore> {
	public:

		uint64_t GetCountFileRecords();
		CRITICAL_SECTION* GetCriticalSection();

		IDStorageFactory* GetDirectStorageFactory() const;
		IDStorageQueue* GetDirectStorageQueue() const;

		FileRecord* LookupByIoHandle(uint32_t ioHandle) const;

		bool IsUsingDirectStorage();

		struct OpenFileIterator {
			FileRecord** it{};
			FileRecord* operator*()  const { return *it; }
			OpenFileIterator& operator++() { ++it; return *this; }
			bool operator!=(const OpenFileIterator& o) const { return it != o.it; }
		};

		struct OpenFileRange {
			FileRecord** first{};
			FileRecord** last{};
			OpenFileIterator begin() const { return { first }; }
			OpenFileIterator end()   const { return { last }; }
			std::size_t size() const { return static_cast<std::size_t>(last - first); }
			bool empty() const { return first == last; }
		};


		OpenFileRange OpenFiles() const {
			auto** begin = reinterpret_cast<FileRecord**>(this->Get()->m_openBegin);
			auto** end = reinterpret_cast<FileRecord**>(this->Get()->m_openEnd);
			return { begin, end };
		}

		struct FileRecordIterator {
			FileRecord* cur{};
			FileRecord* header{};
			FileRecord* operator*() const { return cur; }
			FileRecordIterator& operator++() {
				if (!cur) return *this;
				cur = cur->NextInOrder(header);
				// end() is represented by header itself
				return *this;
			}
			bool operator!=(const FileRecordIterator& o) const { return cur != o.cur; }
		};

		struct FileRecordRange {
			FileRecord* header{}; // sentinel
			FileRecordIterator begin() const { return { FileRecord::Leftmost(header), header }; }
			FileRecordIterator end()   const { return { header, header }; } // header == end()
			bool empty() const { return begin().cur == header; }
		};

		FileRecordRange FileRecords(FileRecord* header) const { return { header }; }

	};

	class NdGameSdk_API FileSystemData : public ISdkRegenny<regenny::shared::ndlib::io::FileSystemData> {
	public:
		StorageCore* GetStorageCore() const;
		ArchiveSystem* GetArchiveSystem() const;
	};

    static_assert(sizeof(FileRecord) == 0x270, "Invalid FileRecord size");
    static_assert(sizeof(StorageCore) == 0x120, "Invalid StorageCore size");
    static_assert(sizeof(FileSystemData) == 0x42450, "Invalid FileSystemData size");

#endif
}

