#include "GameStateGameOver.h"
#include <assert.h>
#include "Game.h"

namespace ApplesGame
{
	void InitGameStateGameOver(GameStateGameOverData& data, Game& game)
	{
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

		data.time_since_game_over = 0.f;

		data.game_over_text.setFont(data.font);
		data.game_over_text.setCharacterSize(48);
		data.game_over_text.setStyle(sf::Text::Bold);
		data.game_over_text.setFillColor(sf::Color::Red);
		data.game_over_text.setString("GAME OVER");
		data.game_over_text.setOrigin(GetItemOrigin(data.game_over_text, { 0.5f, 0.5f }));
		
		data.hint_text.setFont(data.font);
		data.hint_text.setCharacterSize(24);
		data.hint_text.setFillColor(sf::Color::White);
		data.hint_text.setString("Press Space to restart");
		data.hint_text.setOrigin(GetItemOrigin(data.hint_text, { 0.5f, 1.f }));

	}

	void ShutdownGameStateGameOver(GameStateGameOverData& data, Game& game)
	{
		// We dont need to free resources here, because they will be freed automatically
	}

	void HandleGameStateGameOverWindowEvent(GameStateGameOverData& data, Game& game, const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Space)
			{
				SwitchGameState(game, GameStateType::PLAYING);
			}
			else if (event.key.code == sf::Keyboard::Escape)
			{
				SwitchGameState(game, GameStateType::MAIN_MENU);
			}
		}
	}

	void UpdateGameStateGameOver(GameStateGameOverData& data, const Game& game, const float time_delta)
	{
		data.time_since_game_over += time_delta;

		const sf::Color game_over_text_color = static_cast<int>(data.time_since_game_over) % 2 ? sf::Color::Red : sf::Color::Yellow;
		data.game_over_text.setFillColor(game_over_text_color);

	}

	void DrawGameStateGameOver(GameStateGameOverData& data, Game& game, sf::RenderWindow& window)
	{
		const sf::Vector2f view_size = window.getView().getSize();

		data.game_over_text.setPosition(view_size.x / 2.f, view_size.y / 2.f);
		window.draw(data.game_over_text);

		data.hint_text.setPosition(view_size.x / 2.f, view_size.y - 10.f);
		window.draw(data.hint_text);
	}
}
