#pragma once

#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/sdklogger.hpp"
#include "NdGameSdk/components/SdkComponent.hpp"

#include <Utility/helper.hpp>
#include <regex>

namespace NdGameSdk::common {

	class CommonMainWin : public ISdkSubComponent {
	public:
		explicit CommonMainWin();
		void Init() override;
	private:
		static int32_t* SystemInit(int32_t* Err, int32_t argc, char* argv[]);
		InlineHook m_SystemInitHook{};

		/*NdGame Logs*/
		static std::string vformat(const char* fmt, va_list args);
		static void __fastcall CommonGamePrintF(const char* fmt, ...);
		static void __fastcall SsManagerPrintF(void* /*file*/, const char* fmt, ...);
		static void __fastcall SsManagerWarnPrintF(void* /*file*/, const char* fmt, ...);
		static void __fastcall SsManagerErrorPrintF(void* /*file*/, const char* fmt, ...);
		static void __fastcall ScriptManagerErrorPrintF(const char* fmt, ...);

#if defined(T2R)
		static void __fastcall MemoryDumpTaggedHeapMemoryStatsPrintF(void* /*file*/, const char* fmt, ...);
#elif defined(T1X)
		static void __fastcall CommonGameErrorPrintF(const char* fmt, ...);
#endif

		InlineHook m_CommonGamePrintFHook{};
		InlineHook m_SsManagerPrintFHook{};
		InlineHook m_SsManagerWarnPrintFHook{};
		InlineHook m_SsManagerErrorPrintFHook{};
		InlineHook m_ScriptManagerErrorPrintFHook{};

#if defined(T2R)
		InlineHook m_MemoryDumpTaggedHeapMemoryStatsPrintFHook{};
#elif defined(T1X)
		InlineHook m_CommonGameErrorPrintFHook{};
#endif

		shared_ptr<spdlog::logger> m_logger{};
	};
}