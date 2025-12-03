#include "load-registry.hpp"
#include "./NdGameSdk/shared/sharedpatterns.hpp"

namespace NdGameSdk::gamelib::level {
#if defined(T2R)

	LoadRegistry::LoadRegistry(NdGameSdk::ndlib::NdConfigComponent& ndConfig)
		: ISdkSubComponent(TOSTRING(LoadRegistry), InitPolicy::Automatic), m_NdConfigComp{ &ndConfig } {}

	void LoadRegistry::Init() {
		static std::once_flag Initialized;
		std::call_once(Initialized, [this] {
			spdlog::info("Initializing {} patterns...", GetName());

			Patterns::SdkPattern findpattern{};
			auto module = Utility::memory::get_executable();

			findpattern = Patterns::LoadRegistry_AddWantLoad;
			LoadRegistry_AddWantLoad = (LoadRegistry_AddWantLoad_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::LoadRegistry_AddWantLoad), findpattern.offset);

			findpattern = Patterns::LoadRegistry_AddWantLoadInternal;
			LoadRegistry_AddWantLoadInternal = (LoadRegistry_AddWantLoadInternal_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::LoadRegistry_AddWantLoadInternal), findpattern.offset);

			findpattern = Patterns::LoadRegistry_RemoveWantLoad;
			LoadRegistry_RemoveWantLoad = (LoadRegistry_RemoveWantLoad_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::LoadRegistry_RemoveWantLoad), findpattern.offset);

