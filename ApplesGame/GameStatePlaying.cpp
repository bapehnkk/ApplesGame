#include "GameStatePlaying.h"
#include "Game.h"
#include <assert.h>

namespace ApplesGame
{
    void InitGameStatePlaying(GameStatePlayingData& data, Game& game)
    {
        assert(data.player_texture.loadFromFile(RESOURCES_PATH + "Pacman.png"));
        assert(data.apple_texture.loadFromFile(RESOURCES_PATH + "Apple.png"));
        assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

        InitPlayer(data.player, data.player_texture);

        data.apples.clear();
        ClearApplesGrid(data.apples_grid);
        const int num_apples = MIN_APPLES + rand() % (MAX_APPLES + 1 - MIN_APPLES);
        data.apples.resize(num_apples);
        for (Apple& apple : data.apples)
        {
            InitApple(apple, data.apple_texture);
            ResetAppleState(apple);
            AddAppleToGrid(data.apples_grid, apple);
        }

        data.num_eaten_apples = 0;

        data.score_text.setFont(data.font);
        data.score_text.setCharacterSize(24);
        data.score_text.setFillColor(sf::Color::Yellow);

        data.input_hint_text.setFont(data.font);
        data.input_hint_text.setCharacterSize(24);
        data.input_hint_text.setFillColor(sf::Color::White);
        data.input_hint_text.setString("Use arrow keys to move, ESC to exit");
    }

    void ShutdownGameStatePlaying(GameStatePlayingData& data, Game& game)
    {
        // We dont need to free resources here, because they will be freed automatically
    }

    void HandleGameStatePlayingWindowEvent(GameStatePlayingData& data, Game& game, const sf::Event& event)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                PushGameState(game, GameStateType::EXIT_DIALOG, false);
            }
        }
    }

    void UpdateGameStatePlaying(GameStatePlayingData& data, Game& game, const float time_delta)
    {
        // Обновление направления игрока в зависимости от нажатых клавиш
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            data.player.direction = PlayerDirection::Up;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            data.player.direction = PlayerDirection::Right;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            data.player.direction = PlayerDirection::Down;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            data.player.direction = PlayerDirection::Left;
        }

        // Обновление позиции игрока
        UpdatePlayer(data.player, time_delta);

        // Поиск столкновений игрока с яблоками
        std::vector<Apple*> colliding_apples;
        if (FindPlayerCollisionWithApples(data.player.position, data.apples_grid, colliding_apples))
        {
            for (Apple* apple : colliding_apples)
            {
                if (!apple->is_eaten)
                {
                    if (static_cast<std::uint8_t>(game.options) & static_cast<std::uint8_t>(GameOptions::INFINITE_APPLES))
                    {
                        // Перемещение яблока в новую случайную позицию
                        ResetAppleState(*apple);
                        RemoveAppleFromGrid(data.apples_grid, *apple);
                        // Удаляем яблоко из сетки перед обновлением его позиции
                        AddAppleToGrid(data.apples_grid, *apple); // Добавляем обновленное яблоко обратно в сетку
                    }
                    else
                    {
                        // Помечаем яблоко как съеденное
                        MarkAppleAsEaten(*apple);
                        RemoveAppleFromGrid(data.apples_grid, *apple);
                    }

                    // Увеличиваем счетчик съеденных яблок
                    data.num_eaten_apples++;

                    // Увеличиваем скорость игрока, если это предусмотрено настройками
                    if (static_cast<std::uint8_t>(game.options) & static_cast<std::uint8_t>(GameOptions::WITH_ACCELERATION))
                    {
                        data.player.speed += ACCELERATION;
                    }
                }
            }
        }

        // Проверка условий завершения игры
        const bool is_game_finished = (data.num_eaten_apples == data.apples.size()) && !(static_cast<std::uint8_t>(game.options) & static_cast<std::uint8_t>(GameOptions::INFINITE_APPLES));
        if (is_game_finished || HasPlayerCollisionWithScreenBorder(data.player))
        {
            // Обновление рекорда игрока
            game.records_table["Player"] = std::max(game.records_table["Player"], data.num_eaten_apples);

            // Переход к состоянию конца игры
            PushGameState(game, GameStateType::GAME_OVER, false);
        }
    }


    void DrawGameStatePlaying(GameStatePlayingData& data, Game& game, sf::RenderWindow& window)
    {
        DrawPlayer(data.player, window);
        for (Apple& apple : data.apples)
        {
            if (!apple.is_eaten)
            {
                DrawApple(apple, window);
            }
        }

        // Отображение счета и подсказок
        data.score_text.setString("Score: " + std::to_string(data.num_eaten_apples));
        window.draw(data.score_text);
        window.draw(data.input_hint_text);
    }
}
