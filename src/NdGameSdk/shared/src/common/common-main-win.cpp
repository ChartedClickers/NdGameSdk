#include "common-main-win.hpp"
#include "common-game-init.hpp"

#include <NdGameSdk/shared/src/ndlib/render/dev/debugdraw-common.hpp>
#include "./NdGameSdk/shared/sharedpatterns.hpp"

#include <algorithm>
#include <cstring>

namespace NdGameSdk::common {

	CommonMainWin::CommonMainWin() : ISdkSubComponent(TOSTRING(CommonMainWin)) {}

	void CommonMainWin::Init() {

		static std::once_flag Initialized;
		std::call_once(Initialized, [this] {
			spdlog::info("Initializing {} patterns...", GetName());

			Patterns::SdkPattern findpattern{};
			auto module = Utility::memory::get_executable();

			findpattern = Patterns::CommonGame_CommonMainWin_SystemInit;
			auto SystemInit = (void*)Utility::FindAndPrintPattern(module
				, findpattern.pattern, wstr(Patterns::CommonGame_CommonMainWin_SystemInit), findpattern.offset);

			auto CommonGamePrintF = (void*)Utility::FindAndPrintPattern(module
				, Patterns::CommonGame_PrintF.pattern, wstr(Patterns::CommonGame_PrintF), Patterns::CommonGame_PrintF.offset);

			auto SsManagerPrintF = (void*)Utility::FindAndPrintPattern(module
				, Patterns::SsManager_PrintF.pattern, wstr(Patterns::SsManager_PrintF), Patterns::SsManager_PrintF.offset);

			auto SsManagerWarnPrintF = (void*)Utility::FindAndPrintPattern(module
				, Patterns::SsManager_WarnPrintF.pattern, wstr(Patterns::SsManager_WarnPrintF), Patterns::SsManager_WarnPrintF.offset);

			auto SsManagerErrorPrintF = (void*)Utility::FindAndPrintPattern(module
				, Patterns::SsManager_ErrorPrintF.pattern, wstr(Patterns::SsManager_ErrorPrintF), Patterns::SsManager_ErrorPrintF.offset);

			auto ScriptManagerErrorPrintF = (void*)Utility::FindAndPrintPattern(module
				, Patterns::ScriptManager_ErrorPrintF.pattern, wstr(Patterns::ScriptManager_ErrorPrintF), Patterns::ScriptManager_ErrorPrintF.offset);

#if defined(T2R)
			auto MemoryDumpTaggedHeapMemoryStatsPrintF = (void*)Utility::FindAndPrintPattern(module,
				Patterns::Memory_DumpTaggedHeapMemoryStatsPrintF.pattern, wstr(Patterns::Memory_DumpTaggedHeapMemoryStatsPrintF),
				Patterns::Memory_DumpTaggedHeapMemoryStatsPrintF.offset);

			auto DebugPrintF = (void*)Utility::FindAndPrintPattern(module,
				Patterns::DebugPrintF.pattern, wstr(Patterns::DebugPrintF),
				Patterns::DebugPrintF.offset);

            NxAppHooks* pNxAppHooks = GetParentComponent<CommonGame>()->GetSubComponent<NxAppHooks>();
            if (pNxAppHooks) {
                ISdkSubComponent::SubscribeSdkEvent<CommonGame, NxAppHooks>(
                    GetSharedComponents(),
                    &NxAppHooks::e_NxAppInitialized,
					[](NxApp* pNxApp, bool successful) {
						if (successful) {
                            CommonMainWin* pCommonMainWin = GetSharedComponents()->
                                GetComponent<CommonGame>()->GetSubComponent<CommonMainWin>();
							spdlog::info("NxApp initialized successfully, redirecting stdio streams...");
                            NxApp::NixxesLogger* pLogger = pNxApp->GetLogger();
                            if (pLogger) {
                                auto** vft = reinterpret_cast<void**>(pLogger->Get()->vftable);
								pCommonMainWin->m_NixxesLoggerWriteRawLineHook = Utility::MakeSafetyHookInline(
                                    vft[NxApp::NixxesLogger::kIdx_WriteRawLine],
                                    CommonMainWin::NixxesLoggerWriteRawLine,
                                    wstr(Patterns::CommonGame_NxAppHooks_OpenAndRedirectStdIO), 
                                    wstr(vft[NxApp::NixxesLogger::kIdx_WriteRawLine]));

                                if (!pCommonMainWin->m_NixxesLoggerWriteRawLineHook) {
									spdlog::error("Failed to create NixxesLoggerWriteRawLine hook!");
                                }

                            }

						}
					}
                );

            }


#elif defined(T1X)
			auto CommonGameErrorPrintF = (void*)Utility::FindAndPrintPattern(module
				, Patterns::CommonGame_ErrorPrintF.pattern, wstr(Patterns::CommonGame_ErrorPrintF), Patterns::CommonGame_ErrorPrintF.offset);
#endif

			if (!SystemInit) {
				throw SdkComponentEx
				{ std::format("Failed to find addresses!"),
					SdkComponentEx::ErrorCode::PatternFailed, true };
			}

			m_SystemInitHook = Utility::MakeSafetyHookInline(SystemInit, CommonMainWin::SystemInit,
				wstr(Patterns::CommonGame_CommonMainWin_SystemInit), wstr(SystemInit));

            if (Utility::sys::HasAttachedConsole()) {

                m_logger = SdkLogger::GetNdGameLogger();
                spdlog::info("{} Installing logger for NdGame: {}", GetName(), m_logger->name());

                if (CommonGamePrintF &&
                    SsManagerPrintF &&
                    SsManagerWarnPrintF &&
                    SsManagerErrorPrintF &&
                    ScriptManagerErrorPrintF
#if defined(T2R)
                    && MemoryDumpTaggedHeapMemoryStatsPrintF &&
                    DebugPrintF
#elif defined(T1X)
                    && CommonGameErrorPrintF
#endif
                    ) {

                    m_CommonGamePrintFHook = Utility::MakeSafetyHookInline(CommonGamePrintF, CommonMainWin::CommonGamePrintF,
                        wstr(Patterns::CommonGame_PrintF), wstr(CommonGamePrintF));

                    m_SsManagerPrintFHook = Utility::MakeSafetyHookInline(SsManagerPrintF, CommonMainWin::SsManagerPrintF,
                        wstr(Patterns::SsManager_PrintF), wstr(SsManagerPrintF));

                    m_SsManagerWarnPrintFHook = Utility::MakeSafetyHookInline(SsManagerWarnPrintF, CommonMainWin::SsManagerWarnPrintF,
                        wstr(Patterns::SsManager_WarnPrintF), wstr(SsManagerWarnPrintF));

                    m_SsManagerErrorPrintFHook = Utility::MakeSafetyHookInline(SsManagerErrorPrintF, CommonMainWin::SsManagerErrorPrintF,
                        wstr(Patterns::SsManager_ErrorPrintF), wstr(SsManagerErrorPrintF));

                    m_ScriptManagerErrorPrintFHook = Utility::MakeSafetyHookInline(ScriptManagerErrorPrintF, CommonMainWin::ScriptManagerErrorPrintF,
                        wstr(Patterns::ScriptManager_ErrorPrintF), wstr(ScriptManagerErrorPrintF));

#if defined(T2R)
                    m_MemoryDumpTaggedHeapMemoryStatsPrintFHook = Utility::MakeSafetyHookInline(MemoryDumpTaggedHeapMemoryStatsPrintF,
                        CommonMainWin::MemoryDumpTaggedHeapMemoryStatsPrintF,
                        wstr(Patterns::Memory_DumpTaggedHeapMemoryStatsPrintF), wstr(MemoryDumpTaggedHeapMemoryStatsPrintF));

                    m_DebugPrintFHook = Utility::MakeSafetyHookInline(DebugPrintF, CommonMainWin::DebugPrintF, wstr(Patterns::DebugPrintF), wstr(DebugPrintF));

#elif defined(T1X)
                    m_CommonGameErrorPrintFHook = Utility::MakeSafetyHookInline(CommonGameErrorPrintF, CommonMainWin::CommonGameErrorPrintF,
                        wstr(Patterns::CommonGame_ErrorPrintF), wstr(CommonGameErrorPrintF));
#endif

                }
                else {
                    spdlog::error("Failed to find all necessary patterns for NdGame logging!");
                }
            }

		});
	}

