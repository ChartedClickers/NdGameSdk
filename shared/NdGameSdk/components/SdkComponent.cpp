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

	const std::vector<ISdkComponent*>& ISdkComponent::GetSdkComponents() {
		static std::vector<ISdkComponent*> CachedComponents;
		static std::once_flag initFlag;

		if (!g_SdkInitialized) {
			throw SdkComponentEx(
				"SDK is not initialized! Cannot access components.",
				SdkComponentEx::ErrorCode::SdkNotInitialized,
				true
			);
		}

		std::call_once(initFlag, [] {
			const auto& sharedComponents = GetSharedComponents()->GetSdkComponents();
			const auto& ndGameComponents = GetNdGameComponents()->GetSdkComponents();

			CachedComponents.reserve(sharedComponents.size() + ndGameComponents.size());

			for (const auto& [_, comp] : sharedComponents) {
				CachedComponents.push_back(comp.get());
			}
			for (const auto& [_, comp] : ndGameComponents) {
				CachedComponents.push_back(comp.get());
			}
			});

		return CachedComponents;
	}

        void ISdkComponent::InitSubComponents() {

			for (auto& [_, entry] : m_subcomponents) {
				if (!entry.ShouldAutoInitialize() || !entry.instance) { continue; }
				InitSubComponentPtr(entry.instance.get());
			}
        }

        void ISdkComponent::InitSubComponentById(const std::type_index& id) {
			auto it = m_subcomponents.find(id);
			if (it == m_subcomponents.end()) return;
			if (!it->second.instance) return;
			InitSubComponentPtr(it->second.instance.get());
        }



	void ISdkComponent::InitSubComponentPtr(ISdkSubComponent* subraw) {
		if (!subraw || subraw->IsInitialized()) return;
		spdlog::info("Initialize SubComponent: {}", subraw->GetName());
		try {
			subraw->Init();
			subraw->m_Initialized = true;
		}
		catch (SdkComponentEx ComponentEx) {
			spdlog::error("Error initialize {:s}: {:s}", subraw->GetName().data(), ComponentEx.what());
			throw;
		}
		catch (const std::exception& ex) {
			spdlog::error("Error initialize {}: {}", subraw->GetName(), ex.what());
			throw;
		}
		catch (...) {
			spdlog::error("Error initialize: {}", subraw->GetName());
			throw;
		}
	}

}
