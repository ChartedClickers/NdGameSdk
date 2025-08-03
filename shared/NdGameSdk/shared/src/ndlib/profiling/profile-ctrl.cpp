#include "profile-ctrl.hpp"
#include "./NdGameSdk/shared/sharedpatterns.hpp"

namespace NdGameSdk::ndlib::profiling {
#if defined(T2R)
	ProfileController::ProfileController() : ISdkComponent(TOSTRING(ProfileController)) {}

	void ProfileController::Awake() {
		m_ProfileMgr = AddSubComponent<ProfileManager>();
	}

	void ProfileController::Initialize() {
		static std::once_flag Initialized;
		std::call_once(Initialized, [this] {
			spdlog::info("Initializing {} patterns...", GetName());

			Patterns::SdkPattern findpattern{};
			auto module = Utility::memory::get_executable();

			findpattern = Patterns::ProfileCtrl_Initialize;
			ProfileCtrl_Initialize = (ProfileCtrl_Initialize_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::ProfileCtrl_Initialize), findpattern.offset);

			findpattern = Patterns::ProfileCtrl_InitProfileMenu;
			ProfileCtrl_InitProfileMenu = (ProfileCtrl_InitProfileMenu_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::ProfileCtrl_InitProfileMenu), findpattern.offset);

			if (!ProfileCtrl_Initialize ||
				!ProfileCtrl_InitProfileMenu) {
				throw SdkComponentEx{ std::format("Failed to find {}:: game functions!", GetName()), SdkComponentEx::ErrorCode::PatternFailed };
			}

			InitSubComponents();

		});
	}

	void ProfileController::InternalInitialize() {
		always_assert(ProfileCtrl_Initialize == nullptr, "Function pointer was not set!");
		ProfileCtrl_Initialize();
	}

#endif
}
