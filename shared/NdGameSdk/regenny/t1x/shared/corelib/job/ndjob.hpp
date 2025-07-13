#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "..\containers\FixedSizeHeap.hpp"
#include "..\system\platform\ndsys.hpp"
namespace regenny::shared::corelib::job {
#pragma pack(push, 1)
class ndjob {
public:
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

    struct WorkerThreadDesc {
        void* m_listHead; // 0x0
        void* m_listTail; // 0x8
        void* m_next; // 0x10
        void* m_prev; // 0x18
        void* m_waitNext; // 0x20
        void* m_waitPrev; // 0x28
        void* m_tlsBlock; // 0x30
        uint32_t m_flags; // 0x38
        private: char pad_3c[0x3c]; public:
        uint64_t m_context; // 0x78
        private: char pad_80[0x38]; public:
        uint8_t m_scheduler[128]; // 0xb8
        void* m_nativeHandle; // 0x138
        uint32_t m_threadId; // 0x140
        uint32_t m_joinable; // 0x144
        void* m_threadTLS; // 0x148
        uint64_t m_waitCookie; // 0x150
        uint8_t m_shuttingDown; // 0x158
        private: char pad_159[0x7]; public:
        uint8_t m_counters[32]; // 0x160
        uint8_t m_stats[32]; // 0x180
        private: char pad_1a0[0x60]; public:
    }; // Size: 0x200

    struct WorkerInitContext {
        private: char pad_0[0x30]; public:
        regenny::shared::corelib::system::platform::ndsys::Thread m_Thread; // 0x30
        private: char pad_40[0x40]; public:
        regenny::shared::corelib::job::ndjob::WorkerThreadDesc m_WorkerThreadDesc; // 0x80
        regenny::shared::corelib::system::platform::ndsys::Fiber* m_fiber; // 0x280
        regenny::shared::corelib::system::platform::ndsys::ThreadDesc m_ThreadDesc; // 0x288
        private: char pad_3a8[0x58]; public:
        // Metadata: utf8*
        char m_longName[32]; // 0x400
    }; // Size: 0x420

    struct CounterHandle {
        // Metadata: utf8*
        char* m_file; // 0x0
        private: char pad_8[0x4]; public:
        uint32_t m_line; // 0xc
        // Metadata: utf8*
        char* m_function; // 0x10
        uint64_t m_timestampQPC; // 0x18
        void* m_waitListHead; // 0x20
        uint64_t m_field28; // 0x28
        uint64_t m_field30; // 0x30
        uint32_t m_field38; // 0x38
        private: char pad_3c[0x4]; public:
    }; // Size: 0x40

    struct JobDesc {
        void* m_entry; // 0x0
        void* m_WorkData; // 0x8
        regenny::shared::corelib::job::ndjob::JobDesc* m_queueNext; // 0x10
        regenny::shared::corelib::job::ndjob::JobDesc* m_queuePrev; // 0x18
        regenny::shared::corelib::job::ndjob::JobDesc* m_waitNext; // 0x20
        regenny::shared::corelib::job::ndjob::JobDesc* m_waitPrev; // 0x28
        void* m_tlsBlock; // 0x30
        uint32_t m_stateBits; // 0x38
        uint64_t m_debugCookie; // 0x3c
        private: char pad_44[0x3c]; public:
    }; // Size: 0x80

    struct JobArrayHeader {
        uint32_t m_completedCount; // 0x0
        uint32_t m_writeIndex; // 0x4
        uint32_t m_issuedCount; // 0x8
        uint32_t m_jobCapacity; // 0xc
        void* m_jobStorage; // 0x10
        regenny::shared::corelib::job::ndjob::JobDesc* m_jobArray; // 0x18
        regenny::shared::corelib::job::ndjob::CounterHandle* m_counter; // 0x20
        uint32_t m_priority; // 0x28
        void* m_WorkData; // 0x2c
        void* m_jobStorageDup; // 0x34
        uint8_t m_state; // 0x3c
        uint8_t m_category; // 0x3d
        private: char pad_3e[0x6]; public:
        uint8_t m_field44; // 0x44
        private: char pad_45[0xb]; public:
        uint64_t m_field50; // 0x50
        uint8_t m_tlsCookie; // 0x58
        private: char pad_59[0x27]; public:
    }; // Size: 0x80

    struct JobSysData {
        void* m_memoryBuffer; // 0x0
        regenny::shared::corelib::containers::FixedSizeHeap m_jobHeap; // 0x8
        uint64_t m_freeJobOffset; // 0x60
        uint64_t m_freeJobInitialCap; // 0x68
        uint64_t m_freeJobInitFlag; // 0x70
        uint64_t m_field78; // 0x78
        uint32_t m_readyWorkerCount; // 0x80
        private: char pad_84[0xc]; public:
        uint64_t m_field90; // 0x90
        uint64_t m_field98; // 0x98
        uint64_t m_fielda0; // 0xa0
        uint64_t m_fielda8; // 0xa8
        uint64_t m_fieldb0; // 0xb0
        private: char pad_b8[0x28]; public:
        regenny::shared::corelib::system::platform::ndsys::Mutex m_freeJobMutex[24]; // 0xe0
        regenny::shared::corelib::system::platform::ndsys::ConditionVariable m_cvFreeJob[24]; // 0x6e0
        regenny::shared::corelib::system::platform::ndsys::Thread m_workerThreads[24]; // 0x9e0
        uint64_t m_numWorkerThreads; // 0xb60
        void* m_hWorkerReadyEvent; // 0xb68
        uint64_t m_workerMaskLo; // 0xb70
        uint64_t m_workerMaskHi; // 0xb78
        private: char pad_b80[0x80]; public:
        regenny::shared::corelib::job::ndjob::WorkerThreadDesc m_workerInfo[24]; // 0xc00
        private: char pad_3c00[0x1980]; public:
        regenny::shared::corelib::system::platform::ndsys::Mutex m_field5580; // 0x5580
        private: char pad_55c0[0x240]; public:
        regenny::shared::corelib::system::platform::ndsys::Mutex m_CounterHandleLock; // 0x5800
        private: char pad_5840[0x2c0]; public:
        regenny::shared::corelib::system::platform::ndsys::Mutex m_BeginJobArrayLock; // 0x5b00
        private: char pad_5b40[0x2c0]; public:
        void* m_WaitData; // 0x5e00
        private: char pad_5e08[0x20ef8]; public:
    }; // Size: 0x26d00

}; // Size: 0x0
#pragma pack(pop)
}
