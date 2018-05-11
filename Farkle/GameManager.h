#pragma once
#include "Menu.h"
#include "Player.h"
#include <vector>

class GameManager
{
public:
	GameManager();
	void clearScreen();
	void displayMenu();
	void displayRules();
	void play();
	void pause(); // TODO Delete. OS specific function/code for testing
	static bool cmd(const Player& p1, const Player& p2);

	// Getters and Setters
	void setNumPlayers(int numPlayers);


private:
	Menu menu_;
	int numPlayers_;
	int diceSides_; // Stores how many sides the dice have. Possible feature in the future.
	std::vector<Player> players_;

	void recordPlayerName();
	void findWhoGoesFirst();
	int rollSingleDie();
};

