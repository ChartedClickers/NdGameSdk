#pragma once

#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/components/SdkComponent.hpp"

#include "NdGameSdk/shared/src/common/common-game-init.hpp"
#include "NdGameSdk/shared/src/ndlib/render/dev/debugdraw-common.hpp"

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/ndlib/profiling/ProfileCtrl.hpp>
#elif defined (T1X)
#include <NdGameSdk/regenny/t1x/shared/ndlib/profiling/ProfileCtrl.hpp>
#endif

#include ".\profile-mgr.hpp"
#include ".\dmenu-profile.hpp"

using namespace NdGameSdk::ndlib::render::dev;

namespace NdGameSdk::ndlib::profiling {
#if defined(T2R)

	/* Extern classes */
	class ProfileCtrl;

	class NdGameSdk_API ProfileController : public ISdkComponent {
	public:
		ProfileController();
		SDK_DEPENDENCIES(DebugDrawCommon);
	private:
		void Initialize() override;
		void Awake() override;

		/*Extern Functs*/
		// void __cdecl ProfileCtrl::Initialize(void);
		void InternalInitialize();

		ProfileManager* m_ProfileMgr;

		MEMBER_FUNCTION_PTR(void, ProfileCtrl_Initialize, ProfileCtrl* pProfileCtrl);

		friend class NdGameSdk::common::CommonGame;
	};

	class ProfileCtrl : public ISdkRegenny<regenny::shared::ndlib::profiling::ProfileCtrl> {};

#endif
}