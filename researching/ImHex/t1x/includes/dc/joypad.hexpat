#pragma once

import dc.dctypes;

namespace DC {

   // WIP
   namespace joypad {
        
        /*
        @ ScriptIds: *joypad-evade-on-release* | *joypad-adrenaline-hold-square* |#23785CAAD94AB956 | *joypad-l2-hold-x-evade* | #54975C1BD1D22399 | #69F055D6705E10A0 | 
        *joypad-r3-lock-on-toggle-evade* | *joypad-hold-for-repeat* | *joypad-sprint-square* | *joypad-adrenaline-square-x* | *joypad-cinematic* | #9F0A26F152F6F126 | 
        *joypad-swap-sticks* | #B03FEAADB8BC3F3B | #C26197132329B14A
        @ TYPE: action-scheme
        @ EntryPtr: ActionScheme 
        */
        namespace actionscheme {
            // @ Array
            struct inputKeyboard {
                u64 m_flag; // used if inputCommand.field_80 == true 
                u64 m_keycode;
            };
            
            // @ Array
            struct inputJoypad {
                u64 m_flag; // used if inputCommand.field_80 == true 
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
            
            // @ 793D1D63A0498239
            struct inputKeyboardScheme {
                u64 m_count;
                inputKeyboard *m_scheme[m_count] : u64;
            };
            
            // @ 674A8555C679C8ED
            struct inputJoypadScheme {
                u64 m_count;
                inputJoypad *m_scheme[m_count] : u64;
            };
            
            // @ 66D642190729CBE3
            struct inputMouseScheme {
                u64 m_count; // always 2?
                
                if(m_count == 2) {
                    inputMouse *m_scheme : u64;   
                } else {
                    std::print("Undefinded inputMouseScheme: {}", addressof(this));
                    u64 *m_scheme : u64; 
                }
                
            };
            
            // @ 5688596AABA88521
            struct inputScheme {
                u64 m_count;
                Input *m_scheme[m_count] : u64;
            };
            
            // @ FD17AE86396612F7
            struct inputCommand {            
                NullablePtr<inputJoypadScheme> m_Joypadinputs;
                NullablePtr<inputKeyboardScheme> m_Keyboardinputs;
                NullablePtr<inputKeyboardScheme> inputKeyboardButtons; // always nullptr in raw module
                NullablePtr<inputMouseScheme> m_Mouseinputs;
                NullablePtr<inputMouseScheme> inputMouseButtons; // always nullptr in raw module
                bool field_28;
                padding[7];
                NullablePtr<inputScheme> m_inputs; // Common for inputKeyboardButtons & inputMouseButtons & m_inputButtons?
                NullablePtr<inputJoypadScheme> m_inputButtons; // always nullptr in raw module
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
                map<StringId64,Array<inputCommand>> *m_scheme : u64;
            };   
        }

        /*
        @ ScriptId: *persistent-command-list*
        @ TYPE: #B18C294ADE7B782B
        @ EntryPtr: CommandList 
        */
        struct CommandList {
           u64 m_size;
           StringId64 *m_commands[m_size] : StringId64;
        };
        
        /*
        @ ScriptId: *mouse-default-settings*
        @ TYPE: #D6BCF8E23269E80E
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
        
   }
    
}