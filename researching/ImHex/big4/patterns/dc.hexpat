#pragma loop_limit 500000

import dc.dctypes;

namespace DC {
         
   struct Entry {
        StringId32 m_scriptId;
        StringId32 m_typeId;
     
    match (m_scriptId, m_typeId) {
        /* unknown.bin */
        (_,_): u64 *m_entryPtr : u64;

        /* Base dc entry types */
        (_, Type::_float): float *m_entryPtr : u64;
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

DC::Header dc_header @ 0x00;
namespace Script {
    
    struct BitReader {
        u64 m_FixUpTable;
        u32 m_bitIndex;
        u32 m_byteIndex;
        u32 m_size;
        padding[4];
    };

    fn ReadBit(ref BitReader bitdata) {
         std::assert(bitdata.m_byteIndex < bitdata.m_size, "m_byteIndex < m_size");

         u64 byteIndex = bitdata.m_byteIndex;
         u8 bitIndex = bitdata.m_bitIndex;
         
         u8 CheckByteIndex_value @ (byteIndex + bitdata.m_FixUpTable);
         u8 CheckByteIndex = CheckByteIndex_value;    
         
         bitdata.m_bitIndex = (bitdata.m_bitIndex + 1);
         CheckByteIndex = (CheckByteIndex >> bitIndex);
         
         if(bitdata.m_bitIndex == 8) {
            bitdata.m_bitIndex = 0;
            bitdata.m_byteIndex = (byteIndex + 1);
         }

         return CheckByteIndex & 1;        
    };    
    
    fn Login(ref DC::Header pHeader, u64 pFile, u64 lowerBound, u64 upperBound) {     
        
        const u32 MagicNumber = 0x44433030;
        const u32 VersionNumber = 1;

        std::assert(pHeader.m_magic == MagicNumber, "Error! Invalid magic number!");
        std::assert(pHeader.m_versionNumber == VersionNumber, "Error! Wrong version number.");
        
        u64 FileModuleAddr = pFile;
        u64 OffsetIndex = addressof(pHeader);
        u32 FixUpTable = addressof(pHeader.m_versionNumber) + pHeader.m_textSize;
        u32 size @ pHeader.m_textSize;

        BitReader bitdata;
        bitdata.m_FixUpTable = FixUpTable;
        bitdata.m_bitIndex = 0;
        bitdata.m_byteIndex = 0;
        bitdata.m_size = size;

        // Each 8-byte allocated will take 8 bits (1 byte) in the FixUpTable.
        // ((pHeader.m_textSize / 8) + 7) / 8 = FixUpTableSize
        
        u32 iQword = 0;
        u32 FixUpTableBits = (bitdata.m_size * 8);

        std::print("BitReader: {}", bitdata);
        std::print("FixUpTableBits: 0x{:016X}", FixUpTableBits);
        
        if(FixUpTableBits != 0) {
            while(iQword < FixUpTableBits) {

                bool rax = Script::ReadBit(bitdata);
                if(rax) {
                    u64 loc @ OffsetIndex;
                    std::assert(loc == 0 || (loc >= lowerBound && loc < upperBound), "loc == 0 || (loc >= lowerBound && loc < upperBound)");

                    u8 CheckByteIndex_value @ (bitdata.m_byteIndex + bitdata.m_FixUpTable);
                    u8 CheckByteIndex = CheckByteIndex_value;    

                    std::print("FixUpTableIndex: 0x{:016X}/0x{:016X}", CheckByteIndex_value, (bitdata.m_byteIndex + bitdata.m_FixUpTable) + bitdata.m_bitIndex);
                    std::print("OffsetIndex: 0x{:016X}", (FileModuleAddr + loc));
                }
                
                OffsetIndex += 8;
                iQword = (iQword + 1);
            }
        }
        
        return true;
    };
}


/*
Please always correctly pass those arguments in the virtual memory.
lowerBound = Used for relocation in the virtual memory.
upperBound = Actuall Size of file module
*/
//Script::Login(dc_header, addressof(dc_header), 0x0, 0xFFFFFFFFFFFFFFFF);