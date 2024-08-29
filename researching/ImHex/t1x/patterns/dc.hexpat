import dc.dctypes;

import dc.modules;

namespace DC {
            
   struct Entry {
        StringId64 m_scriptId;
        StringId64 m_typeId;
     
    match (m_scriptId, m_typeId) {
        /* Base dc entry types */
        (_, Type::_float): float *m_entryPtr : u64;
        
        /* modules.bin */
        (ScriptId::modules, Type::module_info_array): modules::ModuleInfoArray *m_entryPtr : u64;
        /* joypad.bin */
        (_, Type::action_scheme): joypad::actionscheme::ActionScheme *m_entryPtr : u64;
        (ScriptId::persistent_command_list, Type::command_list): joypad::CommandList *m_entryPtr : u64;
        (ScriptId::mouse_default_settings, Type::mouse_settings): joypad::MouseSettings *m_entryPtr : u64;
        /* unknown.bin */
        (_,_): u64 *m_entryPtr : u64;
    }  
       
   };   
            
    struct Header {
        u32 m_magic;
        u32 m_versionNumber;
        u32 m_textSize;
        u32 unk;
        u32 unk1;
        u32 m_numEntries;
        Entry *m_pStartOfData[m_numEntries] : u64;
    };    
}

DC::Header dc_header_at_0x00 @ 0x00;