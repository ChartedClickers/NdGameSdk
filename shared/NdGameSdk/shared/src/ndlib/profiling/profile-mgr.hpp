#pragma once

#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/components/SdkComponent.hpp"
#include "NdGameSdk/components/SdkSubComponent.hpp"

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/ndlib/profiling/ProfileMgr.hpp>
#elif defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/ndlib/profiling/ProfileMgr.hpp>
#endif

#include <Utility/helper.hpp>
#include <Utility/function_ptr.hpp>

namespace NdGameSdk::ndlib::profiling {
#if defined(T2R)

	/* Extern classes */
	class ProfileMgr;

	class ProfileManager : public ISdkSubComponent {
	public:
		explicit ProfileManager();
		void Init() override;

		/*Extern functions*/
		void DrawProfiler(uint64_t arg1, bool arg2);

	private:

		/*Extern variables*/
		ProfileMgr* s_ProfileMgr{};

		MEMBER_FUNCTION_PTR(void, ProfileCtrl_ProfileMgr_DrawProfiler, uint64_t arg1, bool arg2);
	};

	class ProfileMgr : public ISdkRegenny<regenny::shared::ndlib::profiling::ProfileMgr> {};

#endif
}
