#include "level-def.hpp"

namespace NdGameSdk::gamelib::level {
#if defined(T2R)

	std::string_view LevelDef::GetLevelName() const {
		return this->Get()->m_name;
	}

	StringId64 LevelDef::GetLevelId() const {
		return this->Get()->m_id;
	}

	void LevelDef::Update() {
		always_assert(LevelDefCollection_LevelDef_Update == nullptr, "LevelDef::Update missing function pointer");
		LevelDefCollection_LevelDef_Update(this);
	}

	StaticArray<LevelDef::PackageDef>& LevelDef::GetPackagesDefs() {
		return reinterpret_cast<StaticArray<PackageDef>&>(this->Get()->m_packageDefs);
	}

	const StaticArray<LevelDef::PackageDef>& LevelDef::GetPackagesDefs() const {
		return reinterpret_cast<const StaticArray<PackageDef>&>(this->Get()->m_packageDefs);
	}

	StaticArray<LevelDef::ActorDefs>& LevelDef::GetActorDefs() {
		return reinterpret_cast<StaticArray<ActorDefs>&>(this->Get()->m_actorDefs);
	}

	const StaticArray<LevelDef::ActorDefs>& LevelDef::GetActorDefs() const {
		return reinterpret_cast<const StaticArray<ActorDefs>&>(this->Get()->m_actorDefs);
	}

	StaticArray<StringId64>& LevelDef::GetCaches() {
		return reinterpret_cast<StaticArray<StringId64>&>(this->Get()->m_caches);
	}

	const StaticArray<StringId64>& LevelDef::GetCaches() const {
		return reinterpret_cast<const StaticArray<StringId64>&>(this->Get()->m_caches);
	}

	StaticArray<StringId64>& LevelDef::GetModuleIds() {
		return reinterpret_cast<StaticArray<StringId64>&>(this->Get()->m_moduleIds);
	}

	const StaticArray<StringId64>& LevelDef::GetModuleIds() const {
		return reinterpret_cast<const StaticArray<StringId64>&>(this->Get()->m_moduleIds);
	}

	StaticArray<StringId64>& LevelDef::GetRenderSettingsForLutTables() {
		return reinterpret_cast<StaticArray<StringId64>&>(this->Get()->m_renderSettingsForLutTablesIds);
	}

	const StaticArray<StringId64>& LevelDef::GetRenderSettingsForLutTables() const {
		return reinterpret_cast<const StaticArray<StringId64>&>(this->Get()->m_renderSettingsForLutTablesIds);
	}

	StaticArray<LevelDef::ParticleModuleDef>& LevelDef::GetParticleModuleDefs() {
		return reinterpret_cast<StaticArray<ParticleModuleDef>&>(this->Get()->m_particleModuleDef);
	}

	const StaticArray<LevelDef::ParticleModuleDef>& LevelDef::GetParticleModuleDefs() const {
		return reinterpret_cast<const StaticArray<ParticleModuleDef>&>(this->Get()->m_particleModuleDef);
	}

	StaticArray<LevelDef::SoundBankDef>& LevelDef::GetSoundBankDefs() {
		return reinterpret_cast<StaticArray<SoundBankDef>&>(this->Get()->m_soundBankDefs);
	}

	const StaticArray<LevelDef::SoundBankDef>& LevelDef::GetSoundBankDefs() const {
		return reinterpret_cast<const StaticArray<SoundBankDef>&>(this->Get()->m_soundBankDefs);
	}

	StaticArray<LevelDef::SoundBankDef>& LevelDef::GetVoxCharacterSoundBankDefs() {
		return reinterpret_cast<StaticArray<SoundBankDef>&>(this->Get()->m_voxCharactersSoundBankDefs);
	}

	const StaticArray<LevelDef::SoundBankDef>& LevelDef::GetVoxCharacterSoundBankDefs() const {
		return reinterpret_cast<const StaticArray<SoundBankDef>&>(this->Get()->m_voxCharactersSoundBankDefs);
	}

