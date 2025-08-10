#pragma once

#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/components/SdkComponent.hpp"

#include <NdGameSdk/shared/src/corelib/memory/memory.hpp>
#include <NdGameSdk/shared/src/ndlib/render/dev/debugdraw-common.hpp>
#include <NdGameSdk/shared/src/ndlib/debug/nd-dmenu.hpp>

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/corelib/job/ndjob.hpp>
#include <NdGameSdk/regenny/t2r/shared/corelib/job/JobHeap.hpp>
#include <NdGameSdk/regenny/t2r/shared/corelib/job/JobSystem.hpp>
#include <NdGameSdk/regenny/t2r/shared/corelib/job/JlsContext.hpp>
#include <NdGameSdk/regenny/t2r/shared/corelib/job/JlsEntry.hpp>
#include <NdGameSdk/regenny/t2r/shared/corelib/job/JlsBlock.hpp>
#elif defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/corelib/job/ndjob.hpp>
#include <NdGameSdk/regenny/t1x/shared/corelib/job/JobHeap.hpp>
#include <NdGameSdk/regenny/t1x/shared/corelib/job/JobSystem.hpp>
#include <NdGameSdk/regenny/t1x/shared/corelib/job/JlsContext.hpp>
#include <NdGameSdk/regenny/t1x/shared/corelib/job/JlsEntry.hpp>
#include <NdGameSdk/regenny/t1x/shared/corelib/job/JlsBlock.hpp>
#endif

using namespace NdGameSdk::corelib::memory;

namespace NdGameSdk::corelib::job {

	/* Extern classes */
	using JlsContext = regenny::shared::corelib::job::JlsContext;

	class JobSysData : public ISdkRegenny<regenny::shared::corelib::job::ndjob::JobSysData> {
	public:
		class InitParams : public ISdkRegenny<regenny::shared::corelib::job::ndjob::InitParams> {
		public:
			size_t GetMemoryBufferSize() const;
			size_t GetDebugMemoryBufferSize() const;
			uint64_t GetNumCounters() const;
			uint64_t GetNumJobArrays() const;
			uint64_t GetNumWorkerThreads() const;
			uint64_t GetMaxSmallJobFibers() const;
			uint64_t GetMaxLargeJobFibers() const;
			uint64_t GetSmallJobFiberStackSpace() const;
			uint64_t GetLargeJobFiberStackSpace() const;

			void SetMemoryBufferSize(size_t size);
			void SetDebugMemoryBufferSize(size_t size);
			void SetNumCounters(uint64_t count);
			void SetNumJobArrays(uint64_t count);
			void SetNumWorkerThreads(uint64_t count);
			void SetMaxSmallJobFibers(uint64_t count);
			void SetMaxLargeJobFibers(uint64_t count);
		};
	};
	class JobHeap;
	class JobSystem;
	class JobHeader;
	class CounterHandle;

	template <typename T>
	struct JlsEntry : public ISdkRegenny<regenny::shared::corelib::job::JlsEntry> {

		JlsEntry() = default;

		JlsEntry(StringId64 ctx, T val) {
			auto* self = this->Get();
			self->m_contextid = ctx;
			self->m_payload = reinterpret_cast<uint64_t>(val);
		}

		[[nodiscard]] StringId64 key() const noexcept { return this->Get()->m_contextid; }

		[[nodiscard]] T value() noexcept {
			if constexpr (std::is_pointer_v<T>)
				return reinterpret_cast<T>(this->Get()->m_payload);
			else
				return static_cast<T>(this->Get()->m_payload);
		}

		[[nodiscard]] const T value() const noexcept {
			if constexpr (std::is_pointer_v<T>)
				return reinterpret_cast<const T>(this->Get()->m_payload);
			else
				return static_cast<T>(this->Get()->m_payload);
		}

		void set_value(T val) {
			if constexpr (std::is_pointer_v<T>)
				this->Get()->m_payload = reinterpret_cast<uint64_t>(val);
			else
				this->Get()->m_payload = static_cast<uint64_t>(val);
		}

