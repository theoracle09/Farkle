#include "stdafx.h"
#include "GameManager.h"
#include <algorithm>  // std::rotate, std::sort
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
Prints from the Menu class, and sanitizes
the input for the options listed.
*************************/
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
		// DEV 
		userInput = 4;
		//std::cin >> userInput;
		

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
			numPlayers_ = userInput;
			isDone = true;
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

	// DEV
	std::cout << "\n\n######### DEV -- Josh is going first\n";
	//findWhoGoesFirst();

	// Have the user press any key to continue to the first play
	std::cout << "\nPress any key to begin.\n";

	std::string s;  // Temp string to pause for user input
	std::cin.ignore();
	std::getline(std::cin, s); 

	isDone = false;  // Reset bool flag

	// Begin the core gameplay
	do
	{
		// Loop through each player and have them play their turn
		for (unsigned int i = 0; i < players_.size(); i++)
		{
			players_[i].turn();

			if (players_[i].getIsWinner())
			{
				winner_ = players_[i];
				lastRound();
				isDone = true;
				break;
			}
			
		}

	} while (!isDone);

}

void GameManager::recordPlayerName()
{
	std::string playerName;

	// DEV
	switch (dev_usersNames_)
	{
	case 0:
		playerName = "Josh";
		dev_usersNames_++;
		break;

	case 1:
		playerName = "Jaci";
		dev_usersNames_++;
		break;

	case 2:
		playerName = "Bill";
		dev_usersNames_++;
		break;

	case 3:
		playerName = "Bob";
		break;
	}
	//std::cin >> playerName;
	
	Player player(playerName, diceSides_);
	players_.push_back(player);
}

void GameManager::findWhoGoesFirst()
{

	std::cout << "\nNow we're going to roll a single die. The first person to roll a 6 goes first.\n" <<
		"Otherwise, whoever has the highest number will go first.\n\n";

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
		std::cout << "\nIt looks like no one rolled a 6.\n" <<
			"I'll choose who goes first based on who rolled the highest number.\n";

		// Sort the players_ vector based on their singleDieRoll
		std::sort(players_.begin(), players_.end(), cmd);

		//Check if there are multiple high rolls
		if (players_[0].getSingleDieRoll() == players_[1].getSingleDieRoll())
		{
			std::cout << "Since more than one person rolled the highest number, I'll randomly pick who goes first.\n";

		}

		// With the vector sorted, the game is ready to be started
		std::cout << std::endl;
		std::cout << players_[0].getPlayerName() << ", you're first player with a roll of " << 
			players_[0].getSingleDieRoll() << std::endl;
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

void GameManager::endGame(Player winner)
{
	clearScreen();

	std::cout << "\nCongratulations " << winner.getPlayerName() << "!\n\n";

	std::cout << "\nPress any key to return to main menu.\n";

	std::string s;  // Temp string to pause for user input
	std::cin.ignore();
	std::getline(std::cin, s);
}

void GameManager::lastRound()
{
	// Someone has gotten over 10,000
	std::cout << "Congrats " << winner_.getPlayerName() << ", you scored over 10,000!\n" << 
		"Each player will get one more turn to try and beat your score.\n" <<
		"Good luck everyone!\n";

	// Loop through the player's vector one more time
	for (unsigned int i = 0; i < players_.size(); i++)
	{
		players_[i].turn();

		// Check to see if there's a new winner
		if (players_[i].getTotalScore() > winner_.getTotalScore())
		{
			// We have a new winner
			std::cout << "Nice one " << players_[i].getPlayerName() << ". You beat " << winner_.getPlayerName() << "\n" <<
				"Let's keep going.\n";

			std::cout << "\nPress any key to go to the next player's turn.\n";
			std::string s;
			std::cin.ignore();
			std::getline(std::cin, s);

			winner_ = players_[i];
		}
	}

	// Last round is over, declare the winner
	endGame(winner_);
}

