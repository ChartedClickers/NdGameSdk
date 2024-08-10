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
		class Component : public ISdkRegenny<regenny::shared::ndlib::debug::DMENU::Component> 
		{
		public:
			std::string Name();
			void SetName(const char* new_name);

			template <typename ComponentType = Component>
			ComponentType* SubMenu() {
				return reinterpret_cast<ComponentType*>(this->Get()->m_pSubMenu);
			}

			template <typename ComponentType = Component>
			ComponentType* NextDMenuComponent() {
				return reinterpret_cast<ComponentType*>(this->Get()->m_NextDMenuComponent);
			}

			template <typename ComponentType = Component>
			ComponentType* MenuGroup() {
				return reinterpret_cast<ComponentType*>(this->Get()->m_MenuGroup);
			}
		private:
			static regenny::shared::ndlib::debug::DMENU::Component::VTable* VTable;
			friend class NdGameSdk::gamelib::debug::NdDevMenu;
		};

		class Menu : public ISdkRegenny<regenny::shared::ndlib::debug::DMENU::Menu, Component> 
		{
		private:
			static regenny::shared::ndlib::debug::DMENU::Menu::VTable0* VTable;
			friend class NdGameSdk::gamelib::debug::NdDevMenu;
		};

		class MenuGroup : public ISdkRegenny<regenny::shared::ndlib::debug::DMENU::MenuGroup, Component> 
		{
		public:
			DMENU::Menu* RootMenu();
		private:
			static regenny::shared::ndlib::debug::DMENU::MenuGroup::VTable0* VTable;
			friend class NdGameSdk::gamelib::debug::NdDevMenu;
		};

		DMENU::MenuGroup* DevMenu();
		DMENU::MenuGroup* QuickMenu();
		DMENU::MenuGroup* FavoritesMenu();
	};

	static_assert(sizeof(DMENU) == 0x670, "Size of DMENU is not correct.");
	static_assert(sizeof(DMENU::Component) == 0xb0, "Size of DMENU::Component is not correct.");

	static_assert(sizeof(DMENU::Menu) == sizeof(DMENU::Component) + 0x30, "Size of DMENU::Menu is not correct.");
	static_assert(sizeof(DMENU::MenuGroup) == sizeof(DMENU::Component) + 0x280, "Size of DMENU::MenuGroup is not correct.");
}