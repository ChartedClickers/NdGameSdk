#pragma once
#include <NdGameSdk/components/SdkRegenny.hpp>
#include <NdGameSdk/sdkstringid.hpp>
namespace regenny::shared::ndlib::debug {
#pragma pack(push, 1)
struct DMENU {
    enum Message : uint32_t {
        OnOpen = 0,
        OnClose = 1,
        OnUpdate = 3,
        OnExecute = 5,
        OnReadConfig = 7,
        OnSaveConfig = 8,
        OnFocusOut = 16,
    };

    struct Component {
        struct VTable {
            private: char pad_0[0xb0]; public:
        }; // Size: 0xb0

        void* vftable; // 0x0
        void* UnkString; // 0x8
        // Metadata: utf8*
        char m_name[32]; // 0x10
        // Metadata: utf8*
        char* m_pname; // 0x30
        regenny::shared::ndlib::debug::DMENU::Component* m_ParentComponent; // 0x38
        regenny::shared::ndlib::debug::DMENU::Component* m_NextDMenuComponent; // 0x40
        uint32_t m_MenuLeftPad; // 0x48
        uint32_t m_MenuWidth; // 0x4c
        uint64_t m_ItemLeftPad; // 0x50
        uint64_t Unk2; // 0x58
        uint64_t m_data; // 0x60
        uint32_t m_color; // 0x68
        uint32_t m_selectcolor; // 0x6c
        uint32_t m_editedcolor; // 0x70
        bool m_Islinked; // 0x74
        private: char pad_75[0x3]; public:
        void* m_lazyinitcallback; // 0x78
        // Metadata: utf8*
        char* m_pDescription; // 0x80
        bool m_atsign; // 0x88
        private: char pad_89[0x7]; public:
        regenny::shared::ndlib::debug::DMENU::Component* m_MenuGroup; // 0x90
        private: char pad_98[0x1]; public:
        bool m_isfavorite; // 0x99
        private: char pad_9a[0x6]; public:
        int m_PagePointer; // 0xa0
        int m_MaxPagePointers; // 0xa4
        uint64_t m_ExtraArg; // 0xa8
    }; // Size: 0xb0

    struct Menu : public Component {
        regenny::shared::ndlib::debug::DMENU::Component* m_Item; // 0xb0
        private: char pad_b8[0x4]; public:
        bool m_isActive; // 0xbc
        uint64_t m_pad; // 0xbd
        private: char pad_c5[0x7]; public:
        int m_MaxDisplayItems; // 0xcc
        uint64_t Unk[2]; // 0xd0
    }; // Size: 0xe0

    struct MenuGroup : public Component {
        regenny::shared::ndlib::debug::DMENU::Menu* m_RootMenu; // 0xb0
        private: char pad_b8[0x8]; public:
        bool m_IsDisplayed; // 0xc0
        bool m_Rendering; // 0xc1
        uint16_t Unk[3]; // 0xc2
        uint64_t Unk20[77]; // 0xc8
    }; // Size: 0x330

    struct KeyBoard : public Component {
        bool m_isEditing; // 0xb0
        bool m_needsUpdate; // 0xb1
        bool m_isDirty; // 0xb2
        bool m_isFrameActive; // 0xb3
        private: char pad_b4[0x4]; public:
        uint64_t m_cursorIndex; // 0xb8
        uint64_t m_lastKey; // 0xc0
        private: char pad_c8[0x10]; public:
        // Metadata: utf8*
        char m_inputBuffer[1024]; // 0xd8
        // Metadata: utf8*
        char m_displayBuffer[1024]; // 0x4d8
        // Metadata: utf8*
        char* m_inputBufferPtr; // 0x8d8
        uint64_t m_maxInputLength; // 0x8e0
    }; // Size: 0x8e8

    struct Item : public Component {
        struct VTable0 : public regenny::shared::ndlib::debug::DMENU::Component::VTable {
        }; // Size: 0xb0

        void* m_callbackFunct; // 0xb0
    }; // Size: 0xb8

