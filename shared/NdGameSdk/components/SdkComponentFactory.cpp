#include "SdkComponentFactory.hpp"
#include "SdkComponent.hpp"
#include "SdkSubComponent.hpp"

namespace NdGameSdk {

    void SdkComponentFactory::InitializeSdkComponents() {
        for (auto id : m_orderedSdkComponents)
            m_sdkcomponents[id]->Awake();

        std::size_t progress;
        std::unordered_set<std::type_index> failed;

        auto depSatisfied = [&](std::type_index dep) -> bool {
            for (auto* f : { this,
                             &ISdkComponent::s_SharedComponents,
                             &ISdkComponent::s_NdGameComponents }) {
                auto it = f->m_sdkcomponents.find(dep);
                if (it != f->m_sdkcomponents.end() && it->second->IsInitialized())
                    return true;
            }
            return false;
            };

        auto isReady = [&](ISdkComponent* comp) {
            return std::all_of(comp->Dependencies().begin(),
                comp->Dependencies().end(),
                depSatisfied);
            };

        do {
            progress = 0;
            for (auto id : m_orderedSdkComponents) {

                auto it = m_sdkcomponents.find(id);
                if (it == m_sdkcomponents.end())
                    continue;

                auto& comp = it->second;

                if (!comp || comp->IsInitialized() || failed.contains(id))
                    continue;

                if (!isReady(comp.get()))
                    continue;

                try {
                    spdlog::info("Initialize {}", comp->GetName());
                    comp->Initialize();
                    comp->m_Initialized = true;
                    ++progress;
                }
                catch (const SdkComponentEx& ex) {
                    if (ex.IsCritical()) {
                        spdlog::critical("Critical initialization error in {}: {}", comp->GetName(), ex.what());
                        throw;
                    }
                    spdlog::error("Init failed for {}: {}", comp->GetName(), ex.what());
                    failed.insert(id);
                    m_sdkcomponents.erase(it);
                }
                catch (const std::exception& ex) {
                    spdlog::error("Error initialize {}: {}", comp->GetName(), ex.what());
                    failed.insert(id);
                    m_sdkcomponents.erase(it);
                }
                catch (...) {
                    spdlog::error("Error initialize: {}", comp->GetName());
                    failed.insert(id);
                    m_sdkcomponents.erase(it);
                }
            }
        } while (progress > 0);

        std::deque<std::type_index> queue{ failed.begin(), failed.end() };
        while (!queue.empty()) {
            auto bad = queue.front(); queue.pop_front();
            for (auto& [cid, compPtr] : m_sdkcomponents) {
                if (compPtr->IsInitialized() || failed.contains(cid))
                    continue;
                auto deps = compPtr->Dependencies();
                if (std::find(deps.begin(), deps.end(), bad) != deps.end()) {
                    failed.insert(cid);
                    queue.push_back(cid);
                }
            }
        }

        std::vector<std::pair<std::type_index, std::vector<std::type_index>>> missingDeps;
        for (auto const& [cid, uptr] : m_sdkcomponents) {
            if (!uptr->IsInitialized() && !failed.contains(cid)) {
                std::vector<std::type_index> depsMissing;
                for (auto dep : uptr->Dependencies())
                    if (!depSatisfied(dep))
                        depsMissing.push_back(dep);
                missingDeps.emplace_back(cid, std::move(depsMissing));
            }
        }

        std::erase_if(m_sdkcomponents, [&](auto const& kv) {
            return !kv.second->IsInitialized() || failed.contains(kv.first);
            });

        for (auto cid : failed)
            spdlog::warn("Component {} permanently failed", cid.name());

        for (auto& [cid, deps] : missingDeps) {
            std::vector<std::string> depNames;
            depNames.reserve(deps.size());
            for (auto d : deps)
                depNames.emplace_back(d.name());
            spdlog::warn("Component {} skipped (missing deps: {})", cid.name(), fmt::join(depNames, ", "));
        }
    }

    const std::unordered_map<std::type_index, std::unique_ptr<ISdkComponent>>& 
        SdkComponentFactory::GetSdkComponents() const {
        return m_sdkcomponents;
    }

}