			findpattern = Patterns::LoadRegistry_RebuildWantLoads;
			LoadRegistry_RebuildWantLoads = (LoadRegistry_RebuildWantLoads_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::LoadRegistry_RebuildWantLoads), findpattern.offset);

			findpattern = Patterns::LoadRegistry_SelectLevelSet;
			LoadRegistry_SelectLevelSet = (LoadRegistry_SelectLevelSet_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::LoadRegistry_SelectLevelSet), findpattern.offset);

			findpattern = Patterns::LoadRegistry_GetMissingWantLoads;
			LoadRegistry_GetMissingWantLoads = (LoadRegistry_GetMissingWantLoads_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::LoadRegistry_GetMissingWantLoads), findpattern.offset);

			findpattern = Patterns::LoadRegistry_AllWantLoadsTerminalInternal;
			LoadRegistry_AllWantLoadsTerminalInternal = (LoadRegistry_AllWantLoadsTerminalInternal_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::LoadRegistry_AllWantLoadsTerminalInternal), findpattern.offset);

			findpattern = Patterns::LoadRegistry_IsAssetReloadPending;
			LoadRegistry_IsAssetReloadPending = (LoadRegistry_IsAssetReloadPending_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::LoadRegistry_IsAssetReloadPending), findpattern.offset);

			findpattern = Patterns::LoadRegistry_ReloadAsset;
			LoadRegistry_ReloadAsset = (LoadRegistry_ReloadAsset_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::LoadRegistry_ReloadAsset), findpattern.offset);

			findpattern = Patterns::LoadRegistry_ClearWantLoads;
			LoadRegistry_ClearWantLoads = (LoadRegistry_ClearWantLoads_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::LoadRegistry_ClearWantLoads), findpattern.offset);

			findpattern = Patterns::LoadRegistry_RemoveAllWantLoads;
			LoadRegistry_RemoveAllWantLoads = (LoadRegistry_RemoveAllWantLoads_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::LoadRegistry_RemoveAllWantLoads), findpattern.offset);

			findpattern = Patterns::LoadRegistry_GatherWantLoads;
			LoadRegistry_GatherWantLoads = (LoadRegistry_GatherWantLoads_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::LoadRegistry_GatherWantLoads), findpattern.offset);

			findpattern = Patterns::LoadRegistry_AreWantLoadLevelsFullySpawned;
			LoadRegistry_AreWantLoadLevelsFullySpawned = (LoadRegistry_AreWantLoadLevelsFullySpawned_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::LoadRegistry_AreWantLoadLevelsFullySpawned), findpattern.offset);

			findpattern = Patterns::LoadRegistry_WantLoadInfo_Constructor;
			WantLoadInfo::LoadRegistry_WantLoadInfo_Constructor = (WantLoadInfo::LoadRegistry_WantLoadInfo_Constructor_ptr)Utility::FindAndPrintPattern(module,
				findpattern.pattern, wstr(Patterns::LoadRegistry_WantLoadInfo_Constructor), findpattern.offset);

			if (!LoadRegistry_AddWantLoad ||
				!LoadRegistry_AddWantLoadInternal ||
				!LoadRegistry_RemoveWantLoad ||
				!LoadRegistry_RebuildWantLoads ||
				!LoadRegistry_SelectLevelSet ||
				!LoadRegistry_GetMissingWantLoads ||
				!LoadRegistry_AllWantLoadsTerminalInternal ||
				!LoadRegistry_IsAssetReloadPending ||
				!LoadRegistry_ReloadAsset ||
				!LoadRegistry_ClearWantLoads ||
				!LoadRegistry_RemoveAllWantLoads ||
				!LoadRegistry_GatherWantLoads ||
				!LoadRegistry_AreWantLoadLevelsFullySpawned ||
				!WantLoadInfo::LoadRegistry_WantLoadInfo_Constructor) {
				throw SdkComponentEx{ std::format("Failed to find {}:: game functions!", GetName()), SdkComponentEx::ErrorCode::PatternFailed };
			}
		});
	}

	inline LoadRegistryInternal& LoadRegistry::GetLoadRegistryInternal() const {
		always_assert(m_NdConfigComp == nullptr, "LoadRegistry::GetLoadRegistryInternal missing NdConfigComponent");
		return m_NdConfigComp->GetNdConfig().GetLoadRegistry();
	}

	void LoadRegistry::AddWantLoad(WantLoadInfo& info, bool forceAdd) {
		always_assert(LoadRegistry_AddWantLoad == nullptr, "LoadRegistry_AddWantLoad was not resolved");
		spdlog::debug("LoadRegistry::AddWantLoad name={} nameId={:016X} assetType={} forceAdd={}",
			info.GetName(), info.GetNameId(), static_cast<uint32_t>(info.GetType()), forceAdd);
		LoadRegistry_AddWantLoad(&GetLoadRegistryInternal(), &info, forceAdd);
	}

	void LoadRegistry::RemoveWantLoad(StringId64 nameId, bool includeLocked) {
		always_assert(LoadRegistry_RemoveWantLoad == nullptr, "LoadRegistry_RemoveWantLoad was not resolved");
		spdlog::debug("LoadRegistry::RemoveWantLoad nameId={:016X} includeLocked={}", nameId, includeLocked);
		LoadRegistry_RemoveWantLoad(&GetLoadRegistryInternal(), nameId, includeLocked);
	}

	void LoadRegistry::RebuildWantLoads() {
		always_assert(LoadRegistry_RebuildWantLoads == nullptr, "LoadRegistry_RebuildWantLoads was not resolved");
		LoadRegistry_RebuildWantLoads(&GetLoadRegistryInternal());
	}

	void LoadRegistry::ClearWantLoads() {
		always_assert(LoadRegistry_ClearWantLoads == nullptr, "LoadRegistry_ClearWantLoads was not resolved");
		LoadRegistry_ClearWantLoads(&GetLoadRegistryInternal());
	}

	void LoadRegistry::RemoveAllWantLoads(bool keepLocked) {
		always_assert(LoadRegistry_RemoveAllWantLoads == nullptr, "LoadRegistry_RemoveAllWantLoads was not resolved");
		LoadRegistry_RemoveAllWantLoads(&GetLoadRegistryInternal(), keepLocked);
	}

	void LoadRegistry::GatherWantLoads(ListArray<WantLoadInfo>& wantLoads, bool dedupe) {
		always_assert(LoadRegistry_GatherWantLoads == nullptr, "LoadRegistry_GatherWantLoads was not resolved");
		LoadRegistry_GatherWantLoads(&GetLoadRegistryInternal(), &wantLoads, dedupe);
	}

	bool LoadRegistry::SelectLevelSet(StringId64 levelSet, bool rebuildAfterSwitch, bool clearExistingLoads) {
		always_assert(LoadRegistry_SelectLevelSet == nullptr, "LoadRegistry_SelectLevelSet was not resolved");
		return LoadRegistry_SelectLevelSet(&GetLoadRegistryInternal(), levelSet, rebuildAfterSwitch, clearExistingLoads);
	}

	bool LoadRegistry::AllWantLoadsTerminal(bool includeDisplayDependents, bool propagateOnly, WantLoadInfo** outWantLoad) {
		always_assert(LoadRegistry_AllWantLoadsTerminalInternal == nullptr, "LoadRegistry_AllWantLoadsTerminalInternal was not resolved");
		return LoadRegistry_AllWantLoadsTerminalInternal(&GetLoadRegistryInternal(), includeDisplayDependents, propagateOnly, outWantLoad);
	}

	bool LoadRegistry::IsAssetReloadPending(StringId64 nameId, AssetType assetType) {
		always_assert(LoadRegistry_IsAssetReloadPending == nullptr, "LoadRegistry_IsAssetReloadPending was not resolved");
		return LoadRegistry_IsAssetReloadPending(&GetLoadRegistryInternal(), nameId, assetType);
	}

	bool LoadRegistry::ReloadAsset(StringId64 nameId, AssetType assetType, LoadRegistryInternal::ReloadCallback callback, void* userData) {
		always_assert(LoadRegistry_ReloadAsset == nullptr, "LoadRegistry_ReloadAsset was not resolved");
		return LoadRegistry_ReloadAsset(&GetLoadRegistryInternal(), nameId, assetType, callback, userData);
	}

	bool LoadRegistry::AreWantLoadLevelsFullySpawned() {
		always_assert(LoadRegistry_AreWantLoadLevelsFullySpawned == nullptr, "LoadRegistry_AreWantLoadLevelsFullySpawned was not resolved");
		return LoadRegistry_AreWantLoadLevelsFullySpawned(&GetLoadRegistryInternal());
	}

	uint32_t LoadRegistry::GetMissingWantLoads(std::span<WantLoadInfo> outWantLoads, bool includeLocked) {
		always_assert(LoadRegistry_GetMissingWantLoads == nullptr, "LoadRegistry_GetMissingWantLoads was not resolved");
		if (outWantLoads.empty()) {
			return 0;
		}

		return LoadRegistry_GetMissingWantLoads(&GetLoadRegistryInternal(),
			outWantLoads.data(),
			static_cast<uint32_t>(outWantLoads.size()),
			includeLocked);
	}

	LoadRegistryInternal::WantLoads& LoadRegistryInternal::GetWantLoads() {
		return reinterpret_cast<LoadRegistryInternal::WantLoads&>(this->Get()->m_WantLoads);
	}

	LoadRegistryInternal::WantLoads& LoadRegistryInternal::GetWantLoadsLocked() {
		return reinterpret_cast<LoadRegistryInternal::WantLoads&>(this->Get()->m_WantLoadsLocked);
	}

	ScriptManager::PointerBase* LoadRegistryInternal::GetLevelSets() {
		return reinterpret_cast<ScriptManager::PointerBase*>(&this->Get()->m_levelsets);
	}

	bool LoadRegistryInternal::IsChangedThisFrame() const {
		return this->Get()->m_ChangedThisFrame;
	}

	FixedSizeHashTable<LoadRegistryInternal::ReloadNode>& LoadRegistryInternal::GetReloadTable() {
		return reinterpret_cast<FixedSizeHashTable<LoadRegistryInternal::ReloadNode>&>(this->Get()->m_ReloadMap);
	}

	FixedSizeHashTable<StringId64>& LoadRegistryInternal::GetDisplayMap() {
		return reinterpret_cast<FixedSizeHashTable<StringId64>&>(this->Get()->m_DisplayMap);
	}

	ListArray<WantLoadInfo>& LoadRegistryInternal::WantLoads::GetList() {
		return reinterpret_cast<ListArray<WantLoadInfo>&>(this->Get()->m_list);
	}

	FixedSizeHashTable<LoadRegistryInternal::WantLoads::Node>& LoadRegistryInternal::WantLoads::GetTable() {
		return reinterpret_cast<FixedSizeHashTable<LoadRegistryInternal::WantLoads::Node>&>(this->Get()->m_table);
	}

    StringId64 LoadRegistryInternal::WantLoads::Node::GetKeyNameId() {  
       return this->Get()->m_KeyNameId;
    }

	uint64_t LoadRegistryInternal::WantLoads::Node::GetRefCount() {
		return this->Get()->m_RefCount;
	}

	WantLoadInfo& LoadRegistryInternal::WantLoads::Node::GetInfo() {
		return reinterpret_cast<WantLoadInfo&>(this->Get()->m_Info);
	}

	const WantLoadInfo& LoadRegistryInternal::WantLoads::Node::GetInfo() const {
		return reinterpret_cast<const WantLoadInfo&>(this->Get()->m_Info);
	}

	StringId64 LoadRegistryInternal::ReloadNode::GetNameId() {
		return this->Get()->m_NameId;
	}

	LoadRegistryInternal::ReloadCallback LoadRegistryInternal::ReloadNode::GetCallback() {
		return reinterpret_cast<ReloadCallback>(this->Get()->m_Callback);
	}

	AssetType LoadRegistryInternal::ReloadNode::GetAssetType() {
		return this->Get()->m_AssetType;
	}

	bool LoadRegistryInternal::ReloadNode::IsDispatched() const {
		return this->Get()->m_Dispatched;
	}


#endif
}
