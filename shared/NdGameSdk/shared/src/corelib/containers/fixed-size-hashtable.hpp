#pragma once

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/corelib/containers/FixedSizeHashTable.hpp>
#elif defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/corelib/containers/FixedSizeHashTable.hpp>
#endif

#include "fixedsizeheap.hpp"
#include "../memory/memory.hpp"

#include <algorithm>
#include <cstring>
#include <limits>
#include <utility>

namespace NdGameSdk::corelib::containers {

	namespace detail {

		template<typename NodeT>
		struct FixedSizeHashTableLinks {
			using RawListHead = regenny::shared::corelib::containers::FixedSizeHashTable::ListHead;

			static RawListHead* AsHead(NodeT* node) {
				return reinterpret_cast<RawListHead*>(node);
			}

			static const RawListHead* AsHead(const NodeT* node) {
				return reinterpret_cast<const RawListHead*>(node);
			}

			static NodeT* Next(NodeT* node) {
				return node ? reinterpret_cast<NodeT*>(AsHead(node)->m_next) : nullptr;
			}

			static NodeT* Next(const NodeT* node) {
				return node ? reinterpret_cast<NodeT*>(AsHead(node)->m_next) : nullptr;
			}

			static NodeT* Prev(NodeT* node) {
				return node ? reinterpret_cast<NodeT*>(AsHead(node)->m_prev) : nullptr;
			}

			static NodeT* Prev(const NodeT* node) {
				return node ? reinterpret_cast<NodeT*>(AsHead(node)->m_prev) : nullptr;
			}

			static void SetNext(NodeT* node, NodeT* next) {
				AsHead(node)->m_next = next;
			}

			static void SetPrev(NodeT* node, NodeT* prev) {
				AsHead(node)->m_prev = prev;
			}
		};

		template<typename Fn, typename NodeRef>
		inline void InvokeBucketVisitor(Fn&& fn, NodeRef&& nodeRef, uint32_t bucketIndex) {
			if constexpr (std::is_invocable_v<Fn, NodeRef, uint32_t>) {
				std::invoke(std::forward<Fn>(fn), std::forward<NodeRef>(nodeRef), bucketIndex);
			} else if constexpr (std::is_invocable_v<Fn, NodeRef>) {
				std::invoke(std::forward<Fn>(fn), std::forward<NodeRef>(nodeRef));
			}
		}

		uint32_t UpdatePeakFlagsOnInsert(uint32_t currentFlags, uint64_t newCount);

	}

	template<typename NodeT>
	class NdGameSdk_API FixedSizeHashTable : public ISdkRegenny<regenny::shared::corelib::containers::FixedSizeHashTable> {
	public:
		using RawTable = regenny::shared::corelib::containers::FixedSizeHashTable;
		using Flags = RawTable::Flags;
		using ListHead = RawTable::ListHead;
		using size_type = uint64_t;
		using node_type = NodeT;

