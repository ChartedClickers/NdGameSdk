#include "profile-mgr.hpp"
#include "./NdGameSdk/shared/sharedpatterns.hpp"

namespace NdGameSdk::ndlib::profiling {
#if defined(T2R)
	
	ProfileManager::ProfileManager() : ISdkSubComponent(TOSTRING(ProfileManager)) {}

	void ProfileManager::Init() {

		Patterns::SdkPattern findpattern{};
		auto module = Utility::memory::get_executable();

		findpattern = Patterns::ProfileCtrl_s_ProfileMgr;
		s_ProfileMgr = (ProfileMgr*)Utility::ReadLEA32(module,
			findpattern.pattern, wstr(Patterns::ProfileCtrl_s_ProfileMgr), findpattern.offset, 3, 3);

		if (!s_ProfileMgr) {
			throw SdkComponentEx
			{ std::format("Failed to find addresses!"),
				SdkComponentEx::ErrorCode::PatternFailed };
		}

		findpattern = Patterns::ProfileCtrl_ProfileMgr_DrawProfiler;
		ProfileCtrl_ProfileMgr_DrawProfiler = (ProfileCtrl_ProfileMgr_DrawProfiler_ptr)Utility::FindAndPrintPattern(module,
			findpattern.pattern, wstr(Patterns::ProfileCtrl_ProfileMgr_DrawProfiler), findpattern.offset);

		if (!ProfileCtrl_ProfileMgr_DrawProfiler) {
			throw SdkComponentEx{ std::format("Failed to find {}:: game functions!", GetName()), SdkComponentEx::ErrorCode::PatternFailed };
		}
	}

	void ProfileManager::DrawProfiler(uint64_t arg1, bool arg2) {
		always_assert(ProfileCtrl_ProfileMgr_DrawProfiler == nullptr, "Function pointer was not set!");
		ProfileCtrl_ProfileMgr_DrawProfiler(arg1, arg2);
	}

#endif
}
