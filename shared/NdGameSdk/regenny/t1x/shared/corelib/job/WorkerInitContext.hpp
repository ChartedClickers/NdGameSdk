#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
#include "WorkerThreadDesc.hpp"
#include "..\system\platform\ndsys.hpp"
namespace regenny::shared::corelib::job {
#pragma pack(push, 1)
struct WorkerInitContext {
    private: char pad_0[0x30]; public:
    regenny::shared::corelib::system::platform::ndsys::Thread m_Thread; // 0x30
    private: char pad_40[0x40]; public:
    regenny::shared::corelib::job::WorkerThreadDesc m_WorkerThreadDesc; // 0x80
    regenny::shared::corelib::system::platform::ndsys::Fiber* m_fiber; // 0x280
    regenny::shared::corelib::system::platform::ndsys::ThreadDesc m_ThreadDesc; // 0x288
    private: char pad_3a8[0x58]; public:
    // Metadata: utf8*
    char m_longName[32]; // 0x400
}; // Size: 0x420
#pragma pack(pop)
}
