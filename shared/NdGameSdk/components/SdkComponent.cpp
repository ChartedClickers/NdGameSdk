#include "SdkComponent.hpp"

namespace NdGameSdk {

	SdkComponentFactory ISdkComponent::s_SharedComponents{};
	SdkComponentFactory ISdkComponent::s_NdGameComponents{};

	ISdkComponent::ISdkComponent(std::string name) 
		: m_name{ name }, m_Initialized{ false } {};

	std::string_view ISdkComponent::GetName() const {
		return m_name;
	}

	bool ISdkComponent::IsInitialized() const {
		return m_Initialized;
	}

	SdkComponentFactory* ISdkComponent::GetSharedComponents() {
		return &s_SharedComponents;
	}

	SdkComponentFactory* ISdkComponent::GetNdGameComponents() {
		return &s_NdGameComponents;
	}

	void SdkComponentFactory::InitializeSdkComponents() {

		std::for_each(m_sdkcomponents.begin(), m_sdkcomponents.end(), [](const auto& sdkcomponent) { sdkcomponent.second->Awake(); });

		for (auto& [sdkcomponent, component] : m_sdkcomponents) {
			spdlog::info("Initialize SdkComponent: {:s}", component->GetName().data());

			try {
				component->Initialize();
				component->m_Initialized = true;
			} 
			catch (SdkComponentEx ComponentEx) {
				spdlog::error("Error initialize {:s}: {:s}", component->GetName().data(), ComponentEx.what());

				if (ComponentEx.IsCritical())
					throw ComponentEx;
			}
			catch (std::exception Ex) {
				spdlog::error("Error initialize {:s}: {:s}", component->GetName().data(), Ex.what());
				throw Ex;
			}
			catch (...) {
				spdlog::error("Error initialize: {:s}", component->GetName().data());
				throw;
			}
		}

		std::erase_if(m_sdkcomponents, [](
			const pair<std::type_index, std::shared_ptr<ISdkComponent>>& pair) { return !pair.second->m_Initialized; });
	}

	const auto& SdkComponentFactory::GetSdkComponents() const {
		return m_sdkcomponents;
	}

}