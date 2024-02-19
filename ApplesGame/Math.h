#pragma once
#include <SFML/Graphics.hpp>

namespace ApplesGame
{
	struct Vector2D
	{
		float x = 0.f;
		float y = 0.f;
	};

	Vector2D operator+(const Vector2D& lhs, const Vector2D& rhs);


	typedef Vector2D Position;

	sf::Vector2f OurVectorToSf(const Vector2D& v);
	sf::Vector2f GetSpriteScale(const sf::Sprite& sprite, const Vector2D& desired_size);
	sf::Vector2f GetItemOrigin(const sf::Sprite& sprite, const Vector2D& relative_position);
	sf::Vector2f GetItemOrigin(const sf::Text& text, const sf::Vector2f& relative_position);

	// Helper method for organizing text items
	enum class Orientation
	{
		HORIZONTAL,
		VERTICAL
	};

	enum class Alignment
	{
		MIN, // Left or Top
		MIDDLE,
		MAX // Right or Bottom
	};

	void DrawItemsList(sf::RenderWindow& window, const std::vector<sf::Text*>& items, const float spacing, const Orientation orientation, const
	                   Alignment alignment, const sf::Vector2f& position, const sf::Vector2f& origin);

	bool IsPointInRect(const Vector2D point, const Vector2D rect_tl, const Vector2D rect_br);
}
