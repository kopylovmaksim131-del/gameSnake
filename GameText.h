#pragma once

#include <SFML/Graphics.hpp>
#include "Constants.h"

namespace ApplesGame
{
	struct PlayerScore
	{
		sf::Text text;

		void InitPlayerScore()
		{
			text.setFillColor(sf::Color::Black);
			text.setCharacterSize(20);
			text.setPosition(640, 0);
		}
	};
}

