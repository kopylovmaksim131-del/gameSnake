#include <cassert>
#include "Game.h"

namespace ApplesGame
{
	void InitGame(Game& game, sf::Font& font)
	{
		assert(game.appleTexture.loadFromFile(RESOURCES_PATH + "\\Apple.png"));
		assert(game.rockTexture.loadFromFile(RESOURCES_PATH + "\\Rock.png"));
		assert(game.eatingBuffer.loadFromFile(RESOURCES_PATH + "\\AppleEat.wav"));
		assert(game.crashBuffer.loadFromFile(RESOURCES_PATH + "\\Death.wav"));
		assert(game.backgroundTexture.loadFromFile(RESOURCES_PATH + "\\Grass.png"));
		assert(game.soundEffectBuffer.loadFromFile(RESOURCES_PATH + "\\Effect.wav"));
		assert(game.body.loadFromFile(RESOURCES_PATH + "\\Body.png"));
		assert(game.head.loadFromFile(RESOURCES_PATH + "\\Head.png"));

		game.backgroundSprite.setTexture(game.backgroundTexture);
		setSpriteSize(game.backgroundSprite, SCREEN_WIDTH, SCREEN_HIGHT);

		game.Snake.emplace_back(Position2d{ SCREEN_WIDTH / 2.f, SCREEN_HIGHT / 2.f }, game.head);
		game.Snake.emplace_back(Position2d{ SCREEN_WIDTH / 2.f - PLAYER_SIZE, SCREEN_HIGHT / 2.f }, game.body);
		game.Snake.emplace_back(Position2d{ SCREEN_WIDTH / 2.f - PLAYER_SIZE * 2.f, SCREEN_HIGHT / 2.f }, game.body);

		game.apple = std::make_unique<Apple>(game.appleTexture);

		for (const auto& segment : game.Snake)
		{
			if (IsRectanglesCollide(segment.position.x, segment.position.y, game.apple->sprite.getPosition().x, game.apple->sprite.getPosition().y))
			{
				game.apple->GetApplePos(game.apple->sprite);
			}
		}

		for (int i = 0; i <= (SCREEN_HIGHT / ROCK_SIZE); i++)
		{
			game.wall.emplace_back(Position2d{ ROCK_SIZE / 2.f, ROCK_SIZE / 2.f + ROCK_SIZE * i }, game.rockTexture);
			game.wall.emplace_back(Position2d{ ROCK_SIZE / 2.f + SCREEN_HIGHT, ROCK_SIZE / 2.f + ROCK_SIZE * i }, game.rockTexture);
			game.wall.emplace_back(Position2d{ ROCK_SIZE / 2.f + ROCK_SIZE * i, ROCK_SIZE / 2.f }, game.rockTexture);
			game.wall.emplace_back(Position2d{ ROCK_SIZE / 2.f + ROCK_SIZE * i, SCREEN_HIGHT - ROCK_SIZE / 2.f }, game.rockTexture);
		}

		game.mainMenu.InitMainMenu(font);
		game.settingsMenu.InitSettingsMenu(font);
		game.difficultyMenu.InitDifficultyMenu(font);
		game.crashMenu.InitCrashMenu(font);
		game.recordMenu.InitRecordMenu(font);
		game.pauseMenu.InitPauseMenu(font);

		if (game.settingsMenu.effects[1])
		{
			if (game.music.openFromFile(RESOURCES_PATH + "\\Sound.ogg"))
			{
				game.music.setLoop(true);
				game.music.setVolume(100.f);
				game.music.play();
			}
		}

		game.playerScore.InitPlayerScore();
		game.eatingSound.InitSound(game.eatingBuffer);
		game.crashSound.InitSound(game.crashBuffer);
		game.soundEffect.InitSound(game.soundEffectBuffer);

		game.menuState.push(MenuLevel::MainMenu);
	}