	int32_t* CommonMainWin::SystemInit(int32_t* Err, int32_t argc, char* argv[]) {
		CommonMainWin* pCommonMainWin = GetSharedComponents()->
			GetComponent<CommonGame>()->GetSubComponent<CommonMainWin>();

		DebugDrawCommon* pDebugDraw = GetSharedComponents()->GetComponent<DebugDrawCommon>();
		if (pDebugDraw) {
			auto MsgCon = pDebugDraw->GetMsgCon();
			MsgCon->SetPrintTTY(Utility::sys::HasAttachedConsole());
		}

		return pCommonMainWin->m_SystemInitHook.thiscall<int32_t*>(Err, argc, argv);
	}

    inline bool is_readable_page(DWORD protect);
    bool is_readable_range(const void* ptr, size_t bytes);
    std::string safe_cstr_copy(const char* p, size_t max_len = 1024);

    std::string CommonMainWin::vformat(const char* fmt, va_list args) {
        if (!fmt) return "";

        std::string out;
        __try {
            va_list tmp;
            va_copy(tmp, args);
            int len = std::vsnprintf(nullptr, 0, fmt, tmp);
            va_end(tmp);
            if (len < 0) return "";

            std::vector<char> buf(len + 1);
            std::vsnprintf(buf.data(), buf.size(), fmt, args);
            out.assign(buf.data(), len);
        }
        __except (GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION
            ? EXCEPTION_EXECUTE_HANDLER
            : EXCEPTION_CONTINUE_SEARCH) {
            out = "[Formatting error]";
        }

        return out;
    }

