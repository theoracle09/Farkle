#pragma once
#include "Menu.h"
#include "Player.h"
#include <vector>
#include <iostream>

class GameManager
{
public:
	GameManager();
	void displayMenu();
	void displayRules();
	void play();
	void pause(); // TODO Delete. OS specific function/code for testing
	static bool cmd(const Player& p1, const Player& p2);

	// Getters and Setters


private:
	Menu menu_;
	int numPlayers_;
	int diceSides_; // Stores how many sides the dice have. Possible feature in the future.
	std::vector<Player> players_;
	
	void clearScreen() const { std::cout << std::string(100, '\n'); };
	void recordPlayerName();
	void findWhoGoesFirst();
	int rollSingleDie();
	
	// DEV
	int dev_usersNames_ = 0;
};

