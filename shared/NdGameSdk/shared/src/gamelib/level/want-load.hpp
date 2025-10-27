#pragma once

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/gamelib/level/WantLoadInfo.hpp>
#endif

#include <string_view>
#include <type_traits>

#include "level-def.hpp"

namespace regenny::shared::gamelib::level {
#if defined(T2R)

	using WantLoadFlags = WantLoadInfo::Flags;

	constexpr WantLoadFlags operator|(WantLoadFlags lhs, WantLoadFlags rhs) noexcept {
		using U = std::underlying_type_t<WantLoadFlags>;
		return static_cast<WantLoadFlags>(static_cast<U>(lhs) | static_cast<U>(rhs));
	}

	constexpr WantLoadFlags operator&(WantLoadFlags lhs, WantLoadFlags rhs) noexcept {
		using U = std::underlying_type_t<WantLoadFlags>;
		return static_cast<WantLoadFlags>(static_cast<U>(lhs) & static_cast<U>(rhs));
	}

	constexpr WantLoadFlags operator~(WantLoadFlags value) noexcept {
		using U = std::underlying_type_t<WantLoadFlags>;
		return static_cast<WantLoadFlags>(~static_cast<U>(value));
	}

	inline WantLoadFlags& operator|=(WantLoadFlags& lhs, WantLoadFlags rhs) noexcept {
		lhs = lhs | rhs;
		return lhs;
	}

	inline WantLoadFlags& operator&=(WantLoadFlags& lhs, WantLoadFlags rhs) noexcept {
		lhs = lhs & rhs;
		return lhs;
	}

#endif
}

namespace NdGameSdk::gamelib::level {
#if defined(T2R)

	class LoadRegistry;

	class Level;
	using LevelLoadedCallback = void(*)(Level* pLevel);

	class WantLoadInfo : public ISdkRegenny<regenny::shared::gamelib::level::WantLoadInfo> {
	public:
		using Type = regenny::shared::gamelib::level::WantLoadInfo::Type;
		using Flags = regenny::shared::gamelib::level::WantLoadFlags;

		WantLoadInfo(Type type, const char* name, StringId64 nameId, 
			Flags pFlags = Flags::Portal | Flags::FGVisible | Flags::Locked);

		std::string_view GetName() const;
		StringId64 GetNameId() const;

		LevelDef* GetLevelDef() const;

		LevelLoadedCallback GetOnLoadedCallback() const;
		void SetOnLoadedCallback(LevelLoadedCallback callback);

		Type GetType() const;

		Flags GetFlags() const;
		void SetFlags(Flags flags);
		void EnableFlags(Flags flags);
		void DisableFlags(Flags flags);
		bool HasFlags(Flags flags) const;

		LevelSpec::Layer GetLayer() const;
		void SetLayer(LevelSpec::Layer layers);
		void EnableLayer(LevelSpec::Layer layers);
		void DisableLayer(LevelSpec::Layer layers);
		bool HasLayer(LevelSpec::Layer layers) const;
	private:
		TYPEDEF_FUNCTION_PTR(void, LoadRegistry_WantLoadInfo_Constructor, WantLoadInfo* pThis, Type type, const char* name, StringId64 nameId);
		friend class LoadRegistry;
	};

#endif
}
