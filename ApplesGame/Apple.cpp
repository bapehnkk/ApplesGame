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
		if (apple.isEaten)
		{
			return;
		}
			
		apple.sprite.setPosition(OurVectorToSf(apple.position));
		window.draw(apple.sprite);
	}

	void MarkAppleAsEaten(Apple& apple)
	{
		apple.isEaten = true;
	}

	void ResetAppleState(Apple& apple)
	{
		// init apple state
		apple.position.x = (float)(rand() % SCREEN_WIDTH);
		apple.position.y = (float)(rand() % SCREEN_HEIGHT);
		apple.isEaten = false;
	}

	void ClearApplesGrid(ApplesGrid& applesGrid)
	{
		applesGrid.cells.clear();
	}

	void AddAppleToGrid(ApplesGrid& applesGrid, Apple& apple)
	{
		// Рассчитываем индексы ячеек сетки для яблока
		int cellX = static_cast<int>(apple.position.x / (SCREEN_WIDTH / APPLES_GRID_CELLS_HORIZONTAL));
		int cellY = static_cast<int>(apple.position.y / (SCREEN_HEIGHT / APPLES_GRID_CELLS_VERTICAL));
		GridCoord cellCoord = {cellX, cellY};

		// Добавляем яблоко в соответствующую ячейку
		applesGrid.cells[cellCoord].insert(&apple);
	}


	void RemoveAppleFromGrid(ApplesGrid& applesGrid, Apple& apple)
	{
		for (auto& cell : applesGrid.cells)
		{
			auto it = cell.second.find(&apple);
			if (it != cell.second.end())
			{
				cell.second.erase(it);
				break; // Предполагаем, что яблоко может быть только в одной ячейке
			}
		}
	}

	bool FindPlayerCollisionWithApples(const Vector2D& playerPosition, const ApplesGrid& grid, std::vector<Apple*>& result)
	{
		bool foundCollision = false;

		// Рассчитываем индексы ячеек сетки для игрока
		int cellX = static_cast<int>(playerPosition.x / (SCREEN_WIDTH / APPLES_GRID_CELLS_HORIZONTAL));
		int cellY = static_cast<int>(playerPosition.y / (SCREEN_HEIGHT / APPLES_GRID_CELLS_VERTICAL));
		GridCoord cellCoord = {cellX, cellY};

		// Проверяем наличие яблок в ячейке
		auto it = grid.cells.find(cellCoord);
		if (it != grid.cells.end())
		{
			for (Apple* apple : it->second)
			{
				if (!apple->isEaten)
				{
					float dx = playerPosition.x - apple->position.x;
					float dy = playerPosition.y - apple->position.y;
					float distance = sqrt(dx * dx + dy * dy);
					if (distance < (PLAYER_SIZE + APPLE_SIZE) / 2)
					{
						result.push_back(apple);
						foundCollision = true;
					}
				}
			}
		}

		return foundCollision;
	}
}
