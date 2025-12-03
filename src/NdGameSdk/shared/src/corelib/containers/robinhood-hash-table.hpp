#pragma once

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/corelib/containers/RobinHoodHashTable.hpp>
#elif defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/corelib/containers/RobinHoodHashTable.hpp>
#endif

#include <bit>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <functional>
#include <iterator>
#include <limits>
#include <new>
#include <type_traits>
#include <utility>

#include "../memory/memory.hpp"

#include <Utility/assertion/assert.hpp>

namespace NdGameSdk::corelib::containers {

	namespace detail {

		constexpr uint32_t BitsPerWord = 64;
		inline constexpr uint32_t AlignUpToWord(uint32_t value) {
			return (value + (BitsPerWord - 1)) & ~(BitsPerWord - 1);
		}

		template<typename T>
		concept TriviallyCopyable = std::is_trivially_copyable_v<T>;

		namespace robinhood {

			using OccMask = regenny::shared::corelib::containers::RobinHoodHashTable::OccMask;
			inline constexpr uint32_t kInvalidIndex = (std::numeric_limits<uint32_t>::max)();
			static constexpr uint64_t kEmptyHash = static_cast<uint64_t>(-2);

			uint32_t NextOccupied(const OccMask& mask, uint32_t capacity, uint32_t startIndex);
			void MarkOccupied(OccMask& mask, uint32_t index);
			void ClearOccupied(OccMask& mask, uint32_t index);
			void ZeroOccupancy(OccMask& mask);
		}
	}

	using namespace detail::robinhood;

	template<typename KeyT, typename ValueT, typename HashT = std::hash<KeyT>, typename EqualsT = std::equal_to<KeyT>>
	class NdGameSdk_API RobinHoodHashTable : public ISdkRegenny<regenny::shared::corelib::containers::RobinHoodHashTable> {
	public:
		using RawTable = regenny::shared::corelib::containers::RobinHoodHashTable;
		using Slot = typename RawTable::Slot;
		using RawSlot = Slot;
		using RawOccMask = RawTable::OccMask;

		class Cursor {
		public:
			using table_type = RobinHoodHashTable;

			Cursor() = default;

			Cursor(table_type* table, uint32_t index)
				: m_table(table), m_index(index) {}

			bool IsValid() const {
				return m_table != nullptr && m_index < m_table->Capacity();
			}

			uint32_t Index() const {
				return m_index;
			}

			Slot& SlotRef() {
				return m_table->Slots()[m_index];
			}

			const Slot& SlotRef() const {
				return m_table->Slots()[m_index];
			}

			ValueT& Value() {
				return ValueRef(SlotRef());
			}

			const ValueT& Value() const {
				return ValueRef(SlotRef());
			}

			KeyT& Key() {
				return KeyRef(SlotRef());
			}

			const KeyT& Key() const {
				return KeyRef(SlotRef());
			}

			void Advance() {
				if (m_table == nullptr) {
					return;
				}

				if (m_index >= m_table->Capacity()) {
					m_index = kInvalidIndex;
					return;
				}

				const uint32_t next = m_table->NextOccupied(m_index + 1);
				m_index = next;
			}

			bool operator==(const Cursor& rhs) const {
				return m_table == rhs.m_table && m_index == rhs.m_index;
			}

			bool operator!=(const Cursor& rhs) const {
				return !(*this == rhs);
			}

		private:
			table_type* m_table{ nullptr };
			uint32_t m_index{ kInvalidIndex };
		};

		class Iterator {
		public:
			using iterator_category = std::forward_iterator_tag;
			using value_type = Slot;
			using difference_type = std::ptrdiff_t;
			using pointer = Slot*;
			using reference = Slot&;

			Iterator() = default;

			Iterator(RobinHoodHashTable* table, uint32_t index)
				: m_cursor(table, index) {}

			reference operator*() const {
				return const_cast<Slot&>(m_cursor.SlotRef());
			}

			pointer operator->() const {
				return const_cast<Slot*>(&m_cursor.SlotRef());
			}

