#pragma once

#include <windows.h>
#include <string_view>
#include <vector>
#include <unordered_map>
#include <memory>

#include "Utils/config.hpp"
#include "NdModClient.hpp"

class NdMod
{
 public:
    NdMod() {};
    NdMod(bool pconfig) : m_pconfig{ pconfig } {}
    virtual ~NdMod() = default;

    virtual std::string_view GetName() const { return "Unknown NdMod"; }
    bool IsInitialized() const { return m_Initialized; }

protected:
    template <typename NdModComponent>
    std::shared_ptr<NdModComponent> GetNdModComponent() {
        return GetDependentComponent<NdModComponent>(
            g_ndmodclient->GetNdMods()->GetNdModComponent<NdModComponent>()
        );
    };

    template <typename SdkComponent>
    SdkComponent* GetSharedSdkComponent() {
        return GetDependentComponent<SdkComponent>(
            g_ndmodclient->GetSharedSdkComponent<SdkComponent>()
        );
    };

    template <typename SdkComponent>
    SdkComponent* GetNdGameSdkComponent() {
        return GetDependentComponent<SdkComponent>(
            g_ndmodclient->GetNdGameSdkComponent<SdkComponent>()
        );
    };

private:
    friend class NdMods;

    virtual void OnNdModinitialize() = 0;
    virtual void OnConfigLoad(const Utils::Config& cfg) {}
    virtual void OnConfigSave(Utils::Config& cfg) {}

    template <typename DependentComponent>
    DependentComponent* GetDependentComponent(DependentComponent* component) {
        if (component && component->IsInitialized())
            return component;

        throw NdModComponentEx(
            std::format("Dependent component {} is not available!",
                typeid(DependentComponent).name()),
            NdModComponentEx::DependenciesFailed
        );
        
    };

    bool m_Initialized{};
    bool m_pconfig = false;
};
