#pragma once

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/gamelib/level/Level.hpp>
#endif

#include <NdGameSdk/shared/src/corelib/containers/list-array.hpp>

#include <type_traits>

#include "level-def.hpp"
#include "want-load.hpp"

namespace regenny::shared::gamelib::level {
#if defined(T2R)

	using LevelTypeFlags = Level::TypeFlags;
	using LevelDisplayControlFlags = Level::LevelDisplayControl;
	using LevelStateFlags = Level::StateFlagBits;
	using LevelRuntimeFlags = Level::RuntimeBits;
	using LevelInfoFlags = Level::Info::Flags;

	constexpr LevelTypeFlags operator|(LevelTypeFlags lhs, LevelTypeFlags rhs) noexcept {
		using U = std::underlying_type_t<LevelTypeFlags>;
		return static_cast<LevelTypeFlags>(static_cast<U>(lhs) | static_cast<U>(rhs));
	}

	constexpr LevelTypeFlags operator&(LevelTypeFlags lhs, LevelTypeFlags rhs) noexcept {
		using U = std::underlying_type_t<LevelTypeFlags>;
		return static_cast<LevelTypeFlags>(static_cast<U>(lhs) & static_cast<U>(rhs));
	}

	constexpr LevelTypeFlags operator~(LevelTypeFlags value) noexcept {
		using U = std::underlying_type_t<LevelTypeFlags>;
		return static_cast<LevelTypeFlags>(~static_cast<U>(value));
	}

	inline LevelTypeFlags& operator|=(LevelTypeFlags& lhs, LevelTypeFlags rhs) noexcept {
		lhs = lhs | rhs;
		return lhs;
	}

	inline LevelTypeFlags& operator&=(LevelTypeFlags& lhs, LevelTypeFlags rhs) noexcept {
		lhs = lhs & rhs;
		return lhs;
	}

	constexpr LevelDisplayControlFlags operator|(LevelDisplayControlFlags lhs, LevelDisplayControlFlags rhs) noexcept {
		using U = std::underlying_type_t<LevelDisplayControlFlags>;
		return static_cast<LevelDisplayControlFlags>(static_cast<U>(lhs) | static_cast<U>(rhs));
	}

	constexpr LevelDisplayControlFlags operator&(LevelDisplayControlFlags lhs, LevelDisplayControlFlags rhs) noexcept {
		using U = std::underlying_type_t<LevelDisplayControlFlags>;
		return static_cast<LevelDisplayControlFlags>(static_cast<U>(lhs) & static_cast<U>(rhs));
	}

	constexpr LevelDisplayControlFlags operator~(LevelDisplayControlFlags value) noexcept {
		using U = std::underlying_type_t<LevelDisplayControlFlags>;
		return static_cast<LevelDisplayControlFlags>(~static_cast<U>(value));
	}

	inline LevelDisplayControlFlags& operator|=(LevelDisplayControlFlags& lhs, LevelDisplayControlFlags rhs) noexcept {
		lhs = lhs | rhs;
		return lhs;
	}

	inline LevelDisplayControlFlags& operator&=(LevelDisplayControlFlags& lhs, LevelDisplayControlFlags rhs) noexcept {
		lhs = lhs & rhs;
		return lhs;
	}

	constexpr LevelStateFlags operator|(LevelStateFlags lhs, LevelStateFlags rhs) noexcept {
		using U = std::underlying_type_t<LevelStateFlags>;
		return static_cast<LevelStateFlags>(static_cast<U>(lhs) | static_cast<U>(rhs));
	}

	constexpr LevelStateFlags operator&(LevelStateFlags lhs, LevelStateFlags rhs) noexcept {
		using U = std::underlying_type_t<LevelStateFlags>;
		return static_cast<LevelStateFlags>(static_cast<U>(lhs) & static_cast<U>(rhs));
	}

	constexpr LevelStateFlags operator~(LevelStateFlags value) noexcept {
		using U = std::underlying_type_t<LevelStateFlags>;
		return static_cast<LevelStateFlags>(~static_cast<U>(value));
	}

	inline LevelStateFlags& operator|=(LevelStateFlags& lhs, LevelStateFlags rhs) noexcept {
		lhs = lhs | rhs;
		return lhs;
	}

