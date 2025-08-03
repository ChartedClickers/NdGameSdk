#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::corelib::job {
#pragma pack(push, 1)
struct JobSystem {
    private: char pad_0[0x8]; public:
    bool m_EnableStackChecking; // 0x8
    bool m_field9; // 0x9
    bool m_PrintJobSysDataStats; // 0xa
    bool m_EnableValidation; // 0xb
    bool m_EnablePerfCounters; // 0xc
    private: char pad_d[0x1]; public:
    bool m_EnableDeadlockDetection; // 0xe
    private: char pad_f[0x1]; public:
}; // Size: 0x10
#pragma pack(pop)
}
