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

		std::for_each(m_orderedSdkComponents.begin(), m_orderedSdkComponents.end(), 
			[](const auto& sdkcomponent) { 
				sdkcomponent->Awake(); 
			});

		for (auto& sdkcomponent : m_orderedSdkComponents) {
			spdlog::info("Initialize SdkComponent: {:s}", sdkcomponent->GetName().data());

			try {
				sdkcomponent->Initialize();
				sdkcomponent->m_Initialized = true;
			} 
			catch (SdkComponentEx ComponentEx) {
				spdlog::error("Error initialize {:s}: {:s}", sdkcomponent->GetName().data(), ComponentEx.what());

				if (ComponentEx.IsCritical())
					throw ComponentEx;
			}
			catch (std::exception Ex) {
				spdlog::error("Error initialize {:s}: {:s}", sdkcomponent->GetName().data(), Ex.what());
				throw Ex;
			}
			catch (...) {
				spdlog::error("Error initialize: {:s}", sdkcomponent->GetName().data());
				throw;
			}
		}

		m_orderedSdkComponents.clear();
		std::erase_if(m_sdkcomponents, 
			[](const pair<std::type_index, std::shared_ptr<ISdkComponent>>& pair) 
			{ return !pair.second->m_Initialized; });
	}

	const auto& SdkComponentFactory::GetSdkComponents() const {
		return m_sdkcomponents;
	}

}