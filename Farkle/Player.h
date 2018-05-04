#pragma once
#include <string>
#include <vector>

class Player
{
public:
	Player();
	~Player();

	//Getters and Setters
	void setPlayerName(std::string name);
	std::string getPlayerName() const { return name_; };

private:
	std::string name_;
	std::vector<int> dice_;
};

