#pragma once
#include <string>

namespace ApplesGame
{
	// Resources path
	const std::string RESOURCES_PATH = "Resources/";

	// Game settings constants
	const float PLAYER_SIZE = 20.f;
	const float APPLE_SIZE = 20.f;
	const float INITIAL_SPEED = 100.f;
	const float ACCELERATION = 10.f; // For each eaten apple player speed will be increased by this value
	const int MIN_APPLES = 40;
	const int MAX_APPLES = 80;
	const unsigned int SCREEN_WIDTH = 800;
	const unsigned int SCREEN_HEIGHT = 600;

	const unsigned int APPLES_GRID_CELLS_HORIZONTAL = unsigned(SCREEN_WIDTH / (APPLE_SIZE * 4));
	const unsigned int APPLES_GRID_CELLS_VERTICAL = unsigned(SCREEN_HEIGHT / (APPLE_SIZE * 4));
	const unsigned int MAX_APPLES_IN_CELL = MAX_APPLES / 4; // We don't expect too much apples in one cell

	const int MAX_RECORDS_TABLE_SIZE = 5;
}
