#pragma once

import dc.dctypes;

namespace DC {
    
    /*
      @ ScriptId: *modules*
      @ TYPE: module-info-array
      @ EntryPtr: ModuleInfoArray 
    */
    namespace modules {

     // @ symbol-array
     struct ModuleUnkCollection {
        u64 m_num;
        StringId64 *m_pArray[m_num] : StringId64;
     };   
     
     // @ symbol-array
     struct ModuleCollection {
        u64 m_numModules;
        StringId64 *m_pArray[m_numModules] : StringId64;
     };   
     
     // @ Array
     struct ModuleInfo {
        char *m_name[] : u64;
        StringId64 m_hash;
        u64 m_size;
        ModuleCollection *m_ModuleCollection : u64;
        ModuleUnkCollection *m_unkCollection : u64;
     };
     
    // @ module-info-array
    struct ModuleInfoArray {
       u64 m_numModules;
       ModuleInfo *m_modules[m_numModules] : u64;
    };   
       
   }
}