#pragma once
#include "ScoreRules.h"
#include <string>
#include <vector>

class Player
{
public:
	Player(std::string name, int diceSides);
	void Turn();

	//Getters and Setters
	std::string getPlayerName() const { return name_; };
	int getSingleDieRoll() const { return singleDieRoll_; };
	void setSingleDieRoll(int singleDieRoll) { singleDieRoll_ = singleDieRoll; };
	void setIsFirstPlayer() { isFirstPlayer_ = true; };
	bool getIsFirstPlayer() const { return isFirstPlayer_; };

private:
	int score_;
	int singleDieRoll_;
	int diceSides_;
	bool isFirstPlayer_;
	bool hasEnteredGame_;
	std::string name_;
	std::vector<int> dice_;
	std::vector<int> storedDice_;
	
	void rollDice(int numDice);
};

