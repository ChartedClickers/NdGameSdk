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

#include <NdGameSdk/shared/src/corelib/memory/memory.hpp>
#include <NdGameSdk/shared/src/gamelib/debug/nd-dev-menu.hpp>
#include <NdGameSdk/shared/src/ndlib/render/dev/debugdraw-common.hpp>
#include <NdGameSdk/shared/src/ndlib/render/frame-params.hpp>

namespace NdGameSdk::ndlib::render::dev { class DebugDrawCommon; }

namespace NdGameSdk {
    
    class NdGameSdk_API ISdkModule
    {
    public:
        struct BuildInfo {
            uint8_t major{ 0 }, minor{ 0 }, patch{ 0 };
            std::string buildStamp, gitBranch, buildMode;

            BuildInfo(std::string_view rawVersion, std::string stamp, std::string branch, std::string mode)
                : buildStamp(std::move(stamp)), gitBranch(std::move(branch)), buildMode(std::move(mode)) {
                auto p1 = rawVersion.find('.');
                auto p2 = rawVersion.find('.', p1 + 1);
                if (p1 == std::string_view::npos || p2 == std::string_view::npos)
                    throw std::invalid_argument("BuildInfo: version '" + std::string(rawVersion) + "' must be MAJOR.MINOR.PATCH");

                auto s1 = rawVersion.substr(0, p1);
                auto s2 = rawVersion.substr(p1 + 1, p2 - (p1 + 1));
                auto s3 = rawVersion.substr(p2 + 1);

                int i1 = std::stoi(std::string(s1));
                int i2 = std::stoi(std::string(s2));
                int i3 = std::stoi(std::string(s3));

                if (i1 < 0 || i1>255 || i2 < 0 || i2>255 || i3 < 0 || i3>255)
                    throw std::out_of_range("BuildInfo: version number out of [0,255]");

                major = static_cast<uint8_t>(i1);
                minor = static_cast<uint8_t>(i2);
                patch = static_cast<uint8_t>(i3);
            };

            // Packs into 0xMMmmpp00
            uint32_t toUInt() const noexcept;

            // "?.?.?"
            std::string versionString() const;

            // "?.?.? @{gitBranch} [{buildMode}] ({buildStamp})"
            std::string toString() const;
        };

        ~ISdkModule();
        std::string GetModuleName();
        std::string GetBuildInfoString() const;
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
        ISdkModule(std::string name, BuildInfo buildinfo, HMODULE module);
        std::shared_ptr<spdlog::logger> m_logger;
    private:
        virtual void OnModuleRegistered() = 0;
        virtual void OnGameInitialized(bool status) {};
        virtual void OnMemoryMapped(corelib::memory::Memory* Memory) {};
        virtual void DebugDraw(FrameParams* frame) {};
        virtual void OnAppendSdkDevMenu(gamelib::debug::NdDevMenu* NdDevMenu, gamelib::debug::NdDevMenu::AppendSdkSubMenusCallback AppendSdkDevMenu) {};

        static std::unordered_map<HMODULE, ISdkModule*>* GetSdkModules();

        SdkEvent<ISdkModule*> e_OnUnregister { true };
        bool m_registered { false };
        std::string m_name;
        BuildInfo m_build;
        HMODULE m_module;

        template <typename... Args>
        friend class SdkEvent;

        friend void RegisterSdkModule(ISdkModule* SdkModule);
        friend void UnregisterSdkModule(ISdkModule* SdkModule);
        friend class ndlib::render::dev::DebugDrawCommon;

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