	std::string_view LevelDef::GetAssociatedPartModuleName() const {
		return this->Get()->m_associatedPartModuleName;
	}

	LevelDef::AsyncTxtLoad* LevelDef::GetAsyncTxtLoad() const {
		return reinterpret_cast<AsyncTxtLoad*>(this->Get()->m_AsyncTxtLoad);
	}

	LevelDef::State LevelDef::GetState() const {
		return this->Get()->m_state;
	}

	LevelDef::Flags LevelDef::GetFlags() const {
		return this->Get()->m_bits;
	}

	void LevelDef::SetFlags(Flags flags) {
		this->Get()->m_bits = flags;
	}

	void LevelDef::EnableFlags(Flags flags) {
		this->Get()->m_bits |= flags;
	}

	void LevelDef::DisableFlags(Flags flags) {
		this->Get()->m_bits &= ~flags;
	}

	bool LevelDef::HasFlags(Flags flags) const {
		return (this->Get()->m_bits & flags) == flags;
	}

	bool LevelDef::IsPartPackagesDisabled() const {
		return HasFlags(Flags::DisablePartPackages);
	}

	std::string_view LevelDef::ActorDefs::GetName() const {
		return this->Get()->m_pName;
	}

	StringId64 LevelDef::ActorDefs::GetId() const {
		return this->Get()->m_id;
	}

	std::string_view LevelDef::PackageDef::GetName() const {
		return this->Get()->m_pName;
	}

	StringId64 LevelDef::PackageDef::GetId() const {
		return this->Get()->m_id;
	}

	LevelSpec::Layer LevelDef::PackageDef::GetLayer() const {
		return this->Get()->m_layer;
	}

	void LevelDef::PackageDef::SetLayer(LevelSpec::Layer layers) {
		this->Get()->m_layer = layers;
	}

	void LevelDef::PackageDef::EnableLayer(LevelSpec::Layer layers) {
		this->Get()->m_layer = LevelSpec::EnableLayer(GetLayer(), layers);
	}

	void LevelDef::PackageDef::DisableLayer(LevelSpec::Layer layers) {
		this->Get()->m_layer = LevelSpec::DisableLayer(GetLayer(), layers);
	}

	bool LevelDef::PackageDef::HasLayer(LevelSpec::Layer layers) const {
		return LevelSpec::HasLayer(GetLayer(), layers);
	}

	bool LevelDef::PackageDef::IsOptional() const {
		return this->Get()->m_optional;
	}

	StringId64 LevelDef::ParticleModuleDef::GetId() const {
		return this->Get()->m_id;
	}

	bool LevelDef::ParticleModuleDef::IsIgnored() const {
		return this->Get()->m_ignore;
	}

	std::string_view LevelDef::SoundBankDef::GetName() const {
		return this->Get()->m_pName;
	}

	FileSystemInternal::ReadOnlyFileHandle* LevelDef::AsyncTxtLoad::GetFileHandle() const {
		return reinterpret_cast<FileSystemInternal::ReadOnlyFileHandle*>(&this->Get()->m_handle);
	}

	FileSystemInternal::ReadOperation* LevelDef::AsyncTxtLoad::GetReadOperation() const {
		return reinterpret_cast<FileSystemInternal::ReadOperation*>(&this->Get()->m_readOp);
	}

	uint64_t LevelDef::AsyncTxtLoad::GetFileSize() const {
		return this->Get()->m_fileSize;
	}

	uint64_t LevelDef::AsyncTxtLoad::GetBytesReaded() const {
		return this->Get()->m_bytesRead;
	}

	//INIT_FUNCTION_PTR(LevelDef::LevelDefCollection_LevelDef_LoadTxtFile);
	//INIT_FUNCTION_PTR(LevelDef::LevelDefCollection_LevelDef_LoadAsyncTxtFile);
	INIT_FUNCTION_PTR(LevelDef::LevelDefCollection_LevelDef_Update);

#endif

}
