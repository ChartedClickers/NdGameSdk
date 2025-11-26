#pragma once

import dc.dctypes;

namespace DC {

    /*
      @ ScriptId: *modules*
      @ TYPE: module-info-array
      @ EntryPtr: ModuleInfoArray
    */
    namespace modules {

     // @ Array
     struct ModuleInfo {
        char *m_name[] : u64;
        StringId64 m_nameId;
        u64 m_ImageSize;
        SymbolArray *m_ModuleDependencies : u64;
        SymbolArray *m_ExportedSymbols : u64;
     };

    // @ module-info-array
    struct ModuleInfoArray {
       u64 m_ModuleCount;
       ModuleInfo *m_modules[m_ModuleCount] : u64;
    };

   }
}