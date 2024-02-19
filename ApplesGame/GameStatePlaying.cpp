#include "GameStatePlaying.h"
#include "Game.h"
#include <assert.h>

namespace ApplesGame
{
    void InitGameStatePlaying(GameStatePlayingData& data, Game& game)
    {
        assert(data.playerTexture.loadFromFile(RESOURCES_PATH + "Pacman.png"));
        assert(data.appleTexture.loadFromFile(RESOURCES_PATH + "Apple.png"));
        assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

        InitPlayer(data.player, data.playerTexture);

        data.apples.clear();
        ClearApplesGrid(data.applesGrid);
        int numApples = MIN_APPLES + rand() % (MAX_APPLES + 1 - MIN_APPLES);
        data.apples.resize(numApples);
        for (Apple& apple : data.apples)
        {
            InitApple(apple, data.appleTexture);
            ResetAppleState(apple);
            AddAppleToGrid(data.applesGrid, apple);
        }

        data.numEatenApples = 0;

        data.scoreText.setFont(data.font);
        data.scoreText.setCharacterSize(24);
        data.scoreText.setFillColor(sf::Color::Yellow);

        data.inputHintText.setFont(data.font);
        data.inputHintText.setCharacterSize(24);
        data.inputHintText.setFillColor(sf::Color::White);
        data.inputHintText.setString("Use arrow keys to move, ESC to exit");
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
                PushGameState(game, GameStateType::ExitDialog, false);
            }
        }
    }

    void UpdateGameStatePlaying(GameStatePlayingData& data, Game& game, float timeDelta)
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
        UpdatePlayer(data.player, timeDelta);

        // Поиск столкновений игрока с яблоками
        std::vector<Apple*> collidingApples;
        if (FindPlayerCollisionWithApples(data.player.position, data.applesGrid, collidingApples))
        {
            for (Apple* apple : collidingApples)
            {
                if (!apple->isEaten)
                {
                    if ((std::uint8_t)game.options & (std::uint8_t)GameOptions::InfiniteApples)
                    {
                        // Перемещение яблока в новую случайную позицию
                        ResetAppleState(*apple);
                        RemoveAppleFromGrid(data.applesGrid, *apple);
                        // Удаляем яблоко из сетки перед обновлением его позиции
                        AddAppleToGrid(data.applesGrid, *apple); // Добавляем обновленное яблоко обратно в сетку
                    }
                    else
                    {
                        // Помечаем яблоко как съеденное
                        MarkAppleAsEaten(*apple);
                        RemoveAppleFromGrid(data.applesGrid, *apple);
                    }

                    // Увеличиваем счетчик съеденных яблок
                    data.numEatenApples++;

                    // Увеличиваем скорость игрока, если это предусмотрено настройками
                    if ((std::uint8_t)game.options & (std::uint8_t)GameOptions::WithAcceleration)
                    {
                        data.player.speed += ACCELERATION;
                    }
                }
            }
        }

        // Проверка условий завершения игры
        bool isGameFinished = (data.numEatenApples == data.apples.size()) && !((std::uint8_t)game.options & (
            std::uint8_t)GameOptions::InfiniteApples);
        if (isGameFinished || HasPlayerCollisionWithScreenBorder(data.player))
        {
            // Обновление рекорда игрока
            game.recordsTable["Player"] = std::max(game.recordsTable["Player"], data.numEatenApples);

            // Переход к состоянию конца игры
            PushGameState(game, GameStateType::GameOver, false);
        }
    }


    void DrawGameStatePlaying(GameStatePlayingData& data, Game& game, sf::RenderWindow& window)
    {
        DrawPlayer(data.player, window);
        for (Apple& apple : data.apples)
        {
            if (!apple.isEaten)
            {
                DrawApple(apple, window);
            }
        }

        // Отображение счета и подсказок
        data.scoreText.setString("Score: " + std::to_string(data.numEatenApples));
        window.draw(data.scoreText);
        window.draw(data.inputHintText);
    }
}
