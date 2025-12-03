#include "settings.hpp"
#include "./NdGameSdk/shared/sharedpatterns.hpp"

namespace NdGameSdk::ndlib::settings {

    SettingsControl::SettingsControl() : ISdkComponent(TOSTRING(SettingsControl)) {}

    void SettingsControl::Initialize() {

        static std::once_flag Initialized;
        std::call_once(Initialized, [this] {
            spdlog::info("Initializing {} patterns...", GetName());

            Patterns::SdkPattern findpattern{};
            auto module = Utility::memory::get_executable();

            findpattern = Patterns::SettingsControl_s_SettingsControl;
			s_sSettingsControl = (GameSettingsControl*)Utility::ReadLEA32(module,
				findpattern.pattern, wstr(Patterns::SettingsControl_s_SettingsControl), findpattern.offset, 3, 7);

			findpattern = Patterns::SettingsControl_Init;
			auto SettingsControl_Init = (void*)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::SettingsControl_Init), findpattern.offset);

            if (!s_sSettingsControl || !SettingsControl_Init) {
                throw SdkComponentEx{ std::format("Failed to find {} addresses!", GetName()),
                    SdkComponentEx::ErrorCode::PatternFailed };
            }

			findpattern = Patterns::SettingsControl_NewSetting;
			SettingsControl_NewSetting = (SettingsControl_NewSetting_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::SettingsControl_NewSetting), findpattern.offset);

			findpattern = Patterns::SettingsControl_AddProcessSetting;
			SettingsControl_AddProcessSetting = (SettingsControl_AddProcessSetting_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::SettingsControl_AddProcessSetting), findpattern.offset);

			findpattern = Patterns::SettingsControl_AddTimedSetting;
			SettingsControl_AddTimedSetting = (SettingsControl_AddTimedSetting_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::SettingsControl_AddTimedSetting), findpattern.offset);

			if (!SettingsControl_NewSetting ||
                !SettingsControl_AddProcessSetting ||
                !SettingsControl_AddTimedSetting) {
				throw SdkComponentEx{ std::format("Failed to find {}:: game functions!", GetName()), SdkComponentEx::ErrorCode::PatternFailed };
			}

        });
    }

    GameSettingsControl::Setting* SettingsControl::NewSetting(
        StringId64 key, void* pValue, const void* pInitData, int valueSize, 
        void* pCallback, int param, void* pContextProcess, int inPriority) {
		always_assert(SettingsControl_NewSetting == nullptr, "SettingsControl::NewSetting is null!");
		return SettingsControl_NewSetting(
            s_sSettingsControl, key, pValue, pInitData, valueSize,
            pCallback, param, pContextProcess, inPriority);
    }

    void SettingsControl::AddProcessSetting(
        void* pValue, const void* pInitData, int valueSize, 
        void* pContextProcess, int priority, void* pCallback, int param) {
		always_assert(SettingsControl_AddProcessSetting == nullptr, "SettingsControl::AddProcessSetting is null!");
		SettingsControl_AddProcessSetting(
			s_sSettingsControl, pValue, pInitData, valueSize,
			pContextProcess, priority, pCallback, param);
    }

    GameSettingsControl::Setting* SettingsControl::AddTimedSetting(
        StringId64 key, void* pValue, const void* pInitData, int valueSize, 
        const int* pDurationFrames, int priority, void* pCallback, int param) {
		always_assert(SettingsControl_AddTimedSetting == nullptr, "SettingsControl::AddTimedSetting is null!");
		return SettingsControl_AddTimedSetting(
			s_sSettingsControl, key, pValue, pInitData, valueSize,
			pDurationFrames, priority, pCallback, param);
    }

    GameSettingsControl::SettingFlags GameSettingsControl::Setting::Flags() const {
        return static_cast<SettingFlags>(this->Get()->m_flags);
    }

    void* GameSettingsControl::Setting::Value() const {
        return this->Get()->m_valuePtr;
    }

    StringId64 GameSettingsControl::Setting::Key() const {
        return this->Get()->m_key;
    }

    uint64_t GameSettingsControl::Setting::ExpireFrame() const {
        return this->Get()->m_expireFrame;
    }

    void* GameSettingsControl::Setting::DataPtr() {
        return this->Get()->m_pData;
    }

    uint32_t GameSettingsControl::MaxNumSettings() {
        return this->Get()->m_maxNumSettings;
    }

    uint32_t GameSettingsControl::NumUsedBuckets() {
		return this->Get()->m_numUsedBuckets;
    }

    GameSettingsControl* SettingsControl::s_sSettingsControl = nullptr;

}




