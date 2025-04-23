#pragma once

#include <windows.h>
#include <filesystem>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <typeindex>
#include <deque>
#include <spdlog/spdlog.h>
#include <Utility/helper.hpp>

#include <NdGameSdk/sdk.hpp>
#include <NdGameSdk/sdkconfig.hpp>
#include <NdGameSdk/sdkderived.hpp>
#include <NdGameSdk/sdkexception.hpp>
#include <NdGameSdk/components/event/SdkEvent.hpp>

namespace NdGameSdk {

    class ISdkComponent;

    class SdkComponentFactory final {
    public:
        SdkComponentFactory() = default;

        void InitializeSdkComponents();
        const auto& GetSdkComponents() const;

        template <typename ComponentType, typename... Args>
        std::shared_ptr<ComponentType> AddComponent(Args&&... args) {
            static_assert(SdkDerived::is_derived_from_ISdkComponent<ComponentType>::value, "ComponentType must be derived from ISdkComponent");
            auto sdkcomponent = std::make_shared<ComponentType>(std::forward<Args>(args)...);
            m_orderedSdkComponents.push_back(sdkcomponent);
            m_sdkcomponents.emplace(typeid(ComponentType), sdkcomponent);
            return std::static_pointer_cast<ComponentType>(sdkcomponent);
        }

        template <typename ComponentType>
        NdGameSdk_API std::shared_ptr<ComponentType> GetComponent() {
            static_assert(SdkDerived::is_derived_from_ISdkComponent<ComponentType>::value, "ComponentType must be derived from ISdkComponent");
            auto it = m_sdkcomponents.find(typeid(ComponentType));
            return it != m_sdkcomponents.end() ? std::static_pointer_cast<ComponentType>(it->second) : nullptr;
        }

    private:
        std::unordered_map<std::type_index, std::shared_ptr<ISdkComponent>> m_sdkcomponents{};
        std::deque<std::shared_ptr<ISdkComponent>> m_orderedSdkComponents{};
    };

    class ISdkComponent {
    public:
        virtual ~ISdkComponent() = default;

        NdGameSdk_API std::string_view GetName() const;
        NdGameSdk_API bool IsInitialized() const;

        template <typename... SdkComponents>
        NdGameSdk_API static optional<std::string> CheckSdkComponents(const std::vector<ISdkComponent*>& componentList) {
            static_assert(std::conjunction_v<SdkDerived::is_derived_from_ISdkComponent<SdkComponents>...>,
                "All types must be derived from ISdkComponent");
            std::string missingComponentNames{};
            (([&]() {
                bool found = std::any_of(componentList.begin(), componentList.end(),
                    [](ISdkComponent* component) {
                        return component && (typeid(*component) == typeid(SdkComponents));
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

        template <typename ComponentType, typename EventType, typename MemberFunc, typename ClassType = void>
        NdGameSdk_API static optional<ISdkAction> SubscribeSdkEvent(
            SdkComponentFactory* ComponentFactory,
            EventType ComponentType::* event,
            MemberFunc memberFunc,
            ClassType* Instance = nullptr,
            bool OneTimeInvoke = false)
        {
            auto sdkcomponent = ComponentFactory->GetComponent<ComponentType>().get();
            if (sdkcomponent) {
                if constexpr (!std::is_same_v<ClassType, void>)
                    return (sdkcomponent->*event).Subscribe(Instance, memberFunc, OneTimeInvoke);
                else 
                    return (sdkcomponent->*event).Subscribe(*memberFunc, OneTimeInvoke);
            }
            return {};
        }

        template <typename ComponentType, typename EventType, typename MemberFunc, typename ClassType = void>
        NdGameSdk_API static void UnsubscribeSdkEvent(
            SdkComponentFactory* ComponentFactory,
            EventType ComponentType::* event,
            MemberFunc memberFunc,
            ClassType* Instance = nullptr)
        {
            auto sdkcomponent = ComponentFactory->GetComponent<ComponentType>().get();
            if (sdkcomponent) {
                if constexpr (!std::is_same_v<ClassType, void>)
                    (sdkcomponent->*event).Unsubscribe({ Instance, memberFunc });
                else
                    (sdkcomponent->*event).Unsubscribe(*memberFunc);
            }
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
        virtual void Awake() {};
        virtual void Initialize() = 0;

        std::string m_name;
        bool m_Initialized;

        static const std::vector<ISdkComponent*> GetSdkComponents();

        static SdkComponentFactory s_SharedComponents;
        static SdkComponentFactory s_NdGameComponents;

        friend class SdkComponentFactory;
        friend class ISdkModule;
        friend void InitializeSdk(const SdkConfig* cfg);
        friend void RegisterSdkModule(ISdkModule* SdkModule);
        friend void UnregisterSdkModule(ISdkModule* SdkModule);
        friend void InitSharedComponents(SdkConfig& cfg);
        friend void InitNdGameComponents(SdkConfig& cfg);
    };

    class SdkComponentEx : public NdGameSdkException {
    public:
        enum ErrorCode {
            DependenciesFailed,
            PatternFailed,
            PatchFailed,
            SdkNotInitialized,
            NotAllowed
        };

        SdkComponentEx(const std::string& msg, ErrorCode errcode, bool critical = false)
            : m_errcode{ errcode }, m_critical{ critical }, NdGameSdkException(msg) {
        }

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
