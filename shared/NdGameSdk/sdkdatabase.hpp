#pragma once

#include <string>
#include <fstream>
#include <mutex>
#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>

namespace NdGameSdk {

    class ISdkDataBase {
    public:
        virtual ~ISdkDataBase() = default;

        virtual bool Init(const std::string& folder) = 0;
        virtual bool Flush() = 0;
        virtual void Clear() = 0;

        template<typename T>
        void Set(const std::string& file, const std::string& key, const T& v) {
            SetImpl(file, key, nlohmann::json(v));
        }

        template<typename T>
        [[nodiscard]] T Get(const std::string& file,
            const std::string& key,
            const T& def = {}) {
            nlohmann::json jdef = def;
            return GetImpl(file, key, jdef).template get<T>();
        }

        [[nodiscard]] bool Has(const std::string& file, const std::string& key) {
            return HasImpl(file, key);
        }

    protected:
        virtual void SetImpl(const std::string& file, const std::string& key, const nlohmann::json& v) = 0;
        virtual nlohmann::json GetImpl(const std::string& file, const std::string& key, const nlohmann::json& def) = 0;
        virtual bool HasImpl(const std::string& file, const std::string& key) = 0;
    };

    class JsonDataBase final : public ISdkDataBase {
    public:
        JsonDataBase() = default;
        ~JsonDataBase() override { Flush(); }

        bool Init(const std::string& folder) override;
        bool Flush() override;
        void Clear() override;

        bool FlushFile(const std::string& file, bool dirty = false);
        void ClearFile(const std::string& file, bool removeDisk = false);

    protected:
        void SetImpl(const std::string& file, const std::string& key, const nlohmann::json& v) override;
        nlohmann::json GetImpl(const std::string& file, const std::string& key, const nlohmann::json& def) override;
        bool HasImpl(const std::string& file, const std::string& key) override;

    private:
        struct Entry {
            nlohmann::json data;
            bool dirty{ false };
        };

        std::filesystem::path root_{};
        std::unordered_map<std::string, Entry> cache_{};
        std::mutex mtx_{};

        Entry& loadFile(const std::string& file);
    };

    std::unique_ptr<ISdkDataBase> CreateJsonDataBase(const std::string& folder);

}
