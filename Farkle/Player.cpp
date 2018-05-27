#include "stdafx.h"
#include "Player.h"
#include <chrono>
#include <iomanip> // std::put_time
#include <random>
#include <sstream>


Player::Player(std::string name, int diceSides)
{
	name_ = name;
	turnScore_ = 0;
	totalScore_ = 0;
	diceSides_ = diceSides;
	singleDieRoll_ = 0;
	isFirstPlayer_ = false;
	isFarkled_ = false;
	canRollDice_ = true;
	hasEnteredGame_ = true;
	canStoreDice_ = false;
}

void Player::turn()
{
	// Reset some flags
	bool isPlayersTurn = true;
	bool isFarkled_ = false;
	canRollDice_ = true;


	turnScore_ = 0; // Tracks the player's score throughout the turn

	dice_.clear(); // On subsequent turns, this needs to be cleared for the player to roll again
	storedDice_.clear();

	while (isPlayersTurn)
	{

		clearScreen();

		std::cout << "####### " << name_ << "'s turn! #######\n\n\n";

		// Displays the first 3 lines of our 'fake console' log
		int count = 0;

		for (std::list<std::string>::const_iterator i = gameOutput_.begin(); i != gameOutput_.end(); ++i)
		{
			if (count < 3)
			{
				std::cout << *i << std::endl;
				count++;
			}
			else
			{
				break;
			}
		}

		std::cout << "\n\n\nTotal Score: " << totalScore_;

		std::cout << "\n\n\nRoll: ";

		if (dice_.size() > 0) // Display dice vector, if there's anything in there
		{
			for (unsigned int i = 0; i < dice_.size(); i++)
			{
				std::cout << dice_[i] << " ";
			}
		}

		std::cout << "\n\nStored Dice Total: " << turnScore_;

		std::cout << "\n\nStored Dice: ";

		if (storedDice_.size() > 0)
		{
			for (unsigned int i = 0; i < storedDice_.size(); i++)
			{
				std::cout << storedDice_[i] << " ";
			}
		}
		else
		{
			std::cout << "- - - - - -";
		}

		// Bool to make sure user presses only R, P, S, and Q.
		// Main input bool.
		bool isDone = false;  
		
		// Check if the player has farkled
		if (isFarkled_)
		{
			bool hasTypedP = false;

			std::cout << "\n\n\nPress \'P\' to move to the next player.\n";
			
			char userChar;

			while (!hasTypedP)
			{
				std::cin >> userChar;
				userChar = toupper(userChar);
				
				if (userChar == 'P')
				{
					hasTypedP = true;
					isDone = true;
					isPlayersTurn = false;
					isFarkled_ = false;
					dice_.clear();
				}
				else
				{
					std::cout << "That's not a \'P\'! Try it again please.\n";
				}

			}

		}
		else
		{
			std::cout << "\n\n\nWhat would you like to do?\n";

			if (canRollDice_)
			{
				std::cout << "(R)oll  --  ";
			}

			if (canStoreDice_)
			{
				std::cout << "(S)core  --  ";
			}

			std::cout << "(P)ass  -- (Q)uit\n";

		}


		while (!isDone)
		{
			char userInput;

			std::cin >> userInput;

			switch (userInput)
			{
			case 'r':
			case 'R':
				// Check if the player has already rolled
				if (canRollDice_)
				{
					// Are any dice stored yet?
					if (storedDice_.size() == 0)
					{
						// Roll all 6 dice
						rollDice(6);
					}
					else
					{
						// Subtract the amount of stored dice, and roll the remainder
						rollDice(6 - storedDice_.size());
					}

					int triples = scoreRules_.scoreDice(dice_);

					// Check the new dice to see if the player has farkled
					for (unsigned int i = 0; i < dice_.size(); i++)
					{
						if (dice_[i] == 1 || dice_[i] == 5 || triples != -5)
						{
							// Found a 1 or a 5 or triples, so break out of for loop
							isFarkled_ = false;
							break;
						}
						else
						{
							isFarkled_ = true;
						}
					}

					if (isFarkled_)
					{
						logEntry("Dang, you Farkled! You've lost all of your stored points.  :-(");
						storedDice_.clear();
					}

					canRollDice_ = false; // Flag stops the player from continuously rolling the dice
				}
				else
				{
					logEntry("You've already rolled!");
				}

				canStoreDice_ = true;
				isDone = true;  // Get out of input loop
				break;

			case 'P':
			case 'p':

				// Store the turnScore into the totalScore
				totalScore_ += turnScore_;

				// Move on to the next player's turn
				isPlayersTurn = false;
				isDone = true;
				
				break;

			case 's':
			case 'S':
				storeDice();
				isDone = true;
				break;

			case 'q':
			case 'Q':
				// TODO handle what happens when the player wants to quit to main menu
				break;

			default:
				std::cout << "Invalid input. Please try again.\n";
			}
		}
	}

}

void Player::removeDice(int die, int numTimes)
{
	int count = 0;

	for (unsigned int i = 0; i < dice_.size(); i++)
	{
		if (dice_[i] == die && count < numTimes)
		{
			dice_.erase(dice_.begin() + i);
			count++;
			
			// Subtract 1 from i, so the loop can check the same index again.
			--i;
		}
	}
}

