#pragma once

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/gamelib/level/LevelDef.hpp>
#include <NdGameSdk/regenny/t2r/shared/gamelib/level/LevelSpec.hpp>
#endif

#include <NdGameSdk/shared/src/corelib/containers/static-array.hpp>
#include <NdGameSdk/shared/src/corelib/memory/memory.hpp>
#include <NdGameSdk/shared/src/ndlib/io/file-system-win-fios2.hpp>

#include <string_view>
#include <type_traits>

namespace regenny::shared::gamelib::level {
#if defined(T2R)

	using LevelDefFlags = LevelDef::Flags;

	constexpr LevelDefFlags operator|(LevelDefFlags lhs, LevelDefFlags rhs) noexcept {
		using U = std::underlying_type_t<LevelDefFlags>;
		return static_cast<LevelDefFlags>(static_cast<U>(lhs) | static_cast<U>(rhs));
	}

	constexpr LevelDefFlags operator&(LevelDefFlags lhs, LevelDefFlags rhs) noexcept {
		using U = std::underlying_type_t<LevelDefFlags>;
		return static_cast<LevelDefFlags>(static_cast<U>(lhs) & static_cast<U>(rhs));
	}

	constexpr LevelDefFlags operator~(LevelDefFlags value) noexcept {
		using U = std::underlying_type_t<LevelDefFlags>;
		return static_cast<LevelDefFlags>(~static_cast<U>(value));
	}

	inline LevelDefFlags& operator|=(LevelDefFlags& lhs, LevelDefFlags rhs) noexcept {
		lhs = lhs | rhs;
		return lhs;
	}

	inline LevelDefFlags& operator&=(LevelDefFlags& lhs, LevelDefFlags rhs) noexcept {
		lhs = lhs & rhs;
		return lhs;
	}

	using LevelSpecLayer = LevelSpec::Layer;

	constexpr LevelSpecLayer operator|(LevelSpecLayer lhs, LevelSpecLayer rhs) noexcept {
		using U = std::underlying_type_t<LevelSpecLayer>;
		return static_cast<LevelSpecLayer>(static_cast<U>(lhs) | static_cast<U>(rhs));
	}

	constexpr LevelSpecLayer operator&(LevelSpecLayer lhs, LevelSpecLayer rhs) noexcept {
		using U = std::underlying_type_t<LevelSpecLayer>;
		return static_cast<LevelSpecLayer>(static_cast<U>(lhs) & static_cast<U>(rhs));
	}

	constexpr LevelSpecLayer operator~(LevelSpecLayer value) noexcept {
		using U = std::underlying_type_t<LevelSpecLayer>;
		return static_cast<LevelSpecLayer>(~static_cast<U>(value));
	}

	inline LevelSpecLayer& operator|=(LevelSpecLayer& lhs, LevelSpecLayer rhs) noexcept {
		lhs = lhs | rhs;
		return lhs;
	}

	inline LevelSpecLayer& operator&=(LevelSpecLayer& lhs, LevelSpecLayer rhs) noexcept {
		lhs = lhs & rhs;
		return lhs;
	}

#endif
}

namespace NdGameSdk::gamelib::level {
#if defined(T2R)

	using namespace ndlib::io;
	using namespace corelib::containers;

	class LevelDefCollection;

	struct LevelSpec : public ISdkRegenny<regenny::shared::gamelib::level::LevelSpec> {
		using Layer = regenny::shared::gamelib::level::LevelSpec::Layer;

		inline static constexpr uint32_t kMaxPackagesPerLevel = 0x7;
		inline static constexpr uint32_t kMaxActorsPerLevel = 0x200;
		inline static constexpr uint32_t kMaxCachePerLevel = 0x80;
		inline static constexpr uint32_t kMaxSoundBanksPerLevel = 0x100;
		inline static constexpr uint32_t kMaxPartModulesPerLevel = 0x80;
		inline static constexpr uint32_t kMaxModulesPerLevel = 0x200;
		inline static constexpr uint32_t kMaxVoxCharactersPerLevel = 0x40;
		inline static constexpr uint32_t kMaxLutTablesPerLevel = 0x180;

		static constexpr Layer None = static_cast<Layer>(0);
		static constexpr Layer Base = Layer::Base;
		static constexpr Layer Phys = Layer::Phys;
		static constexpr Layer Ingame = Layer::Ingame;
		static constexpr Layer All = static_cast<Layer>(Base | Phys | Ingame);

		// Common layer combinations
		static constexpr Layer Geometry = Base;
		static constexpr Layer Gameplay = static_cast<Layer>(Phys | Ingame);

		static bool HasLayer(Layer value, Layer flag) noexcept {
			return (value & flag) == flag;
		}

		static Layer EnableLayer(Layer value, Layer flag) noexcept {
			value |= flag;
			return value;
		}

