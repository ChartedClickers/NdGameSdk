#pragma once

#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/components/SdkComponent.hpp"

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/ndlib/settings/SettingsControl.hpp>
#elif defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/ndlib/settings/SettingsControl.hpp>
#endif

#include <Utility/helper.hpp>
#include <Utility/function_ptr.hpp>
#include <type_traits>

namespace regenny::shared::ndlib::settings {
    using SettingFlags = SettingsControl::SettingFlags;

    constexpr SettingFlags operator|(SettingFlags a, SettingFlags b) noexcept {
        using U = std::underlying_type_t<SettingFlags>;
        return static_cast<SettingFlags>(static_cast<U>(a) | static_cast<U>(b));
    }

    constexpr SettingFlags operator&(SettingFlags a, SettingFlags b) noexcept {
        using U = std::underlying_type_t<SettingFlags>;
        return static_cast<SettingFlags>(static_cast<U>(a) & static_cast<U>(b));
    }

    constexpr SettingFlags operator~(SettingFlags a) noexcept {
        using U = std::underlying_type_t<SettingFlags>;
        return static_cast<SettingFlags>(~static_cast<U>(a));
    }

    inline SettingFlags& operator|=(SettingFlags& a, SettingFlags b) noexcept { a = a | b; return a; }
    inline SettingFlags& operator&=(SettingFlags& a, SettingFlags b) noexcept { a = a & b; return a; }
}

namespace NdGameSdk::ndlib::settings {

	/* Extern classes */
    class NdGameSdk_API GameSettingsControl : public ISdkRegenny<regenny::shared::ndlib::settings::SettingsControl> {
    public:
        using SettingFlags= regenny::shared::ndlib::settings::SettingsControl::SettingFlags;

        class Setting : public ISdkRegenny<regenny::shared::ndlib::settings::SettingsControl::Setting> {
        public:
            SettingFlags Flags() const;

            void* Value() const;
            StringId64 Key() const;

            uint64_t ExpireFrame() const;
            void* DataPtr();
        };

        class HashNode : public ISdkRegenny<regenny::shared::ndlib::settings::SettingsControl::HashNode> {
        public:
            HashNode* Next() const { return reinterpret_cast<HashNode*>(this->Get()->m_pNext); }
            HashNode* Prev() const { return reinterpret_cast<HashNode*>(this->Get()->m_pPrev); }
            Setting* First()const { return reinterpret_cast<Setting*>(this->Get()->m_pFirst); }
            Setting* Last() const { return reinterpret_cast<Setting*>(this->Get()->m_pLast); }
        };

        class HashIt : public ISdkRegenny<regenny::shared::ndlib::settings::SettingsControl::HashIt> {};

        class SettingsHash : public ISdkRegenny<regenny::shared::ndlib::settings::SettingsControl::SettingsHash> {
        public:
            uint32_t RoundedCap() const { return this->Get()->m_roundedCap; }
            uint64_t Count() const { return this->Get()->m_count; }
            HashNode** Table() { return reinterpret_cast<HashNode**>(this->Get()->m_table); }
            HashNode* Head() { return reinterpret_cast<HashNode*>(this->Get()->m_head); }
        };

        uint32_t MaxNumSettings();
        uint32_t NumUsedBuckets();
        uint32_t HashRoundedCap();
        uint64_t HashCount();
    };

    class SettingsControl final : public ISdkComponent {
    public:
        SettingsControl();

		GameSettingsControl::Setting* NewSetting(
			StringId64 key, void* pValue,
			const void* pInitData, int valueSize,
			void* pCallback, int param = 0x3f800000, void* pContextProcess = nullptr,
			int inPriority = 0);

		void AddProcessSetting(
			void* pValue, const void* pInitData,
			int valueSize, void* pContextProcess = nullptr,
			int priority = kScriptPriorityBias,
			void* pCallback = nullptr, int param = 0x3f800000);

		GameSettingsControl::Setting* AddTimedSetting(
			StringId64 key, void* pValue,
			const void* pInitData, int valueSize,
			const int* pDurationFrames, int priority = kScriptPriorityBias,
			void* pCallback = nullptr, int param = 0x3f800000);

    private:
        void Initialize() override;
        
        InlineHook m_SettingsControlInitHook{};

        /*Extern variables*/
        static GameSettingsControl* s_sSettingsControl;
        
        MEMBER_FUNCTION_PTR(GameSettingsControl::Setting*, SettingsControl_NewSetting,
            GameSettingsControl* pCtrl, StringId64 key, void* pValue,
            const void* pInitData, int valueSize,
            void* pCallback, int param, void* pContextProcess,
            int inPriority);

        MEMBER_FUNCTION_PTR(void, SettingsControl_AddProcessSetting,
            GameSettingsControl* pCtrl, void* pValue, const void* pInitData,
            int valueSize, void* pContextProcess,
            int priority, void* pCallback, int param);

        MEMBER_FUNCTION_PTR(GameSettingsControl::Setting*, SettingsControl_AddTimedSetting,
            GameSettingsControl* pCtrl, StringId64 key, void* pValue,
            const void* pInitData, int valueSize,
            const int* pDurationFrames, int priority,
            void* pCallback, int param);

        static constexpr int kBuckets = 0x4B;
        static constexpr int kSettingSize = 0xA0;
        static constexpr int kHashNodeSize = 0x20;
        static constexpr int kInlineDataMax = 0x44;
        static constexpr int kUltimateMaxSettingPriority = 0x791D;
        static constexpr int kScriptPriorityBias = 0x791A;
    };

	static_assert(sizeof(GameSettingsControl) == 0x9a70, "Size of GameSettingsControl is not correct.");
	static_assert(sizeof(GameSettingsControl::Setting) == 0xA0, "Size of GameSettingsControl::Setting is not correct.");

}

