#pragma once
#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/components/SdkRegenny.hpp"

#if defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/ndlib/debug/DMENU.hpp>
#endif

namespace NdGameSdk::gamelib::debug {
	class NdDevMenu;
}

namespace NdGameSdk::ndlib::debug {

	class NdGameSdk_API DMENU : public ISdkRegenny<regenny::shared::ndlib::debug::DMENU>
	{
	public:

		class Menu;
		class MenuGroup;

		class Component : public ISdkRegenny<regenny::shared::ndlib::debug::DMENU::Component> {
		public:
			std::string Name();
			void SetName(const char* new_name);
			std::string Description();
			void SetDescription(const char* new_description);

			uint64_t Data();

			Menu* SubMenu();
			MenuGroup* MenuGroup();

			template <typename ComponentType = Component>
			ComponentType* NextDMenuComponent() {
				return reinterpret_cast<ComponentType*>(this->Get()->m_NextDMenuComponent);
			}

		protected:
			static regenny::shared::ndlib::debug::DMENU::Component::VTable* VTable;
			friend class NdGameSdk::gamelib::debug::NdDevMenu;
		};

		class ItemLine : public Component {
		private:
			static regenny::shared::ndlib::debug::DMENU::ItemLine::VTable* VTable;
			friend class NdGameSdk::gamelib::debug::NdDevMenu;
		};

		class MenuGroup : public ISdkRegenny<regenny::shared::ndlib::debug::DMENU::MenuGroup, Component> {
		public:
			Menu* RootMenu();
		private:
			static regenny::shared::ndlib::debug::DMENU::MenuGroup::VTable* VTable;
			friend class NdGameSdk::gamelib::debug::NdDevMenu;
		};

		class Menu : public ISdkRegenny<regenny::shared::ndlib::debug::DMENU::Menu, Component> {
		private:
			static regenny::shared::ndlib::debug::DMENU::Menu::VTable* VTable;
			friend class NdGameSdk::gamelib::debug::NdDevMenu;
		};

		class Item : public ISdkRegenny<regenny::shared::ndlib::debug::DMENU::Item, Component> {
		public:
			void* CallBackFunct();
		};

		class ItemSubText : public Item {
		private:
			static regenny::shared::ndlib::debug::DMENU::ItemSubText::VTable0* VTable;
			friend class NdGameSdk::gamelib::debug::NdDevMenu;
		};

		class ItemSubmenu : public ISdkRegenny<regenny::shared::ndlib::debug::DMENU::ItemSubmenu, Item> {
		public:
			Menu* SubMenu();
		private:
			static regenny::shared::ndlib::debug::DMENU::ItemSubmenu::VTable0* VTable;
			friend class NdGameSdk::gamelib::debug::NdDevMenu;	
		};

		class ItemBool : public ISdkRegenny<regenny::shared::ndlib::debug::DMENU::ItemBool, Item> {
		public:
			bool IsActive();
		private:
			static regenny::shared::ndlib::debug::DMENU::ItemBool::VTable0* VTable;
			friend class NdGameSdk::gamelib::debug::NdDevMenu;
		};

		class ItemDouble : public ISdkRegenny<regenny::shared::ndlib::debug::DMENU::ItemDouble, Item> {
		private:
			static regenny::shared::ndlib::debug::DMENU::ItemDouble::VTable0* VTable;
			friend class NdGameSdk::gamelib::debug::NdDevMenu;
		};

		class ItemFloat : public ISdkRegenny<regenny::shared::ndlib::debug::DMENU::ItemFloat, Item> {
		private:
			static regenny::shared::ndlib::debug::DMENU::ItemFloat::VTable0* VTable;
			friend class NdGameSdk::gamelib::debug::NdDevMenu;
		};

		class ItemFunction : public ISdkRegenny<regenny::shared::ndlib::debug::DMENU::ItemFunction, Item> {
		private:
			static regenny::shared::ndlib::debug::DMENU::ItemFunction::VTable0* VTable;
			friend class NdGameSdk::gamelib::debug::NdDevMenu;
		};

		class ItemSelection : public ISdkRegenny<regenny::shared::ndlib::debug::DMENU::ItemSelection, Item> {
		private:
			static regenny::shared::ndlib::debug::DMENU::ItemSelection::VTable0* VTable;
			friend class NdGameSdk::gamelib::debug::NdDevMenu;
		};

		MenuGroup* DevMenu();
		MenuGroup* QuickMenu();
		MenuGroup* FavoritesMenu();

	};

	static_assert(sizeof(DMENU) == 0x670, "Size of DMENU is not correct.");
	static_assert(sizeof(DMENU::Component) == 0xb0, "Size of DMENU::Component is not correct.");

	static_assert(sizeof(DMENU::Menu) == sizeof(DMENU::Component) + 0x30, "Size of DMENU::Menu is not correct.");
	static_assert(sizeof(DMENU::MenuGroup) == sizeof(DMENU::Component) + 0x280, "Size of DMENU::MenuGroup is not correct.");
	static_assert(sizeof(DMENU::Item) == sizeof(DMENU::Component) + 0x8, "Size of DMENU::Item is not correct.");

	static_assert(sizeof(DMENU::ItemSubmenu) == sizeof(DMENU::Item) + 0x10, "Size of DMENU::ItemSubmenu is not correct.");
	static_assert(sizeof(DMENU::ItemBool) == sizeof(DMENU::Item) + 0x8, "Size of DMENU::ItemBool is not correct.");
	static_assert(sizeof(DMENU::ItemDouble) == sizeof(DMENU::Item) + 0xb8, "Size of DMENU::ItemDouble is not correct.");
	static_assert(sizeof(DMENU::ItemFloat) == sizeof(DMENU::Item) + 0x98, "Size of DMENU::ItemFloat is not correct.");
	static_assert(sizeof(DMENU::ItemFunction) == sizeof(DMENU::Item) + 0x10, "Size of DMENU::ItemFunction is not correct.");
	static_assert(sizeof(DMENU::ItemSelection) == sizeof(DMENU::Item) + 0x30, "Size of DMENU::ItemSelection is not correct.");

}