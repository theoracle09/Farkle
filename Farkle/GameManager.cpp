#include "stdafx.h"
#include "GameManager.h"
#include <iostream>
#include <string>

/************************
Constructor
*************************/
GameManager::GameManager()
{
	numPlayers_ = 0;
}

/************************
Sends 100 newline characters to the output
stream, to 'fake' clearing the screen. This
just makes the text scroll up a ways in the console.
*************************/
void GameManager::clearScreen()
{
	std::cout << std::string(100, '\n');
}

/************************
Prints from the Menu class, and sanitizes
the input for the options listed.
*************************/
void GameManager::displayMenu()
{
	bool isDone = false;
	char userInput;

	clearScreen();
	menu_.printMainMenu();
	std::cout << "\nPlease type the first letter of the option you'd like above\n";
	
	while (!isDone)
	{

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

/************************
Prints the rules from the Menu class.
*************************/
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

/************************
Main game loop. Handles the playing of the game.
*************************/
void GameManager::play()
{
	int userInput;

	clearScreen();
	std::cout << "How many players will be playing today?\n";

	bool isDone = false;

	// Sanitize the user's input. Makes sure they can only enter a number.
	while (!isDone)
	{
		std::cin >> userInput;
		
		if (std::cin.fail())
		{
			std::cin.clear();  // Clear the error flag within std::cin
			std::cin.ignore(10000, '\n');  // Ignores 10k chars up to a newline
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

	// Create a new Player object for each player playing. Heh.
	for (int i = 1; i <= numPlayers_; i++)
	{
		// First player to tell us their name
		if (i == 1)
		{
			std::cout << "So, we have " << numPlayers_ << " players playing today.\n"
				<< "What are your names? Starting with Player 1, and going clockwise.\n"
				<< "Player 1's name: ";

			recordPlayerName();

			std::cout << "Hello " << players_[0].getPlayerName() << ".\n";

		}
		// This will be the LAST player to tell us their name
		else if (i == numPlayers_)
		{
			std::cout << "And the last player's name is: ";

			recordPlayerName();

			// Subtract the total size of players
			std::cout << "Hello " << players_[(players_.size() - 1)].getPlayerName() << ".\n";
			pause(); // TODO Delete
		}
		// This block will exec between the first and last players
		else
		{
			std::cout << "Next player's name: ";
			recordPlayerName();
			std::cout << "Hello " << players_[i - 1].getPlayerName() << ".\n";
		}
		
	}


}

void GameManager::pause()
{
	system("PAUSE");
}

void GameManager::setNumPlayers(int numPlayers)
{
	numPlayers_ = numPlayers;
}

void GameManager::recordPlayerName()
{
	std::string playerName;

	std::cin >> playerName;
	Player player(playerName);
	players_.push_back(player);
}
