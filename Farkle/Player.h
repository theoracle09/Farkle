#pragma once
#include <string>
#include <vector>

class Player
{
public:
	Player(std::string name);

	//Getters and Setters
	std::string getPlayerName() const { return name_; };

private:
	int score_;
	std::string name_;
	std::vector<int> dice_;
};
