#include "Math.h"

namespace ApplesGame
{

	Vector2D operator+(const Vector2D& lhs, const Vector2D& rhs)
	{
		Vector2D result;
		result.x = lhs.x + rhs.x;
		result.y = lhs.y + rhs.y;
		return result;
	}

	sf::Vector2f OurVectorToSf(const Vector2D& v)
	{
		return sf::Vector2f(v.x, v.y);
	}

	sf::Vector2f GetSpriteScale(const sf::Sprite& sprite, const Vector2D& desired_size)
	{
		const sf::Vector2u texture_size = sprite.getTexture()->getSize();
		const sf::Vector2f sprite_scale = { desired_size.x / static_cast<float>(texture_size.x), desired_size.y / static_cast<float>(texture_size.y) };
		return sprite_scale;
	}

	sf::Vector2f GetItemOrigin(const sf::Sprite& sprite, const Vector2D& relative_position)
	{
		const sf::Vector2u texture_size = sprite.getTexture()->getSize();
		return { relative_position.x * static_cast<float>(texture_size.x), relative_position.y * static_cast<float>(texture_size.y) };
	}

	sf::Vector2f GetItemOrigin(const sf::Text& text, const sf::Vector2f& relative_position)
	{
		const sf::FloatRect text_size = text.getLocalBounds();
		return {
			(text_size.left + text_size.width) * relative_position.x,
			(text_size.top + text_size.height) * relative_position.y,
		};
	}

	void DrawItemsList(sf::RenderWindow& window, const std::vector<sf::Text*>& items, const float spacing, const Orientation orientation, const
	                   Alignment alignment, const sf::Vector2f& position, const sf::Vector2f& origin)
	{
		sf::FloatRect total_rect;
		// Calculate total height/width of all texts
		for (auto it = items.begin(); it != items.end(); ++it)
		{
			sf::FloatRect item_rect = (*it)->getGlobalBounds();

			if (orientation == Orientation::HORIZONTAL)
			{
				total_rect.width += item_rect.width + (it != items.end() - 1 ? spacing : 0.f);
				total_rect.height = std::max(total_rect.height, item_rect.height);
			}
			else
			{
				total_rect.width = std::max(total_rect.width, item_rect.width);
				total_rect.height += item_rect.height + (it != items.end() - 1 ? spacing : 0.f);
			}
		}

		total_rect.left = position.x - origin.x * total_rect.width;
		total_rect.top = position.y - origin.y * total_rect.height;
		sf::Vector2f current_pos = { total_rect.left, total_rect.top };
		
		for (auto it = items.begin(); it != items.end(); ++it)
		{
			const sf::FloatRect item_rect = (*it)->getGlobalBounds();
			sf::Vector2f item_origin;

			if (orientation == Orientation::HORIZONTAL)
			{
				item_origin.y = alignment == Alignment::MIN ? 0.f : alignment == Alignment::MIDDLE ? 0.5f : 1.f;
				item_origin.x = 0.f;
				current_pos.y = total_rect.top + item_origin.y * total_rect.height;
			}
			else
			{
				item_origin.y = 0.f;
				item_origin.x = alignment == Alignment::MIN ? 0.f : alignment == Alignment::MIDDLE ? 0.5f : 1.f;
				current_pos.x = total_rect.left + item_origin.x * total_rect.width;
			}
			
			(*it)->setOrigin(GetItemOrigin(**it, item_origin));
			(*it)->setPosition(current_pos);
			window.draw(**it);

			if (orientation == Orientation::HORIZONTAL)
			{
				current_pos.x += item_rect.width + spacing;
			}
			else
			{
				current_pos.y += item_rect.height + spacing;
			}

			
		}
	}

	bool IsPointInRect(const Vector2D point, const Vector2D rect_tl, const Vector2D rect_br)
	{
		if (point.x < rect_tl.x || point.x > rect_br.x)
		{
			return false;
		}
		if (point.y < rect_tl.y || point.y > rect_br.y)
		{
			return false;
		}
		return true;
	}

}
