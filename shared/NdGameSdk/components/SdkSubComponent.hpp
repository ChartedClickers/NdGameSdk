#pragma once

#include <NdGameSdk/sdk.hpp>
#include <string_view>

namespace NdGameSdk {

    class ISdkSubComponent {
    public:
        virtual ~ISdkSubComponent() = default;
        NdGameSdk_API std::string_view GetName() const;
        NdGameSdk_API bool IsInitialized() const;
    protected:
        ISdkSubComponent(std::string name);
    private:
        virtual void Init() = 0;

        std::string m_name;
        bool m_Initialized;
        friend ISdkComponent;
    };

}
