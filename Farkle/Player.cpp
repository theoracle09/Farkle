#include "stdafx.h"
#include "Player.h"
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
	hasEnteredGame_ = true;
}

void Player::turn()
{
	std::string alertMessage = "null";
	bool isPlayersTurn = true;

	while (isPlayersTurn)
	{

		clearScreen();

		std::cout << "####### " << name_ << "'s turn! #######\n\n\n";

		if (alertMessage == "null")
		{
			std::cout << "Roll some dice!";
		}
		else
		{
			std::cout << alertMessage;
		}

		std::cout << "\n\n\nScore: " << turnScore_;

		std::cout << "\n\n\nRoll: ";

		if (dice_.size() > 0)
		{
			for (unsigned int i = 0; i < dice_.size(); i++)
			{
				std::cout << dice_[i] << " ";
			}
		}

		std::cout << "\n\nStored Dice: ";

		if (storedDice_.size() > 0)
		{
			for (unsigned int i = 0; i < storedDice_.size(); i++)
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
				alertMessage = "----You throw your dice against the table...";

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

				for (unsigned int i = 0; i < dice_.size(); i++)
				{
					if (dice_[i] == 1 || dice_[i] == 5)
					{
						// Found a 1 or a 5, so break out of for loop
						isFarkled_ = false;
						continue;
					}
					else
					{
						isFarkled_ = true;
					}
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
				// Make sure the player has dice to score, first
				if (dice_.size() == 0)  
				{
					alertMessage = "Press \'R\' to roll your dice first!";
				}
				else
				{
					std::string line;
					int number;

					std::cout << "\nWhich dice would you like to set aside for scoring?\n";
					std::cout << "Ex. input: 1 1 1 5. Separate your numbers with a space.\n";

					std::cin.ignore(); // Ignore the newline char leftover from last cin operation
					std::getline(std::cin, line);  // Read the entire line of input from user
					std::istringstream stream(line);  // Create our own stream
					while (stream >> number)
					{
						storedDice_.push_back(number);
					}

					// TODO Sanitize user's input on what dice they're trying to store
					// Have a third vector, so we can separate the stored values
					// and the values we want to check against the scoring rules.
					// As it is right now, when the user re-rolls with a triple in the storedDice_,
					// it's being counted in the score as a triple. Not cool.

					// Check to see if there are any triples in the dice to be stored
					int triples = scoreRules_.scoreDice(storedDice_);

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

						break;
					case -5:  // Found no triples
						for (unsigned int i = 0; i < storedDice_.size(); i++)
						{
							if (storedDice_[i] == 1)
							{
								turnScore_ += 100;
								removeDice(1, 1);
							}
							else if (storedDice_[i] == 5)
							{
								turnScore_ += 50;
								removeDice(5, 1);
							}
						}
						break;
					}
				}

				// See what else the player wants to do:
				// Roll remaining dice, or stop and keep points acquired.
				isDone = true;
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

void Player::removeDice(int die, int numTimes)
{
	int count = 0;

	for (unsigned int i = 0; i < dice_.size(); i++)
	{
		if (dice_[i] == die && count < numTimes)
		{
			dice_.erase(dice_.begin() + i);
			count++;
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

