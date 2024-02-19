#pragma once
#include "SFML/Graphics.hpp"
#include "Apple.h"
#include "Player.h"


namespace ApplesGame
{
	struct Game;

	struct GameStatePlayingData
	{
		// Resources
		sf::Texture player_texture;
		sf::Texture apple_texture;
		sf::Font font;

		// Game data
		Player player;
		std::vector<Apple> apples;
		ApplesGrid apples_grid;
		int num_eaten_apples = 0;

		// UI data
		sf::Text score_text;
		sf::Text input_hint_text;
	};

	void InitGameStatePlaying(GameStatePlayingData& data, Game& game);
	void ShutdownGameStatePlaying(GameStatePlayingData& data, Game& game);
	void HandleGameStatePlayingWindowEvent(GameStatePlayingData& data, Game& game, const sf::Event& event);
	void UpdateGameStatePlaying(GameStatePlayingData& data, Game& game, const float time_delta);
	void DrawGameStatePlaying(GameStatePlayingData& data, Game& game, sf::RenderWindow& window);
}
