#pragma once
#include <string>

namespace ApplesGame
{
	// Resources path
	const std::string RESOURCES_PATH = "Resources/";

	// Game settings constants
	constexpr float PLAYER_SIZE = 20.f;
	constexpr float APPLE_SIZE = 20.f;
	constexpr float INITIAL_SPEED = 100.f;
	constexpr float ACCELERATION = 10.f; // For each eaten apple player speed will be increased by this value
	constexpr int MIN_APPLES = 40;
	constexpr int MAX_APPLES = 80;
	constexpr unsigned int SCREEN_WIDTH = 800;
	constexpr unsigned int SCREEN_HEIGHT = 600;

	constexpr unsigned int APPLES_GRID_CELLS_HORIZONTAL = static_cast<unsigned>(SCREEN_WIDTH / (APPLE_SIZE * 4));
	constexpr unsigned int APPLES_GRID_CELLS_VERTICAL = static_cast<unsigned>(SCREEN_HEIGHT / (APPLE_SIZE * 4));
	constexpr unsigned int MAX_APPLES_IN_CELL = MAX_APPLES / 4; // We don't expect too much apples in one cell

	constexpr int MAX_RECORDS_TABLE_SIZE = 5;
}
