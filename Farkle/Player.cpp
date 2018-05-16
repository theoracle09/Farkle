#include "stdafx.h"
#include "Player.h"
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

void Player::turn()
{
	bool isPlayersTurn = true;

	while (isPlayersTurn)
	{

		clearScreen();

		std::cout << "####### " << name_ << "'s turn! #######\n\n\n";

		std::cout << "Roll: ";

		if (dice_.size() > 0)
		{
			for (int i : dice_)
			{
				std::cout << dice_[i] << " ";
			}
		}

		std::cout << "\n\nStored Dice: ";

		if (storedDice_.size() > 0)
		{
			for (int i : storedDice_)
			{
				std::cout << storedDice_[i] << " ";
			}
		}

		std::cout << "\n\n\nWhat would you like to do?\n";
		std::cout << "(R)oll  --  (P)ass  --  (S)core  --  (Q)uit\n";

		bool isDone = false;  // Bool to make sure user presses only R, P, S, and Q

		while (!isDone)
		{
			char userInput;

			std::cin >> userInput;

			switch (userInput)
			{
			case 'r':
			case 'R':
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
				isDone = true;  // Get out of input loop
				break;
			case 'P':
			case 'p':
				// Move on to the next player's turn
				isPlayersTurn = false;
				isDone = true;
				break;
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
				scoreRules_.check(storedDice_);

				// See what else the player wants to do:
				// Roll remaining dice, or stop and keep points acquired.

				break;
			}
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

void Player::removeDice(int diceToRemove)
{
	for (const int i : dice_)
	{
		if (dice_[i] == diceToRemove)
		{
			dice_.erase(dice_.begin() + i);
		}
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

