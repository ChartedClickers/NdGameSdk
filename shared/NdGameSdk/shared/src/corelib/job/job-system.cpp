#include "job-system.hpp"
#include "./NdGameSdk/shared/sharedpatterns.hpp"

#include <Utility/helper.hpp>
#include <NdGameSdk/shared/src/gamelib/debug/nd-dev-menu.hpp>

namespace NdGameSdk::corelib::job {

	NdJob::NdJob() : ISdkComponent(TOSTRING(NdJob)) {}

	void NdJob::Awake() {
		auto SharedComponents = ISdkComponent::GetSharedComponents();
		m_Memory = GetDependencyComponent<Memory>(SharedComponents);
	}

	void NdJob::Initialize() {
		static std::once_flag Initialized;

		std::call_once(Initialized, [this] {

			spdlog::info("Initializing {} patterns...", GetName());

			Patterns::SdkPattern findpattern{};
			auto module = Utility::memory::get_executable();

			findpattern = Patterns::NdJob_g_pJobSysData;
			g_pJobSysData = (JobSysData*)Utility::ReadLEA32(module,
				findpattern.pattern, wstr(Patterns::NdJob_g_pJobSysData), findpattern.offset, 3, 7);

			findpattern = Patterns::NdJob_g_NdJobHeap;
			g_pJobHeap = (JobHeap*)Utility::ReadLEA32(module,
				findpattern.pattern, wstr(Patterns::NdJob_g_NdJobHeap), findpattern.offset, 3, 7);

			findpattern = Patterns::NdJob_s_JobSystem;
			s_JobSystem = (JobSystem*)Utility::ReadLEA32(module,
				findpattern.pattern, wstr(Patterns::NdJob_s_JobSystem), findpattern.offset, 3, 7);

			findpattern = Patterns::NdJob_Initialize;
			auto JobSysDataInit = (void*)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::NdJob_Initialize), findpattern.offset);

			findpattern = Patterns::NdJob_InitializeReturn;
			auto JobSysDataInitReturn = (void*)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::NdJob_InitializeReturn), findpattern.offset);

			if (!g_pJobSysData ||
				!g_pJobHeap ||
				!s_JobSystem ||
				!JobSysDataInit ||
				!JobSysDataInitReturn) {
				throw SdkComponentEx{ std::format("Failed to find JobSysData addresses!"),
					SdkComponentEx::ErrorCode::PatternFailed };
			}

			findpattern = Patterns::NdJob_DisplayJobSystemData;
			NdJob_DisplayJobSystemData = (NdJob_DisplayJobSystemData_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::NdJob_DisplayJobSystemData), findpattern.offset);

			findpattern = Patterns::NdJob_AllocateCounter;
			NdJob_AllocateCounter = (NdJob_AllocateCounter_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::NdJob_AllocateCounter), findpattern.offset);

			findpattern = Patterns::NdJob_WaitForCounter;
			NdJob_WaitForCounter = (NdJob_WaitForCounter_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::NdJob_WaitForCounter), findpattern.offset);

			findpattern = Patterns::NdJob_TryGetWorkerThreadIndex;
			NdJob_TryGetWorkerThreadIndex = (NdJob_TryGetWorkerThreadIndex_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::NdJob_TryGetWorkerThreadIndex), findpattern.offset);

			findpattern = Patterns::NdJob_SetJobLocalStorage;
			NdJob_SetJobLocalStorage = (NdJob_SetJobLocalStorage_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::NdJob_SetJobLocalStorage), findpattern.offset);

			findpattern = Patterns::NdJob_RunJobAndWait;
			NdJob_RunJobAndWait = (NdJob_RunJobAndWait_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::NdJob_RunJobAndWait), findpattern.offset);

			findpattern = Patterns::NdJob_RegisterJobArray;
			NdJob_RegisterJobArray = (NdJob_RegisterJobArray_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::NdJob_RegisterJobArray), findpattern.offset);

			findpattern = Patterns::NdJob_MakeJobHeader;
			NdJob_MakeJobHeader = (NdJob_MakeJobHeader_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::NdJob_MakeJobHeader), findpattern.offset);

			findpattern = Patterns::NdJob_IsWorkerThread;
			NdJob_IsWorkerThread = (NdJob_IsWorkerThread_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::NdJob_IsWorkerThread), findpattern.offset);

			findpattern = Patterns::NdJob_IsGameFrameJob;
			NdJob_IsGameFrameJob = (NdJob_IsGameFrameJob_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::NdJob_IsGameFrameJob), findpattern.offset);

			findpattern = Patterns::NdJob_GetCurrentWorkerPriority;
			NdJob_GetCurrentWorkerPriority = (NdJob_GetCurrentWorkerPriority_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::NdJob_GetCurrentWorkerPriority), findpattern.offset);

			findpattern = Patterns::NdJob_GetCurrentWorkerThreadIndex;
			NdJob_GetCurrentWorkerThreadIndex = (NdJob_GetCurrentWorkerThreadIndex_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::NdJob_GetCurrentWorkerThreadIndex), findpattern.offset);

			findpattern = Patterns::NdJob_Yield;
			NdJob_Yield = (NdJob_Yield_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::NdJob_Yield), findpattern.offset);

			findpattern = Patterns::NdJob_TryGetJlsSlotValue;
			NdJob_TryGetJlsSlotValue = (NdJob_TryGetJlsSlotValue_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::NdJob_TryGetJlsSlotValue), findpattern.offset);

			findpattern = Patterns::NdJob_WaitForCounterAndFree;
			NdJob_WaitForCounterAndFree = (NdJob_WaitForCounterAndFree_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::NdJob_WaitForCounterAndFree), findpattern.offset);

			findpattern = Patterns::NdJob_FreeCounter;
			NdJob_FreeCounter = (NdJob_FreeCounter_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::NdJob_FreeCounter), findpattern.offset);

	#if defined(T2R)
			findpattern = Patterns::NdJob_GetActiveJobId;
			NdJob_GetActiveJobId = (NdJob_GetActiveJobId_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::NdJob_GetActiveJobId), findpattern.offset);

			findpattern = Patterns::NdJob_JlsValueWrite;
			NdJob_JlsValueWrite = (NdJob_JlsValueWrite_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::NdJob_JlsValueWrite), findpattern.offset);

			findpattern = Patterns::NdJob_GetJlsValueByIndex;
			NdJob_GetJlsValueByIndex = (NdJob_GetJlsValueByIndex_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::NdJob_GetJlsValueByIndex), findpattern.offset);

			findpattern = Patterns::NdJob_ClearJlsValueByIndex;
			NdJob_ClearJlsValueByIndex = (NdJob_ClearJlsValueByIndex_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::NdJob_ClearJlsValueByIndex), findpattern.offset);

			findpattern = Patterns::NdJob_DoesJobLocalStorageIdExist;
			NdJob_DoesJobLocalStorageIdExist = (NdJob_DoesJobLocalStorageIdExist_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::NdJob_DoesJobLocalStorageIdExist), findpattern.offset);
	#endif

			if (!NdJob_DisplayJobSystemData ||
				!NdJob_WaitForCounter ||
				!NdJob_AllocateCounter ||
				!NdJob_TryGetWorkerThreadIndex ||
				!NdJob_SetJobLocalStorage ||
				!NdJob_RunJobAndWait ||
				!NdJob_RegisterJobArray ||
				!NdJob_MakeJobHeader ||
				!NdJob_IsWorkerThread ||
				!NdJob_IsGameFrameJob ||
				!NdJob_GetCurrentWorkerPriority ||
				!NdJob_GetCurrentWorkerThreadIndex ||
				!NdJob_Yield ||
				!NdJob_TryGetJlsSlotValue ||
				!NdJob_WaitForCounterAndFree ||
				!NdJob_FreeCounter
			#if defined(T2R)
				|| !NdJob_GetActiveJobId ||
				!NdJob_JlsValueWrite ||
				!NdJob_GetJlsValueByIndex ||
				!NdJob_ClearJlsValueByIndex ||
				!NdJob_DoesJobLocalStorageIdExist
			#endif
				) {
				throw SdkComponentEx{ std::format("Failed to find {}:: game function!", GetName()), SdkComponentEx::ErrorCode::PatternFailed };
			}

			m_JobSysDataInitHook = Utility::MakeSafetyHookInline(JobSysDataInit, NdJobInitialize,
				wstr(Patterns::NdJob_Initialize), wstr(JobSysDataInit));

			m_JobSysDataInitReturnHook = Utility::MakeMidHook(JobSysDataInitReturn,
				[](SafetyHookContext& ctx)
				{
					return;

				}, wstr(Patterns::NdJob_InitializeReturn), wstr(JobSysDataInitReturn));

			if (!m_JobSysDataInitHook ||
				!m_JobSysDataInitReturnHook) {
				throw SdkComponentEx{ "Failed to create JobSysData hooks!",
					SdkComponentEx::ErrorCode::PatchFailed, true };
			}

		});
	}

	bool NdJob::IsWorkerThread() {
	#if defined(T2R) || defined(T1X)
		always_assert(NdJob_IsWorkerThread == nullptr, "Function pointer was not set!");
		return NdJob_IsWorkerThread();
	#else
		return TryGetWorkerThreadIndex() < 0x18;
	#endif
	}

	bool NdJob::IsGameFrameJob() {
		always_assert(NdJob_IsGameFrameJob == nullptr, "Function pointer was not set!");
		return NdJob_IsGameFrameJob();
	}

	const uint64_t NdJob::TryGetWorkerThreadIndex() {
		always_assert(NdJob_TryGetWorkerThreadIndex == nullptr, "Function pointer was not set!");
		return NdJob_TryGetWorkerThreadIndex();
	}

	const uint64_t NdJob::GetCurrentWorkerThreadIndex() {
	#if defined(T2R) || defined(T1X)
		always_assert(NdJob_GetCurrentWorkerThreadIndex == nullptr, "Function pointer was not set!");
		return NdJob_GetCurrentWorkerThreadIndex();
	#else
		const auto jobTls = GetJobTls();
		if (!jobTls) {
			spdlog::warn("Job TLS is null, returning 0 for worker thread index.");
			return 0;
		}
		return jobTls->slot<uint64_t>(JlsContext::workerThreadIndex).value();
	#endif
	}

	const uint64_t NdJob::GetActiveJobId() {
	#if defined(T2R)
		always_assert(NdJob_GetActiveJobId == nullptr, "Function pointer was not set!");
		return NdJob_GetActiveJobId();
	#else
		return GetJobTls()->slot<uint64_t>(JlsContext::jobId).value();
	#endif
	}

	const NdJob::Priority NdJob::GetCurrentWorkerPriority() {
		always_assert(NdJob_GetCurrentWorkerPriority == nullptr, "Function pointer was not set!");
		return NdJob_GetCurrentWorkerPriority();
	}

	void NdJob::MakeJobHeader(JobHeader* dst, void* entry, void* workData) {
		always_assert(NdJob_MakeJobHeader == nullptr, "Function pointer was not set!");
		NdJob_MakeJobHeader(dst, entry, workData);
	}

	void NdJob::RegisterJobArray(JobHeader* headers, uint64_t count, CounterHandle** pCounter, HeapArena_Args, Priority pPriority
		, WorkerMask workerAffinityMask, CounterHandle::CounterWakePolicy counterWakeFlags) {
		always_assert(NdJob_RegisterJobArray == nullptr, "Function pointer was not set!");
		NdJob_RegisterJobArray(headers, count, pCounter, source_file, source_line, source_func, pPriority, workerAffinityMask, counterWakeFlags);
	}

	void NdJob::SubmitJobArray(void* entry, void* const* workItems, uint64_t count,
		Priority prio, HeapArena_Args, CounterHandle** pCounter, JobFlag flags, WorkerMask workerAffinityMask, bool wait) {

		if (count == 0) return;

		// 32 headers * 0x80 = 4KB.
		static constexpr size_t kStackBytesMax = 0x1000; // 4 KiB

		const size_t bytes = count * sizeof(JobHeader);
		JobHeader* headers = nullptr;
		void* rawStack = nullptr;
		bool usedHeap = false;

		if (bytes <= kStackBytesMax) {
			rawStack = _alloca(bytes + 0x3F);
			headers = reinterpret_cast<JobHeader*>((reinterpret_cast<uintptr_t>(rawStack) + 0x3F) & ~uintptr_t(0x3F));
		}
		else {
			headers = m_Memory->AllocateAtContext<JobHeader>(bytes, 0x40, Memory::Context::kAllocAppCpu);
			usedHeap = true;

			if (!headers) {
				spdlog::error("SubmitJobArray: header alloc failed ({} bytes)", bytes);
				return;
			}
		}

		std::memset(headers, 0, bytes);

		for (uint64_t i = 0; i < count; ++i) {
			MakeJobHeader(&headers[i], entry, workItems ? workItems[i] : nullptr);
			headers[i].set_flags(flags);
		}

		RegisterJobArray(headers, count, pCounter,
			source_func, source_line, source_file, prio, workerAffinityMask);

		if (pCounter && wait) {
			WaitForCounterAndFree(pCounter, 0);
		}

		if (usedHeap) {
			m_Memory->Free(headers, source_func, source_line, source_file);
		}
	}

	void NdJob::SubmitJobArray(void* entry, void* workData, uint64_t count,
		Priority prio, HeapArena_Args, CounterHandle** pCounter, JobFlag flags, WorkerMask workerAffinityMask, bool wait) {
		if (count == 0) return;
		std::unique_ptr<void* []> items(new void* [count]);
		for (uint64_t i = 0; i < count; ++i) items[i] = workData;
		NdJob::SubmitJobArray(entry, items.get(), count, prio, source_func, source_line, source_file, pCounter, flags, workerAffinityMask, wait);
	}


	void NdJob::RunJobAndWait(void* pEntry, void* pWorkData, HeapArena_Args, JobFlag pFlags) {
		always_assert(NdJob_RunJobAndWait == nullptr, "Function pointer was not set!");
		const auto flags_u64 = static_cast<uint64_t>(pFlags);
		NdJob_RunJobAndWait(pEntry, pWorkData, flags_u64, source_file, source_line, source_func);
	}

	void NdJob::AllocateCounter(CounterHandle** pCounter, HeapArena_Args, uint64_t pCountJobArray) {
		always_assert(NdJob_AllocateCounter == nullptr, "Function pointer was not set!");
		NdJob_AllocateCounter(pCounter, source_file, source_line, source_func, pCountJobArray, 0);
	}

	void NdJob::WaitForCounter(CounterHandle** pCounter, uint64_t pCountJobArray) {
		always_assert(NdJob_WaitForCounter == nullptr, "Function pointer was not set!");
		NdJob_WaitForCounter(pCounter, pCountJobArray, 0);
	}

	void NdJob::WaitForCounterAndFree(CounterHandle** pCounter, uint64_t pCountJobArray) {
		always_assert(NdJob_WaitForCounterAndFree == nullptr, "Function pointer was not set!");
		NdJob_WaitForCounterAndFree(pCounter, pCountJobArray, 0);
	}

	void NdJob::FreeCounter(CounterHandle** pCounter) {
		always_assert(NdJob_FreeCounter == nullptr, "Function pointer was not set!");
	#if defined(T1X)
		NdJob_FreeCounter(pCounter, 0);
	#else
		NdJob_FreeCounter(pCounter);
	#endif
	}

	
	void NdJob::JobYield() {
		always_assert(NdJob_Yield == nullptr, "Function pointer was not set!");
		NdJob_Yield();
	}

