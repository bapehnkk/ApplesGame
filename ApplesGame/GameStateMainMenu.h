#pragma once
#include "SFML/Graphics.hpp"
#include "Menu.h"

namespace ApplesGame
{
	struct Game;

	struct GameStateMainMenuData
	{
		sf::Font font;

		MenuItem start_game_item;
		MenuItem options_item;
		MenuItem options_infinite_apples_item;
		MenuItem options_with_acceleration_item;
		MenuItem exit_game_item;
		MenuItem yes_item;
		MenuItem no_item;
		Menu menu;
	};

	void InitGameStateMainMenu(GameStateMainMenuData& data, Game& game);
	void ShutdownGameStateMainMenu(GameStateMainMenuData& data, Game& game);
	void HandleGameStateMainMenuWindowEvent(GameStateMainMenuData& data, Game& game, const sf::Event& event);
	void UpdateGameStateMainMenu(GameStateMainMenuData& data, Game& game);
	void DrawGameStateMainMenu(GameStateMainMenuData& data, Game& game, sf::RenderWindow& window);
}
