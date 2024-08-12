#pragma once

#include <windows.h>
#include <filesystem>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <typeindex>
#include <spdlog/spdlog.h>

#include <Utility/helper.hpp>

#include <NdGameSdk/sdk.hpp>
#include <NdGameSdk/sdkconfig.hpp>
#include <NdGameSdk/sdkderived.hpp>
#include <NdGameSdk/sdkexception.hpp>

#include <NdGameSdk/components/event/SdkEvent.hpp>

namespace NdGameSdk {

    class ISdkModule;
    class SdkComponentFactory;

    class ISdkComponent
    {
    public:
        virtual ~ISdkComponent() = default;
        NdGameSdk_API std::string_view GetName() const;
        NdGameSdk_API bool IsInitialized() const;

        template <typename... SdkComponents>
        NdGameSdk_API static optional<std::string> CheckSdkComponents(const std::vector<ISdkComponent*>& componentList, bool MustInitialized = true) {

            static_assert(std::conjunction_v<SdkDerived::is_derived_from_ISdkComponent<SdkComponents>...>,
                "All types must be derived from ISdkComponent");

            std::string missingComponentNames{};

            (([&]() {
                bool found = std::any_of(componentList.begin(), componentList.end(),
                    [MustInitialized](ISdkComponent* component) {
                        auto _found = component && typeid(*component) == typeid(SdkComponents);
                        if (_found && MustInitialized) {
                            return component->IsInitialized();
                        }
                        return _found;
                    });

                if (!found) {
                    if (!missingComponentNames.empty()) {
                        missingComponentNames += ", ";
                    }
                    missingComponentNames += typeid(SdkComponents).name();
                }
                }()), ...);

            if (!missingComponentNames.empty()) {
                return missingComponentNames;
            }

            return {};
        }

    protected:
        ISdkComponent(std::string name);

        template <typename... Args>
        void InvokeSdkEvent(SdkEvent<Args...>& event, Args... args) {
			event.Invoke(args...);
		}

        NdGameSdk_API static SdkComponentFactory* GetSharedComponents();
        NdGameSdk_API static SdkComponentFactory* GetNdGameComponents();
    private:
        friend class SdkComponentFactory;
        friend class ISdkModule;

        friend void InitializeSdk(const SdkConfig* cfg);
        friend void RegisterSdkModule(ISdkModule* SdkModule);
        friend void UnregisterSdkModule(ISdkModule* SdkModule);

        friend void InitSharedComponents(SdkConfig& cfg);
        friend void InitNdGameComponents(SdkConfig& cfg);

        std::string m_name;
        bool m_Initialized;
        virtual void Awake() {};
        virtual void Initialize() = 0;

        static SdkComponentFactory s_SharedComponents;
        static SdkComponentFactory s_NdGameComponents;
    };

    class SdkComponentFactory final {
    public:

        SdkComponentFactory() = default;
        void InitializeSdkComponents();
        const auto& GetSdkComponents() const;

        template <typename ComponentType, typename... Args>
        std::shared_ptr<ComponentType> AddComponent(Args&&... args) {
            static_assert(SdkDerived::is_derived_from_ISdkComponent<ComponentType>::value, "ComponentType must be derived from ISdkComponent");
            auto [sdkcomponent, inserted] = m_sdkcomponents.emplace(typeid(ComponentType), std::make_shared<ComponentType>(std::forward<Args>(args)...));
            return std::static_pointer_cast<ComponentType>(sdkcomponent->second);
        }

        template <typename ComponentType>
        NdGameSdk_API std::shared_ptr<ComponentType> GetComponent() {
            static_assert(SdkDerived::is_derived_from_ISdkComponent<ComponentType>::value, "ComponentType must be derived from ISdkComponent");
            auto sdkcomponent = m_sdkcomponents.find(typeid(ComponentType));
            return sdkcomponent != m_sdkcomponents.end() ? std::static_pointer_cast<ComponentType>(sdkcomponent->second) : nullptr;
        }

    private:
        std::unordered_map<std::type_index, std::shared_ptr<ISdkComponent>> m_sdkcomponents{};
    };

    class SdkComponentEx : public NdGameSdkException {
    public:

        enum ErrorCode {
            DependenciesFailed,
            PatternFailed,
            PatchFailed,
            NotAllowed
        };

        SdkComponentEx(const std::string& msg, ErrorCode errcode, bool critical = false)
            : m_errcode { errcode }, m_critical { critical }, NdGameSdkException(msg) {}

        const ErrorCode ErrCode() const noexcept {
            return m_errcode;
        }

        const bool IsCritical() const noexcept {
            return m_critical;
        }

    private:
        ErrorCode m_errcode;
        bool m_critical;
    };

}