			Iterator& operator++() {
				m_cursor.Advance();
				return *this;
			}

			Iterator operator++(int) {
				Iterator tmp = *this;
				++(*this);
				return tmp;
			}

			bool operator==(const Iterator& rhs) const {
				return m_cursor == rhs.m_cursor;
			}

			bool operator!=(const Iterator& rhs) const {
				return !(*this == rhs);
			}

		private:
			Cursor m_cursor{};
		};

		class ConstIterator {
		public:
			using iterator_category = std::forward_iterator_tag;
			using value_type = Slot;
			using difference_type = std::ptrdiff_t;
			using pointer = const Slot*;
			using reference = const Slot&;

			ConstIterator() = default;

			ConstIterator(const RobinHoodHashTable* table, uint32_t index)
				: m_cursor(const_cast<RobinHoodHashTable*>(table), index) {}

			reference operator*() const {
				return m_cursor.SlotRef();
			}

			pointer operator->() const {
				return &m_cursor.SlotRef();
			}

			ConstIterator& operator++() {
				m_cursor.Advance();
				return *this;
			}

			ConstIterator operator++(int) {
				ConstIterator tmp = *this;
				++(*this);
				return tmp;
			}

			bool operator==(const ConstIterator& rhs) const {
				return m_cursor == rhs.m_cursor;
			}

			bool operator!=(const ConstIterator& rhs) const {
				return !(*this == rhs);
			}

		private:
			Cursor m_cursor{};
		};

		static_assert(detail::TriviallyCopyable<KeyT>, "RobinHoodHashTable requires trivially copyable keys");
		static_assert(detail::TriviallyCopyable<ValueT>, "RobinHoodHashTable requires trivially copyable values");
		static_assert(sizeof(KeyT) <= sizeof(void*), "RobinHoodHashTable key must fit in slot storage");
		static_assert(sizeof(ValueT) <= sizeof(void*), "RobinHoodHashTable value must fit in slot storage");
		static_assert(alignof(KeyT) <= alignof(void*), "RobinHoodHashTable key alignment exceeds slot storage");
		static_assert(alignof(ValueT) <= alignof(void*), "RobinHoodHashTable value alignment exceeds slot storage");

		void Initialize(uint32_t bucketCount,
			const char* sourceFunc = __func__,
			uint32_t sourceLine = __LINE__,
			const char* sourceFile = __FILE__,
			corelib::memory::Memory::Context context = corelib::memory::Memory::Context::kAllocInvalid) {

			Destroy(sourceFunc, sourceLine, sourceFile);

			auto* raw = this->Get();
			auto& memory = corelib::memory::Memory::RequireInstance<corelib::memory::Memory>();

			const uint32_t capacity = bucketCount == 0 ? 1 : bucketCount;
			const uint32_t alignedCapacity = detail::AlignUpToWord(capacity);
			const uint32_t wordCount = alignedCapacity / detail::BitsPerWord;

			if (context != corelib::memory::Memory::Context::kAllocInvalid) {
				memory.PushAllocator(context, sourceFile, static_cast<int>(sourceLine), sourceFunc);
			}

			const size_t slotBytes = static_cast<size_t>(capacity) * sizeof(Slot);
			RawSlot* rawSlots = reinterpret_cast<RawSlot*>(
				memory.Allocate<RawSlot>(slotBytes, alignof(Slot), sourceFunc, static_cast<int>(sourceLine), sourceFile));

			always_assert(rawSlots == nullptr, "RobinHoodHashTable::Initialize slot allocation failed");

			const size_t maskBytes = static_cast<size_t>(wordCount) * sizeof(uint64_t);
			uint64_t* occupancyWords = reinterpret_cast<uint64_t*>(
				memory.Allocate<uint64_t>(maskBytes == 0 ? sizeof(uint64_t) : maskBytes,
					alignof(uint64_t),
					sourceFunc,
					static_cast<int>(sourceLine),
					sourceFile));
			always_assert(occupancyWords == nullptr, "RobinHoodHashTable::Initialize occupancy allocation failed");

			if (context != corelib::memory::Memory::Context::kAllocInvalid) {
				memory.PopAllocator();
			}

			raw->m_Slots = rawSlots;
			std::memset(rawSlots, 0, slotBytes);
			auto* typedSlots = reinterpret_cast<Slot*>(rawSlots);
			for (uint32_t i = 0; i < capacity; ++i) {
				SetEmpty(typedSlots[i]);
			}

			raw->m_occ.m_capacity = capacity;
			raw->m_occ.m_wordCount = wordCount;
			raw->m_occ.m_words = occupancyWords;
			raw->m_occ.m_capacityAligned64 = alignedCapacity;

			detail::robinhood::ZeroOccupancy(raw->m_occ);

			raw->m_numBuckets = capacity;
			raw->m_numElements = 0;
		}

