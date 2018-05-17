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
	isFarkled_ = false;
	hasRolledDice_ = false;
	hasEnteredGame_ = true;
	canStoreDice_ = true;
}

void Player::turn()
{
	bool isPlayersTurn = true;

	turnScore_ = 0; // Tracks the player's score throughout the turn

	while (isPlayersTurn)
	{

		clearScreen();

		std::cout << "####### " << name_ << "'s turn! #######\n\n\n";

		// Displays the first 3 lines of our 'fake console' log
		int count = 0;

		for (std::list<std::string>::const_iterator i = consoleLog_.begin(); i != consoleLog_.end(); ++i)
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

		if (dice_.size() > 0)
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
			std::cout << "(R)oll  --  (P)ass  --  (S)core  --  (Q)uit\n";
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
				// TODO this is messed up. Fix it.
				if (!hasRolledDice_)
				{
					consoleLog_.push_front("----You throw your dice against the table...");

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
						consoleLog_.push_front("Dang, you Farkled! You've lost all of your stored points.  :-(");
						storedDice_.clear(); 
					}
					
					hasRolledDice_ = true; // Flag stops the player from continuously rolling the dice
				}
				else
				{
					consoleLog_.push_front("----You've already rolled!");
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
			{   // Curly braces needed to declare variables inside SWITCH (local scope)
				
				if (!canStoreDice_)
				{
					consoleLog_.push_front("----You must roll your dice again, before you can store anything new!");
					break;
				}

				// Make sure the player has dice to score, first
				if (dice_.size() == 0)  
				{
					consoleLog_.push_front("Press \'R\' to roll your dice first!");
				}
				else
				{
					std::vector<int> userStoringInput;
					std::string inputLine;
					int number;

					std::cout << "\nWhich dice would you like to set aside for scoring?\n";
					std::cout << "Ex. input: 1 1 1 5. Separate your numbers with a space.\n";

					std::cin.ignore(); // Ignore the newline char leftover from last cin operation
					std::getline(std::cin, inputLine);  // Read the entire line of input from user
					std::istringstream stream(inputLine);  // Create our own stream
					while (stream >> number)
					{
						userStoringInput.push_back(number);
					}

					// TODO Sanitize user's input on what dice they're trying to store


					// Check to see if there are any triples in the dice to be stored
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

						break;
					case -5:  // Found no triples
						for (unsigned int i = 0; i < userStoringInput.size(); i++)
						{
							if (userStoringInput[i] == 1)
							{
								turnScore_ += 100;
								removeDice(1, 1);
							}
							else if (userStoringInput[i] == 5)
							{
								turnScore_ += 50;
								removeDice(5, 1);
							}
						}
					}

					// Add values to the storedDice vector
					for (unsigned int i = 0; i < userStoringInput.size(); i++)
					{
						storedDice_.push_back(userStoringInput[i]);
					}

					consoleLog_.push_front("----You stored some dice.");

					hasRolledDice_ = false; // Resets flag to false, so player can roll again
					canStoreDice_ = false;
					isDone = true;
					break;
				}
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

void Player::pass()
{
	
}