	inline LevelStateFlags& operator&=(LevelStateFlags& lhs, LevelStateFlags rhs) noexcept {
		lhs = lhs & rhs;
		return lhs;
	}

	constexpr LevelRuntimeFlags operator|(LevelRuntimeFlags lhs, LevelRuntimeFlags rhs) noexcept {
		using U = std::underlying_type_t<LevelRuntimeFlags>;
		return static_cast<LevelRuntimeFlags>(static_cast<U>(lhs) | static_cast<U>(rhs));
	}

	constexpr LevelRuntimeFlags operator&(LevelRuntimeFlags lhs, LevelRuntimeFlags rhs) noexcept {
		using U = std::underlying_type_t<LevelRuntimeFlags>;
		return static_cast<LevelRuntimeFlags>(static_cast<U>(lhs) & static_cast<U>(rhs));
	}

	constexpr LevelRuntimeFlags operator~(LevelRuntimeFlags value) noexcept {
		using U = std::underlying_type_t<LevelRuntimeFlags>;
		return static_cast<LevelRuntimeFlags>(~static_cast<U>(value));
	}

	inline LevelRuntimeFlags& operator|=(LevelRuntimeFlags& lhs, LevelRuntimeFlags rhs) noexcept {
		lhs = lhs | rhs;
		return lhs;
	}

	inline LevelRuntimeFlags& operator&=(LevelRuntimeFlags& lhs, LevelRuntimeFlags rhs) noexcept {
		lhs = lhs & rhs;
		return lhs;
	}

	constexpr LevelInfoFlags operator|(LevelInfoFlags lhs, LevelInfoFlags rhs) noexcept {
		using U = std::underlying_type_t<LevelInfoFlags>;
		return static_cast<LevelInfoFlags>(static_cast<U>(lhs) | static_cast<U>(rhs));
	}

	constexpr LevelInfoFlags operator&(LevelInfoFlags lhs, LevelInfoFlags rhs) noexcept {
		using U = std::underlying_type_t<LevelInfoFlags>;
		return static_cast<LevelInfoFlags>(static_cast<U>(lhs) & static_cast<U>(rhs));
	}

	constexpr LevelInfoFlags operator~(LevelInfoFlags value) noexcept {
		using U = std::underlying_type_t<LevelInfoFlags>;
		return static_cast<LevelInfoFlags>(~static_cast<U>(value));
	}

	inline LevelInfoFlags& operator|=(LevelInfoFlags& lhs, LevelInfoFlags rhs) noexcept {
		lhs = lhs | rhs;
		return lhs;
	}

	inline LevelInfoFlags& operator&=(LevelInfoFlags& lhs, LevelInfoFlags rhs) noexcept {
		lhs = lhs & rhs;
		return lhs;
	}

#endif
}

namespace NdGameSdk::gamelib::level {
#if defined(T2R)

	using namespace corelib::containers;

	class LevelMgr;

	class Level : public ISdkRegenny<regenny::shared::gamelib::level::Level> {
	public:
		using TypeFlags = regenny::shared::gamelib::level::LevelTypeFlags;
		using DisplayControlFlags = regenny::shared::gamelib::level::LevelDisplayControlFlags;
		using StateFlags = regenny::shared::gamelib::level::LevelStateFlags;
		using RuntimeFlags = regenny::shared::gamelib::level::LevelRuntimeFlags;
		using Status = regenny::shared::gamelib::level::Level::Status;
		using Layer = regenny::shared::gamelib::level::LevelSpecLayer;

		class Info : public ISdkRegenny<regenny::shared::gamelib::level::Level::Info> {
		public:
			using Flags = regenny::shared::gamelib::level::LevelInfoFlags;
			Info::Flags GetInfoFlags() const;
		private:
			void SetInfoFlags(Info::Flags flags);
			void EnableInfoFlags(Info::Flags flags);
			void DisableInfoFlags(Info::Flags flags);
			bool HasInfoFlags(Info::Flags flags) const;
		};

		class DependentProcessNode : public ISdkRegenny<regenny::shared::gamelib::level::Level::DependentProcessNode> {
			// TODO: Add methods after implementing Process reference wrapper
		};
		class SoundBankTable : public ISdkRegenny<regenny::shared::gamelib::level::Level::SoundBankTable> {};
		class BgDrivenByFgCandidate : public ISdkRegenny<regenny::shared::gamelib::level::Level::BgDrivenByFgCandidate> {};

