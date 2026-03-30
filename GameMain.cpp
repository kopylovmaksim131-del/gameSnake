
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> 
#include "Game.h"

int main()
{
	using namespace ApplesGame;

	int seed = (int)time(nullptr);
	srand(seed);

	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HIGHT), "Apple Game");

	Game game;

	sf::Font font;
	font.loadFromFile("C:/WINDOWS/Fonts/arial.ttf");

	InitGame(game, font);

	game.isMainMenu = true;

	sf::Clock gameClock;
	float lastTime = gameClock.getElapsedTime().asSeconds();

	while (window.isOpen())
	{
		sf::sleep(sf::milliseconds(16));

		float currentTime = gameClock.getElapsedTime().asSeconds();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			{
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W && game.isPlayerCrashed)
			{
				if (game.settingsMenu.effects[0])
				{
					game.soundEffect.sound.play();
				}
				game.crashMenu.MoveIndex(-1);
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S && game.isPlayerCrashed)
			{
				if (game.settingsMenu.effects[0])
				{
					game.soundEffect.sound.play();
				}
				game.crashMenu.MoveIndex(1);
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter && game.isPlayerCrashed)
			{
				if (game.settingsMenu.effects[0])
				{
					game.soundEffect.sound.play();
				}
				if (game.crashMenu.selectedIndex == 0)
				{
					RestartGame(game);
				}
				else if (game.crashMenu.selectedIndex == 1)
				{
					game.isPlayerCrashed = false;
					game.isMainMenu = true;
				}
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W && game.isMainMenu)
			{
				if (game.settingsMenu.effects[0])
				{
					game.soundEffect.sound.play();
				}
				if (game.menuState.top() == MenuLevel::MainMenu)
				{
					game.mainMenu.MoveIndex(-1);
				}
				else if (game.menuState.top() == MenuLevel::Difficulty)
				{
					game.difficultyMenu.MoveIndex(-1);
				}
				else if (game.menuState.top() == MenuLevel::Settings)
				{
					game.settingsMenu.MoveIndex(-1);
				}
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S && game.isMainMenu)
			{
				if (game.settingsMenu.effects[0])
				{
					game.soundEffect.sound.play();
				}
				if (game.menuState.top() == MenuLevel::MainMenu)
				{
					game.mainMenu.MoveIndex(1);
				}
				else if (game.menuState.top() == MenuLevel::Difficulty)
				{
					game.difficultyMenu.MoveIndex(1);
				}
				else if (game.menuState.top() == MenuLevel::Settings)
				{
					game.settingsMenu.MoveIndex(1);
				}
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter && game.isMainMenu)
			{
				if (game.settingsMenu.effects[0])
				{
					game.soundEffect.sound.play();
				}
				if (game.menuState.top() == MenuLevel::MainMenu)
				{
					if (game.mainMenu.selectedIndex == 0)
					{
						RestartGame(game);
					}
					else if (game.mainMenu.selectedIndex == game.mainMenu.levels.size() - 1)
					{
						window.close();
					}
					else
					{
						game.menuState.push(game.mainMenu.levels[game.mainMenu.selectedIndex]);
					}
				}
				else if (game.menuState.top() == MenuLevel::Difficulty)
				{
					game.difficultyMenu.SetDifficulty();
				}
				else if (game.menuState.top() == MenuLevel::Settings)
				{
					game.settingsMenu.SetSettings();
					if (!game.settingsMenu.effects[1])
					{
						game.music.stop();
					}
					else
					{
						game.music.play();
					}
				}
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::B && game.isMainMenu)
			{
				if (game.settingsMenu.effects[0])
				{
					game.soundEffect.sound.play();
				}
				if (game.menuState.top() == MenuLevel::MainMenu)
				{
					window.close();
				}
				else 
				{
					game.menuState.pop();
				}
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P && !game.isPlayerCrashed && !game.isMainMenu)
			{
				if (game.settingsMenu.effects[0])
				{
					game.soundEffect.sound.play();
				}
				game.isGamePaused = true;
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W && game.isGamePaused)
			{
				if (game.settingsMenu.effects[0])
				{
					game.soundEffect.sound.play();
				}
				game.pauseMenu.MoveIndex(-1);
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S && game.isGamePaused)
			{
				if (game.settingsMenu.effects[0])
				{
					game.soundEffect.sound.play();
				}
				game.pauseMenu.MoveIndex(1);
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter && game.isGamePaused)
			{
				if (game.settingsMenu.effects[0])
				{
					game.soundEffect.sound.play();
				}

				game.isGamePaused = false;

				if (game.pauseMenu.selectedIndex == 0)
				{
					game.pauseTimer.restart();
					game.pauseDelay = 1.f;
				}
				else if (game.pauseMenu.selectedIndex == 1)
				{
					game.pauseMenu.MoveIndex(-1);
					game.isMainMenu = true;
				}
			}
		}

		UpdateGame(game, deltaTime);

		window.clear();

		DrawGame(game, window, font);

		window.display();
	}

	DeinitGame(game);

	return 0;
}
