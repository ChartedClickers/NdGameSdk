#pragma once
#include "NdGameSdk/sdk.hpp"
#include "NdGameSdk/components/SdkRegenny.hpp"

#include <Utility/cmacros/for_each.hpp>
#include <Utility/color.hpp>
#include <boost/function.hpp>

#if defined(T2R)
#include <NdGameSdk/regenny/t2r/shared/ndlib/debug/DMENU.hpp>
#elif defined(T1X)
#include <NdGameSdk/regenny/t1x/shared/ndlib/debug/DMENU.hpp>
#endif

namespace NdGameSdk::gamelib::debug {
	class NdDevMenu;
}

namespace NdGameSdk::ndlib::debug {

#define ITEM_SELECTION_ENTRY(name) { #name, name },
#define DEFINE_DMENU_ItemSelection(enum_name, ...) \
			enum enum_name { __VA_ARGS__ }; \
			inline NdGameSdk::ndlib::debug::DMENU::ItemSelection::Item_selection enum_name##_selection[] = { \
				FOR_EACH(ITEM_SELECTION_ENTRY,__VA_ARGS__) \
				{nullptr, 0} \
			}

	class NdGameSdk_API DMENU : public ISdkRegenny<regenny::shared::ndlib::debug::DMENU>
	{
	public:

		class Menu;
		class MenuGroup;
		class Item;

		using Message = regenny::shared::ndlib::debug::DMENU::Message;

		class Component : public ISdkRegenny<regenny::shared::ndlib::debug::DMENU::Component> {
		public:
			std::string Name();
			void ChangeName(const char* newName);
			std::string Description();
			void ChangeDescription(const char* newdescription);

			Color GetColor();
			Color GetSelectedColor();
			void SetColor(Color color);
			void SetSelectedColor(Color color);

			long GetLeftPad();
			void SetLeftPad(long leftPad);

			uint64_t Data();

			MenuGroup* MenuGroup();
	        
			template<typename ComponentType = Component>
			ComponentType* ParentComponent() const {
				return reinterpret_cast<ComponentType*>(this->Get()->m_ParentComponent);
			}

			template<typename ComponentType = Component>
			ComponentType* NextDMenuComponent() const {
				return reinterpret_cast<ComponentType*>(this->Get()->m_NextDMenuComponent);
			}

			struct ComponentRange {
				struct iterator {
					Component* cur;
					iterator(Component* c) : cur(c) {}
					bool operator!=(iterator const& o) const { return cur != o.cur; }
					Component* operator*() const { return cur; }
					iterator& operator++() {
						cur = cur->NextDMenuComponent<Component>();
						return *this;
					}
				};
				Component* head;
				size_t size() const {
					auto count = 0;
					for (auto* cur = head; cur; cur = cur->NextDMenuComponent<Component>()) {
						++count;
					}
					return count;
				}
				iterator begin() const { return { head }; }
				iterator end()   const { return { nullptr }; }
			};

			ComponentRange GetNextComponentsRange() const {
				return { this->template NextDMenuComponent<>() };
			}

			template<class ComponentType = Component>
			ComponentType* GetNextComponent(std::size_t index = 0) {
				auto* cur = this->template NextDMenuComponent<>();
				for (std::size_t i = 0; cur && i < index; ++i) {
					cur = cur->template NextDMenuComponent<>();
				}
				return static_cast<ComponentType*>(cur);
			}

		protected:
			static regenny::shared::ndlib::debug::DMENU::Component::VTable* VTable;
			friend class gamelib::debug::NdDevMenu;
		};

		class ItemLine : public Component {
		private:
			static regenny::shared::ndlib::debug::DMENU::ItemLine::VTable* VTable;
			friend class gamelib::debug::NdDevMenu;
		};

		class MenuGroup : public ISdkRegenny<regenny::shared::ndlib::debug::DMENU::MenuGroup, Component> {
		public:
			Menu* RootMenu();
		private:
			static regenny::shared::ndlib::debug::DMENU::MenuGroup::VTable* VTable;
			friend class gamelib::debug::NdDevMenu;
		};

		class Menu : public ISdkRegenny<regenny::shared::ndlib::debug::DMENU::Menu, Component> {
		public:
			using LazyInitCallbackPtr = void(*)(DMENU::Menu&);
			using LazyInitCallback = boost::function<std::remove_pointer<LazyInitCallbackPtr>::type>;

			template<typename Component = Component>
			Component* ItemBegin() const {
				return reinterpret_cast<Component*>(this->Get()->m_Item);
			}

			ComponentRange Items() const {
				return { ItemBegin() };
			}

			template<class ComponentType = Component>
			ComponentType* GetComponent(std::size_t index = 0) {
				static_assert(std::is_base_of_v<Component, ComponentType>, "ComponentType must derive from Component");

				const auto max = static_cast<std::size_t>(this->Get()->m_MaxPagePointers);
				if (index >= max) return nullptr;

				auto* p = ItemBegin();
				for (std::size_t i = 0; i < index && p; ++i) {
					p = p->NextDMenuComponent();
				}

				return static_cast<ComponentType*>(p);
			}

			bool IsActive();
			int GetMenuItemsCount();
			int GetWidth();
			void SetPagePointer(int num);
			bool DeleteItem(DMENU::Component* pItem);
			void SetLazyInitHandler(LazyInitCallback* handler);
			DMENU::Menu* DeleteAllItems(bool freeArena);
			DMENU::Component* PushBackItem(DMENU::Component* pComponent);
		private:
			static regenny::shared::ndlib::debug::DMENU::Menu::VTable* VTable;
			friend class gamelib::debug::NdDevMenu;
		};

		class KeyBoard : public ISdkRegenny<regenny::shared::ndlib::debug::DMENU::KeyBoard, Component> {
		public:
			struct State {
				bool isEditing;
				bool NeedsUpdate;
				bool isDirty;
				uint64_t cursorIndex;
			};

			bool HasInputSettled(std::chrono::milliseconds interval = std::chrono::milliseconds{ 200 });

			State GetState();
			uint64_t GetActiveKey();
			uint64_t GetMaxInputLength();
			uint64_t GetCursorIndex();
			char* GetInputBuffer();
			char* GetDisplayBuffer();

			uint64_t SetMaxInputLength(uint64_t length);
			uint64_t SetBufferPtr(const char* pStr);
		private:
			static regenny::shared::ndlib::debug::DMENU::KeyBoard::VTable* VTable;
			friend class gamelib::debug::NdDevMenu;
		};

		class ItemPlaceHolder : public ISdkRegenny<regenny::shared::ndlib::debug::DMENU::ItemPlaceHolder, Component> {
		public:
			const char* GetContent();
			void SetContent(const char* content);
		private:
			static regenny::shared::ndlib::debug::DMENU::ItemPlaceHolder::VTable* VTable;
			friend class gamelib::debug::NdDevMenu;
		};

		class String : public Component {
		private:
			static regenny::shared::ndlib::debug::DMENU::String::VTable* VTable;
			friend class gamelib::debug::NdDevMenu;
		};


		class Item : public ISdkRegenny<regenny::shared::ndlib::debug::DMENU::Item, Component> {
		public:
			void* CallBackFunct();
		};

		class ItemSubText : public Item {
		private:
			static regenny::shared::ndlib::debug::DMENU::ItemSubText::VTable0* VTable;
			friend class gamelib::debug::NdDevMenu;
		};

		class ItemSubmenu : public ISdkRegenny<regenny::shared::ndlib::debug::DMENU::ItemSubmenu, Item> {
		public:
			using SubmenuCallbackPtr = bool(*)(DMENU::ItemSubmenu&, DMENU::Message);
			using SubmenuCallback = boost::function<std::remove_pointer<SubmenuCallbackPtr>::type>;

			Menu* MenuEntry();
		private:
			static regenny::shared::ndlib::debug::DMENU::ItemSubmenu::VTable0* VTable;
			friend class gamelib::debug::NdDevMenu;	
		};

		class ItemBool : public ISdkRegenny<regenny::shared::ndlib::debug::DMENU::ItemBool, Item> {
		public:
			bool IsActive();
		private:
			static regenny::shared::ndlib::debug::DMENU::ItemBool::VTable0* VTable;
			friend class gamelib::debug::NdDevMenu;
		};

		class ItemDecimal : public ISdkRegenny<regenny::shared::ndlib::debug::DMENU::ItemDecimal, Item> {
		public:
			using DecimalHandlerPtr = uint64_t(*)(DMENU::ItemDecimal&, DMENU::Message, int32_t);
			using DecimalHandler = boost::function<std::remove_pointer<DecimalHandlerPtr>::type>;

			struct ValueParams {
				uint32_t MinValue;
				uint32_t MaxValue;
			};

			struct StepParams {
				uint32_t StepValue;
				uint32_t DoubleStepValue;
			};

			void SetHandler(DecimalHandler* handler);
			ValueParams GetValueParams();
			StepParams GetStepParams();

		private:
			static regenny::shared::ndlib::debug::DMENU::ItemDecimal::VTable0* VTable;
			friend class gamelib::debug::NdDevMenu;
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
			friend class gamelib::debug::NdDevMenu;
		};

		class ItemFunction : public ISdkRegenny<regenny::shared::ndlib::debug::DMENU::ItemFunction, Item> {
		public:
			using FunctionCallbackPtr = bool(*)(DMENU::ItemFunction&, DMENU::Message);
			using FunctionCallback = boost::function<std::remove_pointer<FunctionCallbackPtr>::type>;

			bool IsActive();
			void SetActive(bool status);
		private:
			static regenny::shared::ndlib::debug::DMENU::ItemFunction::VTable0* VTable;
			friend class gamelib::debug::NdDevMenu;
		};

		class ItemSelection : public ISdkRegenny<regenny::shared::ndlib::debug::DMENU::ItemSelection, Item> {
		public:
			using SelectionHandlerPtr = uint64_t(*)(DMENU::ItemSelection&, DMENU::Message, int32_t);
			using SelectionHandler = boost::function<std::remove_pointer<SelectionHandlerPtr>::type>;

			struct Item_selection {
				const char* selection_title;
				uint64_t selection_value;
			};

			Item_selection& ItemSelections();

		private:
			static regenny::shared::ndlib::debug::DMENU::ItemSelection::VTable0* VTable;
			friend class gamelib::debug::NdDevMenu;
		};

		MenuGroup* DevMenu();
		MenuGroup* QuickMenu();
		MenuGroup* FavoritesMenu();

	private:
		static gamelib::debug::NdDevMenu* s_NdDevMenu;
		friend class gamelib::debug::NdDevMenu;
	};

