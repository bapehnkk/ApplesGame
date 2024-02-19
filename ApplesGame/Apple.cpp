#include "Apple.h"
#include "GameSettings.h"

#include <cstdlib>
#include <assert.h>

namespace ApplesGame
{
	void InitApple(Apple& apple, const sf::Texture& texture)
	{
		// Init sprite
		apple.sprite.setTexture(texture);
		apple.sprite.setOrigin(GetItemOrigin(apple.sprite, { 0.5f, 0.5f })); // We need to use texture as origin ignores scale
		apple.sprite.setScale(GetSpriteScale(apple.sprite, { APPLE_SIZE, APPLE_SIZE }));
	}

	void DrawApple(Apple& apple, sf::RenderWindow& window)
	{
		if (apple.is_eaten)
		{
			return;
		}
			
		apple.sprite.setPosition(OurVectorToSf(apple.position));
		window.draw(apple.sprite);
	}

	void MarkAppleAsEaten(Apple& apple)
	{
		apple.is_eaten = true;
	}

	void ResetAppleState(Apple& apple)
	{
		// init apple state
		apple.position.x = static_cast<float>(rand() % SCREEN_WIDTH);
		apple.position.y = static_cast<float>(rand() % SCREEN_HEIGHT);
		apple.is_eaten = false;
	}

	void ClearApplesGrid(ApplesGrid& apples_grid)
	{
		apples_grid.cells.clear();
	}

	void AddAppleToGrid(ApplesGrid& apples_grid, Apple& apple)
	{
		// Рассчитываем индексы ячеек сетки для яблока
		int cell_x = static_cast<int>(apple.position.x / (static_cast<float>(SCREEN_WIDTH) / APPLES_GRID_CELLS_HORIZONTAL));
		int cell_y = static_cast<int>(apple.position.y / (static_cast<float>(SCREEN_HEIGHT) / APPLES_GRID_CELLS_VERTICAL));
		GridCoord cell_coord = {cell_x, cell_y};

		// Добавляем яблоко в соответствующую ячейку
		apples_grid.cells[cell_coord].insert(&apple);
	}


	void RemoveAppleFromGrid(ApplesGrid& apples_grid, Apple& apple)
	{
		for (auto& cell : apples_grid.cells)
		{
			auto it = cell.second.find(&apple);
			if (it != cell.second.end())
			{
				cell.second.erase(it);
				break; // Предполагаем, что яблоко может быть только в одной ячейке
			}
		}
	}

	bool FindPlayerCollisionWithApples(const Vector2D& player_position, const ApplesGrid& grid, std::vector<Apple*>& result)
	{
		bool found_collision = false;

		// Рассчитываем индексы ячеек сетки для игрока
		int cell_x = static_cast<int>(player_position.x / (static_cast<float>(SCREEN_WIDTH) / APPLES_GRID_CELLS_HORIZONTAL));
		int cell_y = static_cast<int>(player_position.y / (static_cast<float>(SCREEN_HEIGHT) / APPLES_GRID_CELLS_VERTICAL));
		const GridCoord cell_coord = {cell_x, cell_y};

		// Проверяем наличие яблок в ячейке
		const auto it = grid.cells.find(cell_coord);
		if (it != grid.cells.end())
		{
			for (Apple* apple : it->second)
			{
				if (!apple->is_eaten)
				{
					const float dx = player_position.x - apple->position.x;
					const float dy = player_position.y - apple->position.y;
					const float distance = sqrt(dx * dx + dy * dy);
					if (distance < (PLAYER_SIZE + APPLE_SIZE) / 2)
					{
						result.push_back(apple);
						found_collision = true;
					}
				}
			}
		}

		return found_collision;
	}
}