#if defined(_MSC_VER) && defined(_M_X64)
	inline const JlsBlock* NdJob::GetJobTls() {
		const auto tlsRecList = __readgsqword(0x20);
		if (!tlsRecList)
			return nullptr;

		const auto slotPtr = *reinterpret_cast<void**>(tlsRecList);
		return static_cast<const JlsBlock*>(slotPtr);
	}
#endif

	DMENU::ItemSubmenu* NdJob::CreateJobSystemMenu(NdDevMenu* pdmenu, DMENU::Menu* pMenu) {
		auto NdJobSystem = Instance<NdJob>();
		if (NdJobSystem) {
			uint64_t NdJobSystemAddr = reinterpret_cast<uint64_t>(static_cast<void*>(NdJobSystem));
			DMENU::Menu* NdJobSystemMenu = pdmenu->Create_DMENU_Menu(NdJobSystem->GetName().data(), HeapArena_Source);
			if (NdJobSystemMenu) {
			#if SDK_DEBUG
				pdmenu->Create_DMENU_ItemFunction("NdJobWorkerThread Status", NdJobSystemMenu, 
					+[](DMENU::ItemFunction& pFunction, DMENU::Message pMessage)->bool {
					if (pMessage == DMENU::Message::OnExecute) {
						auto NdJobSystem = reinterpret_cast<NdJob*>(pFunction.Data());
						NdJobSystem->s_JobSystem->Get()->m_PrintJobSysDataStats = true;

						for (auto& e : *NdJobSystem->GetJobTls()) {
							const auto ctx = e.key();
							const auto payload = e.value();
							spdlog::info("JLS ctx=0x{:016x} payload=0x{:016x}",
								static_cast<uint64_t>(ctx), payload);
						}

						spdlog::info("Test function executed in JobSystem menu!");
					}
					return true;
				}, NdJobSystemAddr, false, HeapArena_Source);

				struct Ctx {
					uint32_t id;
					uint64_t begin;
					uint64_t end;
					uint64_t durationTicks;
					uint64_t* out;
				};

				struct HeavyBatchState {
					bool active{ false };
					uint32_t jobs{ 0 };
					CounterHandle* counter{};
					Ctx* ctx{ nullptr };
					void** work{ nullptr };
					uint64_t* partial{ nullptr };
					uint64_t totalIters{ 0 };
				};
				static HeavyBatchState s{};

				static bool wait_job = false;
				static bool set_counter = true;

				pdmenu->Create_DMENU_ItemBool("wait for completion", NdJobSystemMenu, &wait_job, 0x0, HeapArena_Source);
				pdmenu->Create_DMENU_ItemBool("set counter", NdJobSystemMenu, &set_counter, 0x0, HeapArena_Source);


				pdmenu->Create_DMENU_ItemFunction("Heavy batch (15s/jobs): dispatch", NdJobSystemMenu,
					+[](DMENU::ItemFunction& f, DMENU::Message m)->bool {
						if (m == DMENU::Message::OnExecute) {

							auto heavyEntry = +[](uint64_t arg) {
								auto* c = reinterpret_cast<Ctx*>(arg);

								LARGE_INTEGER freq{}, start{}, now{};
								QueryPerformanceFrequency(&freq);
								QueryPerformanceCounter(&start);

								const uint64_t threeSec = static_cast<uint64_t>(freq.QuadPart) * 3ull;
								const uint64_t stopTick = static_cast<uint64_t>(start.QuadPart) + c->durationTicks;
								uint64_t nextLog = static_cast<uint64_t>(start.QuadPart) + threeSec;

								uint64_t acc = 0xcbf29ce484222325ull;
								uint64_t i = c->begin;

								spdlog::info("[Job #{:02}] start", c->id);

								if (c->id == 0x0) {
									return;
								}

								for (;;) {

									// Do a chunk of CPU work
									for (int inner = 0; inner < (1 << 18); ++inner, ++i) {
										acc ^= i;
										acc *= 0x100000001b3ull;
									}

									// Cooperatively yield to the scheduler
									if (auto* sys = Instance<NdJob>()) sys->JobYield();

									QueryPerformanceCounter(&now);
									const uint64_t nowTick = static_cast<uint64_t>(now.QuadPart);

									// Heartbeat every ~3 seconds
									if (nowTick >= nextLog) {
										const double elapsed = double(nowTick - static_cast<uint64_t>(start.QuadPart)) / double(freq.QuadPart);
										spdlog::info("[Job #{:02}] heartbeat ~{:.1f}s", c->id, elapsed);
										do { nextLog += threeSec; } while (nowTick >= nextLog);
									}

									// Done after ~durationTicks
									if (nowTick >= stopTick) break;
								}

								::QueryPerformanceCounter(&now);
								const double total = double(static_cast<uint64_t>(now.QuadPart) - static_cast<uint64_t>(start.QuadPart)) / double(freq.QuadPart);
								spdlog::info("[Job #{:02}] finished ~{:.2f}s", c->id, total);

								*c->out = acc;
								};

							auto* js = reinterpret_cast<NdJob*>(f.Data());
							if (s.active) {
								spdlog::warn("Heavy batch already active; poll/collect first.");
								return true;
							}

							constexpr uint32_t kJobs = 8;
							const uint64_t kTotalIters = 50'000'000ull;
							const uint64_t chunk = (kTotalIters + kJobs - 1) / kJobs;

							// duration per job: ~15 seconds
							LARGE_INTEGER freq{};
							::QueryPerformanceFrequency(&freq);
							const uint64_t durationTicks = static_cast<uint64_t>(freq.QuadPart) * 15ull;

							// Allocate persistent buffers with game allocator
							s.ctx = js->m_Memory->AllocateAtContext<Ctx>(sizeof(Ctx) * kJobs, 0x10, Memory::Context::kAllocAppCpu);
							s.work = js->m_Memory->AllocateAtContext<void*>(sizeof(void*) * kJobs, 0x10, Memory::Context::kAllocAppCpu);
							s.partial = js->m_Memory->AllocateAtContext<uint64_t>(sizeof(uint64_t) * kJobs, 0x10, Memory::Context::kAllocAppCpu);
							if (!s.ctx || !s.work || !s.partial) {
								spdlog::error("Heavy batch alloc failed; ctx={}, work={}, partial={}", (void*)s.ctx, (void*)s.work, (void*)s.partial);
								if (s.ctx)     js->m_Memory->Free(s.ctx, __func__, __LINE__, __FILE__);
								if (s.work)    js->m_Memory->Free(s.work, __func__, __LINE__, __FILE__);
								if (s.partial) js->m_Memory->Free(s.partial, __func__, __LINE__, __FILE__);
								s = HeavyBatchState{};
								return false;
							}

							for (uint32_t i = 0; i < kJobs; ++i) s.partial[i] = 0;

							for (uint32_t i = 0; i < kJobs; ++i) {
								const uint64_t begin = i * chunk;
								const uint64_t end = std::min<uint64_t>(kTotalIters, begin + chunk);
								s.ctx[i] = Ctx{ i, begin, end, durationTicks, &s.partial[i] };
								s.work[i] = &s.ctx[i];
							}

							s.counter = nullptr;
							js->SubmitJobArray(
								reinterpret_cast<void*>(heavyEntry),
								s.work, kJobs,
								NdJob::Priority::KLow,
								HeapArena_Source,
								set_counter ? &s.counter : nullptr,
								NdJob::JobFlag::None,
								-1,
								wait_job);

							s.active = true;
							s.jobs = kJobs;
							s.totalIters = kTotalIters;

							spdlog::info("Heavy batch dispatched: jobs={}, target ~15s/job (no wait)", s.jobs);
						}
						return true;
					}, NdJobSystemAddr, false, HeapArena_Source);


				pdmenu->Create_DMENU_ItemFunction("Heavy batch: poll/collect", NdJobSystemMenu,
					+[](DMENU::ItemFunction& f, DMENU::Message m)->bool {
						if (m == DMENU::Message::OnExecute) {
							auto* js = reinterpret_cast<NdJob*>(f.Data());


							if (!s.active) {
								spdlog::info("No active heavy batch to collect.");
								return false;
							}

							if (s.counter) {
								const uint32_t remaining = s.counter->GetCountJobArrays();
								if (remaining != 0) {
									spdlog::info("Heavy batch still running... remaining arrays={}", remaining);
									return false;
								}
							}
							else {
								spdlog::warn("No counter set for heavy batch, cannot poll/collect.");
							}

							uint64_t reduced = 0;
							for (uint32_t i = 0; i < s.jobs; ++i) reduced ^= s.partial[i];

							spdlog::info("Heavy batch finished: jobs={}, reduced=0x{:016x}", s.jobs, reduced);

							if (s.ctx)     js->m_Memory->Free(s.ctx, __func__, __LINE__, __FILE__);
							if (s.work)    js->m_Memory->Free(s.work, __func__, __LINE__, __FILE__);
							if (s.partial) js->m_Memory->Free(s.partial, __func__, __LINE__, __FILE__);

							if (s.counter) {
								js->FreeCounter(&s.counter);
								spdlog::warn("Heavy batch counter freed.");
							}

							s = HeavyBatchState{};
						}
						return true;
					}, NdJobSystemAddr, false, HeapArena_Source);


			#endif
				return pdmenu->Create_DMENU_ItemSubmenu(NdJobSystemMenu->Name(),
					pMenu, NdJobSystemMenu, NULL, NULL, nullptr, HeapArena_Source);
			}
		}
		return nullptr;
	}

	int32_t* NdJob::NdJobInitialize(int32_t* Err, NdJob::InitParams* pParams) {
		auto pNdJob = Instance<NdJob>();
		int32_t* ret = pNdJob->m_JobSysDataInitHook.thiscall<int32_t*>(Err, pParams);

		const int32_t code = ret ? *ret : 0;

		if (code <= 0) {
	#if SDK_DEBUG
			static std::once_flag started;
			std::call_once(started, [pNdJob] {

				struct WrapperCtx {
					NdJob* js{};
					std::atomic<bool> stop{ false };
					void* update_entry{};
					void* update_arg{}; 
				};

				auto myUpdate = +[](uint64_t work) {
					(void)work;

					static uint64_t s_count = 0;
					if ((++s_count & 0x3FFull) == 0) {
						spdlog::debug("[MySdkUpdate] tick={}", s_count);
					}

					};

				void* myArg = nullptr;

				auto* ctx = pNdJob->m_Memory->AllocateAtContext<WrapperCtx>(
					sizeof(WrapperCtx), 0x10, Memory::Context::kAllocAppCpu);

				if (!ctx) {
					spdlog::error("[{}] MySdkLoopFiber: ctx alloc failed", pNdJob->GetName());
					return;
				}

				std::memset(ctx, 0, sizeof(WrapperCtx));

				ctx->js = pNdJob;
				ctx->update_entry = myUpdate;
				ctx->update_arg = myArg;

				auto spawner = +[](uint64_t arg) {
					auto* c = reinterpret_cast<WrapperCtx*>(arg);
					spdlog::info("[MySdkFrameSpawner] started");

					while (!c->stop.load(std::memory_order_relaxed)) {
				
						c->js->RunJobAndWait(c->update_entry, c->update_arg,
							HeapArena_Source,
							JobHeader::GameLoopUpdate_RunFlags);

						Sleep(16); 
					}

					spdlog::info("[MySdkFrameSpawner] stopping");
					};

				pNdJob->SubmitJobArray(
					reinterpret_cast<void*>(spawner),
					ctx,
					1,
					NdJob::Priority::KLow,
					HeapArena_Source,
					/*pCounter=*/nullptr,
					NdJob::JobFlag::FrameSpawner,
					1,
					/*wait=*/false
				);

				spdlog::info("[{}] MySdkFrameSpawner submitted.", pNdJob->GetName());

				});
	#endif
		} else {
			spdlog::error("[{}] Init FAILED (Err={})", pNdJob->GetName(), code);
		}

		return ret;
	}

	void NdJob::DisplayJobSystemData() {
		always_assert(NdJob_DisplayJobSystemData == nullptr, "Function pointer was not set!");
		if (s_JobSystem->PrintJobSysDataStats()) {
			NdJob_DisplayJobSystemData();
		}
	}

	size_t JobSysData::InitParams::GetMemoryBufferSize() const {
		return this->Get()->m_memoryBufferSize;
	}

	size_t JobSysData::InitParams::GetDebugMemoryBufferSize() const {
		return this->Get()->m_DebugMemoryBufferSize;
	}

	uint64_t JobSysData::InitParams::GetNumCounters() const {
		return this->Get()->m_numCounters;
	}

	uint64_t JobSysData::InitParams::GetNumJobArrays() const {
		return this->Get()->m_numJobArrays;
	}

	uint64_t JobSysData::InitParams::GetNumWorkerThreads() const {
		return this->Get()->m_numWorkerThreads;
	}

	uint64_t JobSysData::InitParams::GetMaxSmallJobFibers() const {
		return this->Get()->m_maxSmallJobFibers;
	}

	uint64_t JobSysData::InitParams::GetMaxLargeJobFibers() const {
		return this->Get()->m_maxLargeJobFibers;
	}

	uint64_t JobSysData::InitParams::GetSmallJobFiberStackSpace() const {
		return this->Get()->m_smallJobFiberStackSpace;
	}

	uint64_t JobSysData::InitParams::GetLargeJobFiberStackSpace() const {
		return this->Get()->m_largeJobFiberStackSpace;
	}

	void JobSysData::InitParams::SetMemoryBufferSize(size_t size) {
		this->Get()->m_memoryBufferSize = size;
	}

	void JobSysData::InitParams::SetDebugMemoryBufferSize(size_t size) {
		this->Get()->m_DebugMemoryBufferSize = size;
	}

	void JobSysData::InitParams::SetNumCounters(uint64_t count) {
		this->Get()->m_numCounters = count;
	}

	void JobSysData::InitParams::SetNumJobArrays(uint64_t count) {
		this->Get()->m_numJobArrays = count;
	}

	void JobSysData::InitParams::SetNumWorkerThreads(uint64_t count) {
		this->Get()->m_numWorkerThreads = count;
	}

	void JobSysData::InitParams::SetMaxSmallJobFibers(uint64_t count) {
		this->Get()->m_maxSmallJobFibers = count;
	}

	void JobSysData::InitParams::SetMaxLargeJobFibers(uint64_t count) {
		this->Get()->m_maxLargeJobFibers = count;
	}

	std::string CounterHandle::GetFilePath() const {
		return this->Get()->m_file;
	}

	std::string CounterHandle::GetFunctionName() const {
		return this->Get()->m_function;
	}

	uint32_t CounterHandle::GetLine() const {
		return this->Get()->m_line;
	}

	uint64_t CounterHandle::GetTimestampQPC() const {
		return this->Get()->m_timestampQPC;
	}

	uint32_t CounterHandle::GetCountJobArrays() const {
		return this->Get()->m_CountJobArrays;
	}

	CounterHandle::CounterWakePolicy CounterHandle::GetWakePolicy() const {
		return this->Get()->m_wakeFlags;
	}

	bool JobSystem::PrintJobSysDataStats() const {
		return this->Get()->m_PrintJobSysDataStats;
	}

}