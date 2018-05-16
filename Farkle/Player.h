#pragma once
#include "ScoreRules.h"
#include <iostream>
#include <string>
#include <vector>

class Player
{
public:
	Player(std::string name, int diceSides);
	void turn();
	void removeDice(int diceToRemove);

	//Getters and Setters
	std::string getPlayerName() const { return name_; };
	int getSingleDieRoll() const { return singleDieRoll_; };
	void setSingleDieRoll(int singleDieRoll) { singleDieRoll_ = singleDieRoll; };
	void setIsFirstPlayer() { isFirstPlayer_ = true; };
	bool getIsFirstPlayer() const { return isFirstPlayer_; };

private:
	ScoreRules scoreRules_;
	int score_;
	int singleDieRoll_;
	int diceSides_;
	bool isFirstPlayer_;
	bool hasEnteredGame_;
	bool isFarkled_;
	std::string name_;
	std::vector<int> dice_;
	std::vector<int> storedDice_;
	
	void rollDice(int numDice);
	void clearScreen() const { std::cout << std::string(100, '\n'); };
};

