#pragma once

#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/components/SdkSubComponent.hpp"
#include "NdGameSdk/sdkregenny.hpp"

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/gamelib/level/LoadRegistry.hpp>
#endif

#include <NdGameSdk/shared/src/ndlib/nd-config.hpp>
#include <NdGameSdk/shared/src/ndlib/io/asset-view.hpp>
#include <NdGameSdk/shared/src/ndlib/script/script-manager.hpp>
#include <NdGameSdk/shared/src/corelib/containers/fixed-size-hashtable.hpp>
#include <NdGameSdk/shared/src/corelib/containers/list-array.hpp>

#include "want-load.hpp"

namespace NdGameSdk::gamelib::level {
#if defined(T2R)

	using namespace corelib::containers;
	using namespace ndlib::io;
	using namespace ndlib::script;

	class LoadRegistryInternal : public ISdkRegenny<regenny::shared::gamelib::level::LoadRegistry> {
	public:
		using ReloadCallback = void(*)(StringId64 nameId, AssetType pAssetType, void* userData, bool finished);

		class WantLoads : public ISdkRegenny<regenny::shared::gamelib::level::LoadRegistry::WantLoads> {
		public:
			class Node : public ISdkRegenny<regenny::shared::gamelib::level::LoadRegistry::WantLoads::Node, FixedSizeHashTable<Node>::ListHead> {
			public:
				StringId64 GetKeyNameId();
				uint64_t GetRefCount();
				WantLoadInfo& GetInfo();
				const WantLoadInfo& GetInfo() const;
			};

			ListArray<WantLoadInfo>& GetList();
			FixedSizeHashTable<WantLoads::Node>& GetTable();
		};

		class ReloadNode : public ISdkRegenny<regenny::shared::gamelib::level::LoadRegistry::ReloadNode, FixedSizeHashTable<ReloadNode>::ListHead> {
		public:
			StringId64 GetNameId();
			ReloadCallback GetCallback();
			AssetType GetAssetType();
			bool IsDispatched() const;
		};

		WantLoads& GetWantLoads();
		WantLoads& GetWantLoadsLocked();

		ScriptManager::PointerBase* GetLevelSets();

		bool IsChangedThisFrame() const;

		FixedSizeHashTable<ReloadNode>& GetReloadTable();
		FixedSizeHashTable<StringId64>& GetDisplayMap();

	};

	class LoadRegistry final : public ISdkSubComponent {
	public:
		explicit LoadRegistry(ndlib::NdConfigComponent& ndConfig);

		void AddWantLoad(WantLoadInfo& info, bool forceAdd = false);
		void RemoveWantLoad(StringId64 nameId, bool includeLocked = false);
		void RebuildWantLoads();
		void ClearWantLoads();
		void RemoveAllWantLoads(bool keepLocked);
		void GatherWantLoads(ListArray<WantLoadInfo>& wantLoads, bool dedupe);

		bool SelectLevelSet(StringId64 levelSet, bool rebuildAfterSwitch, bool clearExistingLoads);
		bool AllWantLoadsTerminal(bool includeDisplayDependents, bool propagateOnly, WantLoadInfo** outWantLoad = nullptr);
		bool IsAssetReloadPending(StringId64 nameId, AssetType assetType);
		bool ReloadAsset(StringId64 nameId, AssetType assetType, LoadRegistryInternal::ReloadCallback callback, void* userData);
		bool AreWantLoadLevelsFullySpawned();

		uint32_t GetMissingWantLoads(std::span<WantLoadInfo> outWantLoads, bool includeLocked = false);


	private:
		void Init() override;

		inline LoadRegistryInternal& GetLoadRegistryInternal() const;

		ndlib::NdConfigComponent* m_NdConfigComp{ nullptr };

		MEMBER_FUNCTION_PTR(void, LoadRegistry_AddWantLoad, LoadRegistryInternal* pLoadRegistry, WantLoadInfo* pWantLoadInfo, bool forceAdd);
		MEMBER_FUNCTION_PTR(void, LoadRegistry_AddWantLoadInternal, LoadRegistryInternal* pLoadRegistry, WantLoadInfo* pWantLoadInfo, bool forceAdd);
		MEMBER_FUNCTION_PTR(void, LoadRegistry_RemoveWantLoad, LoadRegistryInternal* pLoadRegistry, StringId64 pNameId, bool includeLocked);
		MEMBER_FUNCTION_PTR(void, LoadRegistry_RebuildWantLoads, LoadRegistryInternal* pLoadRegistry);
		MEMBER_FUNCTION_PTR(bool, LoadRegistry_SelectLevelSet, LoadRegistryInternal* pLoadRegistry, StringId64 levelsets, bool rebuildAfterSwitch, bool clearExistingLoads);
		MEMBER_FUNCTION_PTR(uint32_t, LoadRegistry_GetMissingWantLoads, LoadRegistryInternal* pLoadRegistry, WantLoadInfo* outWantLoads, uint32_t maxEntries, bool includeLocked);
		MEMBER_FUNCTION_PTR(bool, LoadRegistry_AllWantLoadsTerminalInternal, LoadRegistryInternal* pLoadRegistry, bool includeDisplayDependents, bool propagateOnly, WantLoadInfo** pWantLoadInfo);
		MEMBER_FUNCTION_PTR(bool, LoadRegistry_IsAssetReloadPending, LoadRegistryInternal* pLoadRegistry, StringId64 pNameId, AssetType pAssetType);
		MEMBER_FUNCTION_PTR(bool, LoadRegistry_ReloadAsset, LoadRegistryInternal* pLoadRegistry, StringId64 pNameId, AssetType pAssetType, LoadRegistryInternal::ReloadCallback pCallback, void* pUserData);
		MEMBER_FUNCTION_PTR(void, LoadRegistry_ClearWantLoads, LoadRegistryInternal* pLoadRegistry);
		MEMBER_FUNCTION_PTR(void, LoadRegistry_RemoveAllWantLoads, LoadRegistryInternal* pLoadRegistry, bool keepLocked);
		MEMBER_FUNCTION_PTR(void, LoadRegistry_GatherWantLoads, LoadRegistryInternal* pLoadRegistry, ListArray<WantLoadInfo>* pWantLoadInfos, bool dedupe);
		MEMBER_FUNCTION_PTR(bool, LoadRegistry_AreWantLoadLevelsFullySpawned, LoadRegistryInternal* pLoadRegistry);
	};

	static_assert(sizeof(LoadRegistryInternal) == 0x320, "Size of LoadRegistry is incorrect");
	static_assert(sizeof(LoadRegistryInternal::WantLoads) == 0xa8, "Size of LoadRegistry::WantLoads is incorrect");
	static_assert(sizeof(LoadRegistryInternal::WantLoads::Node) - sizeof(FixedSizeHashTable<LoadRegistryInternal::WantLoads::Node>::ListHead) == 0x38, "Size of LoadRegistry::WantLoads::Node is incorrect");
	static_assert(sizeof(LoadRegistryInternal::ReloadNode) - sizeof(FixedSizeHashTable<LoadRegistryInternal::ReloadNode>::ListHead) == 0x20, "Size of LoadRegistry::ReloadNode is incorrect");

#endif
}
