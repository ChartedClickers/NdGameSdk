#pragma once

#include <windows.h>
#include <string>
#include <spdlog/spdlog.h>

#include <Utility/memory/Module.hpp>

#include <NdGameSdk/sdk.hpp>
#include <NdGameSdk/sdkconfig.hpp>
#include <NdGameSdk/sdkderived.hpp>
#include <NdGameSdk/sdkexception.hpp>

#include <NdGameSdk/components/SdkComponent.hpp>
#include <NdGameSdk/components/event/SdkEvent.hpp>

namespace NdGameSdk {

    class NdGameSdk_API ISdkModule
    {
    public:
        ~ISdkModule();
        std::string GetModuleName();
        HMODULE GetModule();
        bool IsRegistered();

        template <typename SdkComponent>
        std::shared_ptr<SdkComponent> GetSharedSdkComponent() {
            auto SharedComponents = ISdkComponent::GetSharedComponents();
            return SharedComponents->GetComponent<SdkComponent>();
        };

        template <typename SdkComponent>
        std::shared_ptr<SdkComponent> GetNdGameSdkComponent() {
            auto SharedComponents = ISdkComponent::GetNdGameComponents();
            return SharedComponents->GetComponent<SdkComponent>();
        };

        static ISdkModule* GetRegisteredModule(HMODULE ActionModule);
    protected:
        ISdkModule(std::string name);
        std::shared_ptr<spdlog::logger> m_logger;
    private:
        virtual void OnModuleRegistered() = 0;
        virtual void OnGameInitialized(bool status) {};
        virtual void OnMemoryMapped() {};

        static std::unordered_map<HMODULE, ISdkModule*>* GetSdkModules();

        SdkEvent<ISdkModule*> e_OnUnregister { true };
        bool m_registered { false };
        std::string m_name;
        HMODULE m_module;

        template <typename... Args>
        friend class SdkEvent;

        friend void RegisterSdkModule(ISdkModule* SdkModule);
        friend void UnregisterSdkModule(ISdkModule* SdkModule);

        static std::unordered_map<HMODULE, ISdkModule*> s_SdkModules;
    };

    class NdGameSdk_API SdkModuleException : public NdGameSdkException {
    public:
        enum ErrorCode {
            NotRegistered,
            AlreadyRegistered
        };

        SdkModuleException(const std::string& msg, ErrorCode errcode) : m_errcode { errcode }, NdGameSdkException(msg) {}

        const ErrorCode ErrCode() const noexcept {
            return m_errcode;
        }

    private:
        ErrorCode m_errcode;
    };
    
}