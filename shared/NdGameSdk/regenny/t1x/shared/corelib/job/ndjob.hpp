#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "WorkerThreadDesc.hpp"
#include "..\system\platform\ndsys.hpp"
namespace regenny::shared::corelib::job {
#pragma pack(push, 1)
class ndjob {
public:
    enum Priority : uint64_t {
    };

    struct InitParams {
        void* m_pMemoryBuffer; // 0x0
        uint64_t m_memoryBufferSize; // 0x8
        void* m_pDebugMemoryBuffer; // 0x10
        uint64_t m_DebugMemoryBufferSize; // 0x18
        uint64_t m_numCounters; // 0x20
        uint64_t m_numJobArrays; // 0x28
        uint64_t m_numWorkerThreads; // 0x30
        void* m_field38; // 0x38
        uint16_t m_flags; // 0x40
        private: char pad_42[0x6]; public:
        uint64_t m_field48; // 0x48
        uint64_t m_maxSmallJobFibers; // 0x50
        uint64_t m_maxLargeJobFibers; // 0x58
        uint64_t m_smallJobFiberStackSpace; // 0x60
        uint64_t m_largeJobFiberStackSpace; // 0x68
        bool m_field70; // 0x70
        private: char pad_71[0x7]; public:
    }; // Size: 0x78

    struct CounterHandle {
        // Metadata: utf8*
        char* m_file; // 0x0
        uint32_t m_line; // 0x8
        // Metadata: utf8*
        char* m_function; // 0xc
        uint64_t m_timestampQPC; // 0x14
        void* m_waitListHead; // 0x1c
        uint64_t m_field28; // 0x24
        uint64_t m_CountJobArrays; // 0x2c
        bool m_field38; // 0x34
        private: char pad_35[0xb]; public:
    }; // Size: 0x40

    struct JobHeader {
        void* m_entry; // 0x0
        void* m_WorkData; // 0x8
        regenny::shared::corelib::job::ndjob::CounterHandle* m_Counter; // 0x10
        regenny::shared::corelib::job::ndjob::CounterHandle* m_queuePrev; // 0x18
        regenny::shared::corelib::job::ndjob::CounterHandle* m_waitNext; // 0x20
        private: char pad_28[0x8]; public:
        void* m_tlsBlock; // 0x30
        uint32_t m_stateBits; // 0x38
        uint64_t m_flags; // 0x3c
        private: char pad_44[0xbc]; public:
    }; // Size: 0x100

    struct JobArrayHeader {
        uint32_t m_completedCount; // 0x0
        uint32_t m_writeIndex; // 0x4
        uint32_t m_issuedCount; // 0x8
        uint32_t m_jobCapacity; // 0xc
        regenny::shared::corelib::job::ndjob::JobHeader* m_JobStorage; // 0x10
        regenny::shared::corelib::job::ndjob::CounterHandle* m_JobCounter; // 0x18
        uint64_t m_field20; // 0x20
        regenny::shared::corelib::job::ndjob::Priority m_priority; // 0x28
        void* m_WorkData; // 0x30
        void* m_heapBlock; // 0x38
        uint8_t m_state; // 0x40
        private: char pad_41[0x3]; public:
        uint64_t m_field44; // 0x44
        uint64_t m_QueryPerformance; // 0x4c
        uint64_t m_tlsCookie; // 0x54
        private: char pad_5c[0xa4]; public:
    }; // Size: 0x100

    struct SysData {
        bool m_Initialized; // 0x0
        char m_field1[191]; // 0x1
    }; // Size: 0xc0

    struct CounterData : public SysData {
        private: char pad_c0[0xf8]; public:
        uint64_t m_fieldf8; // 0x1b8
        regenny::shared::corelib::job::ndjob::CounterHandle* m_Counters; // 0x1c0
        uint32_t m_maxSlots; // 0x1c8
        uint32_t m_nextFree; // 0x1cc
        uint32_t m_initialized; // 0x1d0
        private: char pad_1d4[0x2c]; public:
        void* m_heapBlock; // 0x200
    }; // Size: 0x208

    struct JobArrayData : public SysData {
        private: char pad_c0[0x80]; public:
        regenny::shared::corelib::job::ndjob::JobArrayHeader* m_JobArrays; // 0x140
        uint32_t m_maxHeaders; // 0x148
        uint32_t m_topIndex; // 0x14c
        uint32_t m_initialized; // 0x150
        private: char pad_154[0x1c]; public:
        void* m_heapBlock; // 0x170
        private: char pad_178[0x8]; public:
    }; // Size: 0x180

    struct FiberData : public SysData {
        regenny::shared::corelib::system::platform::ndsys::FiberContext* m_FiberCtx; // 0xc0
        regenny::shared::corelib::system::platform::ndsys::Fiber* m_smallFiberPool; // 0xc8
        regenny::shared::corelib::system::platform::ndsys::Fiber* m_largeFiberPool; // 0xd0
        private: char pad_d8[0x28]; public:
    }; // Size: 0x100

