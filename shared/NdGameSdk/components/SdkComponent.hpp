#pragma once

#include <windows.h>
#include <filesystem>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <typeindex>
#include <deque>
#include <array>
#include <span>
#include <atomic>
#include <numeric>
#include <spdlog/spdlog.h>
#include <Utility/helper.hpp>
#include <Utility/assertion/assert.hpp>

#include <NdGameSdk/sdk.hpp>
#include <NdGameSdk/sdkconfig.hpp>
#include <NdGameSdk/sdkderived.hpp>
#include <NdGameSdk/sdkexception.hpp>
#include <NdGameSdk/components/SdkComponentFactory.hpp>
#include <NdGameSdk/components/event/SdkEvent.hpp>

namespace NdGameSdk::ndlib::render::dev { class DebugDrawCommon; }
namespace NdGameSdk::ndlib { class FrameParams; }

namespace NdGameSdk {

    class ISdkComponent;
    class ISdkSubComponent;
    template <typename... Args>
    class SdkEvent;

    class SdkComponentEx : public NdGameSdkException {
    public:
        enum ErrorCode {
            DependenciesFailed,
            PatternFailed,
            PatchFailed,
            SdkNotInitialized,
            InvalidInstance,
            NotAllowed,
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

    class ISdkComponent {
    public:
        virtual ~ISdkComponent() = default;

        ISdkComponent(ISdkComponent const&) = delete;
        ISdkComponent& operator=(ISdkComponent const&) = delete;
        ISdkComponent(ISdkComponent&&) = delete;
        ISdkComponent& operator=(ISdkComponent&&) = delete;

        virtual std::span<const std::type_index> Dependencies() const noexcept {
            static const std::array<std::type_index, 0> none{};
            return { none.data(), none.size() };
        }

        NdGameSdk_API std::string_view GetName() const;
        NdGameSdk_API bool IsInitialized() const;

        template <typename... SdkComponents>
        NdGameSdk_API static std::optional<std::string> CheckSdkComponents(const std::vector<ISdkComponent*>& componentList) {
            static_assert((SdkDerived::is_derived_from_ISdkComponent<SdkComponents>::value && ...),
                "All types must be derived from ISdkComponent");

            std::vector<std::string> missing;
            ([&] {
                bool found = std::any_of(componentList.begin(), componentList.end(),
                    [](ISdkComponent* c) { return c && typeid(*c) == typeid(SdkComponents); });
                if (!found)
                    missing.emplace_back(typeid(SdkComponents).name());
                }(), ...);

            if (!missing.empty())
                return std::optional<std::string>(std::accumulate(
                    std::next(missing.begin()), missing.end(), missing[0],
                    [](const std::string& a, const std::string& b) { return a + ", " + b; }
                ));
            return std::nullopt;
        }

        template<typename SubT>
        NdGameSdk_API SubT* GetSubComponent() {
            static_assert(SdkDerived::is_derived_from_ISdkSubComponent<SubT>::value, "SubT must derive from ISdkSubComponent");
            auto it = m_subcomponents.find(typeid(SubT));
            return (it != m_subcomponents.end())
                ? static_cast<SubT*>(it->second.get())
                : nullptr;
        }