    void __fastcall CommonMainWin::CommonGamePrintF(const char* fmt, ...) {

        // ASCII box-drawing characters
        constexpr char HORIZ = '-';
        constexpr char TL = '+';
        constexpr char TR = '+';
        constexpr char BL = '+';
        constexpr char BR = '+';
        constexpr char VERT = '|';

        va_list args;
        va_start(args, fmt);
        std::string all = vformat(fmt, args);
        va_end(args);

        // split into lines
        std::vector<std::string> lines;
        for (size_t start = 0; start < all.size(); ) {
            size_t pos = all.find('\n', start);
            if (pos == std::string::npos) {
                lines.emplace_back(all.substr(start));
                break;
            }
            lines.emplace_back(all.substr(start, pos - start));
            start = pos + 1;
        }

        auto gamelogger = SdkLogger::GetNdGameLogger();

        bool in_box = false;
        size_t box_width = 0;

        // matches "-[ Title ]-----"
        std::regex header_re(R"(^-\[\s*(.+?)\s*\](-+)$)");

        for (auto& ln : lines) {

            // strip CR if present
            if (!ln.empty() && ln.back() == '\r')
                ln.pop_back();

            bool all_underscore = !ln.empty() && ln.find_first_not_of('_') == std::string::npos;
            bool all_hyphen = !ln.empty() && ln.find_first_not_of('-') == std::string::npos;

            std::smatch m;
            if (std::regex_match(ln, m, header_re)) {

                // section header like "-[ Foo ]-----"
                std::string title = m[1].str();
                box_width = ln.size();

                size_t inner = box_width - 2;
                std::string cent = " " + title + " ";
                size_t pad = (inner > cent.size()) ? (inner - cent.size()) : 0;
                size_t left = pad / 2, right = pad - left;

                // build the horizontal fill
                std::string border;
                border.reserve(inner);
                border.append(left, HORIZ);
                border += cent;
                border.append(right, HORIZ);

                gamelogger->info("{}{}{}", TL, border, TR);
                in_box = true;
            }
            else if ((all_underscore || all_hyphen) && !in_box) {
                // top of a generic box
                box_width = ln.size();
                std::string border(box_width, HORIZ);
                gamelogger->info("{}{}{}", TL, border, TR);
                in_box = true;
            }
            else if ((all_underscore || all_hyphen) && in_box) {
                // bottom of the box
                std::string border(box_width, HORIZ);
                gamelogger->info("{}{}{}", BL, border, BR);
                in_box = false;
            }
            else if (in_box) {
                // interior line (strip leading '|' if present)
                std::string content = (!ln.empty() && ln.front() == '|')
                    ? ln.substr(1)
                    : ln;
                if (content.size() < box_width)
                    content += std::string(box_width - content.size(), ' ');
                else if (content.size() > box_width)
                    content.resize(box_width);
                gamelogger->info("{}{}{}", VERT, content, VERT);
            }
            else {
                // normal, non-boxed line
                gamelogger->info("{}", ln);
            }
        }
	}

	// TODO: Add more detailed logging for SsManager and ScriptManager
    void __fastcall CommonMainWin::SsManagerPrintF(void* /*file*/, const char* fmt, ...) {
        va_list args;
        va_start(args, fmt);
        auto msg = vformat(fmt, args);
        va_end(args);

        auto logger = SdkLogger::GetNdGameLogger();
        logger->info("[SSMGR] {}", msg);
    }

    void __fastcall CommonMainWin::SsManagerWarnPrintF(void* /*file*/, const char* fmt, ...) {
        va_list args;
        va_start(args, fmt);
        auto msg = vformat(fmt, args);
        va_end(args);

        auto logger = SdkLogger::GetNdGameLogger();
		// logger->warn("[SSMGR] {}", msg); // Too noisy, temporarily disabled
    }

    void __fastcall CommonMainWin::SsManagerErrorPrintF(void* /*file*/, const char* fmt, void* argBuffer, void* /*unused*/) {
        if (!fmt) return;

        // Validate we can read two pointer slots
        const size_t slot_bytes = sizeof(const char*) * 2;
        const bool has_slots = is_readable_range(argBuffer, slot_bytes);

        const char* first_ptr  = nullptr;
        const char* second_ptr = nullptr;

        if (has_slots) {
            auto** buf = reinterpret_cast<const char**>(argBuffer);
            first_ptr  = buf[0];
            second_ptr = buf[1];
        }

        const std::string first = safe_cstr_copy(first_ptr);
        const std::string second = safe_cstr_copy(second_ptr);

        std::string result(fmt);

        size_t pos = result.find("%s");
        if (pos != std::string::npos) result.replace(pos, 2, first);
        pos = result.find("%s");
        if (pos != std::string::npos) result.replace(pos, 2, second);

        auto logger = SdkLogger::GetNdGameLogger();
        logger->error("[SSMGR] {}", result);
    }

