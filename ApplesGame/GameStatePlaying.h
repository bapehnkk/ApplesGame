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
		sf::Texture playerTexture;
		sf::Texture appleTexture;
		sf::Font font;

		// Game data
		Player player;
		std::vector<Apple> apples;
		ApplesGrid applesGrid;
		int numEatenApples = 0;

		// UI data
		sf::Text scoreText;
		sf::Text inputHintText;
	};

	void InitGameStatePlaying(GameStatePlayingData& data, Game& game);
	void ShutdownGameStatePlaying(GameStatePlayingData& data, Game& game);
	void HandleGameStatePlayingWindowEvent(GameStatePlayingData& data, Game& game, const sf::Event& event);
	void UpdateGameStatePlaying(GameStatePlayingData& data, Game& game, float timeDelta);
	void DrawGameStatePlaying(GameStatePlayingData& data, Game& game, sf::RenderWindow& window);
}