		void Initialize(uint64_t requestedBuckets,
			uint64_t nodeAlignment = 0x10,
			const char* sourceFunc = __func__,
			uint32_t sourceLine = __LINE__,
			const char* sourceFile = __FILE__,
			NodeT** bucketStorage = nullptr,
			NodeT* headStorage = nullptr) {

			auto* raw = this->Get();
			auto& memory = corelib::memory::Memory::RequireInstance<corelib::memory::Memory>();
			
			const auto peakMask = static_cast<uint32_t>(Flags::PeakMask);
			raw->m_PeakAndFlags = static_cast<Flags>(static_cast<uint32_t>(raw->m_PeakAndFlags) & peakMask);

			const uint64_t bucketCount = requestedBuckets == 0 ? 1 : requestedBuckets;
			const uint64_t alignedBuckets = (bucketCount + 0xFULL) & ~0xFULL;
			const uint64_t slotCount = alignedBuckets + 1;

			constexpr size_t pointerSize = sizeof(NodeT*);
			const bool overflowBuckets = slotCount != 0 && slotCount > ((std::numeric_limits<size_t>::max)() / pointerSize);
			always_assert(overflowBuckets, "FixedSizeHashTable::Initialize bucket allocation overflow");

			constexpr uint64_t nodeSize = sizeof(NodeT);
			uint64_t alignment = nodeAlignment != 0 ? nodeAlignment : 0x10;
			alignment = std::max<uint64_t>(alignment, alignof(NodeT));

			corelib::memory::Memory::Context contextValue = corelib::memory::Memory::Context::kAllocInvalid;
			Pool().template Init<NodeT>(bucketCount, nodeSize, static_cast<NodeT*>(nullptr), &contextValue, alignment,
				sourceFunc, sourceLine, sourceFile);

			const size_t bucketBytes = static_cast<size_t>(slotCount) * sizeof(NodeT*);

			NodeT** buckets = bucketStorage;
			if (buckets == nullptr) {
				buckets = reinterpret_cast<NodeT**>(
					memory.Allocate<NodeT**>(bucketBytes, alignof(NodeT*), sourceFunc, static_cast<int>(sourceLine), sourceFile));
				always_assert(buckets == nullptr, "FixedSizeHashTable::Initialize bucket allocation failed");
			}

			NodeT* head = headStorage;
			if (head == nullptr) {
				head = reinterpret_cast<NodeT*>(
					memory.Allocate<NodeT**>(static_cast<size_t>(nodeSize), alignment, sourceFunc, static_cast<int>(sourceLine), sourceFile));
				always_assert(head == nullptr, "FixedSizeHashTable::Initialize head allocation failed");
			}

			std::memset(head, 0, static_cast<size_t>(nodeSize));
			detail::FixedSizeHashTableLinks<NodeT>::SetNext(head, head);
			detail::FixedSizeHashTableLinks<NodeT>::SetPrev(head, head);

			raw->m_Buckets = reinterpret_cast<void**>(buckets);
			raw->m_Begin = reinterpret_cast<void**>(buckets);
			raw->m_End = reinterpret_cast<void**>(buckets + alignedBuckets);
			raw->m_NodeSize = nodeSize;
			raw->m_RequestedBuckets = bucketCount;
			raw->m_Count = 0;
			raw->m_Head = head;

			const uint32_t maxBucketValue = (std::numeric_limits<uint32_t>::max)();
			always_assert(alignedBuckets > maxBucketValue, "FixedSizeHashTable::Initialize bucket count exceeds range");
			raw->m_BucketCountAligned = static_cast<uint32_t>(alignedBuckets);

			buckets[alignedBuckets] = head;
			if (alignedBuckets > 0) {
				std::memset(buckets, 0, static_cast<size_t>(alignedBuckets) * sizeof(NodeT*));
			}

			Pool().Reset();

			raw->m_PeakAndFlags = static_cast<Flags>(static_cast<uint32_t>(raw->m_PeakAndFlags) | static_cast<uint32_t>(Flags::Initialized));
		}

		void Initialize(uint64_t requestedBuckets,
			const char* sourceFunc,
			uint32_t sourceLine,
			const char* sourceFile) {
			Initialize(requestedBuckets, nullptr, 0x10, sourceFunc, sourceLine, sourceFile);
		}

		size_type Size() const {
			return this->Get()->m_Count;
		}

		bool Empty() const {
			return Size() == 0;
		}

		uint32_t BucketCount() const {
			return this->Get()->m_BucketCountAligned;
		}

		uint64_t RequestedBucketCount() const {
			return this->Get()->m_RequestedBuckets;
		}

		uint64_t NodeSize() const {
			return this->Get()->m_NodeSize;
		}

		bool IsInitialized() const {
			const auto flags = static_cast<uint32_t>(this->Get()->m_PeakAndFlags);
			return (flags & static_cast<uint32_t>(Flags::Initialized)) != 0;
		}

