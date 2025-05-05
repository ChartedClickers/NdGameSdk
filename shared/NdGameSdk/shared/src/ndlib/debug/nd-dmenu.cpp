#include "nd-dmenu.hpp"
#include <NdGameSdk/shared/src/gamelib/debug/nd-dev-menu.hpp>

namespace NdGameSdk::ndlib::debug {

	regenny::shared::ndlib::debug::DMENU::Component::VTable* DMENU::Component::VTable{};
	regenny::shared::ndlib::debug::DMENU::ItemLine::VTable* DMENU::ItemLine::VTable{};
	regenny::shared::ndlib::debug::DMENU::String::VTable* DMENU::String::VTable{};
	regenny::shared::ndlib::debug::DMENU::Menu::VTable* DMENU::Menu::VTable{};
	regenny::shared::ndlib::debug::DMENU::MenuGroup::VTable* DMENU::MenuGroup::VTable{};
	regenny::shared::ndlib::debug::DMENU::KeyBoard::VTable* DMENU::KeyBoard::VTable{};
	regenny::shared::ndlib::debug::DMENU::ItemPlaceHolder::VTable* DMENU::ItemPlaceHolder::VTable{};

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

	void DMENU::Component::ChangeName(const char* newName) {
		if (!newName) return;

		char* buf = this->Get()->m_pname;
		if (buf) {
			std::size_t cap = std::strlen(buf);
			std::size_t n = std::strlen(newName);
			if (n > cap) n = cap;
			std::memcpy(buf, newName, n);
			buf[n] = '\0';
		}
	}

	std::string DMENU::Component::Description() {
		auto Description = this->Get()->m_pDescription;
		return Description != nullptr ? Description : std::string();
	}

	void DMENU::Component::ChangeDescription(const char* newdescription) {

		if (!newdescription) return;

		char* buf = this->Get()->m_pDescription;
		if (buf) {
			std::size_t cap = std::strlen(buf);
			std::size_t n = std::strlen(newdescription);
			if (n > cap) n = cap;
			std::memcpy(buf, newdescription, n);
			buf[n] = '\0';
		}
	}

	Color DMENU::Component::GetColor() {
		return Color(this->Get()->m_color);
	}

	Color DMENU::Component::GetSelectedColor() {
		return Color(this->Get()->m_selectcolor);
	}

	void DMENU::Component::SetColor(Color color) {
		this->Get()->m_color = color.toUint64();
	}

	void DMENU::Component::SetSelectedColor(Color color) {
		this->Get()->m_selectcolor = color.toUint64();
	}

	uint64_t DMENU::Component::Data() {
		return this->Get()->m_data;
	}

	DMENU::Component* DMENU::Component::ParentComponent() {
		return reinterpret_cast<DMENU::Component*>(this->Get()->m_ParentComponent);
	}

	DMENU::MenuGroup* DMENU::Component::MenuGroup() {
		return reinterpret_cast<DMENU::MenuGroup*>(this->Get()->m_MenuGroup);
	}

	DMENU::Menu* DMENU::MenuGroup::RootMenu() {
		return reinterpret_cast<DMENU::Menu*>(this->Get()->m_RootMenu);
	}

	bool DMENU::Menu::IsActive() {
		return this->Get()->m_isActive;
	}

	int DMENU::Menu::GetMenuItemsCount() {
		return this->Get()->m_MaxPagePointers;
	}

	bool DMENU::Menu::DeleteItem(DMENU::Component* pItem) {
		return DMENU::s_NdDevMenu->Menu_DeleteItem(this, pItem);
	}

	DMENU::Menu* DMENU::Menu::DeleteAllItems(bool freeArena) {
		return DMENU::s_NdDevMenu->Menu_DeleteAllItems(this, freeArena);
	}

	DMENU::Component* DMENU::Menu::PushBackItem(DMENU::Component* pComponent) {
		return DMENU::s_NdDevMenu->DMENU_AppendComponent(this, pComponent);
	}

	DMENU::KeyBoard::State DMENU::KeyBoard::GetState()
	{
		auto keyboard_view = this->Get();
		return DMENU::KeyBoard::State
		{
			keyboard_view->m_isEditing,
			keyboard_view->m_needsUpdate,
			keyboard_view->m_isDirty,
			keyboard_view->m_cursorIndex
		};
	}

	uint64_t DMENU::KeyBoard::GetActiveKey() {
		return this->Get()->m_lastKey;
	}

	uint64_t DMENU::KeyBoard::GetMaxInputLength() {
		return this->Get()->m_maxInputLength;
	}

	uint64_t DMENU::KeyBoard::SetMaxInputLength(uint64_t length) {
		return this->Get()->m_maxInputLength = length;
	}

	uint64_t DMENU::KeyBoard::SetBufferPtr(const char* pStr) {
		// guarantee that `pStr` will remain valid for as long as the component lives
		this->Get()->m_inputBufferPtr = const_cast<char*>(pStr);
		return reinterpret_cast<uint64_t>(this->Get()->m_inputBufferPtr);
	}

	char* DMENU::KeyBoard::GetInputBuffer() {
		return this->Get()->m_inputBuffer;
	}

	char* DMENU::KeyBoard::GetDisplayBuffer() {
		return this->Get()->m_displayBuffer;
	}

	const char* DMENU::ItemPlaceHolder::GetContent() {
		return this->Get()->m_placeholder;
	}

	void DMENU::ItemPlaceHolder::SetContent(const char* content) {
		if (!content) return;
		char* buf = this->Get()->m_placeholder;
		if (buf) {
			std::size_t cap = std::strlen(buf);
			std::size_t n = std::strlen(content);
			if (n > cap) n = cap;
			std::memcpy(buf, content, n);
			buf[n] = '\0';
		}
	}

	void* DMENU::Item::CallBackFunct() {
		return this->Get()->m_callbackFunct;
	}

	DMENU::Menu* DMENU::ItemSubmenu::MenuEntry() {
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

	void DMENU::ItemFunction::SetActive(bool status) {
		this->Get()->m_isActive = status;
	}

	DMENU::ItemSelection::Item_selection& DMENU::ItemSelection::ItemSelections() {
		return *reinterpret_cast<DMENU::ItemSelection::Item_selection*>(this->Get()->m_SelectionStruct);
	}

	gamelib::debug::NdDevMenu* DMENU::s_NdDevMenu = nullptr;

}
