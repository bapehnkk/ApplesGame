#pragma once
#include <unordered_map>
#include <unordered_set>
#include <SFML/Graphics.hpp>
#include "GameSettings.h"
#include "Math.h"

namespace ApplesGame
{
	struct Apple;

	// Использование pair для представления координат сетки
	using GridCoord = std::pair<int, int>;

	// Хэшер для GridCoord
	struct GridCoordHasher
	{
		std::size_t operator()(const GridCoord& coord) const
		{
			return std::hash<int>()(coord.first) ^ (std::hash<int>()(coord.second) << 1);
		}
	};
	struct Apple
	{
		Position position;
		sf::Sprite sprite;
		bool is_eaten = false;


		std::unordered_set<Apple*> grid_cells;
	};

	void InitApple(Apple& apple, const sf::Texture& texture);
	void ResetAppleState(Apple& apple);
	void DrawApple(Apple& apple, sf::RenderWindow& window);
	void MarkAppleAsEaten(Apple& apple);

	struct ApplesGrid
	{
		// Использование unordered_map с пользовательским хэшером
		std::unordered_map<GridCoord, std::unordered_set<Apple*>, GridCoordHasher> cells;
	};

	void ClearApplesGrid(ApplesGrid& apples_grid);
	void AddAppleToGrid(ApplesGrid& apples_grid, Apple& apple);
	void RemoveAppleFromGrid(ApplesGrid& apples_grid, Apple& apple);
	bool FindPlayerCollisionWithApples(const Vector2D& player_position, const ApplesGrid& grid, std::vector<Apple*>& result); // Result should be a pointer to an array of MAX_APPLES / 4 pointers to apples
}
