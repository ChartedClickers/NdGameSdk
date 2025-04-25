#include "SdkSubComponent.hpp"

namespace NdGameSdk {

	ISdkSubComponent::ISdkSubComponent(std::string name)
		: m_name{ name }, m_Initialized{ false } {
	};

	std::string_view ISdkSubComponent::GetName() const {
		return m_name;
	}

	bool ISdkSubComponent::IsInitialized() const {
		return m_Initialized;
	}
	
}