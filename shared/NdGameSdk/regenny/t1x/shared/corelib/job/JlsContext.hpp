#pragma once
#include <NdGameSdk/sdkregenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::corelib::job {
#pragma pack(push, 1)
enum JlsContext : uint32_t {
    jobId = 0,
    workerThreadIndex = 1,
    renderFrameParams = 2,
    CurrentAllocator = 3,
    DontAssertOnAllocFail = 4,
    ScriptStackFrame = 6,
    ScriptManagerGlobals = 7,
    ScriptCFuncContext = 8,
    ScriptDebug = 10,
    ContextProcess = 12,
    ContextPlayer = 14,
    NavMeshGlobalLock = 23,
};
#pragma pack(pop)
}
