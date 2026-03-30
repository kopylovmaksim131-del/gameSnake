#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "Constants.h"

namespace ApplesGame
{
	Position2d GetRandomPositionInScreen()
	{
		Position2d resalt;
		int celleCount = (SCREEN_HIGHT - 2 * ROCK_SIZE) / APPLE_SIZE;
		resalt.x = (ROCK_SIZE / APPLE_SIZE + rand() % celleCount) * APPLE_SIZE + APPLE_SIZE / 2;
		resalt.y = (ROCK_SIZE / APPLE_SIZE + rand() % celleCount) * APPLE_SIZE + APPLE_SIZE / 2;
		return resalt;

	}

	bool IsRectanglesCollide(float PlayerX, float PlayerY, float AppleX, float AppleY)
	{
		bool resalt = false;
		float dx = (float)fabs(PlayerX - AppleX);
		float dy = (float)fabs(PlayerY - AppleY);
		float delta = (float)pow(dx, 2) + (float)pow(dy, 2);

		resalt = delta < pow(APPLE_SIZE + PLAYER_SIZE, 2) / 4.f;
		return resalt;
	}

	void setSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight)
	{
		sf::FloatRect spriteRect = sprite.getLocalBounds();
		sf::Vector2f scale = { desiredWidth / spriteRect.width, desiredHeight / spriteRect.height };
		sprite.setScale(scale);
	}

	void setSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY)
	{
		sf::FloatRect spriteRect = sprite.getLocalBounds();
		sf::Vector2f origin = { originX * spriteRect.width, originY * spriteRect.height };
		sprite.setOrigin(origin);
	}
}

