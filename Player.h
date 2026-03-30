#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>
#include "Math.h"
#include "Constants.h"

namespace ApplesGame
{
	enum class PlayerDirection :int
	{
		Right = 0,
		Up,
		Left,
		Down
	};

	struct Player
	{
		Position2d position;
		float speed = INITIAL_SPEED;
		PlayerDirection direction = PlayerDirection::Right;
		sf::Sprite sprite;
		Player(const Position2d& pos, const sf::Texture& tex)
		{
			position = pos;

			sprite.setTexture(tex);
			setSpriteSize(sprite, PLAYER_SIZE, PLAYER_SIZE);
			setSpriteRelativeOrigin(sprite, 0.5f, 0.5f);
			sprite.setPosition(sf::Vector2f(pos.x, pos.y));
		}
	};

	struct SnakePosition
	{
		Position2d position;
		PlayerDirection direction = PlayerDirection::Right;
	};
}