#define ASSERT_DMENU_ITEM_SIZE(type, base_offset) \
    static_assert(sizeof(DMENU::type) == sizeof(DMENU::Item) + base_offset, \
    #type " size mismatch: expected sizeof(Item) + 0x" #base_offset)

	static_assert(sizeof(DMENU) == 0x670, "Size of DMENU is not correct.");
	static_assert(sizeof(DMENU::Component) == 0xb0, "Size of DMENU::Component is not correct.");

	static_assert(sizeof(DMENU::Menu) == sizeof(DMENU::Component) + 0x30, "Size of DMENU::Menu is not correct.");
	static_assert(sizeof(DMENU::MenuGroup) == sizeof(DMENU::Component) + 0x280, "Size of DMENU::MenuGroup is not correct.");
	static_assert(sizeof(DMENU::String) == sizeof(DMENU::Component), "Size of DMENU::String is not correct.");
	static_assert(sizeof(DMENU::Item) == sizeof(DMENU::Component) + 0x8, "Size of DMENU::Item is not correct.");

#if defined(T2R)
	static_assert(sizeof(DMENU::KeyBoard) == sizeof(DMENU::Component) + 0x838, "Size of DMENU::KeyBoard is not correct.");
#elif defined(T1X)
	static_assert(sizeof(DMENU::KeyBoard) == sizeof(DMENU::Component) + 0x830, "Size of DMENU::KeyBoard is not correct.");
#endif
	static_assert(sizeof(DMENU::ItemPlaceHolder) == sizeof(DMENU::Component) + 0x400, "Size of DMENU::ItemPlaceHolder is not correct.");

	ASSERT_DMENU_ITEM_SIZE(ItemSubmenu, 0x10);
	ASSERT_DMENU_ITEM_SIZE(ItemBool, 0x08);
	ASSERT_DMENU_ITEM_SIZE(ItemFunction, 0x10);

#if defined(T2R)
	ASSERT_DMENU_ITEM_SIZE(ItemDecimal, 0xc8);
	ASSERT_DMENU_ITEM_SIZE(ItemFloat, 0xa8);
	ASSERT_DMENU_ITEM_SIZE(ItemSelection, 0x38);
#elif defined(T1X)
	ASSERT_DMENU_ITEM_SIZE(ItemDecimal, 0xb8);
	ASSERT_DMENU_ITEM_SIZE(ItemFloat, 0x98);
	ASSERT_DMENU_ITEM_SIZE(ItemSelection, 0x30);
#else
#error "Unsupported Build for NdDevMenu."
#endif

#undef ASSERT_DMENU_ITEM_SIZE

}