    void CommonMainWin::ScriptManagerErrorPrintF(const char* fmt, ...) {
        va_list args;
        va_start(args, fmt);
        auto msg = vformat(fmt, args);
        va_end(args);

        auto logger = SdkLogger::GetNdGameLogger();
        logger->error("[ScriptManager] {}", msg);
    }


#if defined(T2R)

    void __fastcall CommonMainWin::DebugPrintF(const char* fmt, void* /*arg1*/, ...) {
        va_list args;
        va_start(args, fmt);
        auto msg = vformat(fmt, args);
        va_end(args);
        auto logger = SdkLogger::GetNdGameLogger();
        logger->debug("{}", msg);
    }

    void __fastcall CommonMainWin::MemoryDumpTaggedHeapMemoryStatsPrintF(void*, const char* fmt, ...) {
		va_list args;
		va_start(args, fmt);
		auto msg = vformat(fmt, args);
		va_end(args);
		auto logger = SdkLogger::GetNdGameLogger();
		logger->info("{}", msg);
    }

    void __fastcall CommonMainWin::NixxesLoggerWriteRawLine(NxApp::NixxesLogger* pNLogger, const char* str) {
        auto logger = SdkLogger::GetNdGameLogger();
        logger->info("[NxApp] {}", str);
    }

#elif defined(T1X)
	void __fastcall CommonMainWin::CommonGameErrorPrintF(const char* fmt, ...) {
		va_list args;
		va_start(args, fmt);
		auto msg = vformat(fmt, args);
		va_end(args);
		auto logger = SdkLogger::GetNdGameLogger();
		logger->error("{}", msg);
	}
#endif

    inline bool is_readable_page(DWORD protect) {
        if (protect & (PAGE_NOACCESS | PAGE_GUARD)) 
            return false;
        switch (protect & 0xFF) {
        case PAGE_READONLY:
        case PAGE_READWRITE:
        case PAGE_WRITECOPY:
        case PAGE_EXECUTE_READ:
        case PAGE_EXECUTE_READWRITE:
        case PAGE_EXECUTE_WRITECOPY:
            return true;
        default:
            return false;
        }
    }

    bool is_readable_range(const void* ptr, size_t bytes) {
        if (!ptr || bytes == 0) return false;
        auto addr = reinterpret_cast<uintptr_t>(ptr);
        auto end = addr + bytes;

        MEMORY_BASIC_INFORMATION mbi{};
        while (addr < end) {
            if (VirtualQuery(reinterpret_cast<LPCVOID>(addr), &mbi, sizeof(mbi)) == 0) return false;
            if (mbi.State != MEM_COMMIT || !is_readable_page(mbi.Protect)) return false;

            const auto region_end = reinterpret_cast<uintptr_t>(mbi.BaseAddress) + mbi.RegionSize;
            if (region_end <= addr) return false;
            addr = std::min<uintptr_t>(region_end, end);
        }
        return true;
    }

    std::string safe_cstr_copy(const char* p, size_t max_len) {
        if (!p) return std::string{ "[null]" };
        std::string out{};

        out.reserve(std::min<size_t>(max_len, 256));
        auto cur = reinterpret_cast<uintptr_t>(p);
        const auto cap_end = cur + max_len;

        while (cur < cap_end) {
            MEMORY_BASIC_INFORMATION mbi{};
            if (VirtualQuery(reinterpret_cast<LPCVOID>(cur), &mbi, sizeof(mbi)) == 0) return std::string{ "[invalid]" };
            if (mbi.State != MEM_COMMIT || !is_readable_page(mbi.Protect)) return std::string{ "[invalid]" };

            const auto region_start = reinterpret_cast<uintptr_t>(mbi.BaseAddress);
            const auto region_end = region_start + mbi.RegionSize;
            const auto bytes_left = cap_end - cur;
            const auto read_end = std::min<uintptr_t>(region_end, cur + bytes_left);
            const auto read_len = read_end - cur;

            const char* c = reinterpret_cast<const char*>(cur);
            if (const void* nul = memchr(c, '\0', read_len)) {
                const auto add = static_cast<const char*>(nul) - c;
                out.append(c, add);
                return out;
            }

            out.append(c, read_len);
            cur += read_len;
        }

        out.append("…");
        return out;
    }

}
