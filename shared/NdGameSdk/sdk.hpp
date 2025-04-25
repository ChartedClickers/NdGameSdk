#pragma once

#include "sdkconst.hpp"
#include "sdklogger.hpp"

#include <windows.h>
#include <filesystem>
#include <string>

namespace NdGameSdk {

	class ISdkComponent;
	class ISdkSubComponent;
	class ISdkModule;
	class SdkConfig;

	extern HMODULE g_SdkModuleHandle;
	extern bool g_SdkInitialized;

	NdGameSdk_API void InitializeSdk(const SdkConfig* cfg = nullptr);
	NdGameSdk_API void RegisterSdkModule(ISdkModule* SdkModule);
	NdGameSdk_API void UnregisterSdkModule(ISdkModule* SdkModule);
}