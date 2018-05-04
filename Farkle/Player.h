#pragma once
#include <string>
#include <vector>

class Player
{
public:
	Player(std::string name);

	//Getters and Setters
	std::string getPlayerName() const { return name_; };
	void setSingleDieRoll(int singleDieRoll) { singleDieRoll_ = singleDieRoll; };

private:
	int score_;
	int singleDieRoll_;
	std::string name_;
	std::vector<int> dice_;
};

