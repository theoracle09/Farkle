#include "stdafx.h"
#include "Player.h"
#include <iostream>
#include <random>
#include <sstream>


Player::Player(std::string name, int diceSides)
{
	name_ = name;
	score_ = 0;
	diceSides_ = diceSides;
	singleDieRoll_ = 0;
	isFirstPlayer_ = false;
	hasEnteredGame_ = true;
}

void Player::Turn()
{
	if (hasEnteredGame_)
	{
		std::cout << "\nOkay " << name_ << ", press \'r\' to roll your dice.\n";
		
		char userInput;

		std::cin >> userInput;

		rollDice(6);

		std::cout << "\nYou rolled: ";

		// Print the dice to the screen
		for (unsigned int i = 0; i < dice_.size(); i++)
		{
			std::cout << dice_[i] << "  ";
		}

		std::cout << std::endl;
		std::cout << "\nPress one of the following keys..\n";
		std::cout << "(P)ass  --  (S)core  --  (Q)uit\n";

		bool isDone = false;

		while (!isDone)
		{
			std::cin >> userInput;

			switch (userInput)
			{
			case 's':
			case 'S':  
			{  // Curly braces needed to declare variables inside SWITCH (local scope)
				std::string line;
				int number;
				std::vector<int> triples;

				std::cout << "\nWhich dice would you like to set aside for scoring?\n";
				std::cout << "Ex. input: 1 1 1 5. Separate your numbers with a space.\n";

				std::cin.ignore(); // Ignore the newline char leftover from last cin operation
				std::getline(std::cin, line);  // Read the entire line of input from user
				std::istringstream stream(line);  // Create our own stream
				while (stream >> number)
				{
					storedDice_.push_back(number);
				}

				// Check the storedDice vector against the scoring rules
				//scoreRules_.check(storedDice_);

				// See what else the player wants to do:
				// Roll remaining dice, or stop and keep points acquired.

				break;
			}
			case 'P':
			case 'p':

				isDone = true;
				break;
			default:
				std::cout << "Invalid input. Please try again.\n";
			}
		}
	}
	else
	{
		
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
}

