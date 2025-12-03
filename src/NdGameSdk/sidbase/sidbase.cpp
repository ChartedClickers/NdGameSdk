/******************************************************************************/
/*
  Author  - icemesh
*/
/******************************************************************************/
#include "sidbase.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <Utility/assertion/assert.hpp>

namespace NdGameSdk::Sidbase {

#if defined(Big4R)
    struct SidbaseEntry
    {
        StringId32	m_id;
        size_t		m_offset;
    };
    struct Sidbase
    {
        uint8_t* m_pFile;
        SidbaseEntry* m_pData;
        char* m_pStrings;
        uint32_t m_numEntries;
    };

    static inline uint32_t swapU32(uint32_t value)
    {
        return ((value & 0x000000FF) << 24) | ((value & 0x0000FF00) << 8) | ((value & 0x00FF0000) >> 8) | ((value & 0xFF000000) >> 24);
    }

#else
    struct SidbaseEntry
    {
        StringId64	m_id;
        size_t		m_offset;
    };
    struct Sidbase
    {
        uint8_t* m_pFile;
        SidbaseEntry* m_pData;
        char* m_pStrings;
        uint64_t m_numEntries;
    };
#endif

    Sidbase g_sidbase;
    bool g_bSidbaseAvailable = false;

    bool InitSidbase(const char* sid_path)
    {
        FILE* fh{};
        fopen_s(&fh, sid_path, "rb");
        if (fh)
        {
            fseek(fh, 0x0, SEEK_END);
            size_t fsize = ftell(fh);
            fseek(fh, 0x0, SEEK_SET);
            uint8_t* pMem = reinterpret_cast<uint8_t*>(malloc(fsize));
            if (!pMem)
            {
                spdlog::error("Failed to allocate {:#X} bytes for sid db\n", fsize);
                fclose(fh);
            }
            else
            {
                fread(pMem, fsize, 0x1, fh);
                fclose(fh);

                g_sidbase.m_pFile = pMem;

#if defined(Big4R)
                g_sidbase.m_pData = reinterpret_cast<SidbaseEntry*>(pMem + 0x4);
                uint32_t numEntries = swapU32(*(uint32_t*)pMem);
                g_sidbase.m_numEntries = numEntries;
                g_sidbase.m_pStrings = reinterpret_cast<char*>(pMem + (numEntries << 0x3) + 0x4);
#else
                //TODO: Add fix pointers
                g_sidbase.m_pData = reinterpret_cast<SidbaseEntry*>(pMem + 0x8);
                g_sidbase.m_numEntries = *reinterpret_cast<uint64_t*>(pMem);
#endif

                g_bSidbaseAvailable = true;
                spdlog::info("Sidbase successfully initialized!");
                spdlog::info("g_sidbase.m_pFile: {}", static_cast<void*>(g_sidbase.m_pFile));
                spdlog::info("g_sidbase.m_pData: {}", static_cast<void*>(g_sidbase.m_pData));
                spdlog::info("g_sidbase.m_numEntries: {}", g_sidbase.m_numEntries);
                spdlog::info("g_sidbase.m_pStrings: {}", static_cast<void*>(g_sidbase.m_pStrings));
            }
        }
        else
        {
            spdlog::error("Could not open {:s}! Does it even exist ?", sid_path);
        }

        return g_bSidbaseAvailable;
    }

    void ShutdownSidbase()
    {
        if (g_sidbase.m_pFile != nullptr) {
            free(g_sidbase.m_pFile);
        }

        g_bSidbaseAvailable = false;
    }

    std::unordered_map<StringId, char*> g_sidMap{};

    std::string StringIdToStringInternal(StringId sid)
    {
        if (g_bSidbaseAvailable)
        {
            // Try to find the string in our map first
            auto stringid = g_sidMap.find(sid);
            if (stringid != g_sidMap.end()) {
                if (stringid->second != nullptr) {
                    return stringid->second;
                }
                else {
    #if defined(Big4R)
                    char sidBuffer[0x20];
                    _snprintf_s(sidBuffer, sizeof(sidBuffer), "#%08X", sid);
    #else
                    char sidBuffer[0x20];
                    snprintf(sidBuffer, sizeof(sidBuffer), "#%.16llX", sid);
    #endif
                    return sidBuffer;
                }
            }

            // Try to find string in sidbase
            SidbaseEntry* pEntry = g_sidbase.m_pData;
            // this can be improved..
#if defined(Big4R)
            int32_t nEntries = g_sidbase.m_numEntries;
            for (int32_t iEntries = 0; iEntries < nEntries; iEntries++) {
                StringId id = swapU32(pEntry->m_id);
                if (id == sid)
                {
                    char* str = g_sidbase.m_pStrings + swapU64(pEntry->m_offset);
                    auto stringid = g_sidVector.emplace(sid, str);
                    return str;
                }
                pEntry++;
            }
#else
            uint64_t nEntries = g_sidbase.m_numEntries;
            for (uint64_t iEntries = 0; iEntries < nEntries; iEntries++)
            {
                if (pEntry->m_id == sid)
                {
                    auto string = reinterpret_cast<char*>(g_sidbase.m_pFile) + pEntry->m_offset;
                    auto stringid = g_sidMap.emplace(sid, string);
                    return string;
                }
                pEntry++;
            }
#endif

        }
#if defined(Big4R)
        char sidBuffer[0x20];
        _snprintf_s(sidBuffer, sizeof(sidBuffer), "#%08X", sid);
#else
        char sidBuffer[0x20];
        snprintf(sidBuffer, sizeof(sidBuffer), "#%.16llX", sid);
#endif
        if (g_bSidbaseAvailable) {
            g_sidMap.emplace(sid, nullptr);
        }

        return sidBuffer;
    }
}