		void Destroy(const char* sourceFunc = __func__,
			uint32_t sourceLine = __LINE__,
			const char* sourceFile = __FILE__) {

			auto* raw = this->Get();
			if (raw == nullptr) {
				return;
			}

			auto& memory = corelib::memory::Memory::RequireInstance<corelib::memory::Memory>();

			if (raw->m_Slots != nullptr) {
				memory.Free(raw->m_Slots, sourceFunc, static_cast<int>(sourceLine), sourceFile);
				raw->m_Slots = nullptr;
			}

			if (raw->m_occ.m_words != nullptr) {
				memory.Free(raw->m_occ.m_words, sourceFunc, static_cast<int>(sourceLine), sourceFile);
				raw->m_occ.m_words = nullptr;
			}

			raw->m_occ.m_capacity = 0;
			raw->m_occ.m_wordCount = 0;
			raw->m_occ.m_capacityAligned64 = 0;
			raw->m_numBuckets = 0;
			raw->m_numElements = 0;
		}

		uint32_t Capacity() const {
			auto* raw = this->Get();
			return raw ? raw->m_numBuckets : 0;
		}

		uint32_t Size() const {
			auto* raw = this->Get();
			return raw ? raw->m_numElements : 0;
		}

		bool Empty() const {
			return Size() == 0;
		}

		Iterator begin() {
			return Iterator(this, NextOccupied(0));
		}

		Iterator end() {
			return Iterator(this, kInvalidIndex);
		}

		ConstIterator begin() const {
			return ConstIterator(this, NextOccupied(0));
		}

		ConstIterator end() const {
			return ConstIterator(this, kInvalidIndex);
		}

		ConstIterator cbegin() const {
			return begin();
		}

		ConstIterator cend() const {
			return end();
		}

		Cursor BeginCursor() {
			return Cursor(this, NextOccupied(0));
		}

		Cursor EndCursor() {
			return Cursor(this, kInvalidIndex);
		}

		Cursor BeginCursor() const {
			return Cursor(const_cast<RobinHoodHashTable*>(this), NextOccupied(0));
		}

		std::pair<ValueT*, bool> InsertOrAssign(const KeyT& key, const ValueT& value) {
			return InsertInternal(key, value, InsertMode::InsertOrAssign);
		}

		std::pair<ValueT*, bool> InsertUnique(const KeyT& key, const ValueT& value) {
			return InsertInternal(key, value, InsertMode::InsertUnique);
		}

		ValueT* Find(const KeyT& key) {
			uint32_t index = kInvalidIndex;
			return FindValueInternal(key, index);
		}

		const ValueT* Find(const KeyT& key) const {
			uint32_t index = kInvalidIndex;
			return FindValueInternal(key, index);
		}

		Cursor FindCursor(const KeyT& key) {
			uint32_t index = FindIndex(key);
			return Cursor(this, index);
		}

		Cursor FindCursor(const KeyT& key) const {
			uint32_t index = FindIndex(key);
			return Cursor(const_cast<RobinHoodHashTable*>(this), index);
		}

		bool Erase(const KeyT& key) {
			const uint32_t index = FindIndex(key);
			if (index == kInvalidIndex) {
				return false;
			}

			EraseAt(index);
			return true;
		}

