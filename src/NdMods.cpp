#include "NdMods.hpp"

#include "NdMods/ExampleMod.hpp"

NdMods::NdMods()
{
    AddNdModComponent<ExampleMod::Example>();
}

void NdMods::InitializeNdMods()
{
    for (auto& [modcomponent, ndmod] : m_ndmods) {
        spdlog::info("Initialize: {:s}", ndmod->GetName().data());
        
        try {
            ndmod->OnNdModinitialize();
            ndmod->m_Initialized = true;
        }
        catch (NdModComponentEx InitEx) {
            spdlog::error("Error initialize {:s}: {:s}", ndmod->GetName().data(), InitEx.what());
        }
        catch (...) {
            spdlog::error("Error initialize: {:s}", ndmod->GetName().data());
        }
    }

    std::erase_if(m_ndmods, [](
        const pair<std::type_index, std::shared_ptr<NdMod>>& pair) { return !pair.second->m_Initialized; });


    Utils::Config cfg{};
    if (cfg.IsLoaded()) {
        for (auto& [modcomponent, ndmod] : m_ndmods) {
            if (ndmod->m_pconfig) {
                spdlog::info("Load config for {:s}", ndmod->GetName().data());
                ndmod->OnConfigLoad(cfg);
            }
        }
    }
    else {
        spdlog::error("Config wasn't loaded for Ndmods!");
    }
}

void NdMods::SaveConfig(Utils::Config& cfg)
{
    if (cfg.IsLoaded()) {
        for (auto& [modcomponent, ndmod] : m_ndmods) {
            if (ndmod->m_pconfig) {
                spdlog::info("Save config for {:s}", ndmod->GetName().data());
                ndmod->OnConfigSave(cfg);
            }
        }
    }
}

const auto& NdMods::GetNdMods() const
{
    return m_ndmods;
}