		NodeT** Buckets() {
			return reinterpret_cast<NodeT**>(this->Get()->m_Buckets);
		}

		NodeT* const* Buckets() const {
			return reinterpret_cast<NodeT* const*>(this->Get()->m_Buckets);
		}

		NodeT* Head() {
			return reinterpret_cast<NodeT*>(this->Get()->m_Head);
		}

		const NodeT* Head() const {
			return reinterpret_cast<const NodeT*>(this->Get()->m_Head);
		}

		FixedSizeHeap& Pool() {
			return *reinterpret_cast<FixedSizeHeap*>(&this->Get()->m_Pool);
		}

		const FixedSizeHeap& Pool() const {
			return *reinterpret_cast<const FixedSizeHeap*>(&this->Get()->m_Pool);
		}

		template<bool IsConst>
		class IteratorBase {
		public:
			using NodePtr = std::conditional_t<IsConst, const NodeT*, NodeT*>;
			using BucketPtr = std::conditional_t<IsConst, NodeT* const*, NodeT**>;
			using iterator_category = std::forward_iterator_tag;
			using value_type = NodeT;
			using difference_type = ptrdiff_t;
			using reference = std::conditional_t<IsConst, const NodeT&, NodeT&>;
			using pointer = NodePtr;

			IteratorBase() = default;

			reference operator*() const {
				return *m_current;
			}

			pointer operator->() const {
				return m_current;
			}

			IteratorBase& operator++() {
				Advance();
				return *this;
			}

			IteratorBase operator++(int) {
				IteratorBase tmp = *this;
				Advance();
				return tmp;
			}

			friend bool operator==(const IteratorBase& lhs, const IteratorBase& rhs) {
				return lhs.m_current == rhs.m_current && lhs.m_bucketIndex == rhs.m_bucketIndex;
			}

			friend bool operator!=(const IteratorBase& lhs, const IteratorBase& rhs) {
				return !(lhs == rhs);
			}

		private:
			template<typename TablePtr>
			static IteratorBase MakeBegin(TablePtr table) {
				if (table == nullptr) {
					return {};
				}

				BucketPtr buckets = reinterpret_cast<BucketPtr>(table->Buckets());
				const uint32_t bucketCount = table->BucketCount();

				uint32_t index = 0;
				NodePtr current = nullptr;
				while (index < bucketCount) {
					current = buckets[index];
					if (current != nullptr) {
						break;
					}
					++index;
				}

				if (index >= bucketCount) {
					index = bucketCount;
					current = nullptr;
				}

				return IteratorBase(buckets, bucketCount, index, current);
			}

			template<typename TablePtr>
			static IteratorBase MakeEnd(TablePtr table) {
				if (table == nullptr) {
					return {};
				}

				BucketPtr buckets = reinterpret_cast<BucketPtr>(table->Buckets());
				const uint32_t bucketCount = table->BucketCount();
				return IteratorBase(buckets, bucketCount, bucketCount, nullptr);
			}

			void Advance() {
				if (m_bucketIndex >= m_bucketCount) {
					m_current = nullptr;
					return;
				}

				if (m_current != nullptr) {
					m_current = detail::FixedSizeHashTableLinks<std::remove_const_t<NodeT>>::Next(m_current);
					if (m_current != nullptr) {
						return;
					}
				}

				while (++m_bucketIndex < m_bucketCount) {
					m_current = m_buckets[m_bucketIndex];
					if (m_current != nullptr) {
						return;
					}
				}

				m_current = nullptr;
			}

			IteratorBase(BucketPtr buckets, uint32_t bucketCount, uint32_t bucketIndex, NodePtr current)
				: m_buckets(buckets)
				, m_bucketCount(bucketCount)
				, m_bucketIndex(bucketIndex)
				, m_current(current) {}

			BucketPtr m_buckets{ nullptr };
			uint32_t m_bucketCount{ 0 };
			uint32_t m_bucketIndex{ 0 };
			NodePtr m_current{ nullptr };

