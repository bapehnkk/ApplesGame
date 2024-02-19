#pragma once
#include "SFML/Graphics.hpp"
#include "Math.h"
#include <list>

namespace ApplesGame
{
	struct MenuItem
	{
		sf::Text text;
		sf::Text hint_text; // Visible when child item is selected
		Orientation children_orientation = Orientation::VERTICAL;
		Alignment children_alignment = Alignment::MIN;
		float children_spacing;

		sf::Color selected_color = sf::Color::Yellow;
		sf::Color deselected_color = sf::Color::White;

		bool is_enabled = true;
		std::vector<MenuItem*> children;

		MenuItem* parent = nullptr;
	};

	struct Menu
	{
		MenuItem root_item;
		MenuItem* selected_item = nullptr;
	};

	// Links children to parent
	void InitMenuItem(MenuItem& menu);
	void SelectMenuItem(Menu& menu, MenuItem* item);
	bool SelectPreviousMenuItem(Menu& menu);
	bool SelectNextMenuItem(Menu& menu);
	bool ExpandSelectedItem(Menu& menu);
	bool CollapseSelectedItem(Menu& menu);

	MenuItem* GetCurrentMenuContext(Menu& menu);

	void DrawMenu(Menu& menu, sf::RenderWindow& window, const sf::Vector2f position, const sf::Vector2f origin);
}
