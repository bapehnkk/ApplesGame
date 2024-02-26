#include "SFML/Graphics/RenderWindow.hpp"


#include "GameSettings.h"
#include "Math.h"
#include "Game.h"
#include "GameStateRecordsTable.h"

#include <iostream>


namespace ApplesGame
{
    void InitGameStateRecordsTable(GameStateRecordsTableData& data, Game& game)
    {
        assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));


        data.records_table_text.setFont(data.font);
        data.records_table_text.setCharacterSize(24);
        data.records_table_text.setFillColor(sf::Color::Green);
        data.records_table_text.setString("Records:\nPlayer: 999\nPlayer: 999\nPlayer: 999\nPlayer: 999\nPlayer: 999");
        data.records_table_text.setOrigin(GetItemOrigin(data.records_table_text, {0.5f, 0.f}));
    }

    void HandleGameStateRecordsTableWindowEvent(GameStateRecordsTableData& data, Game& game, const sf::Event& event)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::Space)
            {
                SwitchGameState(game, GameStateType::MAIN_MENU);
            }
        }
    }

    void UpdateGameStateRecordsTable(GameStateRecordsTableData& data, const Game& game, const float time_delta)
    {
        data.records_table_text.setString("Records:");
        for (const auto& item : game.records_table)
        {
            data.records_table_text.setString(data.records_table_text.getString() + "\n" + item.first + ": " + std::to_string(item.second));
        }
        data.records_table_text.setOrigin(GetItemOrigin(data.records_table_text, { 0.5f, 0.f }));
    }

    void ShutdownGameStateRecordsTable(GameStateRecordsTableData& data, Game& game)
    {
        // We dont need to free resources here, because they will be freed automatically
    }

    void DrawGameStateRecordsTable(GameStateRecordsTableData& data, Game& game, sf::RenderWindow& window)
    {
        const sf::Vector2f view_size = window.getView().getSize();

        data.records_table_text.setPosition(view_size.x / 2.f, 30.f);
        window.draw(data.records_table_text);
    }
}