		bool Erase(Cursor cursor) {
			if (!cursor.IsValid()) {
				return false;
			}

			EraseAt(cursor.Index());
			return true;
		}

		template<typename Fn>
		void ForEach(Fn&& fn) {
			for (auto it = begin(); it != end(); ++it) {
				Slot& slot = *it;
				std::invoke(fn, KeyRef(slot), ValueRef(slot));
			}
		}

		template<typename Fn>
		void ForEach(Fn&& fn) const {
			for (auto it = begin(); it != end(); ++it) {
				const Slot& slot = *it;
				std::invoke(fn, KeyRef(slot), ValueRef(slot));
			}
		}

	private:
		enum class InsertMode {
			InsertOrAssign,
			InsertUnique
		};

		static void SetEmpty(Slot& slot) {
			slot.m_hash = kEmptyHash;
			std::memset(&slot.m_key, 0, sizeof(slot.m_key));
			std::memset(&slot.m_value, 0, sizeof(slot.m_value));
		}

		Slot* Slots() {
			auto* raw = this->Get();
			return raw ? raw->m_Slots : nullptr;
		}

		const Slot* Slots() const {
			auto* raw = this->Get();
			return raw ? raw->m_Slots : nullptr;
		}

		uint64_t HashKey(const KeyT& key, HashT& hashFn) const {
			uint64_t hashed = static_cast<uint64_t>(hashFn(key));
			if (hashed == 0) {
				hashed = 1;
			}
			if (hashed == kEmptyHash) {
				hashed -= 1;
			}
			return hashed;
		}

		static uint32_t ProbeDistance(uint32_t slotIndex, uint64_t hash, uint32_t capacity) {
			const uint32_t home = static_cast<uint32_t>(hash % capacity);
			if (slotIndex >= home) {
				return slotIndex - home;
			}
			return capacity - home + slotIndex;
		}

		uint32_t NextOccupied(uint32_t startIndex) const {
			const auto* raw = this->Get();
			if (raw == nullptr || raw->m_occ.m_words == nullptr || raw->m_occ.m_wordCount == 0) {
				return kInvalidIndex;
			}

			return detail::robinhood::NextOccupied(raw->m_occ, raw->m_numBuckets, startIndex);
		}

		void MarkOccupied(uint32_t index) {
			auto* raw = this->Get();
			if (raw == nullptr || raw->m_occ.m_words == nullptr) {
				return;
			}

			detail::robinhood::MarkOccupied(raw->m_occ, index);
		}

		void ClearOccupied(uint32_t index) {
			auto* raw = this->Get();
			if (raw == nullptr || raw->m_occ.m_words == nullptr) {
				return;
			}

			detail::robinhood::ClearOccupied(raw->m_occ, index);
		}

		static KeyT& KeyRef(Slot& slot) {
			return *std::launder(reinterpret_cast<KeyT*>(&slot.m_key));
		}

		static const KeyT& KeyRef(const Slot& slot) {
			return *std::launder(reinterpret_cast<const KeyT*>(&slot.m_key));
		}

		static ValueT& ValueRef(Slot& slot) {
			return *std::launder(reinterpret_cast<ValueT*>(&slot.m_value));
		}

		static const ValueT& ValueRef(const Slot& slot) {
			return *std::launder(reinterpret_cast<const ValueT*>(&slot.m_value));
		}

		static ValueT* ValuePtr(Slot& slot) {
			return std::launder(reinterpret_cast<ValueT*>(&slot.m_value));
		}

		static const ValueT* ValuePtr(const Slot& slot) {
			return std::launder(reinterpret_cast<const ValueT*>(&slot.m_value));
		}

