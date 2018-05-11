#include "stdafx.h"
#include "Player.h"
#include <iostream>
#include <random>


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
		std::cout << "Okay " << name_ << ", press \'r\' to roll your dice.\n";
		
		char userInput;

		std::cin >> userInput;

		rollDice(6);

		// Print the dice to the screen
		for (int i = 0; i < dice_.size(); i++)
		{
			std::cout << dice_[i] << " ";
		}

		

		std::cout << "What would you like to do?\n";
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

