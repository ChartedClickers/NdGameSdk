#pragma once

import dc.dctypes;

namespace DC {

   namespace joypad {

        /*
        @ ScriptIds: *joypad-evade-on-release* | *joypad-adrenaline-hold-square* | *joypad-bond-L4-R4-sprint-dodge-jump* | *joypad-l2-hold-x-evade* | *joypad-dmatts-test* | *joypad-bond-L4-R4-weapon-cross* |
        *joypad-r3-lock-on-toggle-evade* | *joypad-hold-for-repeat* | *joypad-sprint-square* | *joypad-adrenaline-square-x* | *joypad-cinematic* | *joypad-bond-L4-R4-sprint-dodge-melee* |
        *joypad-swap-sticks* | *joypad-efm-mirror* | *joypad-bond-L4-R4-sprint-crouch*
        @ TYPE: action-scheme
        @ EntryPtr: ActionScheme
        */
        namespace actionscheme {
            // @ Array
            struct inputKeyboard {
                u64 m_flag; // used if ActionCommand.field_80 == true
                u64 m_keycode;
            };

            // @ Array
            struct inputJoypad {
                u64 m_flag; // used if ActionCommand.field_80 == true
                u64 m_iBtn;
            };

            // @ Array
            struct inputMouse {
                u64 m_flag;
                u64 m_keycode;
                u64 m_keycode2;
            };

            // @ Array
            struct Input {
                u64 m_flag;
                StringId64 m_hash;
            };

            // @ symbol-array
            struct InputCollection {
                u64 m_numInputs;
                StringId64 *m_pArray[m_numInputs] : StringId64;
            };

            // @ action-keyboard-button-list
            struct ActionKeyboardButtonList {
                u64 m_count;
                inputKeyboard *m_scheme[m_count] : u64;
            };

            // @ action-button-list
            struct ActionButtonList {
                u64 m_count;
                inputJoypad *m_scheme[m_count] : u64;
            };

            // @ action-mouse-button-list
            struct ActionMouseButtonList {
                u64 m_count; // always 2?

                if(m_count == 2) {
                    inputMouse *m_scheme : u64;
                } else {
                    std::warning("Undefinded ActionMouseButtonList: {}", addressof(this));
                    u64 *m_scheme : u64;
                }

            };

            // @ action-input-list
            struct ActionInputList {
                u64 m_count;
                Input *m_scheme[m_count] : u64;
            };

            // @ action-command
            struct ActionCommand {
                NullablePtr<ActionButtonList> m_Joypadinputs;
                NullablePtr<ActionKeyboardButtonList> m_Keyboardinputs;
                NullablePtr<ActionKeyboardButtonList> inputKeyboardButtons; // always nullptr in raw module
                NullablePtr<ActionMouseButtonList> m_Mouseinputs;
                NullablePtr<ActionMouseButtonList> inputMouseButtons; // always nullptr in raw module
                bool field_28;
                padding[0x7];
                NullablePtr<ActionInputList> m_inputs; // Common for inputKeyboardButtons & inputMouseButtons & m_inputButtons?
                NullablePtr<ActionButtonList> m_inputButtons; // always nullptr in raw module
                u32 field_40;
                u32 field_44;
                u64 field_48; // always 000000003DCCCCCD?
                StringId64 m_InputHash; // Example: *gesture-tap-left-stick-up-wide* (Manually allocated in the game)
                u64 field_58;
                NullablePtr<InputCollection>  m_InputCollection; // i guess
                u64 field_68;
                bool field_70; // something for field_68
                padding[0xf];
                bool field_80;
                bool field_81; // inputs allocated??
                padding[0x6];
                NullableCharPtr field_88;
            };

            // @ action-scheme
            struct ActionScheme {
                padding[0x8]; // Not used but a pointer must be specified
                map<StringId64,Array<ActionCommand>> *m_scheme : u64;
            };
        }

        /*
        @ ScriptId: *persistent-command-list*
        @ TYPE: #joypad-persistent-command-list
        @ EntryPtr: PersistentCommandList
        */
        struct PersistentCommandList {
           u64 m_size;
           StringId64 *m_commands[m_size] : StringId64;
        };

        /*
        @ ScriptId: *mouse-default-settings*
        @ TYPE: mouse-default-settings
        @ EntryPtr: MouseSettings
        */
        struct MouseSettings {
            u32 global_sensitivity;
            u32 aim_sensitivity_x;
            u32 aim_sensitivity_y;
            u32 look_sensitivity_x;
            u32 look_sensitivity_y;
            u32 snipe_sensitivity_x;
            u32 snipe_sensitivity_y;
            u32 acceleration_x;
            u32 acceleration_y;
            bool invert_x;
            bool invert_y;
            bool field_26;
            bool use_raw_input;
            padding[0x18];
        };

        /*
        @ ScriptId: *analog-stick-icon-paths*
        @ TYPE: Array
        @ EntryPtr: FixedSizeArray<AnalogStickIconPath>
        */
        struct AnalogStickIconPath {
            char *m_Path[] : u64;
            char *m_Path2[] : u64;
            StringId64 m_hash;
        };

        /*
        @ ScriptId: *action-map*
        @ TYPE: action-collection
        @ EntryPtr: ActionCollection
        */
        namespace actionmap {

            // @ Array
            struct ActionDefinition {
                u64 field_0;
                u64 field_8;
                u64 field_10;
            };

            // @ action-sets
            struct ActionCollections {
                u64 m_size;
                ActionDefinition *field_8[m_size] : u64;
            };

            // @ action-def
            struct InputDefinition {
                u64 field_0;
                u64 field_8;
                u64 field_10;
                u64 field_18;
                StringId64 field_20;
                StringId64 field_28;
                u64 field_30;
                StringId64 field_38;
            };

            // @ action-collection
            struct ActionCollection {
                map<StringId64,Array<InputDefinition>> *m_InputDef: u64;
                StringId64 *field_8[m_InputDef.m_size] : StringId64;
                ActionCollections *field_10: u64;
            };
        }

        /*
        @ ScriptId: *joypad-additional-presets*
        @ TYPE: array*
        @ EntryPtr: FixedSizeArray<Array<AdditionalPresets>>
        */
        namespace presets  {

            // @ #??????????????????
            struct Preset {
                StringId64 field_0;
                u64 field_8;
                u32 field_10;
                u32 field_14;
                u16 field_18;
                u32 field_1a;
                padding[2];
            };

            // @ action-scheme-preset
            struct AdditionalPresets {
                u64 field_0;
                StringId64 field_8;
                StringId64 field_10;
                u64 field_18;
                $ += 0x8;
                u32 m_count;
                $ -= 0xc;
                Preset *m_presets[m_count] : u64;
                $ += 0x8;
                u64 field_30;
            };
        }

   }

}