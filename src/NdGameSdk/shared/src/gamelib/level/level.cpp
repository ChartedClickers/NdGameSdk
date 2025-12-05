#include "level.hpp"

#include <type_traits>

namespace NdGameSdk::gamelib::level {
#if defined(T2R)

	namespace {
		template <typename Enum>
		[[nodiscard]] constexpr Enum EnableFlags(Enum value, Enum flags) noexcept {
			using U = std::underlying_type_t<Enum>;
			return static_cast<Enum>(static_cast<U>(value) | static_cast<U>(flags));
		}
	
		template <typename Enum>
		[[nodiscard]] constexpr Enum DisableFlags(Enum value, Enum flags) noexcept {
			using U = std::underlying_type_t<Enum>;
			return static_cast<Enum>(static_cast<U>(value) & ~static_cast<U>(flags));
		}
	
		template <typename Enum>
		[[nodiscard]] constexpr bool HasFlags(Enum value, Enum flags) noexcept {
			using U = std::underlying_type_t<Enum>;
			return (static_cast<U>(value) & static_cast<U>(flags)) == static_cast<U>(flags);
		}
	}

	const char* Level::GetLevelName() const {
		return this->Get()->m_LevelName;
	}

	StringId64 Level::GetLevelId() const {
		return this->Get()->m_LevelId;
	}

	Level::Status Level::GetStatus() const {
		return this->Get()->m_state;
	}

	std::string_view Level::GetStatusString() const {
		switch (GetStatus()) {
			case Status::Empty: return "Empty";
			case Status::Initialized: return "Initialized";
			case Status::Loading: return "Loading";
			case Status::WaitingForLevelSoundBanks: return "WaitingForLevelSoundBanks";
			case Status::WaitingForLevelSoundBanksVoxUnload: return "WaitingForLevelSoundBanksVoxUnload";
			case Status::DoingLogin: return "DoingLogin";
			case Status::LoadSoundBanks: return "LoadSoundBanks";
			case Status::WaitForSoundBanks: return "WaitForSoundBanks";
			case Status::WaitForActors: return "WaitForActors";
			case Status::UnknownStatus: return "UnknownStatus";
			case Status::PreLoaded: return "PreLoaded";
			case Status::Loaded: return "Loaded";
			case Status::LoadedDisplay: return "LoadedDisplay";
			case Status::Unloading: return "Unloading";
			case Status::UnloadingWaiting: return "UnloadingWaiting";
			case Status::UnloadingLogOut: return "UnloadingLogOut";
			case Status::UnloadingWaitForProcessToDie: return "UnloadingWaitForProcessToDie";
			case Status::UnloadingReleasePackages: return "UnloadingReleasePackages";
			case Status::Zombie: return "Zombie";
			case Status::StalledByReplay: return "StalledByReplay";
			case Status::InterruptedLoading: return "InterruptedLoading";
			case Status::Error: return "Error";
			case Status::Invalid: return "Invalid";
			default: return "Unknown";
		}
	}

	ListArray<StringId64>& Level::GetPackageNameIds() {
		return reinterpret_cast<ListArray<StringId64>&>(this->Get()->m_PackageNameIds);
	}

	uint64_t Level::GetPackagesFinalizedCount() {
		return this->Get()->m_packagesFinalizedCount;
	}

	LevelDef* Level::GetLevelDef() const {
		return reinterpret_cast<LevelDef*>(this->Get()->m_pLevelDef);
	}

	Level::DependentProcessNode* Level::GetDependentProcessHead() const {
		return reinterpret_cast<DependentProcessNode*>(this->Get()->m_dependentProcHead);
	}

	LevelLoadedCallback Level::GetOnLoadedCallback() const {
		return reinterpret_cast<LevelLoadedCallback>(this->Get()->m_onLoadedCallBack);
	}

	Level::Info& Level::GetLevelInfo() {
		return reinterpret_cast<Level::Info&>(this->Get()->m_levelInfo);
	}

	bool Level::IsLoaded() const {
		const auto status = GetStatus();
		return status == Status::Loaded || status == Status::LoadedDisplay;
	}

	bool Level::IsLoadingPhase() const {
		const auto status = GetStatus();
		return status >= Status::Initialized && status <= Status::WaitForActors;
	}