			friend class FixedSizeHashTable<NodeT>;
		};

		using Iterator = IteratorBase<false>;
		using ConstIterator = IteratorBase<true>;

		Iterator begin() {
			return Iterator::MakeBegin(this);
		}

		Iterator end() {
			return Iterator::MakeEnd(this);
		}

		ConstIterator begin() const {
			return ConstIterator::MakeBegin(this);
		}

		ConstIterator end() const {
			return ConstIterator::MakeEnd(this);
		}

		ConstIterator cbegin() const {
			return ConstIterator::MakeBegin(this);
		}

		ConstIterator cend() const {
			return ConstIterator::MakeEnd(this);
		}

		template<typename Fn>
		void ForEach(Fn&& fn) {
			NodeT** buckets = Buckets();
			const uint32_t bucketCount = BucketCount();
			for (uint32_t bucket = 0; bucket < bucketCount; ++bucket) {
				NodeT* node = buckets[bucket];
				while (node != nullptr) {
					detail::InvokeBucketVisitor(fn, *node, bucket);
					node = detail::FixedSizeHashTableLinks<NodeT>::Next(node);
				}
			}
		}

		template<typename Fn>
		void ForEach(Fn&& fn) const {
			NodeT* const* buckets = Buckets();
			const uint32_t bucketCount = BucketCount();
			for (uint32_t bucket = 0; bucket < bucketCount; ++bucket) {
				const NodeT* node = buckets[bucket];
				while (node != nullptr) {
					detail::InvokeBucketVisitor(fn, *node, bucket);
					node = detail::FixedSizeHashTableLinks<NodeT>::Next(node);
				}
			}
		}

		template<typename Key, typename HashFn, typename MatchFn>
		NodeT* Find(const Key& key, HashFn&& hashFn, MatchFn&& matchFn) {
			auto lookup = LocateMutable(key, std::forward<HashFn>(hashFn), std::forward<MatchFn>(matchFn));
			return lookup.node;
		}

		template<typename Key, typename HashFn, typename MatchFn>
		const NodeT* Find(const Key& key, HashFn&& hashFn, MatchFn&& matchFn) const {
			return LocateConst(key, std::forward<HashFn>(hashFn), std::forward<MatchFn>(matchFn));
		}

		template<typename Key, typename HashFn, typename MatchFn, typename InitFn>
		NodeT* FindOrEmplace(const Key& key, HashFn&& hashFn, MatchFn&& matchFn, InitFn&& initFn) {

			auto lookup = LocateMutable(key, std::forward<HashFn>(hashFn), std::forward<MatchFn>(matchFn));

			if (lookup.head == nullptr) {
				return nullptr;
			}

			if (lookup.node != nullptr) {
				std::invoke(std::forward<InitFn>(initFn), *lookup.node, false);
				return lookup.node;
			}

			NodeT* newNode = AllocateNode();
			if (newNode == nullptr) {
				return nullptr;
			}

			ClearNode(newNode, static_cast<size_t>(NodeSize()));

			NodeT* const oldHead = *lookup.head;
			detail::FixedSizeHashTableLinks<NodeT>::SetPrev(newNode, nullptr);
			detail::FixedSizeHashTableLinks<NodeT>::SetNext(newNode, oldHead);

			if (oldHead != nullptr) {
				detail::FixedSizeHashTableLinks<NodeT>::SetPrev(oldHead, newNode);
			}

			*lookup.head = newNode;

			auto* raw = this->Get();
			const uint64_t newCount = raw->m_Count + 1;
			raw->m_Count = newCount;

			const uint32_t currentFlags = static_cast<uint32_t>(raw->m_PeakAndFlags);
			const uint32_t updated = detail::UpdatePeakFlagsOnInsert(currentFlags, newCount);
			raw->m_PeakAndFlags = static_cast<Flags>(updated);

			std::invoke(std::forward<InitFn>(initFn), *newNode, true);
			return newNode;
		}

