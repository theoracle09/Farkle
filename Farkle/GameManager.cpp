#include "stdafx.h"
#include "GameManager.h"
#include <algorithm>  // std::rotate
#include <iostream>
#include <random>
#include <string>

/************************
Constructor
*************************/
GameManager::GameManager()
{
	numPlayers_ = 0;

	// How many sides do the dice have? Possible feature where players can use dice that have
	// more than 6 sides. If it becomes a feature, the user can define this number during set-up.
	diceSides_ = 6;  
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

				// Once the program returns to this line, the game is over
				// TODO delete the cout line at some point.
				std::cout << "If you see this: the program exec is done with the play() method.\n";
				isDone = true;
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
		else if (userInput == 1)
		{
			// TODO This is where we'll handle single player game mode
		}
		else if (userInput > 1)
		{
			setNumPlayers(userInput);
			isDone = true;
		}
	}

	// Create a new Player object for each player playing. Heh.
	for (unsigned int i = 1; i <= numPlayers_; i++)
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
			std::cout << "\nAnd the last player's name is: ";

			recordPlayerName();

			// Subtract 1 from players_.size() because of indexes
			std::cout << "Hello " << players_[(players_.size() - 1)].getPlayerName() << ".\n";
		}
		// This block will exec between the first and last players
		else
		{
			std::cout << "\nNext player's name: ";
			recordPlayerName();
			std::cout << "Hello " << players_[i - 1].getPlayerName() << ".\n";
		}
		
	}

	findWhoGoesFirst();

	

	// TODO Begin the core gameplay

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

void GameManager::findWhoGoesFirst()
{

	std::cout << "\nNow we're going to roll a single die. The first person to roll a 6 goes first.\n" <<
		"Otherwise, whoever has the highest number will go first.\n";

	char input; // Capture input for the single dice roll
	bool rolledHighestNumber = false;  // Flag to store if the highest number has been rolled or not

	for (unsigned int i = 0; i < players_.size(); i++)
	{
		std::cout << players_[i].getPlayerName() << " press R to roll your die.\n";
		bool isDone = false;

		while (!isDone)
		{
			std::cin >> input;

			switch (input)
			{
			case 'r':
			case 'R':
				// TODO Use an exception here. There's 100% no reason why the RNG would give us a value
				// that's not between 1 and 6. Use out of range error.

				int roll;
				roll = rollSingleDie();

				// Check if a player rolls the highest number
				if (roll == diceSides_)
				{
					std::cout << "\nYou rolled a " << roll << ".\n\n";
					std::cout << players_[i].getPlayerName() << ", nice one! You're first.\n";
					players_[i].setIsFirstPlayer();  // Makes this player the first player
					i = players_.size();  // set the loop variable to something which breaks the loop
					rolledHighestNumber = true;
					isDone = true;
					break;
				}
				else  // Player didn't roll the highest number.
				{
					std::cout << "\nYou rolled a " << roll << ".\n\n";
					players_[i].setSingleDieRoll(roll);
					isDone = true;
					break;
				}

			default:
				std::cout << "Input not recognized, please try again.\n";
			}
		}
	}

	if (rolledHighestNumber)
	{
		// Loop through and check who rolled the highest possible number
		for (unsigned int i = 0; i < players_.size(); i++)
		{
			if (players_[i].getIsFirstPlayer())
			{
				// Re-arrange the vector so the person who rolled the highest number is @ index 0
				std::rotate(players_.begin(), players_.begin() + i, players_.end());
			}
		}
	}
	else
	{
		std::cout << "\nIt looks like no one rolled the highest possible number.\n" <<
			"I'll choose who goes first based on who rolled the highest number.\n" <<
			"If multiple people rolled the same, high number, I'll randomly pick one.\n";

		// Sort the players_ vector based on their singleDieRoll
		std::sort(players_.begin(), players_.end(), cmd);

		// With the vector sorted, the game is ready to be started
		std::cout << players_[0].getPlayerName() << " it looks like you're first player!\n";
	}
}

int GameManager::rollSingleDie()
{
	std::random_device rd; // Obtain random number from hardware
	std::mt19937 eng(rd()); // Seed the generator
	std::uniform_int_distribution<> distr(1, diceSides_); // Define the range

	int roll = distr(eng);

	return roll;
}

bool GameManager::cmd(const Player& p1, const Player& p2)
{
	return p1.getSingleDieRoll() > p2.getSingleDieRoll();
}
