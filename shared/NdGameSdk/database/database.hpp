#pragma once

#include <NdGameSdk/sdkdatabase.hpp>

namespace NdGameSdk::DB {

    extern std::unique_ptr<ISdkDataBase> g_DataBase;

    bool Init(const std::string& folder);
    bool Flush();
    bool IsDataBaseAvailable();

    template<typename T>
    inline void Set(const std::string& file, const std::string& key, const T& v)
    {
        g_DataBase->Set(file, key, v);
    }

    template<typename T>
    [[nodiscard]] inline T Get(const std::string& file,
        const std::string& key,
        const T& def = {}) 
    {
        return g_DataBase->Get<T>(file, key, def);
    }

    template<typename K, typename V, typename MergeFn>
    bool RefreshMap(const std::string& file, const std::string& jsonKey, std::map<K, V>& outMap, MergeFn&& mergeFn, bool flush = true) 
    {
        if (!IsDataBaseAvailable()) return false;

        outMap = Get<std::map<K, V>>(file, jsonKey, outMap);
        mergeFn(outMap);

        Set(file, jsonKey, outMap);
        if (flush) FlushFile(file);
        return true;
    }

    [[nodiscard]] bool Has(const std::string& file, const std::string& key);

    void Clear();

    bool FlushJsonFile(const std::string& file, bool dirty = false);
    void ClearJsonFile(const std::string& file);
}