		template<typename Key, typename HashFn, typename MatchFn, typename CleanupFn = std::nullptr_t>
		bool Remove(const Key& key, HashFn&& hashFn, MatchFn&& matchFn, CleanupFn&& cleanup = nullptr) {

			auto lookup = LocateMutable(key, std::forward<HashFn>(hashFn), std::forward<MatchFn>(matchFn));
			if (lookup.node == nullptr || lookup.slot == nullptr) {
				return false;
			}

			NodeT* node = lookup.node;
			NodeT* const next = detail::FixedSizeHashTableLinks<NodeT>::Next(node);

			*lookup.slot = next;

			if (next != nullptr) {
				detail::FixedSizeHashTableLinks<NodeT>::SetPrev(next,
					detail::FixedSizeHashTableLinks<NodeT>::Prev(node));
			}

			if constexpr (!std::is_same_v<std::decay_t<CleanupFn>, std::nullptr_t>) {
				std::invoke(std::forward<CleanupFn>(cleanup), *node);
			}

			Pool().template FreeIndex<NodeT>(node);
			ClearNode(node, static_cast<size_t>(NodeSize()));

			auto* raw = this->Get();
			if (raw->m_Count != 0) {
				raw->m_Count -= 1;
			}

			return true;
		}

	private:
		struct LookupResult {
			NodeT* node{ nullptr };
			NodeT** slot{ nullptr };
			NodeT** head{ nullptr };
			uint32_t bucketIndex{ 0 };
		};

		template<typename Key, typename HashFn, typename MatchFn>
		LookupResult LocateMutable(const Key& key, HashFn&& hashFn, MatchFn&& matchFn) {

			LookupResult out{};
			auto* raw = this->Get();

			if (raw->m_Buckets == nullptr || raw->m_BucketCountAligned == 0) {
				return out;
			}

			const uint64_t hashed = static_cast<uint64_t>(hashFn(key));
			out.bucketIndex = static_cast<uint32_t>(raw->m_BucketCountAligned == 0 ? 0 : hashed % raw->m_BucketCountAligned);

			NodeT** buckets = reinterpret_cast<NodeT**>(raw->m_Buckets);
			out.head = &buckets[out.bucketIndex];

			NodeT** cursor = out.head;
			NodeT* node = *cursor;
			while (node != nullptr) {
				if (matchFn(*node, key)) {
					out.node = node;
					out.slot = cursor;
					return out;
				}

				cursor = reinterpret_cast<NodeT**>(&detail::FixedSizeHashTableLinks<NodeT>::AsHead(node)->m_next);
				node = detail::FixedSizeHashTableLinks<NodeT>::Next(node);
			}

			out.slot = cursor;
			return out;
		}

		template<typename Key, typename HashFn, typename MatchFn>
		const NodeT* LocateConst(const Key& key, HashFn&& hashFn, MatchFn&& matchFn) const {
			auto* raw = this->Get();
			if (raw->m_Buckets == nullptr || raw->m_BucketCountAligned == 0) {
				return nullptr;
			}

			const uint64_t hashed = static_cast<uint64_t>(hashFn(key));
			const uint32_t index = static_cast<uint32_t>(raw->m_BucketCountAligned == 0 ? 0 : hashed % raw->m_BucketCountAligned);

			NodeT* const* buckets = reinterpret_cast<NodeT* const*>(raw->m_Buckets);
			const NodeT* node = buckets[index];
			while (node != nullptr) {
				if (matchFn(*node, key)) {
					return node;
				}
				node = detail::FixedSizeHashTableLinks<NodeT>::Next(node);
			}

			return nullptr;
		}

		static void ClearNode(NodeT* node, size_t nodeSize) {
			if (node != nullptr && nodeSize != 0) {
				std::memset(node, 0, nodeSize);
			}
		}

		NodeT* AllocateNode() {
			return Pool().template AddIndex<NodeT>();
		}

	};

}