		uint32_t FindIndex(const KeyT& key) const {
			auto* raw = this->Get();
			if (raw == nullptr || raw->m_Slots == nullptr || raw->m_numBuckets == 0) {
				return kInvalidIndex;
			}

			const uint32_t capacity = raw->m_numBuckets;
			const Slot* slots = Slots();

			HashT hashFn{};
			EqualsT equalsFn{};
			const uint64_t hashed = HashKey(key, hashFn);

			uint32_t index = static_cast<uint32_t>(hashed % capacity);
			uint32_t distance = 0;

			while (distance < capacity) {
				const Slot& slot = slots[index];
				if (slot.m_hash == kEmptyHash) {
					break;
				}

				if (slot.m_hash == hashed && equalsFn(KeyRef(slot), key)) {
					return index;
				}

				const uint32_t slotDistance = ProbeDistance(index, slot.m_hash, capacity);
				if (slotDistance < distance) {
					break;
				}

				index = (index + 1) % capacity;
				++distance;
			}

			return kInvalidIndex;
		}

		ValueT* FindValueInternal(const KeyT& key, uint32_t& outIndex) const {
			outIndex = FindIndex(key);
			if (outIndex == kInvalidIndex) {
				return nullptr;
			}

			auto* mutableSelf = const_cast<RobinHoodHashTable*>(this);
			return ValuePtr(mutableSelf->Slots()[outIndex]);
		}

		std::pair<ValueT*, bool> InsertInternal(const KeyT& key, const ValueT& value, InsertMode mode) {
			auto* raw = this->Get();
			always_assert(raw == nullptr || raw->m_Slots == nullptr,
				"RobinHoodHashTable::Insert called on uninitialized table");

			const uint32_t capacity = raw->m_numBuckets;
			always_assert(capacity == 0, "RobinHoodHashTable::Insert requires non-zero capacity");

			HashT hashFn{};
			EqualsT equalsFn{};
			uint64_t hashed = HashKey(key, hashFn);

			Slot* slots = Slots();

			uint32_t index = static_cast<uint32_t>(hashed % capacity);
			uint32_t entryDistance = 0;

			uint64_t entryHash = hashed;
			KeyT entryKey = key;
			ValueT entryValue = value;

			while (entryDistance < capacity) {
				Slot& slot = slots[index];

				if (slot.m_hash == kEmptyHash) {
					slot.m_hash = entryHash;
					KeyRef(slot) = entryKey;
					ValueRef(slot) = entryValue;
					MarkOccupied(index);
					raw->m_numElements += 1;
					return { ValuePtr(slot), true };
				}

				auto& slotKey = KeyRef(slot);
				auto& slotValue = ValueRef(slot);

				if (slot.m_hash == hashed && equalsFn(slotKey, key)) {
					if (mode == InsertMode::InsertUnique) {
						return { ValuePtr(slot), false };
					}

					slotValue = value;
					return { ValuePtr(slot), false };
				}

				uint32_t slotDistance = ProbeDistance(index, slot.m_hash, capacity);
				if (slotDistance < entryDistance) {
					std::swap(entryHash, slot.m_hash);
					std::swap(entryKey, slotKey);
					std::swap(entryValue, slotValue);
					std::swap(slotDistance, entryDistance);
					hashed = entryHash;
				}

				index = (index + 1) % capacity;
				++entryDistance;
			}

			always_assert(true, "RobinHoodHashTable::Insert failed – table is full");
			return { nullptr, false };
		}

		void EraseAt(uint32_t index) {
			auto* raw = this->Get();
			auto* slots = Slots();
			const uint32_t capacity = Capacity();

			uint32_t hole = index;
			uint32_t next = (hole + 1) % capacity;

			while (true) {
				Slot& nextSlot = slots[next];
				if (nextSlot.m_hash == kEmptyHash) {
					break;
				}

				const uint32_t distance = ProbeDistance(next, nextSlot.m_hash, capacity);
				if (distance == 0) {
					break;
				}

				slots[hole] = nextSlot;
				MarkOccupied(hole);

				hole = next;
				next = (next + 1) % capacity;
			}

			SetEmpty(slots[hole]);
			ClearOccupied(hole);

			if (raw->m_numElements > 0) {
				raw->m_numElements -= 1;
			}
		}
	};

}
