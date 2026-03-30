#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <deque>
#include <stack>
#include "Player.h"
#include "Apple.h"
#include "Rock.h"
#include "Constants.h"
#include "GameText.h"
#include "GameSound.h"
#include "Menu.h"


namespace ApplesGame
{
	struct Game
	{
		sf::Texture body;
		sf::Texture head;
		std::deque<Player> Snake;
		sf::Texture appleTexture;
		sf::Sprite backgroundSprite;
		sf::Texture backgroundTexture;
		std::unique_ptr<Apple> apple;
		sf::Texture rockTexture;
		std::vector<Rock> wall;
		int sumEatenApples = 0;
		char titleText[40];
		PlayerScore playerScore;
		sf::SoundBuffer eatingBuffer;
		EatingSound eatingSound;
		sf::SoundBuffer crashBuffer;
		SoundEffect soundEffect;
		sf::SoundBuffer soundEffectBuffer;
		sf::Music music;
		CrashSound crashSound;
		MainMenu mainMenu;
		SettingsMenu settingsMenu;
		DifficultyMenu difficultyMenu;
		CrashMenu crashMenu;
		RecordMenu recordMenu;
		PauseMenu pauseMenu;
		sf::Clock pauseTimer;
		float pauseDelay = 0;
		std::deque<int> playerRecords;
		std::stack<MenuLevel> menuState;
		bool isPlayerCrashed = false;
		bool isMainMenu = false;
		bool isGamePaused = false;
	};

	void InitGame(Game& game, sf::Font& font);
	void UpdateGame(Game& game, float& deltaTime);
	void DrawGame(Game& game, sf::RenderWindow& window, sf::Font& font);
	void RestartGame(Game& game);
	void DeinitGame(Game& game);
}