		static inline void* jls_payload(T v) {
			if constexpr (std::is_pointer_v<T>) {
				return const_cast<void*>(static_cast<const void*>(v));
			}
			else if constexpr (std::is_enum_v<T>) {
				using U = std::underlying_type_t<T>;
				return reinterpret_cast<void*>(static_cast<std::uint64_t>(static_cast<U>(v)));
			}
			else if constexpr (std::is_integral_v<T>) {
				return reinterpret_cast<void*>(static_cast<std::uint64_t>(v));
			}
			else if constexpr (std::is_floating_point_v<T>) {
				std::uint64_t bits = 0;
				static_assert(sizeof(v) <= sizeof(bits), "unexpected float size");
				std::memcpy(&bits, &v, sizeof(v));
				return reinterpret_cast<void*>(bits);
			}
			else {
				static_assert(sizeof(T) == 0, "Unsupported T for JlsValueWrite()");
			}
		}
	};

	struct JlsBlock : public ISdkRegenny<regenny::shared::corelib::job::JlsBlock> {
		using Raw = regenny::shared::corelib::job::JlsBlock;
		using RawEntry = regenny::shared::corelib::job::JlsEntry;

		static constexpr std::size_t kSlots = sizeof(Raw::slots) / sizeof(Raw::slots[0]);

		template<class T = void>
		JlsEntry<T>& slot(std::size_t i) {
			return *reinterpret_cast<JlsEntry<T>*>(&this->Get()->slots[i]);
		}

		template<class T = void>
		const JlsEntry<const T>& slot(std::size_t i) const {
			return *reinterpret_cast<const JlsEntry<const T>*>(&this->Get()->slots[i]);
		}

		template<class T = void>
		JlsEntry<T>& slot(JlsContext c) { return slot<T>(static_cast<std::size_t>(c)); }
		template<class T = void>
		const JlsEntry<const T>& slot(JlsContext c) const { return slot<const T>(static_cast<std::size_t>(c)); }

		template<class T = void>
		JlsEntry<T>& write(std::size_t index, const JlsEntry<T>& src) const {
			auto* dst = &this->Get()->slots[index];
			*dst = *src.Get();
			return *reinterpret_cast<JlsEntry<T>*>(dst);
		}

		template<class T = void>
		JlsEntry<T>& write(JlsContext index, const JlsEntry<T>& src) const {
			return write<T>(static_cast<std::size_t>(index), src);
		}

		template<class T = void>
		JlsEntry<T>& write(std::size_t index, StringId64 ctx, T val) const {
			JlsEntry<T> tmp{ ctx, val };
			return write<T>(index, tmp);
		}

		template<class T = void>
		JlsEntry<T>& write(JlsContext index, StringId64 ctx, T val) const {
			return write<T>(static_cast<std::size_t>(index), ctx, val);
		}

		void clear(std::size_t index) const {
			auto& r = this->Get()->slots[index];
			r.m_contextid = 0;
			r.m_payload = 0;
		}

		bool slot_exists(std::size_t index) const {
			return this->Get()->slots[index].m_contextid != 0;
		}

		template<class T = void>
		JlsEntry<T>* find(StringId64 ctx) {
			for (std::size_t i = 0; i < kSlots; ++i) {
				auto& e = slot<T>(i);
				if (e.key() == ctx) return &e;
			}
			return nullptr;
		}

		struct Iterator {
			RawEntry* cur{}; RawEntry* end{};
			void advance() { while (cur != end && cur->m_contextid == 0) ++cur; }
			Iterator& operator++() { ++cur; advance(); return *this; }
			bool operator!=(Iterator const& o) const { return cur != o.cur; }
			JlsEntry<uint64_t>& operator*() { return *reinterpret_cast<JlsEntry<uint64_t>*>(cur); }
		};

		Iterator begin() { auto* b = &this->Get()->slots[0]; auto* e = b + kSlots; Iterator it{ b,e }; it.advance(); return it; }
		Iterator end() { auto* e = &this->Get()->slots[kSlots]; return { e,e }; }

		Iterator begin() const { auto* b = const_cast<RawEntry*>(&this->Get()->slots[0]); auto* e = b + kSlots; Iterator it{ b,e }; it.advance(); return it; }
		Iterator end()   const { auto* e = const_cast<RawEntry*>(&this->Get()->slots[kSlots]); return { e,e }; }
	};

