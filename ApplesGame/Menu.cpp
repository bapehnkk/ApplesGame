#include "Menu.h"
#include <assert.h>

namespace ApplesGame
{
	void InitMenuItem(MenuItem& menu)
	{
		for (const auto& child : menu.children)
		{
			child->parent = &menu;
			InitMenuItem(*child);
		}
	}

	void SelectMenuItem(Menu& menu, MenuItem* item)
	{
		// It is definitely error to select root item
		assert(item != &menu.root_item);

		if (menu.selected_item == item)
		{
			return;
		}

		if (item && !item->is_enabled)
		{
			// Don't allow to select disabled item
			return;
		}

		if (menu.selected_item)
		{
			menu.selected_item->text.setFillColor(menu.selected_item->deselected_color);
		}

		menu.selected_item = item;

		if (menu.selected_item)
		{
			menu.selected_item->text.setFillColor(menu.selected_item->selected_color);
		}
	}

	bool SelectPreviousMenuItem(Menu& menu)
	{
		if (menu.selected_item)
		{
			MenuItem* parent = menu.selected_item->parent;
			assert(parent); // There always should be parent

			auto it = std::find(parent->children.begin(), parent->children.end(), menu.selected_item);
			if (it != parent->children.begin())
			{
				SelectMenuItem(menu, *(--it));
				return true;
			}
		}

		return false;
	}

	bool SelectNextMenuItem(Menu& menu)
	{
		if (menu.selected_item)
		{
			MenuItem* parent = menu.selected_item->parent;
			assert(parent); // There always should be parent
			auto it = std::find(parent->children.begin(), parent->children.end(), menu.selected_item);
			if (it != parent->children.end() - 1)
			{
				SelectMenuItem(menu, *(++it));
				return true;
			}
		}
		return false;
	}

	bool ExpandSelectedItem(Menu& menu)
	{
		if (menu.selected_item && static_cast<int>(menu.selected_item->children.size()) > 0)
		{
			SelectMenuItem(menu, menu.selected_item->children.front());
			return true;
		}

		return false;
	}

	bool CollapseSelectedItem(Menu& menu)
	{
		if (menu.selected_item && menu.selected_item->parent && menu.selected_item->parent != &menu.root_item)
		{
			SelectMenuItem(menu, menu.selected_item->parent);
			return true;
		}
		return false;
	}

	MenuItem* GetCurrentMenuContext(Menu& menu)
	{
		return menu.selected_item ? menu.selected_item->parent : &menu.root_item;
	}

	void DrawMenu(Menu& menu, sf::RenderWindow& window, const sf::Vector2f position, const sf::Vector2f origin)
	{
		const MenuItem* expanded_item = GetCurrentMenuContext(menu);

		std::vector<sf::Text*> texts;
		texts.reserve(expanded_item->children.size());
		for (auto& child : expanded_item->children)
		{
			if (child->is_enabled)
			{
				texts.push_back(&child->text);
			}
		}

		DrawItemsList(window, texts, expanded_item->children_spacing, expanded_item->children_orientation, expanded_item->children_alignment, position, origin);
	}

}
