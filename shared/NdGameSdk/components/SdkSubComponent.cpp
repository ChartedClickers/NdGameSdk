#include "SdkSubComponent.hpp"
#include "SdkComponent.hpp"

namespace NdGameSdk {

	ISdkSubComponent::ISdkSubComponent(std::string_view name) : m_name{name}, m_Initialized{false} {};

	void ISdkSubComponent::AttachOwnerComponent(ISdkComponent* parent) {

        if (!parent) {
            throw SdkComponentEx(
                "Cannot attach SubComponent '" + std::string(GetName()) +
                "': parent pointer is null",
                SdkComponentEx::ErrorCode::NotAllowed
            );
        }

        if (m_parent) {
            throw SdkComponentEx(
                "SubComponent '" + std::string(GetName()) +
                "' is already attached to component '" +
                std::string(m_parent->GetName()) + "'",
                SdkComponentEx::ErrorCode::NotAllowed
            );
        }

		m_parent = parent;
	}

    SdkComponentFactory* ISdkSubComponent::GetSharedComponents() {
        return ISdkComponent::GetSharedComponents();
    }

    SdkComponentFactory* ISdkSubComponent::GetNdGameComponents() {
        return ISdkComponent::GetNdGameComponents();
    }

	std::string_view ISdkSubComponent::GetName() const {
		return m_name;
	}

	bool ISdkSubComponent::IsInitialized() const {
		return m_Initialized;
	}
	
}