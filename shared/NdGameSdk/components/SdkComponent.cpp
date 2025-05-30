#include "SdkComponent.hpp"

namespace NdGameSdk {

	SdkComponentFactory ISdkComponent::s_SharedComponents{};
	SdkComponentFactory ISdkComponent::s_NdGameComponents{};

	ISdkComponent::ISdkComponent(std::string name) 
		: m_name{ name }, m_Initialized{ false } {};

	std::string_view ISdkComponent::GetName() const {
		return m_name;
	}

	bool ISdkComponent::IsInitialized() const {
		return m_Initialized;
	}

	SdkComponentFactory* ISdkComponent::GetSharedComponents() {
		return &s_SharedComponents;
	}

	SdkComponentFactory* ISdkComponent::GetNdGameComponents() {
		return &s_NdGameComponents;
	}

	const std::vector<ISdkComponent*>& ISdkComponent::GetSdkComponents() {
		static std::vector<ISdkComponent*> CachedComponents;
		static std::once_flag initFlag;

		if (!g_SdkInitialized) {
			throw SdkComponentEx(
				"SDK is not initialized! Cannot access components.",
				SdkComponentEx::ErrorCode::SdkNotInitialized,
				true
			);
		}

		std::call_once(initFlag, [] {
			const auto& sharedComponents = GetSharedComponents()->GetSdkComponents();
			const auto& ndGameComponents = GetNdGameComponents()->GetSdkComponents();

			CachedComponents.reserve(sharedComponents.size() + ndGameComponents.size());

			for (const auto& [_, comp] : sharedComponents) {
				CachedComponents.push_back(comp.get());
			}
			for (const auto& [_, comp] : ndGameComponents) {
				CachedComponents.push_back(comp.get());
			}
			});

		return CachedComponents;
	}



	SdkComponentFactory::~SdkComponentFactory() {
		for (auto it = m_orderedSdkComponents.rbegin(); it != m_orderedSdkComponents.rend(); ++it) {
			ISdkComponent* ptr = *it;
			if (!ptr) continue;
			auto found = std::find_if(
				m_sdkcomponents.begin(), m_sdkcomponents.end(),
				[ptr](const auto& kv) { return kv.second.get() == ptr; });
			if (found != m_sdkcomponents.end()) {
				found->second.reset();
			}
		}

		m_orderedSdkComponents.clear();
		m_sdkcomponents.clear();
	}

	void SdkComponentFactory::InitializeSdkComponents() {

		for (auto& comp : m_orderedSdkComponents)
			comp->Awake();

		std::size_t progress;
		std::unordered_set<std::type_index> failed;

		do {

			progress = 0;

			for (auto& comp : m_orderedSdkComponents)
			{
				std::type_index id{ typeid(*comp) };
				if (comp->IsInitialized() || failed.count(id))
					continue;

				bool ready = std::all_of(
					comp->Dependencies().begin(),
					comp->Dependencies().end(),
					[&](auto const& d) {
						auto it = m_sdkcomponents.find(d);
						if (it != m_sdkcomponents.end())
							return it->second->IsInitialized();

						if (this != &ISdkComponent::s_SharedComponents) {
							const auto& shared = ISdkComponent::s_SharedComponents.GetSdkComponents();
							auto it_shared = shared.find(d);
							return it_shared != shared.end() && it_shared->second->IsInitialized();
						}

						return false;
					});


				if (!ready)
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
				}
				catch (const std::exception& ex) {
					spdlog::error("Error initialize {}: {}", comp->GetName(), ex.what());
					failed.insert(id);
				}
				catch (...) {
					spdlog::error("Error initialize: {}", comp->GetName());
					failed.insert(id);
				}
			}

		} while (progress > 0);

		{
			std::deque<std::type_index> queue{ failed.begin(), failed.end() };
			while (!queue.empty()) {
				auto bad = queue.front(); queue.pop_front();

				for (auto& [cid, compPtr] : m_sdkcomponents) {
					if (compPtr->IsInitialized() || failed.count(cid))
						continue;

					auto deps = compPtr->Dependencies();
					if (std::find(deps.begin(), deps.end(), bad) != deps.end()) {
						failed.insert(cid);
						queue.push_back(cid);
					}
				}
			}
		}

		std::erase_if(m_sdkcomponents,
			[&](auto const& kv) {
				auto& ptr = kv.second;
				auto  cid = kv.first;
				return !ptr->IsInitialized() || failed.count(cid);
			});

		for (auto const& cid : failed) {
			spdlog::warn("Component {} permanently failed", cid.name());
		}
	}

	void ISdkComponent::InitSubComponents() {

		for (auto& subcomponent : m_subcomponents)
		{
			const auto& sub = subcomponent.second;
			if (!sub || sub->IsInitialized())
				continue;

			spdlog::info("Initialize SubComponent: {}", sub->GetName());

			try
			{
				sub->Init();
				sub->m_Initialized = true;
			}
			catch (SdkComponentEx ComponentEx) {
				spdlog::error("Error initialize {:s}: {:s}", sub->GetName().data(), ComponentEx.what());
				throw;
			}
			catch (const std::exception& ex) {
				spdlog::error("Error initialize {}: {}", sub->GetName(), ex.what());
				throw;
			}
			catch (...) {
				spdlog::error("Error initialize: {}", sub->GetName());
				throw;
			}
		}
	}

	const std::unordered_map<std::type_index, std::unique_ptr<ISdkComponent>>& SdkComponentFactory::GetSdkComponents() const {
		return m_sdkcomponents;
	}

}