		const char* GetLevelName() const;
		StringId64 GetLevelId() const;
		Status GetStatus() const;
		std::string_view GetStatusString() const;
		ListArray<StringId64>& GetPackageNameIds();
		uint64_t GetPackagesFinalizedCount();
		
		LevelDef* GetLevelDef() const;
		DependentProcessNode* GetDependentProcessHead() const;
		LevelLoadedCallback GetOnLoadedCallback() const;

		Info& GetLevelInfo();

		bool IsLoaded() const;
		bool IsLoadingPhase() const;
		bool IsInUnloadingPhase() const;

		bool IsStreamingWorld() const;
		bool IsDisplayLevel() const;
		bool IsBackgroundLevel() const;

		void GoStatus(Status newStatus);
		void ReloadInGameData();
		bool SetWantFlags(WantLoadInfo::Flags wantFlags);

		TypeFlags GetTypeFlags() const;
		void SetTypeFlags(TypeFlags flags);
		void EnableTypeFlags(TypeFlags flags);
		void DisableTypeFlags(TypeFlags flags);
		bool HasTypeFlags(TypeFlags flags) const;
	
		DisplayControlFlags GetDisplayControlFlags() const;
		void SetDisplayControlFlags(DisplayControlFlags flags);
		void EnableDisplayControlFlags(DisplayControlFlags flags);
		void DisableDisplayControlFlags(DisplayControlFlags flags);
		bool HasDisplayControlFlags(DisplayControlFlags flags) const;
	
		Layer GetActiveLayers() const;
		void SetActiveLayers(Layer layers);
		void EnableActiveLayers(Layer layers);
		void DisableActiveLayers(Layer layers);
		bool HasActiveLayers(Layer layers) const;
	
		Layer GetDesiredLayers() const;
		void SetDesiredLayers(Layer layers);
		void EnableDesiredLayers(Layer layers);
		void DisableDesiredLayers(Layer layers);
		bool HasDesiredLayers(Layer layers) const;
	
		StateFlags GetStateFlags() const;
		void SetStateFlags(StateFlags flags);
		void EnableStateFlags(StateFlags flags);
		void DisableStateFlags(StateFlags flags);
		bool HasStateFlags(StateFlags flags) const;
	
		RuntimeFlags GetRuntimeFlags() const;
		void SetRuntimeFlags(RuntimeFlags flags);
		void EnableRuntimeFlags(RuntimeFlags flags);
		void DisableRuntimeFlags(RuntimeFlags flags);
		bool HasRuntimeFlags(RuntimeFlags flags) const;

		static DependentProcessNode* GetDependentNode(Level* pLevel);
		static void FreeDependentNode(DependentProcessNode* pNode);

	private:
		TYPEDEF_FUNCTION_PTR(void, LevelMgr_Level_GoStatus, Level* pLevel, Status newStatus);
		TYPEDEF_FUNCTION_PTR(DependentProcessNode*, LevelMgr_Level_GetDependentNode, Level* pLevel);
		TYPEDEF_FUNCTION_PTR(void, LevelMgr_Level_FreeDependentNode, Level::DependentProcessNode* pNode);
		TYPEDEF_FUNCTION_PTR(void, LevelMgr_Level_ReloadInGameData, Level* pLevel);
		TYPEDEF_FUNCTION_PTR(bool, LevelMgr_Level_SetWantFlags, Level* pLevel, WantLoadInfo::Flags wantFlags);

		// TODO: Implement Process reference wrapper
		TYPEDEF_FUNCTION_PTR(void, LevelMgr_Level_AttachProcess, Level* pLevel, void* pProcess);
		TYPEDEF_FUNCTION_PTR(void, LevelMgr_Level_DetachProcess, Level* pLevel, void* pProcess);
		TYPEDEF_FUNCTION_PTR(void, LevelMgr_Level_DetachProcesses, Level* pLevel);
		TYPEDEF_FUNCTION_PTR(void, LevelMgr_Level_KillDependentProcesses, Level* pLevel, int pCodeReason);
		friend class LevelMgr;
	};

	static_assert(sizeof(Level) == 0xac0, "Size of Level is not correct.");

#endif
}