	class NdGameSdk_API NdJob : public ISdkComponent {
	public:
		using InitParams = JobSysData::InitParams;
		using Priority = ::regenny::shared::corelib::job::ndjob::Priority;
		SDK_DEPENDENCIES(Memory);

		NdJob();

		bool IsWorkerThread();
		bool IsGameFrameJob();

		const uint64_t TryGetWorkerThreadIndex();
		const uint64_t GetCurrentWorkerThreadIndex();
		const uint64_t GetActiveJobId();
		const Priority GetCurrentWorkerPriority();

		template <typename T>
		bool TryGetJlsSlotValue(JlsContext index, T* outValue) {
			always_assert(NdJob_TryGetJlsSlotValue == nullptr, "Function pointer was not set!");
			return NdJob_TryGetJlsSlotValue(index, outValue);
		}

		template <typename T>
		bool JlsValueWrite(JlsContext index, StringId64 hash, T value) {
		#if defined(T2R)
			always_assert(NdJob_JlsValueWrite == nullptr, "Function pointer was not set!");
			return NdJob_JlsValueWrite(index, hash, JlsEntry<T>::jls_payload(value));
		#else
			if (auto* jobTls = GetJobTls()) {
				const JlsEntry<T> entry{ hash, value };
				jobTls->write<T>(index, entry);
				return true;
			}
			return false;
		#endif
		}

		template <typename T>
		bool GetJlsValueByIndex(JlsContext index, T* outValue) {
		#if defined(T2R)
			always_assert(NdJob_GetJlsValueByIndex == nullptr, "Function pointer was not set!");
			return NdJob_GetJlsValueByIndex(index, outValue);
		#else
			if (auto* jobTls = GetJobTls()) {
				const JlsEntry<const T>& entry = jobTls->slot<T>(index);
				if (entry.key() != 0) {
					*outValue = entry.value();
				}
				return true;
			}
			return false;
		#endif
		}

		void ClearJlsValueByIndex(JlsContext index) {
		#if defined(T2R)
			always_assert(NdJob_ClearJlsValueByIndex == nullptr, "Function pointer was not set!");
			NdJob_ClearJlsValueByIndex(index);
		#else
			if (auto* jobTls = GetJobTls()) {
				jobTls->clear(index);
			}
		#endif
		}

		bool DoesJobLocalStorageIdExist(JlsContext index) {
		#if defined(T2R)
			always_assert(NdJob_DoesJobLocalStorageIdExist == nullptr, "Function pointer was not set!");
			return NdJob_DoesJobLocalStorageIdExist(index);
		#else
			if (auto* jobTls = GetJobTls()) {
				return jobTls->slot_exists(index);
			}
			return false;
		#endif
		}

		void MakeJobHeader(JobHeader* dst, void* entry, void* workData);
		void RegisterJobArray(JobHeader* headers, uint64_t count, CounterHandle** pCounter, HeapArena_Args,
			uint64_t arg7 = 1, uint64_t arg8 = ~0ull, uint64_t arg9 = 0);

		void SubmitJobArray(void* entry, void* const* workItems, uint64_t count,
			Priority prio, HeapArena_Args, CounterHandle** pCounter = nullptr,
			uint64_t flagsLow60 = 0, bool wait = false);

		void SubmitJobArray(void* entry, void* workData, uint64_t count,
			Priority prio, HeapArena_Args, CounterHandle** pCounter = nullptr,
			uint64_t flagsLow60 = 0, bool wait = false);

		void RunJobAndWait(void* pEntry, void* pWorkData, HeapArena_Args, int64_t pFlags = 0);
		void WaitForCounter(CounterHandle** pCounter, uint64_t pCountJobArray = 0, uint32_t arg3 = 0);

		// This function is used to yield the current job execution, 
		// allowing other jobs to run.
		void JobYield();

	private:
		void Initialize() override;
		void Awake() override;

		void DisplayJobSystemData();

#if defined(_MSC_VER) && defined(_M_X64)
		inline const JlsBlock* GetJobTls();
#endif

