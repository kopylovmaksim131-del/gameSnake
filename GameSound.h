#pragma once

#include <SFML/Audio.hpp>

namespace ApplesGame
{
	struct EatingSound
	{
		sf::Sound sound;

		void InitSound(sf::SoundBuffer& buffer)
		{
			sound.setBuffer(buffer);
		}
	};

	struct CrashSound
	{
		sf::Sound sound;

		void InitSound(sf::SoundBuffer& buffer)
		{
			sound.setBuffer(buffer);
		}
	};

	struct SoundEffect
	{
		sf::Sound sound;

		void InitSound(sf::SoundBuffer& buffer)
		{
			sound.setBuffer(buffer);
		}
	};
}
