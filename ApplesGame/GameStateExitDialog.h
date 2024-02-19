#pragma once
#include <SFML/Graphics.hpp>

namespace ApplesGame
{
	struct Game;

	struct GameStateExitDialogData
	{
		sf::Font font;

		sf::RectangleShape background;
		sf::Text hint_text;
	};

	void InitGameStateExitDialog(GameStateExitDialogData& data, Game& game);
	void ShutdownGameStateExitDialog(GameStateExitDialogData& data, Game& game);
	void HandleGameStateExitDialogWindowEvent(GameStateExitDialogData& data, Game& game, const sf::Event& event);
	void UpdateGameStateExitDialog(GameStateExitDialogData& data, Game& game, float time_delta);
	void DrawGameStateExitDialog(GameStateExitDialogData& data, Game& game, sf::RenderWindow& window);
}
