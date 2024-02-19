// ©2023, XYZ School. All rights reserved.
// Authored by Aleksandr Rybalka (polterageist@gmail.com)

#include <SFML/Graphics.hpp>
#include <cstdlib>

#include "Game.h"

using namespace ApplesGame;

int main()
{
	// Init random number generator
	const unsigned int seed = static_cast<unsigned int>(time(nullptr)); // Get current time as seed. You can also use any other number to fix randomization
	srand(seed);

	// Init window
	sf::RenderWindow window(sf::VideoMode(ApplesGame::SCREEN_WIDTH, ApplesGame::SCREEN_HEIGHT), "AppleGame");

	// We now use too much memory for stack, so we need to allocate it on heap
	ApplesGame::Game* game = new ApplesGame::Game();
	InitGame(*game);

	// Init game clock
	const sf::Clock game_clock;
	sf::Time last_time = game_clock.getElapsedTime();

	// Game loop
	while (window.isOpen())
	{
		HandleWindowEvents(*game, window);

		if (!window.isOpen())
		{
			break;
		}

		// Calculate time delta
		sf::Time current_time = game_clock.getElapsedTime();
		const float time_delta = current_time.asSeconds() - last_time.asSeconds();
		last_time = current_time;
		if (UpdateGame(*game, time_delta))
		{
			// Draw everything here
		// Clear the window first
			window.clear();

			DrawGame(*game, window);

			// End the current frame, display window contents on screen
			window.display();
		}
		else
		{
			window.close();
		}
	}

	ShutdownGame(*game);
	delete game;
	game = nullptr;

	return 0;
}