	bool Level::IsInUnloadingPhase() const {
		const auto status = GetStatus();
		return status >= Status::Unloading && status <= Status::Zombie;
	}

	bool Level::IsStreamingWorld() const {
		return HasTypeFlags(TypeFlags::StreamingWorld);
	}

	bool Level::IsDisplayLevel() const {
		constexpr auto mask = static_cast<uint16_t>(TypeFlags::SubtypeMask);
		const auto flags = static_cast<uint16_t>(GetTypeFlags());
		return (flags & mask) == static_cast<uint16_t>(TypeFlags::DisplayLevel);
	}

	bool Level::IsBackgroundLevel() const {
		constexpr auto mask = static_cast<uint16_t>(TypeFlags::SubtypeMask);
		const auto flags = static_cast<uint16_t>(GetTypeFlags());
		return (flags & mask) == static_cast<uint16_t>(TypeFlags::BackgroundLevel);
	}

	void Level::GoStatus(Status newStatus) {
		always_assert(LevelMgr_Level_GoStatus == nullptr, "Function pointer was not set!");
		LevelMgr_Level_GoStatus(this, newStatus);
	}

	void Level::ReloadInGameData() {
		always_assert(LevelMgr_Level_ReloadInGameData == nullptr, "Function pointer was not set!");
		LevelMgr_Level_ReloadInGameData(this);
	}

	bool Level::SetWantFlags(WantLoadInfo::Flags wantFlags) {
		always_assert(LevelMgr_Level_SetWantFlags == nullptr, "Function pointer was not set!");
		return LevelMgr_Level_SetWantFlags(this, wantFlags);
	}

	Level::TypeFlags Level::GetTypeFlags() const {
		return this->Get()->m_typeFlags;
	}
	
	void Level::SetTypeFlags(TypeFlags flags) {
		this->Get()->m_typeFlags = flags;
	}
	
	void Level::EnableTypeFlags(TypeFlags flags) {
		auto* self = this->Get();
		self->m_typeFlags = EnableFlags(self->m_typeFlags, flags);
	}
	
	void Level::DisableTypeFlags(TypeFlags flags) {
		auto* self = this->Get();
		self->m_typeFlags = DisableFlags(self->m_typeFlags, flags);
	}
	
	bool Level::HasTypeFlags(TypeFlags flags) const {
		return HasFlags(this->Get()->m_typeFlags, flags);
	}
	
	Level::DisplayControlFlags Level::GetDisplayControlFlags() const {
		return this->Get()->m_displayControlFlags;
	}
	
	void Level::SetDisplayControlFlags(DisplayControlFlags flags) {
		this->Get()->m_displayControlFlags = flags;
	}
	
	void Level::EnableDisplayControlFlags(DisplayControlFlags flags) {
		auto* self = this->Get();
		self->m_displayControlFlags = EnableFlags(self->m_displayControlFlags, flags);
	}
	
	void Level::DisableDisplayControlFlags(DisplayControlFlags flags) {
		auto* self = this->Get();
		self->m_displayControlFlags = DisableFlags(self->m_displayControlFlags, flags);
	}
	
	bool Level::HasDisplayControlFlags(DisplayControlFlags flags) const {
		return HasFlags(this->Get()->m_displayControlFlags, flags);
	}
	
	Level::Layer Level::GetActiveLayers() const {
		return this->Get()->m_activeContentFlags;
	}
	
	void Level::SetActiveLayers(Layer layers) {
		this->Get()->m_activeContentFlags = layers;
	}
	
	void Level::EnableActiveLayers(Layer layers) {
		auto* self = this->Get();
		self->m_activeContentFlags = EnableFlags(self->m_activeContentFlags, layers);
	}
	
	void Level::DisableActiveLayers(Layer layers) {
		auto* self = this->Get();
		self->m_activeContentFlags = DisableFlags(self->m_activeContentFlags, layers);
	}
	
	bool Level::HasActiveLayers(Layer layers) const {
		return HasFlags(this->Get()->m_activeContentFlags, layers);
	}
	
	Level::Layer Level::GetDesiredLayers() const {
		return this->Get()->m_desiredContentFlags;
	}
	
	void Level::SetDesiredLayers(Layer layers) {
		this->Get()->m_desiredContentFlags = layers;
	}
	
