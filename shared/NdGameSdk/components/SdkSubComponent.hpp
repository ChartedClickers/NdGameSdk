#pragma once

#include <NdGameSdk/sdk.hpp>
#include <string_view>
#include <type_traits>

namespace NdGameSdk {

    class ISdkComponent;
    class SdkComponentFactory;

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

    protected:
        ISdkSubComponent(std::string_view name);

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