bool Player::getIsWinner()
{
	if (totalScore_ >= 10000)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Player::rollDice(int numDice)
{
	dice_.clear();  // Clear the dice vector

	std::random_device rd; // Obtain random number from hardware
	std::mt19937 eng(rd()); // Seed the generator
	std::uniform_int_distribution<> distr(1, diceSides_); // Define the range

	for (int i = 0; i < numDice; i++)
	{
		dice_.push_back(distr(eng));
	}

	std::stringstream ss;
	std::string output;
	ss << "You rolled: ";

	for (unsigned int i = 0; i < dice_.size(); i++)
	{
		ss << dice_[i] << " ";
	}

	logEntry(ss.str());
}

/************************
Affixes the time to the front of a custom message
*************************/
void Player::logEntry(std::string message)
{
	auto now = std::chrono::system_clock::now();
	auto now_c = std::chrono::system_clock::to_time_t(now);

	std::stringstream ss;
	// std::localtime throws a thread safe warning. I turned the warning off in Visual Studio.
	ss << std::put_time(std::localtime(&now_c), "%T") << ": " << message;

	// Add string to consoleLog
	gameOutput_.push_front(ss.str());
}

void Player::storeDice()
{
	if (!canStoreDice_)
	{
		logEntry("You must roll your dice again, before you can store anything new!");
		return;
	}

	// Make sure the player has dice to score, first
	if (dice_.size() == 0)
	{
		logEntry("Press \'R\' to roll your dice first!");
	}
	else
	{
		std::vector<int> userStoringInput;
		std::vector<int> userInputCopy;
		std::vector<int> diceCopy;
		std::vector<int> storedCurrentTurn; // Numbers player wants to store during current turn
		std::string inputLine;
		int number, amountOfNumbersToStore;

		std::cout << "\nWhich dice would you like to set aside for scoring?\n";
		std::cout << "Ex. input: 1 1 1 5. Separate your numbers with a space.\n";

		std::cin.ignore(); // Ignore the newline char leftover from last cin operation
		std::getline(std::cin, inputLine);  // Read the entire line of input from user
		std::istringstream stream(inputLine);  // Create our own stream
		while (stream >> number)
		{
			userStoringInput.push_back(number);
		}

		// How many numbers is the player trying to store?
		amountOfNumbersToStore = userStoringInput.size();

		// Copy user input into a temp vector
		for (unsigned int i = 0; i < userStoringInput.size(); i++)
		{
			userInputCopy.push_back(userStoringInput[i]);
		}

		// Copy dice into temp vector
		for (unsigned int i = 0; i < dice_.size(); i++)
		{
			diceCopy.push_back(dice_[i]);
		}

		// Check both temp vectors against eachother for matching numbers
		while (amountOfNumbersToStore > 0)
		{
			for (unsigned int j = 0; j < diceCopy.size(); j++)
			{
				for (unsigned int i = 0; i < userInputCopy.size(); i++)
				{
					if (userInputCopy[i] == diceCopy[j])
					{
						// Only delete the amount of numbers the user specified. If the user only entered 
						// 2 numbers to store, only delete those 2 numbers and not others as well.
						if (amountOfNumbersToStore > 0)
						{
							// Delete the number from both temp vectors
							userInputCopy.erase(userInputCopy.begin() + i);
							diceCopy.erase(diceCopy.begin() + j);
							--amountOfNumbersToStore;
						}
					}
				}
			}
		}


		// Check if the user input temp vector is empty
		if (userInputCopy.size() == 0)
		{
			// User typed the correct numbers
			// Check to see if there are any triples in the dice to be stored
			// Function returns -5 if it doesn't find a triple. Returns 1-6 otherwise
			// if it does find a triple. 
			int triples = scoreRules_.scoreDice(userStoringInput);

			switch (triples)
			{
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
				// We have a triple, which number do we need to delete from the rolled dice?
				removeDice(triples, 3);

				// Now add the triple score to the user's score
				if (triples == 1)
				{
					turnScore_ += 1000;
				}
				else
				{
					turnScore_ += (triples * 100);
				}

				for (int i = 0; i < 3; i++)
				{
					storedDice_.push_back(triples);
					storedCurrentTurn.push_back(triples);
				}

				break;
			case -5:  // Found no triples

					  // Loop through storedInput and add the 1 or 5 to the user's score
				for (unsigned int i = 0; i < userStoringInput.size(); i++)
				{
					if (userStoringInput[i] == 1)
					{
						turnScore_ += 100;
						removeDice(1, 1);
						storedDice_.push_back(1);
						storedCurrentTurn.push_back(1);
					}
					else if (userStoringInput[i] == 5)
					{
						turnScore_ += 50;
						removeDice(5, 1);
						storedDice_.push_back(5);
						storedCurrentTurn.push_back(5);
					}
				}
			}

			std::stringstream ss;
			std::string output;
			ss << "You stored: ";

			for (unsigned int i = 0; i < storedCurrentTurn.size(); i++)
			{
				ss << storedCurrentTurn[i] << " ";
			}

			logEntry(ss.str());
			
			// Already stored the dice, so set flag to false...however...
			// still have to run a check to see if any dice remain that can be stored.
			canStoreDice_ = false; 

			// Are any numbers left in the dice_ vector which can be stored?
			for (unsigned int i = 0; i < dice_.size(); i++)
			{
				if (dice_[i] == 1 || dice_[i] == 5)
				{
					canStoreDice_ = true;
				}
			}

			canRollDice_ = true; // Resets flag to true, so player can roll again

		}
		else
		{
			// User has incorrect input
			logEntry("Sorry, I don't recognize some of your numbers. Please try again.");
		}	
	}
}

