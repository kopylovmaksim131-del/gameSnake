#pragma once

#include <SFML/Graphics.hpp>
#include "Math.h"
#include "Constants.h"

namespace ApplesGame
{
	struct Rock
	{
		Position2d position;
		sf::Sprite sprite;

		Rock(const Position2d& pos, const sf::Texture& tex)
		{
			position = pos;

			sprite.setTexture(tex);
			setSpriteSize(sprite, ROCK_SIZE, ROCK_SIZE);
			setSpriteRelativeOrigin(sprite, 0.5f, 0.5f);
			sprite.setPosition(sf::Vector2f(position.x, position.y));
		}

	};
}

