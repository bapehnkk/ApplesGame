#include "GameStateExitDialog.h"
#include "Game.h"
#include <assert.h>

namespace ApplesGame
{
	void InitGameStateExitDialog(GameStateExitDialogData& data, Game& game)
	{
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

		data.hint_text.setString("Are you sure you want to stop this game? Enter - Yes, Esc - No");
		data.hint_text.setFont(data.font);
		data.hint_text.setCharacterSize(24);
		data.hint_text.setFillColor(sf::Color::White);
		data.hint_text.setOrigin(GetItemOrigin(data.hint_text, { 0.5f, 0.5f }));

		data.background.setFillColor(sf::Color(0, 0, 0, 128)); // Semi-transparent black
	}

	void ShutdownGameStateExitDialog(GameStateExitDialogData& data, Game& game)
	{
		// We dont need to free resources here, because they will be freed automatically
	}

	void HandleGameStateExitDialogWindowEvent(GameStateExitDialogData& data, Game& game, const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				PopGameState(game);
			}
			else if (event.key.code == sf::Keyboard::Enter)
			{
				SwitchGameState(game, GameStateType::MAIN_MENU);
			}
		}
	}

	void UpdateGameStateExitDialog(GameStateExitDialogData& data, Game& game, float time_delta)
	{

	}

	void DrawGameStateExitDialog(GameStateExitDialogData& data, Game& game, sf::RenderWindow& window)
	{
		const auto window_size = static_cast<sf::Vector2f>(window.getSize());
		
		data.background.setSize(window_size);
		window.draw(data.background);

		data.hint_text.setPosition(window_size / 2.f);
		window.draw(data.hint_text);
	}

}