	void Level::EnableDesiredLayers(Layer layers) {
		auto* self = this->Get();
		self->m_desiredContentFlags = EnableFlags(self->m_desiredContentFlags, layers);
	}
	
	void Level::DisableDesiredLayers(Layer layers) {
		auto* self = this->Get();
		self->m_desiredContentFlags = DisableFlags(self->m_desiredContentFlags, layers);
	}
	
	bool Level::HasDesiredLayers(Layer layers) const {
		return HasFlags(this->Get()->m_desiredContentFlags, layers);
	}
	
	Level::StateFlags Level::GetStateFlags() const {
		return this->Get()->m_stateFlag;
	}
	
	void Level::SetStateFlags(StateFlags flags) {
		this->Get()->m_stateFlag = flags;
	}
	
	void Level::EnableStateFlags(StateFlags flags) {
		auto* self = this->Get();
		self->m_stateFlag = EnableFlags(self->m_stateFlag, flags);
	}
	
	void Level::DisableStateFlags(StateFlags flags) {
		auto* self = this->Get();
		self->m_stateFlag = DisableFlags(self->m_stateFlag, flags);
	}
	
	bool Level::HasStateFlags(StateFlags flags) const {
		return HasFlags(this->Get()->m_stateFlag, flags);
	}
	
	Level::RuntimeFlags Level::GetRuntimeFlags() const {
		return this->Get()->m_runtimeFlags;
	}
	
	void Level::SetRuntimeFlags(RuntimeFlags flags) {
		this->Get()->m_runtimeFlags = flags;
	}
	
	void Level::EnableRuntimeFlags(RuntimeFlags flags) {
		auto* self = this->Get();
		self->m_runtimeFlags = EnableFlags(self->m_runtimeFlags, flags);
	}
	
	void Level::DisableRuntimeFlags(RuntimeFlags flags) {
		auto* self = this->Get();
		self->m_runtimeFlags = DisableFlags(self->m_runtimeFlags, flags);
	}
	
	bool Level::HasRuntimeFlags(RuntimeFlags flags) const {
		return HasFlags(this->Get()->m_runtimeFlags, flags);
	}
	
	Level::Info::Flags Level::Info::GetInfoFlags() const {
		return this->Get()->m_value;
	}
	
	void Level::Info::SetInfoFlags(Level::Info::Flags flags) {
		this->Get()->m_value = flags;
	}
	
	void Level::Info::EnableInfoFlags(Level::Info::Flags flags) {
		auto* self = this->Get();
		self->m_value = EnableFlags(self->m_value, flags);
	}
	
	void Level::Info::DisableInfoFlags(Level::Info::Flags flags) {
		auto* self = this->Get();
		self->m_value = DisableFlags(self->m_value, flags);
	}
	
	bool Level::Info::HasInfoFlags(Level::Info::Flags flags) const {
		return HasFlags(this->Get()->m_value, flags);
	}

	Level::DependentProcessNode* Level::GetDependentNode(Level* pLevel) {
		always_assert(LevelMgr_Level_GetDependentNode == nullptr, "Function pointer was not set!");
		return LevelMgr_Level_GetDependentNode(pLevel);
	}

	void Level::FreeDependentNode(DependentProcessNode* pNode) {
		always_assert(LevelMgr_Level_FreeDependentNode == nullptr, "Function pointer was not set!");
		LevelMgr_Level_FreeDependentNode(pNode);
	}

	INIT_FUNCTION_PTR(Level::LevelMgr_Level_GoStatus);
	INIT_FUNCTION_PTR(Level::LevelMgr_Level_GetDependentNode);
	INIT_FUNCTION_PTR(Level::LevelMgr_Level_FreeDependentNode);
	INIT_FUNCTION_PTR(Level::LevelMgr_Level_ReloadInGameData);
	INIT_FUNCTION_PTR(Level::LevelMgr_Level_SetWantFlags);

	INIT_FUNCTION_PTR(Level::LevelMgr_Level_AttachProcess);
	INIT_FUNCTION_PTR(Level::LevelMgr_Level_DetachProcess);
	INIT_FUNCTION_PTR(Level::LevelMgr_Level_DetachProcesses);
	INIT_FUNCTION_PTR(Level::LevelMgr_Level_KillDependentProcesses);

#endif
}
