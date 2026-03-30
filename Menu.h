#pragma once

#include <SFML/Graphics.hpp>
#include "Math.h"
#include "Constants.h"

namespace ApplesGame
{
	enum class MenuLevel
	{
		MainMenu,
		StartGame,
		Difficulty,
		Recrods,
		Settings,
		Exit
	};

	struct MainMenu
	{
		std::vector <sf::String> names;
		int selectedIndex = 0;
		std::vector<sf::Text> menuTextes;
		std::vector<MenuLevel> levels;
		
		void InitMainMenu(sf::Font& font)
		{
			names = { L"Начать игру", L"Уровень сложности", L"Таблица рекордов", L"Настройки", L"Выход" };
			levels = { MenuLevel::StartGame, MenuLevel::Difficulty, MenuLevel::Recrods, MenuLevel::Settings, MenuLevel::Exit };
            
            for (int i = 0; i < names.size(); i++)
            {
                sf::Text text;
                text.setFont(font);
                text.setString(names[i]);
                text.setCharacterSize(24);
                text.setFillColor(i == 0 ? sf::Color::Green : sf::Color::White);
                text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
                text.setPosition(SCREEN_WIDTH / 2, SCREEN_HIGHT / 2 - 50 + i * 30.f);

				menuTextes.push_back(text);
            }
		}
		void MoveIndex(int i)
		{
			int newIndex = selectedIndex + i;
			if (newIndex >= 0 && newIndex <= menuTextes.size() - 1)
			{
				menuTextes[newIndex].setFillColor(sf::Color::Green);
				menuTextes[selectedIndex].setFillColor(sf::Color::White);
				selectedIndex = newIndex;
			}
		}

	};

	struct SettingsMenu
	{
		std::vector <sf::String> names;
		int selectedIndex = 0;
		std::vector <bool> effects;
		std::vector<sf::Text> menuTextes;

		void InitSettingsMenu(sf::Font& font)
		{
			names = { L"Звук", L"Музыка" };

			effects = { true, true };

			for (int i = 0; i < names.size(); i++)
			{
				sf::Text textMusic;
				textMusic.setFont(font);
				textMusic.setString(names[i]);
				textMusic.setCharacterSize(24);
				textMusic.setFillColor(i == 0 ? sf::Color::Green : sf::Color::White);
				textMusic.setPosition(SCREEN_WIDTH / 2 - 100, SCREEN_HIGHT / 2 - 50 + i * 30.f);

				menuTextes.push_back(textMusic);

				sf::Text value;
				value.setFont(font);
				value.setString(effects[i] ? sf::String("[x]") : sf::String(L"[  ]"));
				value.setCharacterSize(24);
				value.setFillColor(i + 1 == 1 ? sf::Color::Green : sf::Color::White);
				sf::FloatRect bounds1 = value.getLocalBounds();
				value.setPosition(SCREEN_WIDTH / 2 + 50, SCREEN_HIGHT / 2 - 50 + i * 30.f);

				menuTextes.push_back(value);
			}
		}
		void MoveIndex(int i)
		{
			int newIndex = selectedIndex + i;
			if (newIndex >= 0 && newIndex <= names.size() - 1)
			{
				menuTextes[newIndex * 2].setFillColor(sf::Color::Green);
				menuTextes[newIndex * 2 + 1].setFillColor(sf::Color::Green);
				menuTextes[selectedIndex * 2].setFillColor(sf::Color::White);
				menuTextes[selectedIndex * 2 + 1].setFillColor(sf::Color::White);
				selectedIndex = newIndex;
			}
		}
		void SetSettings()
		{
			effects[selectedIndex] = !effects[selectedIndex];
			menuTextes[selectedIndex * 2 + 1].setString(effects[selectedIndex] ? sf::String("[x]") : sf::String(L"[  ]"));
		}

	};

	struct DifficultyMenu
	{
		std::vector <sf::String> names;
		int selectedIndex = 0;
		std::vector<sf::Text> menuTextes;
		float playerSpeed = 0.2f;
		int scorePerApple = 2;

		void InitDifficultyMenu(sf::Font& font)
		{
			names = { L"Простой", L"Тяжелей простого", L"Средний", L"Легче тяжелого", L"Тяжелый" };

			for (int i = 0; i < names.size(); i++)
			{
				sf::Text text;
				text.setFont(font);
				text.setString(names[i]);
				text.setCharacterSize(24);
				text.setFillColor(i == 0 ? sf::Color::Green : sf::Color::White);
				text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
				text.setPosition(SCREEN_WIDTH / 2, SCREEN_HIGHT / 2 - 50 + i * 30.f);

				menuTextes.push_back(text);
			}
		}
		void MoveIndex(int i)
		{
			int newIndex = selectedIndex + i;
			if (newIndex >= 0 && newIndex <= menuTextes.size() - 1)
			{
				menuTextes[newIndex].setFillColor(sf::Color::Green);
				menuTextes[selectedIndex].setFillColor(sf::Color::White);
				selectedIndex = newIndex;
			}
		}
		void SetDifficulty()
		{
			playerSpeed = 0.2f - selectedIndex * 0.03f;
			scorePerApple = 2 + selectedIndex * 2;
		}
	};

