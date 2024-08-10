#include "nd-dmenu.hpp"

namespace NdGameSdk::ndlib::debug {

	regenny::shared::ndlib::debug::DMENU::Component::VTable* DMENU::Component::VTable{};
	regenny::shared::ndlib::debug::DMENU::Menu::VTable0* DMENU::Menu::VTable{};
	regenny::shared::ndlib::debug::DMENU::MenuGroup::VTable0* DMENU::MenuGroup::VTable{};

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
		return this->Get()->m_pname;
	}

	void DMENU::Component::SetName(const char* new_name) {
		strcpy(this->Get()->m_pname, new_name);
	}

	DMENU::Menu* DMENU::MenuGroup::RootMenu() {
		return reinterpret_cast<DMENU::Menu*>(this->Get()->m_RootMenu);
	}

}