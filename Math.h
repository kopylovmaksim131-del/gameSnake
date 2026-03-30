#pragma once

namespace sf
{
	class Sprite;
}

namespace ApplesGame
{
	struct Vector2D
	{
		float x = 0.0f;
		float y = 0.0f;
	};

	typedef Vector2D Position2d;

	Position2d GetRandomPositionInScreen();

	bool IsRectanglesCollide(float PlayerX, float PlayerY, float AppleX, float AppleY);
	void setSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight);
	void setSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY);
}
