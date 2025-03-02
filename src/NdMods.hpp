#pragma once

#include <spdlog/spdlog.h>

#include "NdModClient.hpp"
#include "NdDerived.hpp"

class NdMod;

class NdMods final {
public:
	NdMods();
	virtual ~NdMods() {};

	void InitializeNdMods();
	void SaveConfig(Utils::Config& cfg);
	const auto& GetNdMods() const;

	template <typename NdModComponent>
	std::shared_ptr<NdModComponent> GetNdModComponent() {
		static_assert(NdDerived::is_derived_from_NdMod<NdModComponent>::value, "NdModComponent must be derived from NdMod");
		auto modcomponent = m_ndmods.find(typeid(NdModComponent));
		return modcomponent != m_ndmods.end() ? std::static_pointer_cast<NdModComponent>(modcomponent->second) : nullptr;
	}

	template<typename NdModComponent>
	std::vector<std::shared_ptr<NdModComponent>> GetNdModComponents() {
		static_assert(NdDerived::is_derived_from_NdMod<NdModComponent>::value, "NdModComponent must be derived from NdMod");
		std::vector<std::shared_ptr<NdModComponent>> modcomponent;
		for (const auto& ndmod : m_ndmods) {
			if (auto component = std::dynamic_pointer_cast<NdModComponent>(ndmod.second)) {
				modcomponent.push_back(component);
			}
		}

		return modcomponent;
	}

private:

	template <typename NdModComponent, typename... Args>
	std::shared_ptr<NdModComponent> AddNdModComponent(Args&&... args) {
		static_assert(NdDerived::is_derived_from_NdMod<NdModComponent>::value, "NdModComponent must be derived from NdMod");
		auto modcomponent = m_ndmods.find(typeid(NdModComponent));

		if (modcomponent == m_ndmods.end()) {
			auto modcomponent = std::make_shared<NdModComponent>(std::forward<Args>(args)...);
			m_ndmods.emplace(typeid(NdModComponent), std::move(modcomponent));
			return modcomponent;
		}

		return std::static_pointer_cast<NdModComponent>(modcomponent->second);
	}

	std::unordered_map<std::type_index, std::shared_ptr<NdMod>> m_ndmods;
};


class NdModComponentEx : public NdModClientException {
public:

	enum ErrorCode {
		DependenciesFailed,
		PatternFailed,
	};

	NdModComponentEx(const std::string& msg, ErrorCode errcode)
		: m_errcode{ errcode }, NdModClientException(msg) {}

	const ErrorCode ErrCode() const noexcept {
		return m_errcode;
	}

private:
	ErrorCode m_errcode;
};