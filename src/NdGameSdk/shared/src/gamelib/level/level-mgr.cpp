#include "level-mgr.hpp"
#include "./NdGameSdk/shared/sharedpatterns.hpp"

#include <Utility/helper.hpp>
#include <spdlog/spdlog.h>
#include <mutex>

namespace NdGameSdk::gamelib::level {
#if defined (T2R)

	LevelMgr::LevelMgr() : ISdkComponent(TOSTRING(LevelMgr)) {}

	void LevelMgr::Awake() {
		auto SharedComponents = ISdkComponent::GetSharedComponents();
		m_EngineComponents = GetDependencyComponent<EngineComponents>(SharedComponents);
	}

	void LevelMgr::Initialize() {
		static std::once_flag Initialized;
		std::call_once(Initialized, [this] {
			spdlog::info("Initializing {} patterns...", GetName());

			Patterns::SdkPattern findpattern{};
			auto module = Utility::memory::get_executable();

			findpattern = Patterns::LevelMgr_Init;
			auto LevelMgrInit = (void*)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::LevelMgr_Init), findpattern.offset);

			findpattern = Patterns::LevelMgr_Sync;
			LevelMgr_Sync = (LevelMgr_Sync_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::LevelMgr_Sync), findpattern.offset);

			findpattern = Patterns::LevelMgr_GetLevelSafe;
			LevelMgr_GetLevelSafe = (LevelMgr_GetLevelSafe_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::LevelMgr_GetLevelSafe), findpattern.offset);

			findpattern = Patterns::LevelMgr_GetNumCriticalLoads;
			LevelMgr_GetNumCriticalLoads = (LevelMgr_GetNumCriticalLoads_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::LevelMgr_GetNumCriticalLoads), findpattern.offset);

			findpattern = Patterns::LevelMgr_AddCriticalLoadLevel;
			LevelMgr_AddCriticalLoadLevel = (LevelMgr_AddCriticalLoadLevel_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::LevelMgr_AddCriticalLoadLevel), findpattern.offset);

			findpattern = Patterns::LevelMgr_ShouldPauseForCriticalLoads;
			LevelMgr_ShouldPauseForCriticalLoads = (LevelMgr_ShouldPauseForCriticalLoads_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::LevelMgr_ShouldPauseForCriticalLoads), findpattern.offset);

			findpattern = Patterns::LevelMgr_Level_GoStatus;
			Level::LevelMgr_Level_GoStatus = (Level::LevelMgr_Level_GoStatus_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::LevelMgr_Level_GoStatus), findpattern.offset);

			findpattern = Patterns::LevelMgr_Level_GetDependentNode;
			Level::LevelMgr_Level_GetDependentNode = (Level::LevelMgr_Level_GetDependentNode_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::LevelMgr_Level_GetDependentNode), findpattern.offset);

			findpattern = Patterns::LevelMgr_Level_FreeDependentNode;
			Level::LevelMgr_Level_FreeDependentNode = (Level::LevelMgr_Level_FreeDependentNode_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::LevelMgr_Level_FreeDependentNode), findpattern.offset);

			findpattern = Patterns::LevelMgr_Level_ReloadInGameData;
			Level::LevelMgr_Level_ReloadInGameData = (Level::LevelMgr_Level_ReloadInGameData_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::LevelMgr_Level_ReloadInGameData), findpattern.offset);

			findpattern = Patterns::LevelMgr_Level_SetWantFlags;
			Level::LevelMgr_Level_SetWantFlags = (Level::LevelMgr_Level_SetWantFlags_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::LevelMgr_Level_SetWantFlags), findpattern.offset);

			findpattern = Patterns::LevelMgr_Level_AttachProcess;
			Level::LevelMgr_Level_AttachProcess = (Level::LevelMgr_Level_AttachProcess_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::LevelMgr_Level_AttachProcess), findpattern.offset);

			findpattern = Patterns::LevelMgr_Level_DetachProcess;
			Level::LevelMgr_Level_DetachProcess = (Level::LevelMgr_Level_DetachProcess_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::LevelMgr_Level_DetachProcess), findpattern.offset);

			findpattern = Patterns::LevelMgr_Level_DetachProcesses;
			Level::LevelMgr_Level_DetachProcesses = (Level::LevelMgr_Level_DetachProcesses_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::LevelMgr_Level_DetachProcesses), findpattern.offset);

			findpattern = Patterns::LevelMgr_Level_KillDependentProcesses;
			Level::LevelMgr_Level_KillDependentProcesses = (Level::LevelMgr_Level_KillDependentProcesses_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::LevelMgr_Level_KillDependentProcesses), findpattern.offset);

			if (!LevelMgrInit ||
				!LevelMgr_Sync ||
				!LevelMgr_GetLevelSafe ||
				!LevelMgr_GetNumCriticalLoads ||
				!LevelMgr_AddCriticalLoadLevel ||
				!LevelMgr_ShouldPauseForCriticalLoads ||
				!Level::LevelMgr_Level_GoStatus ||
				!Level::LevelMgr_Level_GetDependentNode ||
				!Level::LevelMgr_Level_FreeDependentNode ||
				!Level::LevelMgr_Level_ReloadInGameData ||
				!Level::LevelMgr_Level_SetWantFlags ||
				!Level::LevelMgr_Level_AttachProcess ||
				!Level::LevelMgr_Level_DetachProcess ||
				!Level::LevelMgr_Level_DetachProcesses ||
				!Level::LevelMgr_Level_KillDependentProcesses) {
				throw SdkComponentEx{ std::format("Failed to find {} patterns!", GetName()),
					SdkComponentEx::ErrorCode::PatternFailed };
			}

			m_LevelMgrInitHook = Utility::MakeSafetyHookInline(LevelMgrInit, LevelMgr::InitInternal,
				wstr(Patterns::LevelMgr_Init), wstr(LevelMgr::InitInternal));

			if (!m_LevelMgrInitHook) {
				throw SdkComponentEx{ "Failed to create hooks!", SdkComponentEx::ErrorCode::PatchFailed };
			}
		});
	}

	void __cdecl LevelMgr::InitInternal(LevelMgrInternal* pLevelMgrInternal, LevelMgr::Configuration& pConfig) {
		auto pLevelMgr = Instance<LevelMgr>();
		pLevelMgr->m_LevelMgrInitHook.thiscall<void>(pLevelMgrInternal, &pConfig);
		return;
	}

	void LevelMgr::Sync(bool runStreamingOnly) {
		always_assert(LevelMgr_Sync == nullptr, "Function pointer was not set!");
		LevelMgr_Sync(GetLevelMgrInternal(), runStreamingOnly);
	}

	Level* LevelMgr::GetLevelSafe(StringId64 levelId) {
		always_assert(LevelMgr_GetLevelSafe == nullptr, "Function pointer was not set!");
		// Using WaitLock inside
		return LevelMgr_GetLevelSafe(GetLevelMgrInternal(), levelId);
	}

	int LevelMgr::GetNumCriticalLoads() {
		always_assert(LevelMgr_GetNumCriticalLoads == nullptr, "Function pointer was not set!");
		return LevelMgr_GetNumCriticalLoads(GetLevelMgrInternal());
	}

	bool LevelMgr::IsLevelLoaded(StringId64 levelId) const {
		auto* levelMgrInternal = GetLevelMgrInternal();

		auto& table = levelMgrInternal->GetActiveLevelsTable();
		const auto* node = table.Find(
			levelId,
			[](StringId64 key) noexcept { return static_cast<uint64_t>(key); },
			[](const LevelLookupNode& entry, StringId64 key) noexcept { return entry.GetLevelId() == key; });

		if (node == nullptr) {
			return false;
		}

		auto* level = node->GetLevelPtr();
		return level != nullptr && level->IsLoaded();
	}

	bool LevelMgr::ShouldPauseForCriticalLoads() {
		always_assert(LevelMgr_ShouldPauseForCriticalLoads == nullptr, "Function pointer was not set!");
		return LevelMgr_ShouldPauseForCriticalLoads(GetLevelMgrInternal());
	}

	void LevelMgr::AddCriticalLoadLevel(StringId64 levelId) {
		always_assert(LevelMgr_AddCriticalLoadLevel == nullptr, "Function pointer was not set!");
		LevelMgr_AddCriticalLoadLevel(GetLevelMgrInternal(), levelId);
	}


	LevelMgrInternal* LevelMgr::GetLevelMgrInternal() const {
		return &m_EngineComponents->GetLevelMgr();
	}

	FixedSizeHeap* LevelMgrInternal::GetLevelPool() {
		return reinterpret_cast<FixedSizeHeap*>(&this->Get()->m_levelPool);
	}

	ListArray<LevelMgrInternal::Request>& LevelMgrInternal::GetRequests() {
		return reinterpret_cast<ListArray<Request>&>(this->Get()->m_requests);
	}

	FixedSizeHashTable<LevelMgrInternal::LevelLookupNode>& LevelMgrInternal::GetActiveLevelsTable() {
		return reinterpret_cast<FixedSizeHashTable<LevelLookupNode>&>(this->Get()->m_activeLevelMap);
	}

	FixedSizeHashTable<LevelMgrInternal::LevelLookupNode>& LevelMgrInternal::GetPendingLevelsTable() {
		return reinterpret_cast<FixedSizeHashTable<LevelLookupNode>&>(this->Get()->m_pendingLevelMap);
	}

	ListArray<Level>& LevelMgrInternal::GetLoadedLevels() {
		return reinterpret_cast<ListArray<Level>&>(this->Get()->m_loadedLevels);
	}

	ListArray<Level>& LevelMgrInternal::GetPendingLevels() {
		return reinterpret_cast<ListArray<Level>&>(this->Get()->m_pendingLevels);
	}

	ListArray<Level>& LevelMgrInternal::GetDisplayReadyLevels() {
		return reinterpret_cast<ListArray<Level>&>(this->Get()->m_displayReadyLevels);
	}

	ListArray<Level>& LevelMgrInternal::GetEntitySpawnerLevels() {
		return reinterpret_cast<ListArray<Level>&>(this->Get()->m_entitySpawnerLevels);
	}

	ListArray<StringId64>& LevelMgrInternal::GetCriticalLoadIds() {
		return reinterpret_cast<ListArray<StringId64>&>(this->Get()->m_criticalLoadIds);
	}

	BitArray<4096>& LevelMgrInternal::GetSoundBankInfoBits() {
		return reinterpret_cast<BitArray<4096>&>(this->Get()->m_aSoundBankInfoBits);
	}

	BitArray<2048>& LevelMgrInternal::GetMiniSoundBankInfoBits() {
		return reinterpret_cast<BitArray<2048>&>(this->Get()->m_aMiniSoundBankInfoBits);
	}

	BitArray<160>& LevelMgrInternal::GetBackgroundInUseBits() {
		return reinterpret_cast<BitArray<160>&>(this->Get()->m_backgroundInUseBits);
	}

	BlockMeshMgr* LevelMgrInternal::GetBlockMeshMgr() {
		return reinterpret_cast<BlockMeshMgr*>(&this->Get()->m_BlockmeshMgr);
	}

	LevelLoadObserver* LevelMgrInternal::GetLevelLoadObserver() {
		return reinterpret_cast<LevelLoadObserver*>(&this->Get()->m_levelLoadObserver);
	}

	StringId64 LevelMgrInternal::LevelLookupNode::GetLevelId() {
		return this->Get()->m_Key;
	}

	StringId64 LevelMgrInternal::LevelLookupNode::GetLevelId() const {
		return this->Get()->m_Key;
	}

	Level* LevelMgrInternal::LevelLookupNode::GetLevelPtr() {
		return reinterpret_cast<Level*>(this->Get()->m_Level);
	}

	const Level* LevelMgrInternal::LevelLookupNode::GetLevelPtr() const {
		return reinterpret_cast<const Level*>(this->Get()->m_Level);
	}

	Level* LevelMgrInternal::Request::GetLevel() {
		return reinterpret_cast<Level*>(this->Get()->m_level);
	}

	WantLoadInfo* LevelMgrInternal::Request::GetWantLoadInfo() {
		return reinterpret_cast<WantLoadInfo*>(this->Get()->m_WantLoadInfo);
	}

	LevelMgrInternal::Request::LoadingType LevelMgrInternal::Request::GetLoadingType() {
		return this->Get()->m_loadingType;
	}

	bool LevelMgrInternal::Request::IsProcessed() const {
		return this->Get()->m_processed;
	}

#endif
}
