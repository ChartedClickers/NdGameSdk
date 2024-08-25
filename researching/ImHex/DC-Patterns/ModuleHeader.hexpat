import std.io; 
import std.mem; 
import std.math; 

namespace DC {
    
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