	struct RecordMenu
	{
		std::vector<sf::Text> menuTextes;

		void InitRecordMenu(sf::Font& font)
		{
			sf::Text text;
			text.setFont(font);
			text.setString(sf::String(L"Нет установленных рекордов"));
			text.setCharacterSize(24);
			text.setFillColor(sf::Color::White);
			text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
			text.setPosition(SCREEN_WIDTH / 2, SCREEN_HIGHT / 2);

			menuTextes.push_back(text);
		}
	};
	
	struct CrashMenu
	{
		std::vector <sf::String> names;
		int selectedIndex = 0;
		std::vector<sf::Text> menuTextes;

		void InitCrashMenu(sf::Font& font)
		{
			names = { L"Начать", L"игру", L"Главное", L"меню" };

			for (int i = 0; i < names.size(); i = i + 2)
			{
				sf::Text text;
				text.setFont(font);
				text.setString(names[i]);
				text.setCharacterSize(20);
				text.setFillColor(i == 0 ? sf::Color::Green : sf::Color::Black);
				text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
				text.setPosition(SCREEN_WIDTH / 2, SCREEN_HIGHT / 2 + 84 + i * 25.f);

				menuTextes.push_back(text);

				sf::Text text2;
				text2.setFont(font);
				text2.setString(names[i + 1]);
				text2.setCharacterSize(20);
				text2.setFillColor(i == 0 ? sf::Color::Green : sf::Color::Black);
				text2.setOrigin(text2.getLocalBounds().width / 2, text2.getLocalBounds().height / 2);
				text2.setPosition(SCREEN_WIDTH / 2, SCREEN_HIGHT / 2 + 104 + i * 25.f);

				menuTextes.push_back(text2);
			}
		}
		void MoveIndex(int i)
		{
			int newIndex = selectedIndex + i;
			if (newIndex >= 0 && newIndex <= (names.size() - 1) / 2)
			{
				menuTextes[newIndex * 2].setFillColor(sf::Color::Green);
				menuTextes[newIndex * 2 + 1].setFillColor(sf::Color::Green);
				menuTextes[selectedIndex * 2].setFillColor(sf::Color::Black);
				menuTextes[selectedIndex * 2 + 1].setFillColor(sf::Color::Black);
				selectedIndex = newIndex;
			}
		}

	};

	struct PauseMenu
	{
		std::vector <sf::String> names;
		int selectedIndex = 0;
		std::vector<sf::Text> menuTextes;

		void InitPauseMenu(sf::Font& font)
		{
			names = { L"Продолжить", L"игру", L"Выйти", L"из игры" };

			for (int i = 0; i < names.size(); i = i + 2)
			{
				sf::Text text;
				text.setFont(font);
				text.setString(names[i]);
				text.setCharacterSize(15);
				text.setFillColor(i == 0 ? sf::Color::Green : sf::Color::Black);
				text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
				text.setPosition(SCREEN_WIDTH / 2, SCREEN_HIGHT / 2 - 12 + i * 30.f);

				menuTextes.push_back(text);

				sf::Text text2;
				text2.setFont(font);
				text2.setString(names[i + 1]);
				text2.setCharacterSize(15);
				text2.setFillColor(i == 0 ? sf::Color::Green : sf::Color::Black);
				text2.setOrigin(text2.getLocalBounds().width / 2, text2.getLocalBounds().height / 2);
				text2.setPosition(SCREEN_WIDTH / 2, SCREEN_HIGHT / 2 + 5 + i * 30.f);

				menuTextes.push_back(text2);
			}
		}
		void MoveIndex(int i)
		{
			int newIndex = selectedIndex + i;
			if (newIndex >= 0 && newIndex <= (names.size() - 1) / 2)
			{
				menuTextes[newIndex * 2].setFillColor(sf::Color::Green);
				menuTextes[newIndex * 2 + 1].setFillColor(sf::Color::Green);
				menuTextes[selectedIndex * 2].setFillColor(sf::Color::Black);
				menuTextes[selectedIndex * 2 + 1].setFillColor(sf::Color::Black);
				selectedIndex = newIndex;
			}
		}

	};
}