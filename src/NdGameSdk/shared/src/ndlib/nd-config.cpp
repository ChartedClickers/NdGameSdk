#include "nd-config.hpp"
#include "./NdGameSdk/shared/sharedpatterns.hpp"

#include <global_resolver.hpp>

namespace NdGameSdk::ndlib {

	NdConfigComponent::NdConfigComponent() : ISdkComponent("NdConfig") {}

	void NdConfigComponent::Initialize() {
		static std::once_flag Initialized;
		std::call_once(Initialized, [this] {
			
			spdlog::info("Initializing {} component...", GetName());

			Patterns::SdkPattern findpattern{};

			findpattern = Patterns::NdConfig_g_ndConfig;
			g_ndConfig = Utility::GlobalResolver::RipSlotOrNull<NdConfig>(Utility::memory::get_executable(), findpattern.pattern,
				wstr(Patterns::EngineComponents_s_ndConfig), findpattern.offset, 3, 7);

			if (!g_ndConfig) {
				throw SdkComponentEx{ std::format("Failed to find {}:: game variables!", GetName()),
					SdkComponentEx::ErrorCode::PatternFailed };
			}

		});
	}

	NdConfig& NdConfigComponent::GetNdConfig() {
		always_assert(g_ndConfig == nullptr, "g_ndConfig was not set!");
		return *g_ndConfig;
	}

	ndlib::debug::DMENU& NdConfig::GetDmenu() {
		auto* dmenu = reinterpret_cast<ndlib::debug::DMENU*>(this->Get()->m_DMENU);
		always_assert(dmenu == nullptr, "m_DMENU was null");
		return *dmenu;
	}

	ndlib::debug::DMENU::MenuGroup& NdConfig::GetNdDevMenu() {
		auto* devMenu = reinterpret_cast<ndlib::debug::DMENU::MenuGroup*>(this->Get()->m_DevMenu);
		always_assert(devMenu == nullptr, "m_DevMenu was null");
		return *devMenu;
	}

#if defined(T2R)

	gamelib::level::LevelDefCollectionInternal& NdConfig::GetLevelDefCollection() {
		auto* levelDefCollection = reinterpret_cast<gamelib::level::LevelDefCollectionInternal*>(this->Get()->m_LevelDefCollection);
		always_assert(levelDefCollection == nullptr, "m_LevelDefCollection was null");
		return *levelDefCollection;
	}

	gamelib::level::LoadRegistryInternal& NdConfig::GetLoadRegistry() {
		auto* loadRegistry = reinterpret_cast<gamelib::level::LoadRegistryInternal*>(this->Get()->m_LoadRegistry);
		always_assert(loadRegistry == nullptr, "m_LoadRegistry was null");
		return *loadRegistry;
	}

#endif 

	NdConfig* NdConfigComponent::g_ndConfig = nullptr;
}
