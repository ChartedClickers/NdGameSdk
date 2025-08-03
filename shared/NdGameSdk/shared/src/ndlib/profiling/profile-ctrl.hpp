#pragma once

#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/components/SdkComponent.hpp"

#include "NdGameSdk/shared/src/common/common-game-init.hpp"

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/ndlib/profiling/ProfileCtrl.hpp>
#elif defined (T1X)
#include <NdGameSdk/regenny/t1x/shared/ndlib/profiling/ProfileCtrl.hpp>
#endif

#include ".\profile-mgr.hpp"
#include ".\dmenu-profile.hpp"

namespace NdGameSdk::ndlib::profiling {
#if defined(T2R)
	class NdGameSdk_API ProfileController : public ISdkComponent {
	public:
		ProfileController();
	private:
		void Initialize() override;
		void Awake() override;

		/*Extern Functs*/
		// void __cdecl ProfileCtrl::Initialize(void);
		void InternalInitialize();

		ProfileManager* m_ProfileMgr;

		MEMBER_FUNCTION_PTR(void, ProfileCtrl_Initialize);

		friend class NdGameSdk::common::CommonGame;
	};


#endif
}