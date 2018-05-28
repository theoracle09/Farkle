#pragma once
#include "ScoreRules.h"
#include <iostream>
#include <string>
#include <vector>
#include <list>

class Player
{
public:
	Player();
	Player(std::string name, int diceSides);
	void turn();
	void removeDice(int die, int count);

	//Getters and Setters
	std::string getPlayerName() const { return name_; };
	int getSingleDieRoll() const { return singleDieRoll_; };
	void setSingleDieRoll(int singleDieRoll) { singleDieRoll_ = singleDieRoll; };
	void setIsFirstPlayer() { isFirstPlayer_ = true; };
	bool getIsFirstPlayer() const { return isFirstPlayer_; };
	int getTotalScore() const { return totalScore_; };
	void addToScore(int amount) { turnScore_ += amount; };
	bool getIsWinner();

private:
	ScoreRules scoreRules_;
	int turnScore_;
	int totalScore_;
	int singleDieRoll_;
	int diceSides_;
	bool isFirstPlayer_;
	bool hasEnteredGame_;
	bool isFarkled_;
	bool canRollDice_;
	bool canStoreDice_;
	std::string name_;
	std::vector<int> dice_;
	std::vector<int> storedDice_;
	std::list<std::string> gameOutput_;
	
	void clearScreen() const { std::cout << std::string(100, '\n'); };
	void rollDice(int numDice);
	void logEntry(std::string message);
	void storeDice();
};