		static DMENU::ItemSubmenu* CreateJobSystemMenu(NdDevMenu* pdmenu, DMENU::Menu* pMenu);
		/*Extern Functs*/
		static int32_t* NdJobInitialize(int32_t* Err, NdJob::InitParams* pParams);

		Memory* m_Memory;

		InlineHook m_JobSysDataInitHook{};
		MidHook m_JobSysDataInitReturnHook{};

		/*Extern variables*/
		JobSysData* g_pJobSysData{};
		JobSystem* s_JobSystem{};
		JobHeap* g_pJobHeap{};

		MEMBER_FUNCTION_PTR(void, NdJob_DisplayJobSystemData);
		MEMBER_FUNCTION_PTR(void, NdJob_WaitForCounter, CounterHandle** pCounter, uint64_t pCountJobArray, uint32_t arg3);
		MEMBER_FUNCTION_PTR(uint64_t, NdJob_TryGetWorkerThreadIndex);
		MEMBER_FUNCTION_PTR(void, NdJob_SetJobLocalStorage, uint64_t arg1, uint64_t pSlotIndexes);
		MEMBER_FUNCTION_PTR(void, NdJob_RunJobAndWait, void* pEntry, void* pWorkData, uint64_t pFlags, char const* pFile, uint32_t pLine, char const* pFunc);
		MEMBER_FUNCTION_PTR(void, NdJob_RegisterJobArray, JobHeader* pJobHeaders, uint64_t pCountJobArrays, CounterHandle** pCounter,
			char const* pFile, uint32_t pLine, char const* pFunc, uint64_t arg7, uint64_t arg8, uint64_t arg9);
		MEMBER_FUNCTION_PTR(void, NdJob_MakeJobHeader, JobHeader* pJobHeaders, void* pEntry, void* pWorkData);
		MEMBER_FUNCTION_PTR(bool, NdJob_IsGameFrameJob);
		MEMBER_FUNCTION_PTR(bool, NdJob_IsWorkerThread);
		MEMBER_FUNCTION_PTR(Priority, NdJob_GetCurrentWorkerPriority);
		MEMBER_FUNCTION_PTR(uint64_t, NdJob_GetCurrentWorkerThreadIndex);
		MEMBER_FUNCTION_PTR(void, NdJob_Yield);
		MEMBER_FUNCTION_PTR(bool, NdJob_TryGetJlsSlotValue, uint32_t index, void* outValue);
#if defined (T2R)
		MEMBER_FUNCTION_PTR(uint64_t, NdJob_GetActiveJobId);
		MEMBER_FUNCTION_PTR(bool, NdJob_JlsValueWrite, uint32_t index, StringId64 hash, void* Value);
		MEMBER_FUNCTION_PTR(bool, NdJob_GetJlsValueByIndex, int32_t index, void* outValue);
		MEMBER_FUNCTION_PTR(bool, NdJob_ClearJlsValueByIndex, int32_t index);
		MEMBER_FUNCTION_PTR(bool, NdJob_DoesJobLocalStorageIdExist, uint32_t index);
#endif

		friend class ndlib::render::dev::DebugDrawCommon;
		friend class NdDevMenu;
	};

	class CounterHandle : public ISdkRegenny<regenny::shared::corelib::job::ndjob::CounterHandle> {
	public:
		CounterHandle() = default;

		std::string GetFilePath() const;
		std::string GetFunctionName() const;
		uint32_t GetLine() const;

		uint64_t GetTimestampQPC() const;
		uint32_t GetCountJobArrays() const;
	};

	class JobHeap : public ISdkRegenny<regenny::shared::corelib::job::JobHeap> {};

	class JobSystem : public ISdkRegenny<regenny::shared::corelib::job::JobSystem> {
	public:
		bool PrintJobSysDataStats() const;
	};

	class JobHeader : public ISdkRegenny<regenny::shared::corelib::job::ndjob::JobHeader> {
	public:
		JobHeader() = default;
		JobHeader(void* pEntry, void* pWorkData) {
			auto self = this->Get();
			self->m_entry = pEntry;
			self->m_WorkData = pWorkData;
			self->m_stateBits &= ~0xfffffff0;
			self->m_flags &= 0xf000000000000000;
		}
	};
}