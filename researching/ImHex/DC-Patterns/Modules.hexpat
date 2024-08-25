import std.io; 
import std.mem; 
import std.math; 

namespace DC {
     
     // symbol-array
     struct ModuleUnkCollection {
        u64 m_num;
        u64 m_pArray; // ARRAY
     };   
     
     // symbol-array
     struct ModuleCollection {
        u64 m_numModules;
        u64 m_pArray; // ARRAY
     };   
     
     struct ModuleInfo {
        u64 m_name; // const char*
        u64 m_hash;
        u64 m_size;
        u64 m_pCollection; // ModuleCollection
        u64 m_unkCollection; // UnkCollection
     };   
     
    struct ModuleInfoArray {
       u32 m_numModules;
       u64 m_modules; // array
     };   
    
    struct Entry {
        u64 m_scriptId;
        u64 m_typeId;
        u64 m_entryPtr;
     };   
            
    struct Header {
        u32 m_magic;
        u32 m_versionNumber;
        u32 m_textSize;
        u32 unk;
        u32 unk1;
        u32 m_numEntries;
        u64 m_pStartOfData;
    };
    
    
}

DC::Header dc_header_at_0x00 @ 0x00;
DC::Entry dc_entry_at_0x28[dc_header_at_0x00.m_numEntries] @ 0x28;
DC::ModuleInfoArray dc_moduleinfoarray_at_0x48 @ 0x48;
DC::ModuleInfo dc_moduleinfo_at_0x60[dc_moduleinfoarray_at_0x48.m_numModules] @ 0x60;