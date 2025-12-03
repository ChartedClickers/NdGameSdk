#include "want-load.hpp"

namespace NdGameSdk::gamelib::level {
#if defined(T2R)

	WantLoadInfo::WantLoadInfo(Type type, const char* name, StringId64 nameId, Flags pFlags) {
		always_assert(LoadRegistry_WantLoadInfo_Constructor == nullptr, "Function pointer was not set!");
		LoadRegistry_WantLoadInfo_Constructor(this, type, name, nameId);
		this->SetFlags(pFlags);
	}

	std::string_view WantLoadInfo::GetName() const {
		const char* name = this->Get()->m_name;
		return name ? std::string_view{name} : std::string_view{};
	}

	StringId64 WantLoadInfo::GetNameId() const {
		return this->Get()->m_nameId;
	}

	LevelDef* WantLoadInfo::GetLevelDef() const {
		return reinterpret_cast<LevelDef*>(this->Get()->m_pLevelDef);
	}

	LevelLoadedCallback WantLoadInfo::GetOnLoadedCallback() const {
		return reinterpret_cast<LevelLoadedCallback>(this->Get()->m_onLoadedCallback);
	}

	void WantLoadInfo::SetOnLoadedCallback(LevelLoadedCallback callback) {
		this->Get()->m_onLoadedCallback = reinterpret_cast<void*>(callback);
	}

	WantLoadInfo::Type WantLoadInfo::GetType() const {
		return this->Get()->m_type;
	}

	WantLoadInfo::Flags WantLoadInfo::GetFlags() const {
		return this->Get()->m_flags;
	}

	void WantLoadInfo::SetFlags(Flags flags) {
		this->Get()->m_flags = flags;
	}

	void WantLoadInfo::EnableFlags(Flags flags) {
		this->Get()->m_flags |= flags;
	}

	void WantLoadInfo::DisableFlags(Flags flags) {
		this->Get()->m_flags &= ~flags;
	}

	bool WantLoadInfo::HasFlags(Flags flags) const {
		return (this->Get()->m_flags & flags) == flags;
	}

	LevelSpec::Layer WantLoadInfo::GetLayer() const {
		return this->Get()->m_layerMask;
	}

	void WantLoadInfo::SetLayer(LevelSpec::Layer layers) {
		this->Get()->m_layerMask = layers;
	}

	void WantLoadInfo::EnableLayer(LevelSpec::Layer layers) {
		this->Get()->m_layerMask = LevelSpec::EnableLayer(GetLayer(), layers);
	}

	void WantLoadInfo::DisableLayer(LevelSpec::Layer layers) {
		this->Get()->m_layerMask = LevelSpec::DisableLayer(GetLayer(), layers);
	}

	bool WantLoadInfo::HasLayer(LevelSpec::Layer layers) const {
		return LevelSpec::HasLayer(GetLayer(), layers);
	}

	INIT_FUNCTION_PTR(WantLoadInfo::LoadRegistry_WantLoadInfo_Constructor);

#endif
}
