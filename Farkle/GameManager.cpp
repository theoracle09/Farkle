#include "stdafx.h"
#include "GameManager.h"
#include <iostream>
#include <string>


GameManager::GameManager()
{
	numPlayers_ = 0;
}

void GameManager::clearScreen()
{
	std::cout << std::string(100, '\n');
}

void GameManager::displayMenu()
{
	bool isDone = false;
	char userInput;
	
	while (!isDone)
	{
		clearScreen();
		menu_.printMainMenu();

		std::cout << "\nPlease type the first letter of the option you'd like above\n";
		std::cin >> userInput;

		switch (userInput)
		{
			case 'p':
			case 'P':
				play();
				break;

			case 'r':
			case 'R':
				displayRules();
				break;

			case 'e':
			case 'E':
				std::cout << "Thanks for playing!\n";
				isDone = true;
				break;

			default:
				std::cout << "Input not recognized, please try again.\n";
		}
	}
}

void GameManager::displayRules()
{
	bool isDone = false;
	char userInput;

	clearScreen();
	menu_.printRules();

	std::cout << "\nPress 'e' to return to main menu\n";

	while (!isDone)
	{
		std::cin >> userInput;

		switch (userInput)
		{
			case 'e':
			case 'E':
				isDone = true;
				break;

			default:
				std::cout << "Input not recognized, please try again.\n";

		}
	}
}

void GameManager::play()
{
	int userInput;

	clearScreen();
	std::cout << "How many players will be playing today?\n";

	bool isDone = false;

	while (!isDone)
	{
		std::cin >> userInput;
		
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore();
			std::cout << "That's not a number. Try again: ";
		}
		else if (userInput <= 0)
		{
			std::cout << "Well, you can't have zero or negative players, right? Try again: ";
		}
		else
		{
			isDone = true;
			setNumPlayers(userInput);
		}
	}
	
}

void GameManager::setNumPlayers(int numPlayers)
{
	numPlayers_ = numPlayers;
}
