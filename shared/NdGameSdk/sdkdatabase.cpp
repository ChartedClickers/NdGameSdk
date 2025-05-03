#include "sdkdatabase.hpp"  
#include <filesystem>  

namespace fs = std::filesystem;

namespace NdGameSdk {

	inline std::unique_ptr<ISdkDataBase> CreateJsonDataBase(const std::string& folder) {
		auto db = std::make_unique<JsonDataBase>();
		db->Init(folder);
		return db;
	}

	inline bool JsonDataBase::Init(const std::string& folder) {
		std::scoped_lock lock(mtx_);
		root_ = fs::path(folder);
		fs::create_directories(root_);
		cache_.clear();
		return true;
	}

    inline void JsonDataBase::Clear() {
        std::scoped_lock lock(mtx_);
        cache_.clear();
    }

    inline auto JsonDataBase::loadFile(const std::string& file) -> Entry& {
        auto it = cache_.find(file);

        if (it != cache_.end()) 
            return it->second;

        Entry ent{};
        std::ifstream is(root_ / file);
        if (is) {
            try { is >> ent.data; }
            catch (const std::exception& e) {
                spdlog::warn("[JsonDB] Failed to parse {}: {}", file, e.what());
            }
        }

        auto [pos, _] = cache_.emplace(file, std::move(ent));
        return pos->second;
    }

    inline void JsonDataBase::SetImpl(const std::string& file, const std::string& key, const nlohmann::json& v) {
        std::scoped_lock lock(mtx_);
        auto& ent = loadFile(file);
        ent.data[key] = v;
        ent.dirty = true;
    }

    inline nlohmann::json JsonDataBase::GetImpl(const std::string& file, const std::string& key, const nlohmann::json& def) {
        std::scoped_lock lock(mtx_);
        auto& ent = loadFile(file);
        return ent.data.value(key, def);
    }

    inline bool JsonDataBase::HasImpl(const std::string& file, const std::string& key) {
        std::scoped_lock lock(mtx_);
        auto& ent = loadFile(file);
        return ent.data.contains(key);
    }

    inline bool JsonDataBase::Flush() {
        std::scoped_lock lock(mtx_);
        bool flush_success = true;
        for (auto& [fname, ent] : cache_) {
            if (!ent.dirty) continue;
            std::ofstream os(root_ / fname);
            if (!os) {
                spdlog::error("[JsonDB] Cannot write {}", fname);
                flush_success = false; continue;
            }
            os << ent.data.dump(2);
            ent.dirty = false;
        }
        return flush_success;
    }
}
