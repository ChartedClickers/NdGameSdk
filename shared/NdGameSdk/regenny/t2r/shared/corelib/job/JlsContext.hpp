#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::corelib::job {
#pragma pack(push, 1)
enum JlsContext : uint32_t {
    jobId = 0,
    workerThreadIndex = 1,
    renderFrameParams = 2,
    CurrentAllocator = 3,
    ScriptStackFrame = 6,
    ScriptCFuncContext = 8,
    ContextProcess = 12,
    ContextPlayer = 14,
};
#pragma pack(pop)
}