		static Layer DisableLayer(Layer value, Layer flag) noexcept {
			value &= ~flag;
			return value;
		}
	};

	class LevelDef : public ISdkRegenny<regenny::shared::gamelib::level::LevelDef> {
	public:
		using State = regenny::shared::gamelib::level::LevelDef::State;
		using Flags = regenny::shared::gamelib::level::LevelDef::Flags;

		class ActorDefs : public ISdkRegenny<regenny::shared::gamelib::level::LevelDef::ActorDefs> {
		public:
			std::string_view GetName() const;
			StringId64 GetId() const;
		};

		class PackageDef : public ISdkRegenny<regenny::shared::gamelib::level::LevelDef::PackageDef> {
		public:
			std::string_view GetName() const;
			StringId64 GetId() const;

			LevelSpec::Layer GetLayer() const;
			void SetLayer(LevelSpec::Layer layers);
			void EnableLayer(LevelSpec::Layer layers);
			void DisableLayer(LevelSpec::Layer layers);
			bool HasLayer(LevelSpec::Layer layers) const;
			bool IsOptional() const;
		};

		class ParticleModuleDef : public ISdkRegenny<regenny::shared::gamelib::level::LevelDef::ParticleModuleDef> {
		public:
			StringId64 GetId() const;
			bool IsIgnored() const;
		};

		class SoundBankDef : public ISdkRegenny<regenny::shared::gamelib::level::LevelDef::SoundBankDef> {
		public:
			std::string_view GetName() const;
		};

		class AsyncTxtLoad : public ISdkRegenny<regenny::shared::gamelib::level::LevelDef::AsyncTxtLoad> {
		public:

			FileSystemInternal::ReadOnlyFileHandle* GetFileHandle() const;
			FileSystemInternal::ReadOperation* GetReadOperation() const;

			uint64_t GetFileSize() const;
			uint64_t GetBytesReaded() const;
		};

		std::string_view GetLevelName() const;
		StringId64 GetLevelId() const;

		void Update();

		StaticArray<PackageDef>& GetPackagesDefs();
		const StaticArray<PackageDef>& GetPackagesDefs() const;

		StaticArray<ActorDefs>& GetActorDefs();
		const StaticArray<ActorDefs>& GetActorDefs() const;

		StaticArray<StringId64>& GetCaches();
		const StaticArray<StringId64>& GetCaches() const;

		StaticArray<StringId64>& GetModuleIds();
		const StaticArray<StringId64>& GetModuleIds() const;

		StaticArray<StringId64>& GetRenderSettingsForLutTables();
		const StaticArray<StringId64>& GetRenderSettingsForLutTables() const;

		StaticArray<ParticleModuleDef>& GetParticleModuleDefs();
		const StaticArray<ParticleModuleDef>& GetParticleModuleDefs() const;

		StaticArray<SoundBankDef>& GetSoundBankDefs();
		const StaticArray<SoundBankDef>& GetSoundBankDefs() const;

		StaticArray<SoundBankDef>& GetVoxCharacterSoundBankDefs();
		const StaticArray<SoundBankDef>& GetVoxCharacterSoundBankDefs() const;

		std::string_view GetAssociatedPartModuleName() const;

		AsyncTxtLoad* GetAsyncTxtLoad() const;
		State GetState() const;

		Flags GetFlags() const;
		void SetFlags(Flags flags);
		void EnableFlags(Flags flags);
		void DisableFlags(Flags flags);
		bool HasFlags(Flags flags) const;

		bool IsPartPackagesDisabled() const;
	private:
		//TYPEDEF_FUNCTION_PTR(bool, LevelDefCollection_LevelDef_LoadTxtFile, LevelDef* pLevelDef, Memory::Allocator* pAllocator);
		//TYPEDEF_FUNCTION_PTR(void, LevelDefCollection_LevelDef_LoadAsyncTxtFile, LevelDef* pLevelDef, Memory::Allocator* pAllocator);
		TYPEDEF_FUNCTION_PTR(void, LevelDefCollection_LevelDef_Update, LevelDef* pLevelDef);
		friend class LevelDefCollection;
	};

	static_assert(sizeof(LevelDef) == 0xe0, "Size of LevelDef is not correct.");
	static_assert(sizeof(LevelDef::ActorDefs) == 0x10, "Size of LevelDef::ActorDefs is not correct.");
	static_assert(sizeof(LevelDef::PackageDef) == 0x18, "Size of LevelDef::PackageDef is not correct.");
	static_assert(sizeof(LevelDef::ParticleModuleDef) == 0x10, "Size of LevelDef::ParticleModuleDef is not correct.");
	static_assert(sizeof(LevelDef::SoundBankDef) == 0x10, "Size of LevelDef::SoundBankDef is not correct.");
	static_assert(sizeof(LevelDef::AsyncTxtLoad) == 0x58, "Size of LevelDef::AsyncTxtLoad is not correct.");

#endif
}
