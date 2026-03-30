#pragma once

#include <SFML/Graphics.hpp>
#include <deque>
#include "Math.h"
#include "Constants.h"

namespace ApplesGame
{
	struct Apple
	{
		sf::Sprite sprite;
		Apple(const sf::Texture& tex)
		{
			sprite.setTexture(tex);
			setSpriteSize(sprite, APPLE_SIZE, APPLE_SIZE);
			setSpriteRelativeOrigin(sprite, 0.5f, 0.5f);
			GetApplePos(sprite);
		}

		void GetApplePos(sf::Sprite& sprite)
		{
			Position2d pos = GetRandomPositionInScreen();
			sprite.setPosition(sf::Vector2f(pos.x, pos.y));
		}
	};
}
