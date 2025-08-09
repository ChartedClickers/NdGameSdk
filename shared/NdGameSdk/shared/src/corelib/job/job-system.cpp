#include "job-system.hpp"
#include "./NdGameSdk/shared/sharedpatterns.hpp"

#include <Utility/helper.hpp>

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
				!NdJob_TryGetJlsSlotValue
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

	void NdJob::RunJobAndWait(void* pEntry, void* pWorkData, HeapArena_Args, int64_t pFlags) {
		always_assert(NdJob_RunJobAndWait == nullptr, "Function pointer was not set!");
		spdlog::debug("Running job with entry: {}, work data: {}, flags: {}, source file: {}, source line: {}, source function: {}",
			pEntry, pWorkData, pFlags, source_file, source_line, source_func);
		NdJob_RunJobAndWait(pEntry, pWorkData, pFlags, source_file, source_line, source_func);
	}

	
	void NdJob::JobYield() {
		always_assert(NdJob_Yield == nullptr, "Function pointer was not set!");
		spdlog::debug("Yielding job execution for Job ID: {}", GetActiveJobId());
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
				pdmenu->Create_DMENU_ItemFunction("Run function in the native NdJobWorkerThread", NdJobSystemMenu, 
					+[](DMENU::ItemFunction& pFunction, DMENU::Message pMessage)->bool {
					if (pMessage == DMENU::Message::OnExecute) {
						auto NdJobSystem = reinterpret_cast<NdJob*>(pFunction.Data());
						NdJobSystem->s_JobSystem->Get()->m_PrintJobSysDataStats = true;
						spdlog::info("Test function executed in JobSystem menu!");
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
		return pNdJob->m_JobSysDataInitHook.thiscall<int32_t*>(Err, pParams);
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

	uint64_t CounterHandle::GetCountJobArrays() const {
		return this->Get()->m_CountJobArrays;
	}

	bool JobSystem::PrintJobSysDataStats() const {
		return this->Get()->m_PrintJobSysDataStats;
	}

}