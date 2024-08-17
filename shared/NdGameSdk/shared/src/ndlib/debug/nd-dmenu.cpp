#include "nd-dmenu.hpp"

namespace NdGameSdk::ndlib::debug {

	regenny::shared::ndlib::debug::DMENU::Component::VTable* DMENU::Component::VTable{};
	regenny::shared::ndlib::debug::DMENU::ItemLine::VTable* DMENU::ItemLine::VTable{};
	regenny::shared::ndlib::debug::DMENU::Menu::VTable* DMENU::Menu::VTable{};
	regenny::shared::ndlib::debug::DMENU::MenuGroup::VTable* DMENU::MenuGroup::VTable{};

	regenny::shared::ndlib::debug::DMENU::ItemSubText::VTable0* DMENU::ItemSubText::VTable{};
	regenny::shared::ndlib::debug::DMENU::ItemSubmenu::VTable0* DMENU::ItemSubmenu::VTable{};
	regenny::shared::ndlib::debug::DMENU::ItemBool::VTable0* DMENU::ItemBool::VTable{};
	regenny::shared::ndlib::debug::DMENU::ItemDecimal::VTable0* DMENU::ItemDecimal::VTable{};
	regenny::shared::ndlib::debug::DMENU::ItemFloat::VTable0* DMENU::ItemFloat::VTable{};
	regenny::shared::ndlib::debug::DMENU::ItemFunction::VTable0* DMENU::ItemFunction::VTable{};
	regenny::shared::ndlib::debug::DMENU::ItemSelection::VTable0* DMENU::ItemSelection::VTable{};

	DMENU::MenuGroup* DMENU::DevMenu() {
		return reinterpret_cast<DMENU::MenuGroup*>(this->Get()->m_DevMenu);
	}

	DMENU::MenuGroup* DMENU::QuickMenu() {
		return reinterpret_cast<DMENU::MenuGroup*>(this->Get()->m_QuickMenu);
	}

	DMENU::MenuGroup* DMENU::FavoritesMenu() {
		return reinterpret_cast<DMENU::MenuGroup*>(this->Get()->m_FavoritesMenu);
	}

	std::string DMENU::Component::Name() {
		auto name = this->Get()->m_pname;
		return name != nullptr ? name : "Component";
	}

	void DMENU::Component::SetName(const char* new_name) {
		strcpy(this->Get()->m_pname, new_name);
	}

	std::string DMENU::Component::Description() {
		return this->Get()->m_pDescription;
	}

	void DMENU::Component::SetDescription(const char* new_description) {
		strcpy(this->Get()->m_pDescription, new_description);
	}

	uint64_t DMENU::Component::Data() {
		return this->Get()->m_data;
	}

	DMENU::Menu* DMENU::Component::SubMenu() {
		return reinterpret_cast<DMENU::Menu*>(this->Get()->m_pSubMenu);
	}

	DMENU::MenuGroup* DMENU::Component::MenuGroup() {
		return reinterpret_cast<DMENU::MenuGroup*>(this->Get()->m_MenuGroup);
	}

	DMENU::Menu* DMENU::MenuGroup::RootMenu() {
		return reinterpret_cast<DMENU::Menu*>(this->Get()->m_RootMenu);
	}

	void* DMENU::Item::CallBackFunct() {
		return this->Get()->m_callbackFunct;
	}

	DMENU::Menu* DMENU::ItemSubmenu::SubMenu() {
		return reinterpret_cast<DMENU::Menu*>(this->Get()->m_pHeader);
	}

	bool DMENU::ItemBool::IsActive() {
		return this->Get()->m_status;
	}

	DMENU::ItemDecimal::ValueParams DMENU::ItemDecimal::GetValueParams() {
		return { (uint32_t)this->Get()->m_MinValue, (uint32_t)this->Get()->m_MaxValue };
	}

	DMENU::ItemDecimal::StepParams DMENU::ItemDecimal::GetStepParams() {
		return { (uint32_t)this->Get()->m_StepValue, (uint32_t)this->Get()->m_DoubleStepValue };
	}

	DMENU::ItemFloat::ValueParams DMENU::ItemFloat::GetValueParams() {
		return { this->Get()->m_MinValue, this->Get()->m_MaxValue };
	}

	DMENU::ItemFloat::StepParams DMENU::ItemFloat::GetStepParams() {
		return { this->Get()->m_StepValue, this->Get()->m_DoubleStepValue };
	}

	bool DMENU::ItemFunction::IsActive() {
		return this->Get()->m_isActive;
	}

	DMENU::ItemSelection::Item_selection** DMENU::ItemSelection::ItemSelections() {
		return reinterpret_cast<DMENU::ItemSelection::Item_selection**>(this->Get()->m_SelectionStruct);
	}

}