#pragma once

#include <NdGameSdk/sdk.hpp>
#include <NdGameSdk/components/SdkComponentFactory.hpp>
#include <NdGameSdk/components/event/SdkEvent.hpp>

#include <string_view>
#include <type_traits>
#include <optional>
#include <atomic>

namespace NdGameSdk {

    class ISdkComponent;
    class SdkComponentFactory;
    template <typename... Args>
    class SdkEvent;

    class ISdkSubComponent {
    public:
        virtual ~ISdkSubComponent() = default;

        NdGameSdk_API std::string_view GetName() const;
        NdGameSdk_API bool IsInitialized() const;

        template<typename CompT>
        CompT* GetParentComponent() const noexcept {
            static_assert(std::is_base_of_v<ISdkComponent, CompT>,
                          "CompT must derive from ISdkComponent");
            return static_cast<CompT*>(m_parent);
        }

        template <typename OwnerComponent, typename SubComponentType, typename EventType, typename MemberFunc, typename ClassType = void>
        NdGameSdk_API static std::optional<ISdkAction> SubscribeSdkEvent(
            SdkComponentFactory* ComponentFactory,
            EventType SubComponentType::* event,
            MemberFunc memberFunc,
            ClassType* Instance = nullptr,
            bool OneTimeInvoke = false)
        {
            auto owner = ComponentFactory->GetComponent<OwnerComponent>();
            if (owner) {
                auto sub = owner->template GetSubComponent<SubComponentType>();
                if (sub) {
                    if constexpr (!std::is_same_v<ClassType, void>)
                        return (sub->*event).Subscribe(Instance, memberFunc, OneTimeInvoke);
                    else
                        return (sub->*event).Subscribe(*memberFunc, OneTimeInvoke);
                }
            }
            return {};
        }

        template <typename OwnerComponent, typename SubComponentType, typename EventType, typename MemberFunc, typename ClassType = void>
        NdGameSdk_API static void UnsubscribeSdkEvent(
            SdkComponentFactory* ComponentFactory,
            EventType SubComponentType::* event,
            MemberFunc memberFunc,
            ClassType* Instance = nullptr)
        {
            auto owner = ComponentFactory->GetComponent<OwnerComponent>();
            if (owner) {
                auto sub = owner->template GetSubComponent<SubComponentType>();
                if (sub) {
                    if constexpr (!std::is_same_v<ClassType, void>)
                        (sub->*event).Unsubscribe({ Instance, memberFunc });
                    else
                        (sub->*event).Unsubscribe(*memberFunc);
                }
            }
        }

    protected:
        ISdkSubComponent(std::string_view name);

        template <typename... Args>
        void InvokeSdkEvent(SdkEvent<Args...>& event, Args... args) {
            event.Invoke(args...);
        }

        template<typename CompT, typename SubCompT>
        static SubCompT* Instance()
        {
            static std::atomic<SubCompT*> p{ nullptr };
            auto* v = p.load(std::memory_order_acquire);
            if (!v) {
                if (auto* owner = CompT::template Instance<CompT>()) {
                    v = owner->template GetSubComponent<SubCompT>();
                    if (v) p.store(v, std::memory_order_release);
                }
            }
            return v;
        }

        NdGameSdk_API static SdkComponentFactory* GetSharedComponents();
        NdGameSdk_API static SdkComponentFactory* GetNdGameComponents();
       
    private:
        virtual void Init() = 0;
        void AttachOwnerComponent(ISdkComponent* parent);

        std::string m_name;
        
        ISdkComponent* m_parent{nullptr};
        bool m_Initialized{false};

        friend class ISdkComponent;
    };

}
