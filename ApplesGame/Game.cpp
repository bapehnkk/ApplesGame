#include "Game.h"
#include <assert.h>
#include <algorithm>
#include "GameStatePlaying.h"
#include "GameStateGameOver.h"
#include "GameStateExitDialog.h"
#include "GameStateMainMenu.h"

namespace ApplesGame
{
    void InitGame(Game& game)
    {
        // Generate fake records table
        game.recordsTable =
        {
            {"John", MAX_APPLES},
            {"Jane", MAX_APPLES / 2},
            {"Alice", MAX_APPLES / 3},
            {"Bob", MAX_APPLES / 4},
            {"Clementine", MAX_APPLES / 5},
        };

        game.game_state_change_type = GameStateChangeType::NONE;
        game.pending_game_state_type = GameStateType::NONE;
        game.pending_game_state_is_exclusively_visible = false;
        SwitchGameState(game, GameStateType::MAIN_MENU);
    }

    void HandleWindowEvents(Game& game, sf::RenderWindow& window)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window if close button or Escape key pressed
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (static_cast<float>(game.game_state_stack.size()) > 0)
            {
                HandleWindowEventGameState(game, game.game_state_stack.back(), event);
            }
        }
    }

    bool UpdateGame(Game& game, const float time_delta)
    {
        if (game.game_state_change_type == GameStateChangeType::SWITCH)
        {
            // Shutdown all game states
            while (static_cast<float>(game.game_state_stack.size()) > 0)
            {
                ShutdownGameState(game, game.game_state_stack.back());
                game.game_state_stack.pop_back();
            }
        }
        else if (game.game_state_change_type == GameStateChangeType::POP)
        {
            // Shutdown only current game state
            if (static_cast<float>(game.game_state_stack.size()) > 0)
            {
                ShutdownGameState(game, game.game_state_stack.back());
                game.game_state_stack.pop_back();
            }
        }

        // Initialize new game state if needed
        if (game.pending_game_state_type != GameStateType::NONE)
        {
            game.game_state_stack.push_back({
                game.pending_game_state_type, nullptr, game.pending_game_state_is_exclusively_visible
            });
            InitGameState(game, game.game_state_stack.back());
        }

        game.game_state_change_type = GameStateChangeType::NONE;
        game.pending_game_state_type = GameStateType::NONE;
        game.pending_game_state_is_exclusively_visible = false;

        if (static_cast<float>(game.game_state_stack.size()) > 0)
        {
            UpdateGameState(game, game.game_state_stack.back(), time_delta);
            return true;
        }

        return false;
    }

    void DrawGame(Game& game, sf::RenderWindow& window)
    {
        if (static_cast<float>(game.game_state_stack.size()) > 0)
        {
            std::vector<GameState*> visibleGameStates;
            for (auto it = game.game_state_stack.rbegin(); it != game.game_state_stack.rend(); ++it)
            {
                visibleGameStates.push_back(&(*it));
                if (it->is_exclusively_visible)
                {
                    break;
                }
            }

            for (auto it = visibleGameStates.rbegin(); it != visibleGameStates.rend(); ++it)
            {
                DrawGameState(game, **it, window);
            }
        }
    }

    void ShutdownGame(Game& game)
    {
        // Shutdown all game states
        while (static_cast<float>(game.game_state_stack.size()) > 0)
        {
            ShutdownGameState(game, game.game_state_stack.back());
            game.game_state_stack.pop_back();
        }

        game.game_state_change_type = GameStateChangeType::NONE;
        game.pending_game_state_type = GameStateType::NONE;
        game.pending_game_state_is_exclusively_visible = false;
    }

    void PushGameState(Game& game, GameStateType state_type, bool is_exclusively_visible)
    {
        game.pending_game_state_type = state_type;
        game.pending_game_state_is_exclusively_visible = is_exclusively_visible;
        game.game_state_change_type = GameStateChangeType::PUSH;
    }

    void PopGameState(Game& game)
    {
        game.pending_game_state_type = GameStateType::NONE;
        game.pending_game_state_is_exclusively_visible = false;
        game.game_state_change_type = GameStateChangeType::POP;
    }

    void SwitchGameState(Game& game, GameStateType new_state)
    {
        game.pending_game_state_type = new_state;
        game.pending_game_state_is_exclusively_visible = false;
        game.game_state_change_type = GameStateChangeType::SWITCH;
    }

    void InitGameState(Game& game, GameState& state)
    {
        switch (state.type)
        {
        case GameStateType::MAIN_MENU:
            {
                state.data = new GameStateMainMenuData();
                InitGameStateMainMenu(*static_cast<GameStateMainMenuData*>(state.data), game);
                break;
            }
        case GameStateType::PLAYING:
            {
                state.data = new GameStatePlayingData();
                InitGameStatePlaying(*static_cast<GameStatePlayingData*>(state.data), game);
                break;
            }
        case GameStateType::GAME_OVER:
            {
                state.data = new GameStateGameOverData();
                InitGameStateGameOver(*static_cast<GameStateGameOverData*>(state.data), game);
                break;
            }
        case GameStateType::EXIT_DIALOG:
            {
                state.data = new GameStateExitDialogData();
                InitGameStateExitDialog(*static_cast<GameStateExitDialogData*>(state.data), game);
                break;
            }
        case GameStateType::NONE:
            {
                break;
            }
        default:
            {
                assert(false); // We want to know if we forgot to implement new game statee
                break;
            }
        }
    }

    void ShutdownGameState(Game& game, GameState& state)
    {
        switch (state.type)
        {
        case GameStateType::MAIN_MENU:
            {
                ShutdownGameStateMainMenu(*static_cast<GameStateMainMenuData*>(state.data), game);
                delete static_cast<GameStateMainMenuData*>(state.data);
                break;
            }
        case GameStateType::PLAYING:
            {
                ShutdownGameStatePlaying(*static_cast<GameStatePlayingData*>(state.data), game);
                delete static_cast<GameStatePlayingData*>(state.data);
                break;
            }
        case GameStateType::GAME_OVER:
            {
                ShutdownGameStateGameOver(*static_cast<GameStateGameOverData*>(state.data), game);
                delete static_cast<GameStateGameOverData*>(state.data);
                break;
            }
        case GameStateType::EXIT_DIALOG:
            {
                ShutdownGameStateExitDialog(*static_cast<GameStateExitDialogData*>(state.data), game);
                delete static_cast<GameStateExitDialogData*>(state.data);
                break;
            }
        case GameStateChangeType::NONE:
            {
                break;
            }
        default:
            {
                assert(false); // We want to know if we forgot to implement new game statee
                break;
            }
        }

        state.data = nullptr;
    }

    void HandleWindowEventGameState(Game& game, GameState& state, sf::Event& event)
    {
        switch (state.type)
        {
        case GameStateType::MAIN_MENU:
            {
                HandleGameStateMainMenuWindowEvent(*static_cast<GameStateMainMenuData*>(state.data), game, event);
                break;
            }
        case GameStateType::PLAYING:
            {
                HandleGameStatePlayingWindowEvent(*static_cast<GameStatePlayingData*>(state.data), game, event);
                break;
            }
        case GameStateType::GAME_OVER:
            {
                HandleGameStateGameOverWindowEvent(*static_cast<GameStateGameOverData*>(state.data), game, event);
                break;
            }
        case GameStateType::EXIT_DIALOG:
            {
                HandleGameStateExitDialogWindowEvent(*static_cast<GameStateExitDialogData*>(state.data), game, event);
                break;
            }
        case GameStateType::NONE:
            {
                break;
            }
        default:
            {
                assert(false); // We want to know if we forgot to implement new game statee
                break;
            }
        }
    }

    void UpdateGameState(Game& game, const GameState& state, const float time_delta)
    {
        switch (state.type)
        {
        case GameStateType::MAIN_MENU:
            {
                UpdateGameStateMainMenu(*static_cast<GameStateMainMenuData*>(state.data), game);
                break;
            }
        case GameStateType::PLAYING:
            {
                UpdateGameStatePlaying(*static_cast<GameStatePlayingData*>(state.data), game, time_delta);
                break;
            }
        case GameStateType::GAME_OVER:
            {
                UpdateGameStateGameOver(*static_cast<GameStateGameOverData*>(state.data), game, time_delta);
                break;
            }
        case GameStateType::EXIT_DIALOG:
            {
                UpdateGameStateExitDialog(*static_cast<GameStateExitDialogData*>(state.data), game, time_delta);
                break;
            }
        case GameStateChangeType::NONE:
            {
                break;
            }
        default:
            {
                assert(false); // We want to know if we forgot to implement new game statee
                break;
            }
        }
    }

    void DrawGameState(Game& game, const GameState& state, sf::RenderWindow& window)
    {
        switch (state.type)
        {
        case GameStateType::MAIN_MENU:
            {
                DrawGameStateMainMenu(*static_cast<GameStateMainMenuData*>(state.data), game, window);
                break;
            }
        case GameStateType::PLAYING:
            {
                DrawGameStatePlaying(*static_cast<GameStatePlayingData*>(state.data), game, window);
                break;
            }
        case GameStateType::GAME_OVER:
            {
                DrawGameStateGameOver(*static_cast<GameStateGameOverData*>(state.data), game, window);
                break;
            }
        case GameStateType::EXIT_DIALOG:
            {
                DrawGameStateExitDialog(*static_cast<GameStateExitDialogData*>(state.data), game, window);
                break;
            }
        case GameStateChangeType::NONE:
            {
                break;
            }
        default:
            {
                assert(false); // We want to know if we forgot to implement new game statee
                break;
            }
        }
    }
}