    struct ItemSubmenu : public Item {
        regenny::shared::ndlib::debug::DMENU::Menu* m_pHeader; // 0xb8
        uint64_t Unk[1]; // 0xc0
    }; // Size: 0xc8

    struct ItemBool : public Item {
        bool m_status; // 0xb8
        bool m_pad[7]; // 0xb9
    }; // Size: 0xc0

    struct ItemDecimal : public Item {
        uint64_t* m_format; // 0xb8
        void* m_HandlerFunc; // 0xc0
        // Metadata: i64
        uint64_t m_DisplayValue; // 0xc8
        // Metadata: i64
        uint64_t UnkDouble; // 0xd0
        private: char pad_d8[0x8]; public:
        // Metadata: i64
        uint64_t m_MinValue; // 0xe0
        // Metadata: i64
        uint64_t m_MaxValue; // 0xe8
        // Metadata: i64
        uint64_t m_StepValue; // 0xf0
        // Metadata: i64
        uint64_t m_DoubleStepValue; // 0xf8
        private: char pad_100[0x40]; public:
        // Metadata: utf8*
        char m_StringDisplayValue[32]; // 0x140
        uint64_t Unk[4]; // 0x160
    }; // Size: 0x180

    struct ItemFloat : public Item {
        uint64_t* m_format; // 0xb8
        void* m_HandlerFunc; // 0xc0
        float m_DisplayValue; // 0xc8
        float UnkFloat; // 0xcc
        private: char pad_d0[0x4]; public:
        float m_MinValue; // 0xd4
        float m_MaxValue; // 0xd8
        float m_StepValue; // 0xdc
        float m_DoubleStepValue; // 0xe0
        private: char pad_e4[0x3f]; public:
        // Metadata: utf8*
        char m_StringDisplayValue[32]; // 0x123
        char Unk[29]; // 0x143
    }; // Size: 0x160

    struct ItemFunction : public Item {
        void* unkData; // 0xb8
        private: char pad_c0[0x1]; public:
        bool m_isActive; // 0xc1
        bool m_pad[6]; // 0xc2
    }; // Size: 0xc8

    struct ItemSelection : public Item {
        void* UnkData; // 0xb8
        void* m_callbackFormat; // 0xc0
        uint64_t Unk2[3]; // 0xc8
        private: char pad_e0[0x8]; public:
        void* m_SelectionStruct; // 0xe8
    }; // Size: 0xf0

    struct ItemSubText : public Item {
    }; // Size: 0xb8

    struct String : public Component {
    }; // Size: 0xb0

    struct ItemPlaceHolder : public Component {
        // Metadata: utf8*
        char m_placeholder[1024]; // 0xb0
    }; // Size: 0x4b0

    struct ItemLine : public Component {
    }; // Size: 0xb0

    void* vftable; // 0x0
    private: char pad_8[0x8]; public:
    bool m_Text2DropShadows; // 0x10
    bool m_PauseDuringMenus; // 0x11
    bool m_PauseDuringMenusMP; // 0x12
    bool m_Pauseonexit; // 0x13
    bool m_ShowPausedIndicator; // 0x14
    bool UnkBool; // 0x15
    bool m_SquareButtontoBackOutofMenus; // 0x16
    bool m_ChordtoSave; // 0x17
    bool m_AlignMenusRight; // 0x18
    private: char pad_19[0x3]; public:
    int m_Rightmargin; // 0x1c
    // Metadata: f32
    float m_MenuAlpha; // 0x20
    // Metadata: f32
    float m_MenuScale; // 0x24
    private: char pad_28[0x39]; public:
    bool m_Pause; // 0x61
    private: char pad_62[0xe]; public:
    // Metadata: u64
    MenuGroup* m_CurrentMenu; // 0x70
    MenuGroup* m_QuickMenu; // 0x78
    // Metadata: u64
    MenuGroup* m_DevMenu; // 0x80
    // Metadata: u64
    MenuGroup* m_FavoritesMenu; // 0x88
    uint64_t Unk2[188]; // 0x90
}; // Size: 0x670
#pragma pack(pop)
}
