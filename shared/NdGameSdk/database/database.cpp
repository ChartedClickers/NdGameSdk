#include "database.hpp" 
#include <spdlog/spdlog.h>

namespace NdGameSdk::DB
{
    std::unique_ptr<ISdkDataBase> g_DataBase;

    bool Init(const std::string& folder) {
        g_DataBase = CreateJsonDataBase(folder);
        if (g_DataBase)
        {
            spdlog::info("[DB] Json database initialised at '{}'/", folder);
            return true;
        }
        spdlog::error("[DB] Failed to initialise Json database at '{}'/", folder);
        return false;
    }

    bool Flush() {
        if (!g_DataBase)
        {
            spdlog::warn("[DB] Flush called before Init()");
            return false;
        }

        bool ok = g_DataBase->Flush();
        spdlog::info("[DB] Flush {}", ok ? "succeeded" : "failed");
        return ok;
    }

    bool IsDataBaseAvailable() {
        return static_cast<bool>(g_DataBase);
    }

    bool Has(const std::string& file, const std::string& key) {
        if (!g_DataBase)
        {
            spdlog::error("[DB] Has() before Init()");
            return false;
        }
        return g_DataBase->Has(file, key);
    }

    void Clear() {
        if (!g_DataBase)
        {
            spdlog::error("[DB] Clear() before Init()");
            return;
        }

        g_DataBase->Clear();
        spdlog::info("[DB] Cache cleared");
    }

    bool FlushJsonFile(const std::string& file, bool dirty) {
        return g_DataBase ? static_cast<JsonDataBase*>(g_DataBase.get())->FlushFile(file, dirty) : false;
    }

    void ClearJsonFile(const std::string& file)
    {
        if (g_DataBase) {
            static_cast<JsonDataBase*>(g_DataBase.get())->ClearFile(file);
        }
    }
}
