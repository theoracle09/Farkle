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
	static bool cmd(const Player& p1, const Player& p2);

	// Getters and Setters


private:
	Menu menu_;
	int numPlayers_;
	int diceSides_; // Stores how many sides the dice have. Possible feature in the future.
	std::vector<Player> players_;
	
	void recordPlayerName();
	void findWhoGoesFirst();
	int rollSingleDie();
	void endGame(Player winner);
	void clearScreen() const { std::cout << std::string(100, '\n'); };
	
	// DEV
	int dev_usersNames_ = 0;
};

