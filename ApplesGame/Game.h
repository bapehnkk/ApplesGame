#pragma once
#include <SFML/Graphics.hpp>

#include "Player.h"
#include "Apple.h"
#include "GameSettings.h"
#include <unordered_map>

namespace ApplesGame
{
	enum class GameOptions: std::uint8_t
	{
		INFINITE_APPLES = 1 << 0,
		WITH_ACCELERATION = 1 << 1,

		DEFAULT = INFINITE_APPLES | WITH_ACCELERATION,
		EMPTY = 0
	};




	enum class GameStateType
	{
		NONE = 0,
		MAIN_MENU,
		PLAYING,
		GAME_OVER,
		EXIT_DIALOG,
	};

	struct GameState
	{
		GameStateType type = GameStateType::NONE;
		void* data = nullptr;
		bool is_exclusively_visible = false;
	};

	enum class GameStateChangeType
	{
		NONE,
		PUSH,
		POP,
		SWITCH
	};

	struct Game
	{
		std::vector<GameState> game_state_stack;
		GameStateChangeType game_state_change_type = GameStateChangeType::NONE;
		GameStateType pending_game_state_type = GameStateType::NONE;
		bool pending_game_state_is_exclusively_visible = false;

		GameOptions options = GameOptions::DEFAULT;
		std::unordered_map<std::string, int> recordsTable;
	};

	
	void InitGame(Game& game);
	void HandleWindowEvents(Game& game, sf::RenderWindow& window);
	bool UpdateGame(Game& game, const float time_delta); // Return false if game should be closed
	void DrawGame(Game& game, sf::RenderWindow& window);
	void ShutdownGame(Game& game);

	// Add new game state on top of the stack
	void PushGameState(Game& game, GameStateType state_type, bool is_exclusively_visible);

	// Remove current game state from the stack
	void PopGameState(Game& game);

	// Remove all game states from the stack and add new one
	void SwitchGameState(Game& game, GameStateType new_state);

	void InitGameState(Game& game, GameState& state);
	void ShutdownGameState(Game& game, GameState& state);
	void HandleWindowEventGameState(Game& game, GameState& state, sf::Event& event);
	void UpdateGameState(Game& game, const GameState& state, const float time_delta);
	void DrawGameState(Game& game, const GameState& state, sf::RenderWindow& window);
}