    struct WaitData : public SysData {
        private: char pad_c0[0x8]; public:
        void* m_field8; // 0xc8
        uint32_t m_field10; // 0xd0
        uint32_t m_flags; // 0xd4
        bool m_Initialized0; // 0xd8
        private: char pad_d9[0x7]; public:
        regenny::shared::corelib::job::ndjob::JobArrayHeader** m_JobStorage; // 0xe0
        regenny::shared::corelib::job::ndjob::JobArrayHeader* m_WaitingJobs; // 0xe8
        regenny::shared::corelib::job::ndjob::JobArrayHeader* m_field30; // 0xf0
        uint64_t m_numWaitingJobs; // 0xf8
    }; // Size: 0x100

    struct WakeUpData : public SysData {
        char m_field0[131588]; // 0xc0
        char m_field20204[4]; // 0x202c4
        char m_field20208[4]; // 0x202c8
        char m_field2020c[4]; // 0x202cc
        char m_field20210[12]; // 0x202d0
        char m_field2021c[4]; // 0x202dc
        char m_field20220[4]; // 0x202e0
        char m_field20224[4]; // 0x202e4
        char m_field20228[24]; // 0x202e8
        char m_field20240[64]; // 0x20300
    }; // Size: 0x20340

    struct SchedData : public SysData {
        regenny::shared::corelib::job::ndjob::JobHeader* m_JobsSheduled; // 0xc0
        private: char pad_c8[0x38]; public:
    }; // Size: 0x100

    struct JobSysData {
        regenny::shared::corelib::job::ndjob::InitParams m_initParams; // 0x0
        bool m_IsQuit; // 0x78
        private: char pad_79[0x7]; public:
        uint32_t m_readyWorkerCount; // 0x80
        private: char pad_84[0xc]; public:
        uint64_t m_field90; // 0x90
        uint64_t m_field98; // 0x98
        uint64_t m_fielda0; // 0xa0
        uint64_t m_fielda8; // 0xa8
        uint64_t m_fieldb0; // 0xb0
        private: char pad_b8[0x28]; public:
        regenny::shared::corelib::system::platform::ndsys::Mutex m_PowerSaveLocks[24]; // 0xe0
        regenny::shared::corelib::system::platform::ndsys::ConditionVariable m_cvFreeJob[24]; // 0x6e0
        regenny::shared::corelib::system::platform::ndsys::Thread m_workerThreads[24]; // 0x9e0
        uint64_t m_numWorkerThreads; // 0xb60
        void* m_hWorkerReadyEvent; // 0xb68
        uint64_t m_workerMaskLo; // 0xb70
        uint64_t m_workerMaskHi; // 0xb78
        private: char pad_b80[0x80]; public:
        regenny::shared::corelib::job::WorkerThreadDesc m_workerInfo[24]; // 0xc00
        private: char pad_3c00[0x18c0]; public:
        regenny::shared::corelib::job::ndjob::SysData m_SysStatsData; // 0x54c0
        regenny::shared::corelib::system::platform::ndsys::Mutex m_StatsDataLock; // 0x5580
        regenny::shared::corelib::job::ndjob::CounterData m_CounterData; // 0x55c0
        private: char pad_57c8[0x38]; public:
        regenny::shared::corelib::system::platform::ndsys::Mutex m_CounterDataLock; // 0x5800
        regenny::shared::corelib::job::ndjob::JobArrayData m_JobArrayData; // 0x5840
        private: char pad_59c0[0xc0]; public:
        regenny::shared::corelib::system::platform::ndsys::Mutex m_JobArrayDataLock; // 0x5a80
        regenny::shared::corelib::job::ndjob::FiberData m_FiberData; // 0x5ac0
        private: char pad_5bc0[0xc0]; public:
        regenny::shared::corelib::system::platform::ndsys::Mutex m_FiberDataLock; // 0x5c80
        regenny::shared::corelib::job::ndjob::WaitData m_WaitData; // 0x5cc0
        private: char pad_5dc0[0x40]; public:
        regenny::shared::corelib::system::platform::ndsys::Mutex m_WaitDataLock; // 0x5e00
        regenny::shared::corelib::job::ndjob::WakeUpData m_WakeUpData; // 0x5e40
        regenny::shared::corelib::system::platform::ndsys::Mutex m_WakeUpDataLock; // 0x26180
        regenny::shared::corelib::job::ndjob::SchedData m_SchedData; // 0x261c0
        private: char pad_262c0[0xc0]; public:
        regenny::shared::corelib::system::platform::ndsys::Mutex m_SchedDataLock[9]; // 0x26380
        private: char pad_265c0[0x740]; public:
    }; // Size: 0x26d00

}; // Size: 0x0
#pragma pack(pop)
}
