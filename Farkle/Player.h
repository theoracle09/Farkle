#pragma once
#include <string>
#include <vector>

class Player
{
public:
	Player(std::string name);

	//Getters and Setters
	std::string getPlayerName() const { return name_; };
	int getSingleDieRoll() const { return singleDieRoll_; };
	void setSingleDieRoll(int singleDieRoll) { singleDieRoll_ = singleDieRoll; };
	void setIsFirstPlayer() { isFirstPlayer_ = true; };
	bool getIsFirstPlayer() { return isFirstPlayer_; };

private:
	int score_;
	int singleDieRoll_;
	bool isFirstPlayer_;
	std::string name_;
	std::vector<int> dice_;
};