	void UpdateGame(Game& game, float& deltaTime)
	{
		if (!game.isPlayerCrashed && !game.isMainMenu && !game.isGamePaused)
		{
			if (game.pauseDelay > 0.f)
			{
				if (game.pauseDelay > game.pauseTimer.getElapsedTime().asSeconds())
				{
					return;
				}
				else
				{
					game.pauseDelay = 0.f;
				}
			};

			static float moveTimer = 0.0f;
			moveTimer += deltaTime;
			float moveDelay = game.difficultyMenu.playerSpeed;
			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && game.Snake[0].direction != PlayerDirection::Left)
			{
				game.Snake[0].direction = PlayerDirection::Right;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && game.Snake[0].direction != PlayerDirection::Down)
			{
				game.Snake[0].direction = PlayerDirection::Up;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && game.Snake[0].direction != PlayerDirection::Right)
			{
				game.Snake[0].direction = PlayerDirection::Left;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && game.Snake[0].direction != PlayerDirection::Up)
			{
				game.Snake[0].direction = PlayerDirection::Down;
			}

			Position2d newPos = game.Snake[0].position;
			PlayerDirection oldDir = game.Snake[0].direction;

			if (moveTimer >= moveDelay)

			{
				moveTimer = 0.0f;

				switch (game.Snake[0].direction)
				{
				case PlayerDirection::Right:
					
					newPos.x += PLAYER_SIZE;
					break;

				case PlayerDirection::Up:

					newPos.y -= PLAYER_SIZE;
					break;

				case PlayerDirection::Left:

					newPos.x -= PLAYER_SIZE;
					break;

				case PlayerDirection::Down:

					newPos.y += PLAYER_SIZE;
					break;

				}

				if (newPos.x > SCREEN_HIGHT || newPos.x < ROCK_SIZE ||
					newPos.y > SCREEN_HIGHT - ROCK_SIZE || newPos.y < ROCK_SIZE)
				{
					game.isPlayerCrashed = true;
					game.crashMenu.MoveIndex(-1);

					if (game.playerRecords.size() == 10)
					{
						game.playerRecords.pop_back();
					}
					game.playerRecords.push_front( game.sumEatenApples * game.difficultyMenu.scorePerApple );

					if (game.settingsMenu.effects[0])
					{
						game.crashSound.sound.play();
					}
					return;
				}

				for (int i = 1; i <= game.Snake.size() - 1; i++)
				{
					if (newPos.x == game.Snake[i].position.x && newPos.y == game.Snake[i].position.y)
					{
						game.isPlayerCrashed = true;
						game.crashMenu.MoveIndex(-1);

						if (game.playerRecords.size() == 10)
						{
							game.playerRecords.pop_back();
						}
						game.playerRecords.push_front( game.sumEatenApples * game.difficultyMenu.scorePerApple );

						if (game.settingsMenu.effects[0])
						{
							game.crashSound.sound.play();
						}
						return;
					}
				}

				if (IsRectanglesCollide(newPos.x, newPos.y, game.apple->sprite.getPosition().x, game.apple->sprite.getPosition().y))
				{
					Position2d oldPos = game.Snake[game.Snake.size() - 1].position;

					switch (game.Snake[game.Snake.size() - 1].direction)
					{
					case PlayerDirection::Right:

						oldPos.x -= PLAYER_SIZE;
						break;

					case PlayerDirection::Up:

						oldPos.y += PLAYER_SIZE;
						break;

					case PlayerDirection::Left:

						oldPos.x += PLAYER_SIZE;
						break;

					case PlayerDirection::Down:

						oldPos.y -= PLAYER_SIZE;
						break;

					}

					game.Snake.emplace_back(oldPos, game.body);
					game.Snake[game.Snake.size() - 1].direction = game.Snake[game.Snake.size() - 2].direction;

					game.apple->GetApplePos(game.apple->sprite);

					for (const auto& segment : game.Snake)
					{
						if (IsRectanglesCollide(segment.position.x, segment.position.y, game.apple->sprite.getPosition().x, game.apple->sprite.getPosition().y))
						{
							game.apple->GetApplePos(game.apple->sprite);
						}
					}

					++game.sumEatenApples;
					if (game.settingsMenu.effects[0])
					{
						game.eatingSound.sound.play();
					}
				}

				game.Snake.emplace_front(newPos, game.head);
				game.Snake[0].direction = game.Snake[1].direction;
				
				switch (game.Snake[0].direction)
				{
				case PlayerDirection::Right:
					game.Snake[0].sprite.setRotation(0.f);
					break;
				case PlayerDirection::Up:
					game.Snake[0].sprite.setRotation(-90.f);
					break;
				case PlayerDirection::Left:
					game.Snake[0].sprite.setRotation(180.f);
					break;
				case PlayerDirection::Down:
					game.Snake[0].sprite.setRotation(90.f);
					break;
				};

				game.Snake[1].sprite.setTexture(game.body);
				game.Snake.pop_back();
			}
			
		}
	}

	void DrawGame(Game& game, sf::RenderWindow& window, sf::Font& font)
	{
		sprintf_s(game.titleText, sizeof(game.titleText), "Score: %d", game.sumEatenApples * game.difficultyMenu.scorePerApple);

		window.draw(game.backgroundSprite);

		game.playerScore.text.setFont(font);
		game.playerScore.text.setString(game.titleText);

		for (const auto& segment : game.Snake)
		{
			window.draw(segment.sprite);
		}

		window.draw(game.apple->sprite);
		
		for (const auto& rock : game.wall)
		{
			window.draw(rock.sprite);
		}

		window.draw(game.playerScore.text);

		if (game.isPlayerCrashed)
		{
			sf::RectangleShape popup(sf::Vector2f(400, 400));
			popup.setFillColor(sf::Color(50, 50, 50));
			popup.setOutlineColor(sf::Color::White);
			popup.setOutlineThickness(2);
			popup.setOrigin(sf::Vector2f(400 / 2, 400 / 2));
			popup.setPosition(SCREEN_WIDTH / 2, SCREEN_HIGHT / 2);

			sf::Text text; 
			text.setFillColor(sf::Color::White);
			text.setString(L"Количество очков");
			text.setFont(font);
			text.setCharacterSize(24);
			text.setPosition(SCREEN_WIDTH / 2 - text.getLocalBounds().width / 2, SCREEN_HIGHT / 2 - 200);
			
			sf::Text textScore(std::to_string(game.sumEatenApples * game.difficultyMenu.scorePerApple), font, 24);
			textScore.setFillColor(sf::Color::White);
			textScore.setPosition(SCREEN_WIDTH / 2 - textScore.getLocalBounds().width / 2, SCREEN_HIGHT / 2 - 170);

			sf::RectangleShape startGameButton(sf::Vector2f(100, 40));
			startGameButton.setFillColor(sf::Color(250, 250, 250));
			startGameButton.setOrigin(sf::Vector2f(100 / 2, 40 / 2));
			startGameButton.setPosition(SCREEN_WIDTH / 2, SCREEN_HIGHT / 2 + 100);

			sf::RectangleShape mainMenuButton(sf::Vector2f(100, 40));
			mainMenuButton.setFillColor(sf::Color(250, 250, 250));
			mainMenuButton.setOrigin(sf::Vector2f(100 / 2, 40 / 2));
			mainMenuButton.setPosition(SCREEN_WIDTH / 2, SCREEN_HIGHT / 2 + 150);

			window.draw(popup);
			window.draw(text);
			window.draw(textScore);
			window.draw(startGameButton);
			window.draw(mainMenuButton);

			sf::Text text1;
			text1.setFillColor(sf::Color::White);
			text1.setString(sf::String(L"Рекорды"));
			text1.setFont(font);
			text1.setCharacterSize(20);
			text1.setOrigin(text1.getLocalBounds().width / 2, text1.getLocalBounds().height / 2);
			text1.setPosition(SCREEN_WIDTH / 2, SCREEN_HIGHT / 2 - 110);
			window.draw(text1);

			std::deque<int> sortedByScore = game.playerRecords;
			std::sort(sortedByScore.begin(), sortedByScore.end(), std::greater<int>());

			for (int i = 0; i < sortedByScore.size(); i++)
			{
				if (i < 3)
				{
					sf::Text text;
					text.setFillColor(sf::Color::White);
					text.setString(std::to_string(i + 1) + ".");
					text.setFont(font);
					text.setCharacterSize(20);
					text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
					text.setPosition(SCREEN_WIDTH / 2 - text.getLocalBounds().width / 2 - 30, SCREEN_HIGHT / 2 - 90 + i * 30.f);
					window.draw(text);

					sf::Text value;
					value.setFillColor(sf::Color::White);
					value.setString(std::to_string(sortedByScore[i]));
					value.setFont(font);
					value.setCharacterSize(20);
					value.setOrigin(0, text.getLocalBounds().height / 2);
					value.setPosition(SCREEN_WIDTH / 2 - value.getLocalBounds().width / 2 - 10, SCREEN_HIGHT / 2 - 90 + i * 30.f);
					window.draw(value);
				}
			}

			for (const auto& menuText : game.crashMenu.menuTextes)
			{
				window.draw(menuText);
			}
		}
		else if (game.isMainMenu)
		{
			sf::RectangleShape popup(sf::Vector2f(400, 400));
			popup.setFillColor(sf::Color(50, 50, 50));
			popup.setOutlineColor(sf::Color::White);
			popup.setOutlineThickness(2);
			popup.setOrigin(sf::Vector2f(400 / 2, 400 / 2));
			popup.setPosition(SCREEN_WIDTH / 2, SCREEN_HIGHT / 2);

			window.draw(popup);

			if (game.menuState.top() == MenuLevel::MainMenu)
			{
				sf::Text textName;
				textName.setFillColor(sf::Color::White);
				textName.setString(L"Змейка");
				textName.setFont(font);
				textName.setCharacterSize(30);
				textName.setPosition(SCREEN_WIDTH / 2 - textName.getLocalBounds().width / 2, SCREEN_HIGHT / 2 - 180);
				window.draw(textName);

				for (const auto& menuText : game.mainMenu.menuTextes)
				{
					window.draw(menuText);
				}
			}
			else if (game.menuState.top() == MenuLevel::Difficulty)
			{
				sf::Text textName;
				textName.setFillColor(sf::Color::White);
				textName.setString(L"Уровень сложности");
				textName.setFont(font);
				textName.setCharacterSize(30);
				textName.setPosition(SCREEN_WIDTH / 2 - textName.getLocalBounds().width / 2, SCREEN_HIGHT / 2 - 180);
				window.draw(textName);

				for (const auto& menuText : game.difficultyMenu.menuTextes)
				{
					window.draw(menuText);
				}
			}
			else if (game.menuState.top() == MenuLevel::Recrods)
			{
				sf::Text textName;
				textName.setFillColor(sf::Color::White);
				textName.setString(L"Таблица рекордов");
				textName.setFont(font);
				textName.setCharacterSize(30);
				textName.setPosition(SCREEN_WIDTH / 2 - textName.getLocalBounds().width / 2, SCREEN_HIGHT / 2 - 180);
				window.draw(textName);

				if (game.playerRecords.empty())
				{
					for (const auto& menuText : game.recordMenu.menuTextes)
					{
						window.draw(menuText);
					}
				}
				else
				{
					std::deque<int> sortedByScore = game.playerRecords;
					std::sort(sortedByScore.begin(), sortedByScore.end(), std::greater<int>());

					for (int i = 0; i < sortedByScore.size(); i++)
					{
						sf::Text text;
						text.setFillColor(sf::Color::White);
						text.setString(std::to_string(i + 1) + ".");
						text.setFont(font);
						text.setCharacterSize(20);
						text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
						text.setPosition(SCREEN_WIDTH / 2 - text.getLocalBounds().width / 2 - 30, SCREEN_HIGHT / 2 - 90 + i * 30.f);
						window.draw(text);

						sf::Text value;
						value.setFillColor(sf::Color::White);
						value.setString(std::to_string(sortedByScore[i]));
						value.setFont(font);
						value.setCharacterSize(20);
						value.setOrigin(0, text.getLocalBounds().height / 2);
						value.setPosition(SCREEN_WIDTH / 2 - value.getLocalBounds().width / 2 - 10, SCREEN_HIGHT / 2 - 90 + i * 30.f);
						window.draw(value);
					}
				}
			}
			else if (game.menuState.top() == MenuLevel::Settings)
			{
				sf::Text textName;
				textName.setFillColor(sf::Color::White);
				textName.setString(L"Настройки");
				textName.setFont(font);
				textName.setCharacterSize(30);
				textName.setPosition(SCREEN_WIDTH / 2 - textName.getLocalBounds().width / 2, SCREEN_HIGHT / 2 - 180);
				window.draw(textName);

				for (const auto& menuText : game.settingsMenu.menuTextes)
				{
					window.draw(menuText);
				}
			}
		}
		else if (game.isGamePaused)
		{
			sf::RectangleShape popup(sf::Vector2f(200, 300));
			popup.setFillColor(sf::Color(50, 50, 50));
			popup.setOutlineColor(sf::Color::White);
			popup.setOutlineThickness(2);
			popup.setOrigin(sf::Vector2f(200 / 2, 300 / 2));
			popup.setPosition(SCREEN_WIDTH / 2, SCREEN_HIGHT / 2);

			sf::Text textName;
			textName.setFillColor(sf::Color::White);
			textName.setString(L"Пауза");
			textName.setFont(font);
			textName.setCharacterSize(30);
			textName.setPosition(SCREEN_WIDTH / 2 - textName.getLocalBounds().width / 2, SCREEN_HIGHT / 2 - 140);

			sf::RectangleShape continueGameButton(sf::Vector2f(100, 40));
			continueGameButton.setFillColor(sf::Color(250, 250, 250));
			continueGameButton.setOrigin(sf::Vector2f(100 / 2, 40 / 2));
			continueGameButton.setPosition(SCREEN_WIDTH / 2, SCREEN_HIGHT / 2);

			sf::RectangleShape mainMenuButton(sf::Vector2f(100, 40));
			mainMenuButton.setFillColor(sf::Color(250, 250, 250));
			mainMenuButton.setOrigin(sf::Vector2f(100 / 2, 40 / 2));
			mainMenuButton.setPosition(SCREEN_WIDTH / 2, SCREEN_HIGHT / 2 + 60);

			window.draw(popup);
			window.draw(textName);
			window.draw(continueGameButton);
			window.draw(mainMenuButton);
			
			for (const auto& menuText : game.pauseMenu.menuTextes)
			{
				window.draw(menuText);
			}
		}
	}

	void RestartGame(Game& game)
	{
		game.isPlayerCrashed = false;
		game.isMainMenu = false;
		game.sumEatenApples = 0;

		game.Snake.clear();
		game.Snake.emplace_back(Position2d{SCREEN_WIDTH / 2.f, SCREEN_HIGHT / 2.f}, game.head);
		game.Snake.emplace_back(Position2d{ SCREEN_WIDTH / 2.f - PLAYER_SIZE, SCREEN_HIGHT / 2.f }, game.body);
		game.Snake.emplace_back(Position2d{ SCREEN_WIDTH / 2.f - PLAYER_SIZE * 2.f, SCREEN_HIGHT / 2.f }, game.body);
	}

	void DeinitGame(Game& game)
	{

	}

}


