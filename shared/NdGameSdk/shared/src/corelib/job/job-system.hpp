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
#elif defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/corelib/job/ndjob.hpp>
#include <NdGameSdk/regenny/t1x/shared/corelib/job/JobHeap.hpp>
#include <NdGameSdk/regenny/t1x/shared/corelib/job/JobSystem.hpp>
#endif

using namespace NdGameSdk::corelib::memory;

namespace NdGameSdk::corelib::job {

	/* Extern classes */
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

	class NdJob : public ISdkComponent {
	public:
		using InitParams = JobSysData::InitParams;
		using Priority = ::regenny::shared::corelib::job::ndjob::Priority;
		SDK_DEPENDENCIES(Memory);

		NdJob();

		bool IsWorkerThread();
		bool IsGameFrameJob();

		void RunJobAndWait(void* pEntry, void* pWorkData, HeapArena_Args, int64_t pFlags = 0);

	private:
		void Initialize() override;
		void Awake() override;

		void DisplayJobSystemData();

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
		MEMBER_FUNCTION_PTR(void, NdJob_WaitForCounter, CounterHandle* pCounter, uint64_t pCountJobArray, uint32_t arg3);
		MEMBER_FUNCTION_PTR(void*, NdJob_TryGetTlsBlock);
		MEMBER_FUNCTION_PTR(void, NdJob_SetJobLocalStorage, uint64_t arg1, uint64_t pSlotIndexes);
		MEMBER_FUNCTION_PTR(void, NdJob_RunJobAndWait, void* pEntry, void* pWorkData, int64_t pFlags, char const* pFile, uint32_t pLine, char const* pFunc);
		MEMBER_FUNCTION_PTR(void, NdJob_RegisterJobArray, JobHeader* pJobHeaders, int64_t pCountJobArrays, CounterHandle* pCounter,
			char const* pFile, uint32_t pLine, char const* pFunc, uint64_t arg7, uint64_t arg8, uint64_t arg9);
		MEMBER_FUNCTION_PTR(JobHeader*, NdJob_MakeJobHeader, JobHeader* pJobHeaders, void* pEntry, void* pWorkData);
		MEMBER_FUNCTION_PTR(bool, NdJob_IsWorkerThread);
		MEMBER_FUNCTION_PTR(bool, NdJob_IsGameFrameJob);
		MEMBER_FUNCTION_PTR(Priority, NdJob_GetCurrentWorkerPriority);
		MEMBER_FUNCTION_PTR(void, NdJob_Yield);
		MEMBER_FUNCTION_PTR(uint64_t, NdJob_GetActiveJobId);

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
		uint64_t GetCountJobArrays() const;
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