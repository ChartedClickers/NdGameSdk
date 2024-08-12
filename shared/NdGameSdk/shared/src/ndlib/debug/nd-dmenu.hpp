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

		class Item : public ISdkRegenny<regenny::shared::ndlib::debug::DMENU::Item, Component> {};

		class ItemEntry : public ISdkRegenny<regenny::shared::ndlib::debug::DMENU::ItemEntry, Item> {
		private:
			static regenny::shared::ndlib::debug::DMENU::ItemEntry::VTable0* VTable;
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

	static_assert(sizeof(DMENU::ItemEntry) == sizeof(DMENU::Item) + 0x10, "Size of DMENU::ItemEntry is not correct.");
}