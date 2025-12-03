#pragma once

#include "NdGameSdk/components/SdkComponent.hpp"

#include <NdGameSdk/shared/src/ndlib/engine-components.hpp>
#include <NdGameSdk/shared/src/corelib/job/job-system.hpp>
#include <NdGameSdk/shared/src/ndlib/io/file-system-win-fios2.hpp>

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/gamelib/level/GameLoading.hpp>
#elif defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/gamelib/level/GameLoading.hpp>
#endif

using namespace NdGameSdk::corelib::job;
using namespace NdGameSdk::ndlib::io;

namespace NdGameSdk::gamelib::level {

	class GameLoading final : public ISdkComponent {
	public:
		using TransitionStatus = regenny::shared::gamelib::level::GameLoading::TransitionStatus;
		using SpMpMode = regenny::shared::gamelib::level::GameLoading::SpMpMode;

		GameLoading();
		SDK_DEPENDENCIES(NdJob);

		/*Extern Functs*/
		static void SwitchToSPLevel(const char* pWorldLevel, const char* companionName, bool requireSecondaryCopyPhaseGate);
		static void MountArchiveIfNotMounted(const char* pArchiveName, FileSystemWin::ArchiveMount* pArchiveMountSlot);
		static void UnmountArchive(FileSystemWin::ArchiveMount* pArchiveMountSlot);
		static uint64_t StageStepDown(CounterHandle* pGameLoadingState);
		static void RequestLoadPackageWithDictionary(const char* pBasePackageName);
		static bool SetModeAndScheduleSwitch(SpMpMode newMode);

		static void WaitForSteadyState();
		static void WaitForSPCommonAvailability();
		static void WaitForFirstWorldAvailability();
		static void WaitForCoreAvailability();
		static void WaitForCommonAvailability();
		static void WaitForBinAvailability();

	private:
		void Awake() override;
		void Initialize() override;

		static DMENU::ItemSubmenu* CreateGameLoadingMenu(NdDevMenu* pdmenu, DMENU::Menu* pMenu);
		static CounterHandle* GetGameLoadingState();

		/*Extern Functs*/
		static void InitializeInternal();

		NdJob* m_NdJob;

		InlineHook m_GameLoadingInitializeHook{};

		/*Extern variables*/
		static uint64_t* g_NumCoreArchives;
		static SpMpMode* g_SpMpModeCurrent;
		static SpMpMode* g_SpMpModeDesired;

		static CounterHandle** g_pGameLoadingState;
		static CounterHandle** g_pStepCounter;
		static const char** g_WorldNameTarget; 
		static const char** g_WorldCompanionNameTarget;
		static const char** g_WorldNamePrevious;
		static const char** g_WorldNameCurrent;

		static FileSystemWin::ArchiveMount* g_CoreArchives; 

		TYPEDEF_FUNCTION_PTR(void, GameLoading_SwitchToSPLevel, const char* worldName, const char* companionName, bool requireSecondaryCopyPhaseGate);
		TYPEDEF_FUNCTION_PTR(void, GameLoading_MountArchiveIfNotMounted, const char* pArchiveName, FileSystemWin::ArchiveMount* pArchiveMountSlot);
		TYPEDEF_FUNCTION_PTR(void, GameLoading_UnmountArchive, FileSystemWin::ArchiveMount* pArchiveMountSlot);
		TYPEDEF_FUNCTION_PTR(uint64_t, GameLoading_StageStepDown, CounterHandle* pGameLoadingState);
		TYPEDEF_FUNCTION_PTR(void, GameLoading_RequestLoadPackageWithDictionary, const char* pBasePackageName);
#if defined(T1X)
		TYPEDEF_FUNCTION_PTR(void, GameLoading_SetModeSP);
		TYPEDEF_FUNCTION_PTR(void, GameLoading_SetModeMP);
#else
		TYPEDEF_FUNCTION_PTR(void, GameLoading_SetModeAndScheduleSwitch, SpMpMode newMode);
#endif
		friend class NdDevMenu;
	};

}

