#pragma once
#include <cassert>

#include "SFML/Graphics/Text.hpp"


namespace ApplesGame
{
    struct Game;


    struct GameStateRecordsTableData
    {
        // Resources
        sf::Font font;

        // UI data
        sf::Text records_table_text;
    };

    void InitGameStateRecordsTable(GameStateRecordsTableData& data, Game& game);
    void ShutdownGameStateRecordsTable(GameStateRecordsTableData& data, Game& game);
    void HandleGameStateRecordsTableWindowEvent(GameStateRecordsTableData& data, Game& game, const sf::Event& event);
    void UpdateGameStateRecordsTable(GameStateRecordsTableData& data, const Game& game, const float time_delta);
    void DrawGameStateRecordsTable(GameStateRecordsTableData& data, Game& game, sf::RenderWindow& window);
}