        template <typename ComponentType, typename EventType, typename MemberFunc, typename ClassType = void>
        NdGameSdk_API static optional<ISdkAction> SubscribeSdkEvent(
            SdkComponentFactory* ComponentFactory,
            EventType ComponentType::* event,
            MemberFunc memberFunc,
            ClassType* Instance = nullptr,
            bool OneTimeInvoke = false)
        {
            auto sdkcomponent = ComponentFactory->GetComponent<ComponentType>();
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
            auto sdkcomponent = ComponentFactory->GetComponent<ComponentType>();
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

        void InitSubComponents();
        void InitSubComponentById(const std::type_index& id);

        template<typename... Deps>
        static std::span<const std::type_index> MakeDependencies() noexcept {
            static const std::array<std::type_index, sizeof...(Deps)> deps = {
                typeid(Deps)...
            };
            return { deps.data(), deps.size() };
        }

        template <typename DepT>
        DepT* GetDependencyComponent(SdkComponentFactory* factory) const {
            auto deps = this->Dependencies();
            bool found = std::find(deps.begin(), deps.end(), typeid(DepT)) != deps.end();
            always_assert(!found, std::format("Tried to get component '{}' in '{}' but not declared in SDK DEPENDENCIES!",
                typeid(DepT).name(), typeid(*this).name()).c_str());
            auto* dep = factory->GetComponent<DepT>();
            return dep;
        }

        template<typename SubT, typename... Args>
        SubT* AddSubComponent(Args&&... a)
        {
            static_assert(SdkDerived::is_derived_from_ISdkSubComponent<SubT>::value, "SubT must derive from ISdkSubComponent");
            auto sub = std::make_unique<SubT>(std::forward<Args>(a)...);
            sub->AttachOwnerComponent(this);
            SubT* rawPtr = sub.get();
            m_subcomponents[typeid(SubT)] = std::move(sub);
            return rawPtr;
        }

        template<typename SubT>
        SubT* InitSubComponent()
        {
            auto* ptr = GetSubComponent<SubT>();
            if (!ptr) return nullptr;
            InitSubComponentPtr(reinterpret_cast<ISdkSubComponent*>(ptr));
            return ptr;
        }

        template<typename... Subs>
        void InitSubComponentsOnly()
        {
            (InitSubComponent<Subs>(), ...);
        }

        template<typename CompT>
        static CompT* Instance() noexcept
        {
            static std::atomic<CompT*> p{ nullptr };
            auto* v = p.load(std::memory_order_acquire);
            if (!v) {
                if (auto* s = ISdkComponent::GetSharedComponents()->GetComponent<CompT>()) {
                    v = s;
                } else if (auto* n = ISdkComponent::GetNdGameComponents()->GetComponent<CompT>()) {
                    v = n;
                }
                if (v) p.store(v, std::memory_order_release);
            }
            return v;
        }

        template<typename T>
        static T& RequireInstance(bool requireInitialized = true) {
            auto* p = Instance<T>();
            if (!p) {
                throw SdkComponentEx{
                    std::string(typeid(T).name()) + " instance is null!",
                    SdkComponentEx::InvalidInstance
                };
            }
            if (requireInitialized && !p->IsInitialized()) {
                throw SdkComponentEx{
                    std::string(typeid(T).name()) + " is not initialized",
                    SdkComponentEx::NotAllowed
                };
            }
            return *p;
        }

    private:
        virtual void Awake() {};
        virtual void Initialize() = 0;
        virtual void DebugDraw(ndlib::FrameParams* frame) {};

        std::string m_name;
        bool m_Initialized;

        std::unordered_map<std::type_index, std::unique_ptr<ISdkSubComponent>> m_subcomponents;

        static const std::vector<ISdkComponent*>& GetSdkComponents();
        static void InitSubComponentPtr(ISdkSubComponent* sub);

        static SdkComponentFactory s_SharedComponents;
        static SdkComponentFactory s_NdGameComponents;

        friend class SdkComponentFactory;
        friend class ISdkModule;
        friend class ISdkSubComponent;
        friend class ndlib::render::dev::DebugDrawCommon;

        friend void InitializeSdk(const SdkConfig* cfg);
        friend void RegisterSdkModule(ISdkModule* SdkModule);
        friend void UnregisterSdkModule(ISdkModule* SdkModule);
        friend void InitSharedComponents();
        friend void InitNdGameComponents();
    };

#define SDK_DEPENDENCIES(...)                                                 \
std::span<const std::type_index> Dependencies() const noexcept override       \
{                                                                              \
    return MakeDependencies<__VA_ARGS__>();                                    \
}

}
