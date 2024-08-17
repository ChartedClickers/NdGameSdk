#pragma once
#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/components/SdkRegenny.hpp"

#include <Utility/cmacros/for_each.hpp>
#include <Utility/color.hpp>
#include <boost/function.hpp>

#if defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/ndlib/debug/DMENU.hpp>
#endif

namespace NdGameSdk::gamelib::debug {
	class NdDevMenu;
}

namespace NdGameSdk::ndlib::debug {

#define ITEM_SELECTION_ENTRY(name) { #name, name },
#define DEFINE_DMENU_ItemSelection(enum_name, ...) \
			enum enum_name { __VA_ARGS__ }; \
			NdGameSdk::ndlib::debug::DMENU::ItemSelection::Item_selection enum_name##_selection[] = { \
				FOR_EACH(ITEM_SELECTION_ENTRY,__VA_ARGS__) \
				{nullptr, 0} \
			}

	class NdGameSdk_API DMENU : public ISdkRegenny<regenny::shared::ndlib::debug::DMENU>
	{
	public:

		class Menu;
		class MenuGroup;

		using Message = regenny::shared::ndlib::debug::DMENU::Message;

		class Component : public ISdkRegenny<regenny::shared::ndlib::debug::DMENU::Component> {
		public:
			std::string Name();
			void SetName(const char* new_name);
			std::string Description();
			void SetDescription(const char* new_description);

			Color GetColor();
			Color GetSelectedColor();
			void SetColor(Color color);
			void SetSelectedColor(Color color);

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
			using SubmenuCallbackPtr = bool(*)(DMENU::ItemSubmenu&, DMENU::Message);
			using SubmenuCallback = boost::function<std::remove_pointer<SubmenuCallbackPtr>::type>;

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

		class ItemDecimal : public ISdkRegenny<regenny::shared::ndlib::debug::DMENU::ItemDecimal, Item> {
		public:
			struct ValueParams {
				uint32_t MinValue;
				uint32_t MaxValue;
			};

			struct StepParams {
				uint32_t StepValue;
				uint32_t DoubleStepValue;
			};

			ValueParams GetValueParams();
			StepParams GetStepParams();

		private:
			static regenny::shared::ndlib::debug::DMENU::ItemDecimal::VTable0* VTable;
			friend class NdGameSdk::gamelib::debug::NdDevMenu;
		};

		class ItemFloat : public ISdkRegenny<regenny::shared::ndlib::debug::DMENU::ItemFloat, Item> {
		public:
			struct ValueParams {
				float MinValue;
				float MaxValue;
			};

			struct StepParams {
				float StepValue;
				float DoubleStepValue;
			};

			ValueParams GetValueParams();
			StepParams GetStepParams();

		private:
			static regenny::shared::ndlib::debug::DMENU::ItemFloat::VTable0* VTable;
			friend class NdGameSdk::gamelib::debug::NdDevMenu;
		};

		class ItemFunction : public ISdkRegenny<regenny::shared::ndlib::debug::DMENU::ItemFunction, Item> {
		public:
			using FunctionCallbackPtr = bool(*)(DMENU::ItemFunction&, DMENU::Message);
			using FunctionCallback = boost::function<std::remove_pointer<FunctionCallbackPtr>::type>;

			bool IsActive();
		private:
			static regenny::shared::ndlib::debug::DMENU::ItemFunction::VTable0* VTable;
			friend class NdGameSdk::gamelib::debug::NdDevMenu;
		};

		class ItemSelection : public ISdkRegenny<regenny::shared::ndlib::debug::DMENU::ItemSelection, Item> {
		public:
			struct Item_selection {
				const char* selection_title;
				uint64_t selection_value;
			};

			Item_selection& ItemSelections();

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
	static_assert(sizeof(DMENU::ItemDecimal) == sizeof(DMENU::Item) + 0xb8, "Size of DMENU::ItemDecimal is not correct.");
	static_assert(sizeof(DMENU::ItemFloat) == sizeof(DMENU::Item) + 0x98, "Size of DMENU::ItemFloat is not correct.");
	static_assert(sizeof(DMENU::ItemFunction) == sizeof(DMENU::Item) + 0x10, "Size of DMENU::ItemFunction is not correct.");
	static_assert(sizeof(DMENU::ItemSelection) == sizeof(DMENU::Item) + 0x30, "Size of DMENU::ItemSelection is not correct.");

}