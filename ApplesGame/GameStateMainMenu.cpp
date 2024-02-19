#include "GameStateMainMenu.h"
#include "Game.h"
#include <assert.h>

namespace ApplesGame
{
	void InitGameStateMainMenu(GameStateMainMenuData& data, Game& game)
	{
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

		data.menu.root_item.hint_text.setString("Apples Game");
		data.menu.root_item.hint_text.setFont(data.font);
		data.menu.root_item.hint_text.setCharacterSize(48);
		data.menu.root_item.hint_text.setFillColor(sf::Color::Red);
		data.menu.root_item.children_orientation = Orientation::VERTICAL;
		data.menu.root_item.children_alignment = Alignment::MIDDLE;
		data.menu.root_item.children_spacing = 10.f;
		data.menu.root_item.children.push_back(&data.start_game_item);
		data.menu.root_item.children.push_back(&data.options_item);
		data.menu.root_item.children.push_back(&data.exit_game_item);

		data.start_game_item.text.setString("Start Game");
		data.start_game_item.text.setFont(data.font);
		data.start_game_item.text.setCharacterSize(24);
		
		data.options_item.text.setString("Options");
		data.options_item.text.setFont(data.font);
		data.options_item.text.setCharacterSize(24);
		data.options_item.hint_text.setString("Options");
		data.options_item.hint_text.setFont(data.font);
		data.options_item.hint_text.setCharacterSize(48);
		data.options_item.hint_text.setFillColor(sf::Color::Red);
		data.options_item.children_orientation = Orientation::VERTICAL;
		data.options_item.children_alignment = Alignment::MIDDLE;
		data.options_item.children_spacing = 10.f;
		data.options_item.children.push_back(&data.options_infinite_apples_item);
		data.options_item.children.push_back(&data.options_with_acceleration_item);

		data.options_infinite_apples_item.text.setString("Infinite Apples: On/Off");
		data.options_infinite_apples_item.text.setFont(data.font);
		data.options_infinite_apples_item.text.setCharacterSize(24);

		data.options_with_acceleration_item.text.setString("With Acceleration: On/Off");
		data.options_with_acceleration_item.text.setFont(data.font);
		data.options_with_acceleration_item.text.setCharacterSize(24);

		data.exit_game_item.text.setString("Exit Game");
		data.exit_game_item.text.setFont(data.font);
		data.exit_game_item.text.setCharacterSize(24);
		data.exit_game_item.hint_text.setString("Are you sure?");
		data.exit_game_item.hint_text.setFont(data.font);
		data.exit_game_item.hint_text.setCharacterSize(48);
		data.exit_game_item.hint_text.setFillColor(sf::Color::Red);
		data.exit_game_item.children_orientation = Orientation::HORIZONTAL;
		data.exit_game_item.children_alignment = Alignment::MIDDLE;
		data.exit_game_item.children_spacing = 10.f;
		data.exit_game_item.children.push_back(&data.yes_item);
		data.exit_game_item.children.push_back(&data.no_item);

		data.yes_item.text.setString("Yes");
		data.yes_item.text.setFont(data.font);
		data.yes_item.text.setCharacterSize(24);

		data.no_item.text.setString("No");
		data.no_item.text.setFont(data.font);
		data.no_item.text.setCharacterSize(24);

		InitMenuItem(data.menu.root_item);
		SelectMenuItem(data.menu, &data.start_game_item);
	}

	void ShutdownGameStateMainMenu(GameStateMainMenuData& data, Game& game)
	{
		// No need to do anything here
	}

	void HandleGameStateMainMenuWindowEvent(GameStateMainMenuData& data, Game& game, const sf::Event& event)
	{
		if (!data.menu.selected_item)
		{
			return;
		}

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				CollapseSelectedItem(data.menu);
			}
			else if (event.key.code == sf::Keyboard::Enter)
			{
				if (data.menu.selected_item == &data.start_game_item)
				{
					SwitchGameState(game, GameStateType::PLAYING);
				}
				else if (data.menu.selected_item == &data.options_item)
				{
					ExpandSelectedItem(data.menu);
				}
				else if (data.menu.selected_item == &data.options_infinite_apples_item)
				{
					game.options = static_cast<GameOptions>(static_cast<std::uint8_t>(game.options) ^ static_cast<std::uint8_t>(GameOptions::INFINITE_APPLES));
				}
				else if (data.menu.selected_item == &data.options_with_acceleration_item)
				{
					game.options = static_cast<GameOptions>(static_cast<std::uint8_t>(game.options) ^ static_cast<std::uint8_t>(GameOptions::WITH_ACCELERATION));
				}
				else if (data.menu.selected_item == &data.exit_game_item)
				{
					ExpandSelectedItem(data.menu);
				}
				else if (data.menu.selected_item == &data.yes_item)
				{
					SwitchGameState(game, GameStateType::NONE);
				}
				else if (data.menu.selected_item == &data.no_item)
				{
					CollapseSelectedItem(data.menu);
				}
				else
				{
					ExpandSelectedItem(data.menu);
				}
			}

			const Orientation orientation = data.menu.selected_item->parent->children_orientation;
			if (orientation == Orientation::VERTICAL && event.key.code == sf::Keyboard::Up ||
				orientation == Orientation::HORIZONTAL && event.key.code == sf::Keyboard::Left)
			{
				SelectPreviousMenuItem(data.menu);
			}
			else if (orientation == Orientation::VERTICAL && event.key.code == sf::Keyboard::Down ||
						orientation == Orientation::HORIZONTAL && event.key.code == sf::Keyboard::Right)
			{
				SelectNextMenuItem(data.menu);
			}
		}
	}

	void UpdateGameStateMainMenu(GameStateMainMenuData& data, Game& game)
	{
		const bool is_infinite_apples = (static_cast<std::uint8_t>(game.options) & static_cast<std::uint8_t>(GameOptions::INFINITE_APPLES)) != static_cast<std::uint8_t>(GameOptions::EMPTY);
		data.options_infinite_apples_item.text.setString("Infinite Apples: " + std::string(is_infinite_apples ? "On" : "Off"));

		const bool is_with_acceleration = (static_cast<std::uint8_t>(game.options) & static_cast<std::uint8_t>(GameOptions::WITH_ACCELERATION)) != static_cast<std::uint8_t>(GameOptions::EMPTY);
		data.options_with_acceleration_item.text.setString("With Acceleration: " + std::string(is_with_acceleration ? "On" : "Off"));
	}

	void DrawGameStateMainMenu(GameStateMainMenuData& data, Game& game, sf::RenderWindow& window)
	{
		const auto view_size = static_cast<sf::Vector2f>(window.getSize());

		sf::Text* hint_text = &GetCurrentMenuContext(data.menu)->hint_text;
		hint_text->setOrigin(GetItemOrigin(*hint_text, { 0.5f, 0.f }));
		hint_text->setPosition(view_size.x / 2.f, 150.f);
		window.draw(*hint_text);

		DrawMenu(data.menu, window, view_size / 2.f, { 0.5f, 0.f });
	}

}
