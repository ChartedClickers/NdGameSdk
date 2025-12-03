#pragma once

#include <NdGameSdk/sdk.hpp>
#include <NdGameSdk/sdkderived.hpp>

#include <windows.h>
#include <typeindex>
#include <unordered_map>
#include <unordered_set>

namespace NdGameSdk {
	
    class ISdkComponent;
    class ISdkSubComponent;

    class SdkComponentFactory final {
    public:
        SdkComponentFactory() = default;
        ~SdkComponentFactory() = default;

        void InitializeSdkComponents();
        const std::unordered_map<std::type_index, std::unique_ptr<ISdkComponent>>& GetSdkComponents() const;

        template <typename ComponentType, typename... Args>
        ComponentType* AddComponent(Args&&... args) {
            static_assert(SdkDerived::is_derived_from_ISdkComponent<ComponentType>::value,
                "ComponentType must be derived from ISdkComponent");

            auto id = std::type_index(typeid(ComponentType));
            auto sdkcomponent = std::make_unique<ComponentType>(std::forward<Args>(args)...);
            auto rawcomponent = sdkcomponent.get();

            if (m_sdkcomponents.contains(id))
                spdlog::warn("Component {} already exists � replacing.", id.name());

            m_sdkcomponents[id] = std::move(sdkcomponent);

            if (std::find(m_orderedSdkComponents.begin(), m_orderedSdkComponents.end(), id)
                == m_orderedSdkComponents.end()) {
                m_orderedSdkComponents.push_back(id);
            }

            return static_cast<ComponentType*>(rawcomponent);
        }

        template <typename ComponentType>
        NdGameSdk_API ComponentType* GetComponent() {
            static_assert(SdkDerived::is_derived_from_ISdkComponent<ComponentType>::value, "ComponentType must be derived from ISdkComponent");
            auto it = m_sdkcomponents.find(typeid(ComponentType));
            return (it != m_sdkcomponents.end()) ? static_cast<ComponentType*>(it->second.get()) : nullptr;
        }

    private:
        std::unordered_map<std::type_index, std::unique_ptr<ISdkComponent>> m_sdkcomponents{};
        std::vector<std::type_index> m_orderedSdkComponents{};
    };

}